/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgePlatformNative.h
 * date: 2018/11/13
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

#ifndef SGE_PLATFORM_NATIVE_H
#define SGE_PLATFORM_NATIVE_H

#include <core/sgeMath.h>
#include <core/sgeDelegate.h>
#include <core/sgePlatform.h>
#include <core/sgeGLContext.h>

namespace sge
{

    /**
     * The key states masks for mouse message
     */
    typedef enum Mask_KeyState
    {
        Mask_LBUTTON  =   0x0001,
        Mask_RBUTTON  =   0x0002,
        Mask_SHIFT    =   0x0004,
        Mask_CONTROL  =   0x0008,
        Mask_MBUTTON  =   0x0010,
        Mask_XBUTTON1 =   0x0020,
        Mask_XBUTTON2 =   0x0040,
    } Mask_KeyState;

    /**
     * Mouse button down event
     */
    typedef struct MouseButtonEvent
    {        
        int2    _pos;
        byte    _masks;
    } MouseDownEvent, MouseUpEvent, MouseMoveEvent, MouseClickEvent, MouseDBClickEvent;
    
    /**
     * Mouse wheel event
     */
    typedef struct MouseWheelEvent
    {
        int     _zDelta;
        int2    _pos;
        byte    _masks;
    } MouseWheelEvent;
         
    typedef struct KeyDownEvent
    {
        byte    _vKeyCode;
    } KeyDownEvent, KeyUpEvent;

    /**
     * Surface resized event
     */
    typedef struct ResizeEvent
    {
        int2    _size;
    } ResizeEvent;

    typedef Delegate1<bool, const MouseDownEvent&>  OnMouseDownEvent;
    typedef Delegate1<bool, const MouseUpEvent&>    OnMouseUpEvent;
    typedef Delegate1<bool, const MouseClickEvent&> OnMouseClickEvent;
    typedef Delegate1<bool, const MouseMoveEvent&>  OnMouseMoveEvent;
    typedef Delegate1<bool, const MouseWheelEvent&> OnMouseWheelEvent;
    typedef Delegate1<bool, const KeyDownEvent&>    OnKeyDownEvent;
    typedef Delegate1<bool, const KeyUpEvent&>      OnKeyUpEvent;
    typedef Delegate1<bool, const ResizeEvent&>     OnResizeEvent;
    typedef Delegate0<bool>                         OnCloseEvent;

    /**
     * The native platform interface
     */
    class SGE_API PlatformNative
    {
    public:
        OnMouseDownEvent    _OnLeftButtonDownEvent;
        OnMouseUpEvent      _OnLeftButtonUpEvent;
        OnMouseClickEvent   _OnLeftButtonClickEvent;

        OnMouseDownEvent    _OnRightButtonDownEvent;
        OnMouseUpEvent      _OnRightButtonUpEvent;
        OnMouseClickEvent   _OnRightButtonClickEvent;

        OnMouseDownEvent    _OnMiddleButtonDownEvent;
        OnMouseUpEvent      _OnMiddleButtonUpEvent;
        OnMouseClickEvent   _OnMiddleButtonClickEvent;

        OnMouseMoveEvent    _OnMouseMoveEvent;
        OnMouseWheelEvent   _OnMouseWheelEvent;

        OnKeyDownEvent      _OnKeyDownEvent;
        OnKeyUpEvent        _OnKeyUpEvent;

        OnResizeEvent       _OnResizeEvent;
        OnCloseEvent        _OnCloseEvent;

    public:
        virtual ~PlatformNative() {}

#ifdef OPENGLES
        virtual EGLNativeWindowType     getWindow() = 0;
        virtual EGLNativeDisplayType    getDisplay() = 0;
#endif

        // virtual void    sendUserEvent(const char* name, void* data1, void* data2);

        /**
         * try process a native events
         * @return false if no event processed.
         */
        virtual bool    ProcessEvents() = 0;

        /**
         * Send close message to native
         */
        virtual void    Close() = 0;

        /**
         * Check native has closed
         * @return true if closed
         */
        virtual bool    IsClosed() = 0;

    protected:
        PlatformNative() {}

        DISABLE_COPY(PlatformNative)
    };

}

#endif
