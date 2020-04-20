#include <chrono>
#include <Windows.h>
#include "Capture.h"
#include "AppStarter.h"

Capture capture;
AppStarter appStarter;

int main(int argc, char **argv)
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
    appStarter.InitializeMSAA();
    //ret = capture.Grab60FPS(nFrames);
    appStarter.StartApps();
    const sec duration = clock::now() - before;

    printf("It took %.1f s (%.1f FPS)", duration.count(), nFrames / duration.count());
    // while (true);
    // return ret;
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0) > 0)
    {
        //TranslateMessage(&msg);
        //DispatchMessage(&msg);
    }
    return msg.wParam;
}
