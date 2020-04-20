#include <chrono>
#include <Windows.h>
#include "Capture.h"
#include "AppStarter.h"

AppStarter appStarter;

int monitorCount;
BOOL Monitorenumproc(
    HMONITOR Arg1,
    HDC Arg2,
    LPRECT rect,
    LPARAM Arg4)
{
    ++monitorCount;
    printf("Found monitor %d. Left: %d, Right: %d\n", monitorCount, rect->left, rect->right);
    if (monitorCount == 2)
    {
        appStarter.InitializeMSAA(rect);
        appStarter.StartApps();
        return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    EnumDisplayMonitors(NULL, NULL, Monitorenumproc, 0);
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0) > 0)
    {
        //TranslateMessage(&msg);
        //DispatchMessage(&msg);
    }
    return msg.wParam;
}
