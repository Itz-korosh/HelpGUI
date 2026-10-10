#include "Window.hpp"

// ─── The Win32 → C++ bridge ─────────────────────────────────
// Win32 will call WndProcStatic. We need to find *which* Window
// instance the message belongs to, then call its WndProc.
static const wchar_t* WINDOW_CLASS = L"HelpGUIWindowClass";

LRESULT CALLBACK Window::WndProcStatic(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    Window* self = nullptr;

    if (msg == WM_NCCREATE) {
        // When the window is first created, Windows passes our Window*
        // as the "lpCreateParams". Grab it and store it.
        CREATESTRUCTW* cs = reinterpret_cast<CREATESTRUCTW*>(lp);
        self = static_cast<Window*>(cs->lpCreateParams);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    } else {
        // Any other message: fetch the Window* we stored earlier.
        self = reinterpret_cast<Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    }

    if (self) return self->WndProc(hwnd, msg, wp, lp);

    return DefWindowProcW(hwnd, msg, wp, lp);
}

LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

// ─── Construction / destruction ─────────────────────────────
Window::Window(const std::wstring& title, int width, int height)
    : title_(title), width_(width), height_(height) {}

Window::~Window() {
    if (hwnd_) DestroyWindow(hwnd_);
}

// ─── Create ─────────────────────────────────────────────────
bool Window::Create(HINSTANCE hInstance) {
    WNDCLASSW wc = {};
    wc.lpfnWndProc   = Window::WndProcStatic;
    wc.hInstance     = hInstance;
    wc.lpszClassName = WINDOW_CLASS;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassW(&wc)) {
        // If the class already exists, RegisterClass fails but that's ok.
        // Any *other* failure means we can't create the window.
        if (GetLastError() != ERROR_CLASS_ALREADY_EXISTS) return false;
    }

    hwnd_ = CreateWindowExW(
        0,
        WINDOW_CLASS,
        title_.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width_, height_,
        NULL, NULL, hInstance,
        this            // ← this is how WndProcStatic finds us
    );

    return hwnd_ != nullptr;
}

// ─── AddComponent ───────────────────────────────────────────
void Window::AddComponent(BaseComponent& component) {
    component.Create(hwnd_);      // let the component build itself
    components_.push_back(&component);
}

// ─── Show / Run ─────────────────────────────────────────────
void Window::Show(int nCmdShow) {
    ShowWindow(hwnd_, nCmdShow);
    UpdateWindow(hwnd_);
}

int Window::RunMessageLoop() {
    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}