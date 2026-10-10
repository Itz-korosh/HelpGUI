#pragma once
#include <windows.h>

class BaseComponent {
public:
    virtual ~BaseComponent() = default;

    virtual void Create(HWND parent) = 0;
    HWND Handle() const { return hwnd_; }

protected:
    HWND hwnd_ = nullptr;
};