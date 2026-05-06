#include "./main.h"
#include "./ChWindow.h"
#include "./ClientFolder.h"
#include "./WebView2Installer.h"
#include <windows.h>

// Change this to "Teacher Client" or whatever you like!
constexpr const wchar_t *title = L"Teacher Client";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 1. Setup Folder logic
    ClientFolder folder(L"TeacherClient");
    
    // 2. FORCE UNCAP FPS (The most important part for you)
    // We pass the flags directly to the WebView2 environment
    auto options = Microsoft::WRL::Make<CoreWebView2EnvironmentOptions>();
    options->put_AdditionalBrowserArguments(L"--disable-frame-rate-limit --disable-gpu-vsync --max-gum-fps=9999 --disable-background-timer-throttling");

    // 3. Create the Window and Load Krunker
    ChWindows windows(hInstance, nCmdShow, title, &folder, options.Get());
    
    // 4. Message Loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}