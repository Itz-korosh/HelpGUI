#include <windows.h>
#include "GUIComponents/Window.hpp"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    Window app(L"HelpGUI", 800, 600);
    if (!app.Create(hInst)) return 1;
    app.Show(nCmdShow);
    return app.RunMessageLoop();
}