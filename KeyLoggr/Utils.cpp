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
            return TEXT("\u232b");

        case VK_TAB:
            return TEXT("\u21e5");

        case VK_RETURN:
            return TEXT("\u21a9");

        case VK_SHIFT:
            return TEXT("\u21e7");

        case VK_CONTROL:
            return TEXT("\u2303");

        case VK_MENU:
            return TEXT("\u2325");

        case VK_PAUSE:
            return TEXT("Pause");

        case VK_CAPITAL:
            return TEXT("\u21ea");

        case VK_ESCAPE:
            return TEXT("\u238b");

        case VK_SPACE:
            return TEXT(" ");

        case VK_PRIOR:
            return TEXT("\u21de");

        case VK_NEXT:
            return TEXT("\u21df");

        case VK_END:
            return TEXT("\u2198");

        case VK_HOME:
            return TEXT("\u2196");

        case VK_LEFT:
            return TEXT("\u2190");

        case VK_UP:
            return TEXT("\u2191");

        case VK_RIGHT:
            return TEXT("\u2192");

        case VK_DOWN:
            return TEXT("\u2193");

        case VK_SELECT:
            return TEXT("Select");

        case VK_PRINT:
            return TEXT("Print");

        case VK_INSERT:
            return TEXT("Ins");

        case VK_DELETE:
            return TEXT("\u232b");

        case VK_HELP:
            return TEXT("Help");

        default:
            return TEXT("-");
    }
}
