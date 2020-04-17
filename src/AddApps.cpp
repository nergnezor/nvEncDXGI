
#pragma region Move window
#include "AddApps.h"
#include <oleacc.h>
#include <stdio.h>
#include <vector>
// Global variable.
HWINEVENTHOOK g_hook;
int counter;
// Callback function that handles events.
//
void CALLBACK HandleWinEvent(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
                             LONG idObject, LONG idChild, DWORD dwEventThread,
                             DWORD dwmsEventTime)
{
    IAccessible *pAcc = NULL;
    VARIANT varChild;
    HRESULT hr =
        AccessibleObjectFromEvent(hwnd, idObject, idChild, &pAcc, &varChild);
    if ((hr == S_OK) && (pAcc != NULL))
    {
        BSTR bstrName;
        pAcc->get_accName(varChild, &bstrName);
        if (event == EVENT_SYSTEM_MENUSTART)
        {
            printf("Begin: ");
        }
        else if (event == EVENT_SYSTEM_MENUEND)
        {
            printf("End:   ");
        }
        else if (event == EVENT_SYSTEM_FOREGROUND)
        {
            printf("EVENT_SYSTEM_FOREGROUND:   ");
            SetWindowPos(hwnd, NULL, 400 * counter++, 0, 400, 400, NULL);
        }
        printf("%S\n", bstrName);
        SysFreeString(bstrName);
        pAcc->Release();
    }
}
// Initializes COM and sets up the event hook.
//
void AddApps::InitializeMSAA()
{
    CoInitialize(NULL);
    g_hook = SetWinEventHook(
        EVENT_SYSTEM_FOREGROUND,
        EVENT_SYSTEM_MENUEND,                             // Range of events (4 to 5).
        NULL,                                             // Handle to DLL.
        HandleWinEvent,                                   // The callback.
        0, 0,                                             // Process and thread IDs of interest (0 = all)
        WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS); // Flags.
}

// Unhooks the event and shuts down COM.
//
void ShutdownMSAA()
{
    UnhookWinEvent(g_hook);
    CoUninitialize();
}
struct ProcessWindowsInfo
{
    DWORD ProcessID;
    std::vector<HWND> Windows;

    ProcessWindowsInfo(DWORD const AProcessID) : ProcessID(AProcessID) {}
};

BOOL __stdcall EnumProcessWindowsProc(HWND hwnd, LPARAM lParam)
{
    ProcessWindowsInfo *Info = reinterpret_cast<ProcessWindowsInfo *>(lParam);
    DWORD WindowProcessID;

    GetWindowThreadProcessId(hwnd, &WindowProcessID);

    if (WindowProcessID == Info->ProcessID)
        Info->Windows.push_back(hwnd);

    return true;
}
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    int written = GetWindowTextA(hwnd, buffer, 128);
    printf("%s\n", buffer);
    if (written && strstr(buffer, "Instagram") != NULL)
    {
        *(HWND *)lParam = hwnd;
        return FALSE;
    }
    return TRUE;
}

HWND GetFirefoxHwnd()
{
    HWND hWnd = NULL;

    EnumWindows(EnumWindowsProc, (LPARAM)&hWnd);
    return hWnd;
}
void AddApps::StartApps()
{
    wchar_t filename[] = L"DDATest_0.h264";
    //ShellExecuteW(NULL, L"open", filename, NULL, NULL, SW_SHOWNORMAL);
    // ShellExecuteA(0, 0, "chrome.exe", "http://google.com  --incognito", 0, SW_SHOWMAXIMIZED);
    ShellExecuteA(0, 0, "chrome.exe", "--app=http://m.facebook.com", 0, SW_SHOWNORMAL);
    ShellExecuteA(0, 0, "chrome.exe", "--app=http://m.instagram.com", 0, SW_SHOWNORMAL);

    // ShellExecuteW(NULL, NULL, L"http://m.facebook.com", NULL, NULL,
    //               SW_SHOWNORMAL);
    // HWND hwnd = ::FindWindowW(_T("Microsoft Edge"), NULL);
    // HWND hwnd = ::FindWindow(0, _T("Microsoft Edge"));
    // SHELLEXECUTEINFO sei = { 0 };
    // sei.cbSize = sizeof(SHELLEXECUTEINFO);
    // sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    // sei.hwnd = 0;  // This app's window handle sei.lpVerb = _T("open");
    // sei.lpFile = L"http://m.facebook.com";
    // sei.lpDirectory = NULL;
    // sei.nShow = SW_SHOW;
    // sei.hInstApp = NULL;
    // if (ShellExecuteEx(&sei)) {
    // 	WaitForInputIdle(sei.hProcess, INFINITE);

    // 	ProcessWindowsInfo Info(GetProcessId(sei.hProcess));

    // 	EnumWindows((WNDENUMPROC)EnumProcessWindowsProc,
    // 		reinterpret_cast<LPARAM>(&Info));
    // 	for (const auto& hwnd : Info.Windows)
    // 		SetWindowPos(hwnd, NULL, 0, 0, 200, 200, NULL);
    // }
    //HWND hwnd = GetFirefoxHwnd();
    //if (hwnd)
    //	SetWindowPos(hwnd, NULL, 400, 0, 400, 800, NULL);
}