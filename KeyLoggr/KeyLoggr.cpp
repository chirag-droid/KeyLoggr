// spdx-license-identifier: gpl-3.0-or-later
/*
 * copyright (c) 2024 chirag singla
 */

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#include "KeyLoggr.h"

wchar_t gLastKeyPressed[] = L"\0";

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"KeyLoggr";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
            WS_EX_TOPMOST,
            CLASS_NAME,
            L"KeyLoggrDisplay",
            WS_POPUP,

            // Size and position
            10, 10, 300, 70,

            nullptr,   // Parent window
            nullptr,   // Menu
            hInstance, // Instance handle
            nullptr    // Additional application
    );

    if (hwnd == nullptr) {
        return -1;
    }

    // Make the window transparent
    SetWindowLong(hwnd, GWL_EXSTYLE,
                  GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 100, LWA_ALPHA);
    ShowWindow(hwnd, nCmdShow);

    // Install the keyboard hook
    HHOOK hKeyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, KeyboardProc, hInstance, 0);

    // Run the message loop.
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Unhook the keyboard hook before exiting
    UnhookWindowsHookEx(hKeyboardHook);

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc;
            hdc = BeginPaint(hwnd, &ps);

            // Fill the window with black color
            RECT rc;
            GetClientRect(hwnd, &rc);
            FillRect(hdc, &rc, (HBRUSH) GetStockObject(BLACK_BRUSH));

            // Create a font with larger size
            HFONT hFont = CreateFont(48, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                                     OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                     DEFAULT_PITCH | FF_DONTCARE,
                                     L"Arial");
            auto hOldFont = (HFONT) SelectObject(hdc, hFont);

            SetTextColor(hdc, RGB(255, 255, 255));
            SetBkMode(hdc, TRANSPARENT);
            DrawText(hdc, gLastKeyPressed, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_MODIFYSTRING);

            // Restore the original font and clean up
            SelectObject(hdc, hOldFont);
            DeleteObject(hFont);

            EndPaint(hwnd, &ps);
        }
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK KeyboardProc(
        int code,
        WPARAM wParam,
        LPARAM lParam
) {
    if (code >= 0) {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            auto *pKeyInfo = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);
            wchar_t keyPressed = MapVirtualKey(pKeyInfo->vkCode, MAPVK_VK_TO_CHAR);
            gLastKeyPressed[0] = keyPressed;

            // Redraw the Keyboard Display Window
            HWND hwnd = FindWindow(nullptr, L"KeyLoggrDisplay");
            if (hwnd != nullptr) {
                InvalidateRect(hwnd, nullptr, TRUE);
            }
        }
    }

    return CallNextHookEx(nullptr, code, wParam, lParam);
}
