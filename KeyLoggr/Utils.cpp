// spdx-license-identifier: gpl-3.0-or-later
/*
 * copyright (c) 2024 chirag singla
 */

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "Utils.h"

const wchar_t * MapModifierKey(DWORD code) {
    switch (code) {
        case VK_BACK:
            return TEXT("Backspace");

        case VK_TAB:
            return TEXT("Tab");

        case VK_RETURN:
            return TEXT("Enter");

        case VK_SHIFT:
            return TEXT("Shift");

        case VK_CONTROL:
            return TEXT("Ctrl");

        case VK_MENU:
            return TEXT("Alt");

        case VK_PAUSE:
            return TEXT("Pause");

        case VK_CAPITAL:
            return TEXT("Caps");

        case VK_ESCAPE:
            return TEXT("ESC");

        case VK_SPACE:
            return TEXT("_");

        case VK_PRIOR:
            return TEXT("PgUp");

        case VK_NEXT:
            return TEXT("PgDn");

        case VK_END:
            return TEXT("End");

        case VK_HOME:
            return TEXT("Home");

        case VK_LEFT:
            return TEXT("Left");

        case VK_UP:
            return TEXT("Up");

        case VK_RIGHT:
            return TEXT("Right");

        case VK_DOWN:
            return TEXT("Down");

        case VK_SELECT:
            return TEXT("Select");

        case VK_PRINT:
            return TEXT("Print");

        case VK_INSERT:
            return TEXT("Ins");

        case VK_DELETE:
            return TEXT("Del");

        case VK_HELP:
            return TEXT("Help");

        default:
            return TEXT("-");
    }
}
