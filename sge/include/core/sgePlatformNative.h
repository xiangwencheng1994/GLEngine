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
     * Mouse or keybord action type
     */
    enum NativePressAction
    {
        PressDown,
        PressUp
    };

    /**
     * Mouse button type
     */
    enum NativeMouseButton
    {
        LeftButton,
        RightButton,
        MidleButton
    };

    /**
     * Mouse button event
     */
    typedef struct NativeMouseButtonEvent
    {
        NativePressAction   _action;
        NativeMouseButton   _button;
        int2                _pos;
    } NativeMouseButtonEvent;

    /**
     * Mouse move event
     */
    typedef struct NativeMouseMoveEvent
    {
        int2                _pos;
    } NativeMouseMoveEvent;

    /**
     * Mouse wheel event
     */
    typedef struct NativeMouseWheelEvent
    {
        float               _delta;
    } NativeMouseWhellEvent;

    /**
     * Click event
     */
    typedef struct NativeClickEvent
    {
        int2                _pos;
    } NativeClickEvent;

    /**
     * Keybord event
     */
    typedef struct NativeKeyEvent
    {
        NativePressAction   _action;
        byte                _keyCode;  //TODO: define key map
    } NativeKeyEvent;

    /**
     * Surface resized event
     */
    typedef struct NativeResizeEvent
    {
        int2                _size;
    } NativeResizeEvent;

    /**
     * User defined event
     */
    typedef struct NativeUserEvent
    {
        const char*     _name;
        void *          _data1;
        void *          _data2;
    } NativeUserEvent;

    /**
     * The native platform interface
     */
    class SGE_API sgePlatformNative
    {
    public:
        typedef Delegate1<bool, NativeMouseButtonEvent&>    OnMouseButtonEvent;
        typedef Delegate1<bool, NativeMouseMoveEvent&>      OnMouseMoveEvent;
        typedef Delegate1<bool, NativeMouseWheelEvent&>     OnMouseWheelEvent;
        typedef Delegate1<bool, NativeClickEvent&>          OnClickEvent;
        typedef Delegate1<bool, NativeKeyEvent&>            OnKeyEvent;
        typedef Delegate1<bool, NativeResizeEvent&>         OnResizeEvent;
        typedef Delegate1<void, NativeUserEvent&>           OnUserEvent;
        typedef Delegate0<bool>                             OnCloseEvent;

    public:
        OnMouseButtonEvent      _onMouseButtonEvent;
        OnMouseMoveEvent        _onMouseMoveEvent;
        OnMouseWheelEvent       _onMouseWheelEvent;
        OnClickEvent            _onClickEvent;
        OnKeyEvent              _onKeyEvent;
        OnResizeEvent           _onResizeEvent;
        OnUserEvent             _onUserEvent;
        OnCloseEvent            _onCloseEvent;

    public:
        virtual ~sgePlatformNative() {}

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
        sgePlatformNative() {}

        DISABLE_COPY(sgePlatformNative)
    };

}

#endif
