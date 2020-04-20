#include <chrono>
#include <Windows.h>
#include "Capture.h"
#include "AppStarter.h"

Capture capture;
AppStarter appStarter;

void CaptureAndEncode()
{
    /// The app will try to capture 60 times, by default
    int nFrames = 60;
    int ret = 0;
    bool useNvenc = true;

    using clock = std::chrono::system_clock;
    using sec = std::chrono::duration<double>;
    // for milliseconds, use using ms = std::chrono::duration<double, std::milli>;

    const auto before = clock::now();
    setvbuf(stdout, NULL, _IONBF, 0); // disable output buffer

    /// Kick off the demo
    ret = capture.Grab60FPS(nFrames);
    const sec duration = clock::now() - before;

    printf("It took %.1f s (%.1f FPS)", duration.count(), nFrames / duration.count());
}

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
        CaptureAndEncode();
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
