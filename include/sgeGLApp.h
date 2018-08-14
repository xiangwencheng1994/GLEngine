/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGLApp.h
 * date: 2017/12/08
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

#ifndef SGE_GLAPP_H
#define SGE_GLAPP_H

#include <sge.h>
#include <sgeGLContext.h>
#include <sgeMath.h>

namespace sge
{
    class GLAppPrivate;

    struct KeyEvent
    {
        enum EventType
        {
            KeyDown,
            KeyUp
        }type;
        uchar   keyCode;
    };

    struct MouseEvent
    {
        enum EventType
        {
            MouseMove = 0,
            LeftBtnDown,
            LeftBtnUp,
            LeftBtnDbClk,
            RightBtnDown,
            RightBtnUp,
            RightBtnDbClk,
            MiddleBtnDown,
            MiddleBtnUp,
            MiddleBtnDbClk,
            MouseWheel
        }type;
        int2 pos;
    };

    /**
     * Class GLApp
     * A encapsulation class for opengl window and messageloop.
     */
    class SGE_API GLApp
    {
    public:

        /**
         * Constructor
         */
        GLApp();

        /**
         * Get the window title
         */
        const char* title() const;

        /**
         * Set window title
         * @param title New title for window
         */
        void setTitle(const char* title);

        /**
         * Get window size
         */
        const int2& size() const;

        /**
         * Set window size
         * @param size New size for window
         */
        void setSize(int2 size);

        /**
         * Get window pos at screen
         */
        const int2& pos() const;

        /**
         * Set window pos
         * @param pos New pos for window
         */
        void setPos(int2 pos);

        /**
         * Run this app
         * first it create window and GLContext, then show window and exec message loop.
         * quit if get WM_QUIT message.
         */
        int run();

        /**
         * Set window visibility.
         */
        void setVisible(bool visibility);

        /**
         * Get the GLContext
         * @return NULL if failed
         */
        GLContext* getGLContext() const;

        /**
         * Send a destroy message to message loop.
         */
        void destroy();

#ifdef _WIN32
        /**
         * Get the window handle
         */
        HWND getHWND() const;
        /**
         * App window message process.
         */
        virtual LRESULT wndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam);
#endif
    protected:
        
        /**
         * This function will called by 'run' after Window and GLContent created.
         */
        virtual void onCreate() = 0;
        
        /**
         * This function will called by 'run' in each message loop while no message.
         */
        virtual void onRender(float elapsed) = 0;

        /**
         * This function will called after 'onRender' for GUI draws.
         */
        virtual void onRenderUI(float elapsed) {}

        /**
         * This function will called by 'run' after break the message loop and try destory app.
         */
        virtual void onDestory() = 0;

        /**
         * This function will called by message loop whe get window size has changed.
         * @param width The new width.
         * @param height The new height.
         */
        virtual void onSizeChanged(int width, int height) { glViewport(0, 0, width, height); }

        /**
         * This function will called by message loop when get KeyEvent message
         * @param event The KeyEvent struct.
         */
        virtual bool onKeyEvent(const KeyEvent& event) { return false; }

        /**
         * This function will called by message loop when get MouseEvent message
         * @param event The mouse event struct
         */
        virtual bool onMouseEvent(const MouseEvent & event) { return false; }

        /**
         * This function will call by message loop when get WM_CLOSE message
         * @return true will prevent close, by default it return false, will close app.
         */
        virtual bool onClose() { return false; }

    private:
        GLAppPrivate* d;
        DISABLE_COPY(GLApp)
    };

}

#endif // ! SGE_GLAPP_H