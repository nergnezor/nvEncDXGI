

#pragma region WindowsAPI
#if 0
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = { 'e','r' };

// The string that appears in the application's title bar.
static TCHAR szTitle[] = { 'e','r' };//_T("Windows Desktop Guided Tour Application");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
       /* MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);*/

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindow explained:
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 100,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        //MessageBox(NULL,
        //    _T("Call to CreateWindow failed!"),
        //    _T("Windows Desktop Guided Tour"),
        //    NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = { 'e','r' };//_T("Hello, Windows desktop!");

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        // Here your application is laid out.
        // For this introduction, we just print out "Hello, Windows desktop!"
        // in the top left corner.
        TextOut(hdc,
            5, 5,
            //greeting, _tcslen(greeting));
        greeting, 2);
        // End application-specific layout section.

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}
#endif
#pragma endregion

#pragma region Capture
#if 1
#include <Gui.h>
#include <Capture.h>
#include <stdio.h>
#include <chrono>
#include <thread>
// #include <shellapi.h>
// #include <NvDecoder/NvDecoder.h>

Gui gui;
int main(int argc, char **argv)
// void Capture()
{
    /// The app will try to capture 60 times, by default
    int nFrames = 60;
    int ret = 0;
    bool useNvenc = true;

/// Parse arguments
#if 0
    try
    {
        if (argc > 1)
        {
            for (int i = 0; i < argc; i++)
            {
                if (!strcmpi("-frames", argv[i]))
                {
                    nFrames = atoi(argv[i + 1]);
                }
                else if (!strcmpi("-frames", argv[i]))
                {
                    useNvenc = true;
                }
                else if ((!strcmpi("-help", argv[i])) ||
                         (!strcmpi("-h", argv[i])) ||
                         (!strcmpi("h", argv[i])) ||
                         (!strcmpi("help", argv[i])) ||
                         (!strcmpi("-usage", argv[i])) ||
                         (!strcmpi("-about", argv[i])) ||
                         (!strcmpi("-?", argv[i])) ||
                         (!strcmpi("?", argv[i])) ||
                         (!strcmpi("about", argv[i])) ||
                         (!strcmpi("usage", argv[i])))
                {
                    printHelp();
                }
            }
        }
        else
        {
            printHelp();
            return 0;
        }
    }
    catch (...)
    {
        printf(" DXGIOUTPUTDuplication_NVENC_Demo: Invalid arguments passed.\n\
                                                   Continuing to grab 60 frames.\n");
        printHelp();
    }
#endif
    printf(" DXGIOUTPUTDuplication_NVENC_Demo: Frames to Capture: %d.\n", nFrames);

    using clock = std::chrono::system_clock;
    using sec = std::chrono::duration<double>;
    // for milliseconds, use using ms = std::chrono::duration<double, std::milli>;

    const auto before = clock::now();

    /// Kick off the demo
    Capture capture;
    ret = capture.Grab60FPS(nFrames);
    _fcloseall();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    const sec duration = clock::now() - before;

    printf("It took %.1f s (%.1f FPS)", duration.count(), nFrames / duration.count());
    gui.Init();

    return ret;
}
#endif
#pragma endregion
