#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include "BaseComponent.hpp"

class Window {
public:
    Window(const std::wstring& title, int width, int height);
    ~Window();

    // Non-copyable (a Win32 window can't be cloned)
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Create the OS window. Returns false on failure.
    bool Create(HINSTANCE hInstance);

    // Add a component. It gets created inside this window.
    void AddComponent(BaseComponent& component);

    void Show(int nCmdShow);
    int  RunMessageLoop();

    HWND Handle() const { return hwnd_; }

private:
    std::wstring title_;
    int width_;
    int height_;
    HWND hwnd_ = nullptr;
    std::vector<BaseComponent*> components_;

    // Win32 needs a plain function pointer, not a member function.
    // We route through this static, which finds the Window instance.
    static LRESULT CALLBACK WndProcStatic(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
    LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
};