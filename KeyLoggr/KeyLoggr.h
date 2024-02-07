// spdx-license-identifier: gpl-3.0-or-later
/*
 * copyright (c) 2024 chirag singla
 */


#pragma once

LRESULT CALLBACK KeyboardProc(
        int code,
        WPARAM wParam,
        LPARAM lParam
);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam);
