/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgePlatformNativeWin32.cpp
 * date: 2018/11/14
 * author: xiang
 *
 * License
 *
 * Copyright (c) 2017-2018, Xiang Wencheng <xiangwencheng@outlook.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * - Neither the names of its contributors may be used to endorse or
 *   promote products derived from this software without specific
 *   prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <win32/sgePlatformNativeWin32.h>
#include <core/sgeLog.h>

#if (SGE_TARGET_PLATFORM == SGE_PLATFORM_WIN32)

namespace sge
{    
    #define ENGINE_WIN32_WND_CLASS "sgeEngineWnd"

    static LRESULT CALLBACK sgeNativeWin32WndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
    {
        LONG_PTR    plptrWin = GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (plptrWin)
        {
            PlatformWin32Native* native =
                (PlatformWin32Native*)(plptrWin);
            return native->wndProc(hWnd, msgId, wParam, lParam);
        }
        return DefWindowProc(hWnd, msgId, wParam, lParam);
    }

    static bool registerWin32Class()
    {
        WNDCLASSEXA wnd;
        memset(&wnd, 0, sizeof(wnd));
        wnd.cbSize = sizeof(wnd);

        wnd.lpfnWndProc = sgeNativeWin32WndProc;
        wnd.hbrBackground = NULL;
        wnd.hCursor = LoadCursor(0, IDC_ARROW);
        wnd.hIcon = 0;
        wnd.hIconSm = 0;
        wnd.hInstance = 0;
        wnd.lpszClassName = ENGINE_WIN32_WND_CLASS;
        wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
                
        bool    ret = RegisterClassExA(&wnd);
        if (!ret)
        {
            Log::error("RegisterClassExA failed with error: 0x%X", GetLastError());
        }
        return ret;
    }

