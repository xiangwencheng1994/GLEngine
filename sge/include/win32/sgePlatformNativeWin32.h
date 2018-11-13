/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgePlatformNativeWin32.h
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


#ifndef SGE_PLATFORM_NATIVE_WIN32_H
#define SGE_PLATFORM_NATIVE_WIN32_H

#include <core/sgePlatform.h>
#include <core/sgePlatformNative.h>

#if (SGE_TARGET_PLATFORM == SGE_PLATFORM_WIN32)

namespace sge
{

    /**
     * Win32 native platform interface implement
     */
    class SGE_API sgePlatformWin32Native : public sgePlatformNative
    {
    public:
        sgePlatformWin32Native(HWND pWnd, int width = 800, int height = 600);
        ~sgePlatformWin32Native();

#ifdef OPENGLES
        virtual EGLNativeWindowType     getWindow() { return _hWnd; }
        virtual EGLNativeDisplayType    getDisplay() { return _hDC; }
#endif

        void    Close() { PostMessage(_hWnd, WM_CLOSE, 0, 0); }
        bool    IsClosed() { return _hWnd == NULL; }
        
        virtual bool        ProcessEvents();

    public:
        virtual LRESULT     wndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam);
        
    private:
        HWND    _hWnd;
        HDC     _hDC;
    };

}

#endif

#endif // !SGE_PLATFORM_NATIVE_WIN32_H
