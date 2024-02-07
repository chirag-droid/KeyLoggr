// spdx-license-identifier: gpl-3.0-or-later
/*
 * copyright (c) 2024 chirag singla
 */

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#include "KeyLoggr.h"
#include "Utils.h"

TCHAR gKeyboardMessage[100];
DWORD gPrevTime = 0;

DWORD kThreshold = 200;

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

        // Enable dragging of this window
        case WM_NCHITTEST:
            LRESULT hit;
            hit = DefWindowProc(hwnd, uMsg, wParam, lParam);
            if (hit == HTCLIENT) hit = HTCAPTION;
            return hit;

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

            // Draw text from keyboard message
            SetTextColor(hdc, RGB(255, 255, 255));
            SetBkMode(hdc, TRANSPARENT);
            DrawText(hdc, gKeyboardMessage, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_MODIFYSTRING);

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
    // only process if the code >= 0
    // otherwise transfer to next hook
    if (code >= 0) {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            auto *pKeyInfo = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);

            TCHAR keyboardMessage[100];

            // Windows provided function to convert keys to chars
            // This doesn't convert modifier keys like Shift, etc.
            wchar_t keyPressed = MapVirtualKey(pKeyInfo->vkCode, MAPVK_VK_TO_CHAR);

            if ((pKeyInfo->vkCode >= 0x01) && (pKeyInfo->vkCode <= 0x2F)) {
                // key is a modifier key
                wsprintf(keyboardMessage, TEXT("%s"), MapModifierKey(pKeyInfo->vkCode));
            } else {
                // key is a simple char key

                // Check if modifers are pressed
                if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
                    wsprintf(keyboardMessage, TEXT("%s + %c"), MapModifierKey(VK_SHIFT) , (TCHAR) keyPressed);
                } else if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
                    wsprintf(keyboardMessage, TEXT("%s + %c"), MapModifierKey(VK_CONTROL) , (TCHAR) keyPressed);
                } else if (GetAsyncKeyState(VK_MENU) & 0x8000) {
                    wsprintf(keyboardMessage, TEXT("%s + %c"), MapModifierKey(VK_MENU) , (TCHAR) keyPressed);
                } else {
                    // No additional modifier are pressed
                    wsprintf(keyboardMessage, TEXT("%c"), (TCHAR)keyPressed);
                }
            }

            // Calculate change in time since last call
            if (gPrevTime == 0) {
                gPrevTime = pKeyInfo->time;
            }
            DWORD dt = pKeyInfo->time - gPrevTime;

//             Append to last message if less than threshold
            if (dt <= kThreshold) {
                wsprintf(gKeyboardMessage, TEXT("%s%s"), gKeyboardMessage, keyboardMessage);
            } else {
                wsprintf(gKeyboardMessage, keyboardMessage);
            }

            // Redraw the Keyboard Display Window
            HWND hwnd = FindWindow(nullptr, L"KeyLoggrDisplay");
            if (hwnd != nullptr) {
                InvalidateRect(hwnd, nullptr, TRUE);
            }

            gPrevTime = pKeyInfo->time;
        }
    }

    return CallNextHookEx(nullptr, code, wParam, lParam);
}