    static HWND createWin32Wnd(HWND pWnd, int width, int height,void* userData)
    {
        RECT    rect;
        if (pWnd)
        {
            GetClientRect(pWnd, &rect);
        }
        else
        {
            // center the desktop
            HWND desktop = GetDesktopWindow();
            RECT    sceen;
            GetClientRect(desktop, &sceen);
            rect.left = ((sceen.right - sceen.left - width)) / 2;
            rect.top = ((sceen.bottom - sceen.top - height)) / 2;
            rect.right = rect.left + width;
            rect.bottom = rect.top + height;
        }

        HWND    hWnd = CreateWindowExA(0
            , ENGINE_WIN32_WND_CLASS
            , "wizEngineApp"
            , pWnd ? WS_CHILD : WS_OVERLAPPEDWINDOW
            , rect.left
            , rect.top
            , rect.right - rect.left
            , rect.bottom - rect.top
            , pWnd
            , 0
            , 0
            , userData);

        if (hWnd)
        {
#ifndef GWL_USERDATA
#define GWL_USERDATA    (-21)
#endif // !GWL_USERDATA

#ifdef _WIN64
            SetWindowLongPtr(hWnd, GWL_USERDATA, (LONGLONG)(LONG_PTR)userData);
#else
            SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)(LONG_PTR)userData);
#endif
        }
        else
        {
            Log::error("CreateWindowExA failed with error: 0x%X", GetLastError());
        }

        return hWnd;
    }

    PlatformWin32Native::PlatformWin32Native(HWND pWnd, int width, int height)
    {
        if (!registerWin32Class())
        {
            return;
        }

        _hWnd = createWin32Wnd(pWnd, width, height, this);
        if (NULL == _hWnd)
        {
            return;
        }

        _hDC = GetDC(_hWnd);
        if (NULL == _hDC)
        {
            Log::error("GetDC from HWND failed");
        }

        UpdateWindow(_hWnd);
        ShowWindow(_hWnd, SW_SHOW);

        Log::info("Native window created");
    }

    PlatformWin32Native::~PlatformWin32Native()
    {
        if (_hWnd)
        {
            DestroyWindow(_hWnd);
            _hWnd = NULL;
            _hDC = NULL;
        }

        UnregisterClassA(ENGINE_WIN32_WND_CLASS, 0);
    }

    bool PlatformWin32Native::ProcessEvents()
    {
        ASSERT(_hWnd);

        MSG msg = { 0 };

        if (PeekMessage(&msg, _hWnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            return true;
        }

        return false;
    }

    LRESULT PlatformWin32Native::wndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
    {
        bool ret = false;

        switch (msgId)
        {

        case WM_LBUTTONDOWN:
        {
            int2 pos((short)LOWORD(lParam), (short)HIWORD(lParam));
            MouseDownEvent event = { pos, (byte)GET_KEYSTATE_WPARAM(wParam) };
            ret = _OnLeftButtonDownEvent(event);
        } break;

        case WM_LBUTTONUP:
        {
            int2 pos((short)LOWORD(lParam), (short)HIWORD(lParam));
            MouseUpEvent event = { pos, (byte)GET_KEYSTATE_WPARAM(wParam) };
            ret = _OnLeftButtonUpEvent(event);
        } break;

        case WM_RBUTTONDOWN:
        {
            int2 pos((short)LOWORD(lParam), (short)HIWORD(lParam));
            MouseDownEvent event = { pos, (byte)GET_KEYSTATE_WPARAM(wParam) };
            ret = _OnRightButtonDownEvent(event);
        } break;

        case WM_RBUTTONUP:
        {
            int2 pos((short)LOWORD(lParam), (short)HIWORD(lParam));
            MouseUpEvent event = { pos, (byte)GET_KEYSTATE_WPARAM(wParam) };
            ret = _OnRightButtonUpEvent(event);
        } break;

        case WM_MBUTTONDOWN:
        {
            int2 pos((short)LOWORD(lParam), (short)HIWORD(lParam));
            MouseDownEvent event = { pos, (byte)GET_KEYSTATE_WPARAM(wParam) };
            ret = _OnMiddleButtonDownEvent(event);
        } break;

        case WM_MBUTTONUP:
        {
            int2 pos((short)LOWORD(lParam), (short)HIWORD(lParam));
            MouseUpEvent event = { pos, (byte)GET_KEYSTATE_WPARAM(wParam) };
            ret = _OnMiddleButtonUpEvent(event);
        } break;

        case WM_MOUSEWHEEL:
        {
            int2 pos((short)LOWORD(lParam), (short)HIWORD(lParam));
            MouseWheelEvent event = { GET_WHEEL_DELTA_WPARAM(wParam), pos, (byte)GET_KEYSTATE_WPARAM(wParam) };
            ret = _OnMouseWheelEvent(event);
        } break;

        case WM_MOUSEMOVE:
        {
            int2 pos((short)LOWORD(lParam), (short)HIWORD(lParam));
            MouseMoveEvent event = { pos, (byte)GET_KEYSTATE_WPARAM(wParam) };
            ret = _OnMouseMoveEvent(event);
        } break;

        case WM_SIZE:
        {
            int2 size((short)LOWORD(lParam), (short)HIWORD(lParam));
            ResizeEvent event = { size };
            ret = _OnResizeEvent(event);
        } break;

        case WM_KEYDOWN:
        {
            KeyDownEvent event = { (byte)wParam };
            ret = _OnKeyDownEvent(event);
        } break;

        case WM_KEYUP:
        {
            KeyUpEvent event = { (byte)wParam };
            ret = _OnKeyUpEvent(event);
        } break;

        case WM_CLOSE:
        {
            ret = _OnCloseEvent();
        } break;

        case WM_DESTROY:
        {
            Log::info("Native window destoryed");
            _hWnd = NULL;
        } break;

        default:
            break;
        }

        if (!ret)
        {
            return DefWindowProc(hWnd, msgId, wParam, lParam);
        }

        return S_OK;
    }

}

#endif
