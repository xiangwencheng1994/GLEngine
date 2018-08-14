/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGLAppWin.cpp
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

#ifdef _WIN32
#include <sgeGLApp.h>
#include <sgeLog.h>
#include <sgeTimer.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_win32.h>

#include <Windows.h>

#define DEFALUT_TITLE       "sgeGLApp"
#define CLASS_NAME          "sgeGLAppClass"
#define DEFALUT_WIDTH       800
#define DEFALUT_HEIGHT      600

#define WIN_NAME_MAXLEN     256

namespace sge
{
    static LRESULT CALLBACK GLAppWndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
    {
        LONG_PTR plptrWin = GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (plptrWin)
        {
            GLApp* app = reinterpret_cast<GLApp*>(plptrWin);
            assert(app);
            return app->wndProc(hWnd, msgId, wParam, lParam);
        }
        return DefWindowProc(hWnd, msgId, wParam, lParam);
    }

    class GLAppPrivate
    {
        struct WinAttr
        {
            char    title[WIN_NAME_MAXLEN];
            int2    size;
            int2    pos;
			DWORD   style;
        }*attr;

        GLContext*  glContext;
        HWND        hWnd;
        ImGuiContext*   guiContext;


        GLAppPrivate()
            : attr(new WinAttr()),hWnd(NULL), glContext(NULL), guiContext(NULL)
        {
			strcpy_s(attr->title, DEFALUT_TITLE);
            attr->size  =   int2(DEFALUT_WIDTH, DEFALUT_HEIGHT);
            attr->pos   =   int2(CW_USEDEFAULT, CW_USEDEFAULT);
			attr->style =   WS_OVERLAPPEDWINDOW;
        }

        ~GLAppPrivate()
        {
            if (attr)
            {
                delete attr;
                attr    =   NULL;
            }
            if (glContext)
            {
                delete glContext;
                glContext   =   NULL;
            }
        }

        friend class GLApp;

        bool registerClass()
        {
            WNDCLASSEXA wnd;
            memset(&wnd, 0, sizeof(wnd));
            wnd.cbSize  =   sizeof(wnd);

            wnd.lpfnWndProc     =   GLAppWndProc;
            wnd.hbrBackground   =   NULL;
            wnd.hCursor         =   LoadCursor(0, IDC_ARROW);
            wnd.hIcon           =   0;
            wnd.hIconSm         =   0;
            wnd.hInstance       =   0;
            wnd.lpszClassName   =   CLASS_NAME;
            wnd.style           =   CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

            bool    ret =   RegisterClassExA(&wnd);
            if (! ret)
                Log::error("RegisterClassExA failed with %d", ::GetLastError());

            return ret;
        }

        void unregisterClass()
        {
            UnregisterClassA(CLASS_NAME, 0);
        }

        bool createWnd()
        {
            assert(hWnd == NULL);

            hWnd = ::CreateWindowExA(0
                , CLASS_NAME
                , attr->title
                , attr->style
                , attr->pos.x
                , attr->pos.y
                , attr->size.x
                , attr->size.y
                , NULL
                , 0
                , 0
                , this);

            bool ret = (hWnd != NULL);
            if (!ret) Log::error("CreateWindowExA failed with %d", ::GetLastError());
            return ret;
        }

        void destroyWnd()
        {
            if (hWnd)
            {
                DestroyWindow(hWnd);
                hWnd    =   NULL;
            }
        }

        bool createGLContext(int format)
        {
            assert(hWnd && "Must createWnd before createGLContext");
            assert(glContext == NULL && "Already has glContext, not need create again");
            glContext   =   GLContext::CreateGLContext(hWnd, 0, format);
            guiContext  =   ImGui::CreateContext();
            ImGui_ImplOpenGL3_Init("#version 330");
            ImGui_ImplWin32_Init(hWnd);
            ImGui::StyleColorsDark();
            return glContext != NULL;
        }

        void destoryGLContext()
        {
            if (guiContext)
            {
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplWin32_Shutdown();
                ImGui::DestroyContext(guiContext);                
                guiContext  =   NULL;
            }
            if (glContext)
            {
                delete glContext;
                glContext   =   NULL;
            }
        }

    };

    GLApp::GLApp()
        : d(new GLAppPrivate())
    {
    }

    const char * GLApp::title() const
    {
        if (d->hWnd)
        {
            GetWindowTextA(d->hWnd, d->attr->title, WIN_NAME_MAXLEN);
        }
        return d->attr->title;
    }

    void GLApp::setTitle(const char *title)
    {
        strcpy_s(d->attr->title, WIN_NAME_MAXLEN, title);
        if (d->hWnd)
        {
            ::SetWindowTextA(d->hWnd, title);
        }
    }

    const int2& GLApp::size() const
    {
        return d->attr->size;
    }

    void GLApp::setSize(int2 size)
    {
        d->attr->size = size;
        if (d->hWnd)
        {
            SetWindowPos(d->hWnd, 0, 0, 0, size.x, size.y, SWP_NOMOVE | SWP_NOZORDER);
        }
    }

    const int2 & GLApp::pos() const
    {
        return d->attr->pos;
    }

    void GLApp::setPos(int2 pos)
    {
        d->attr->pos = pos;
        if (d->hWnd)
        {
            SetWindowPos(d->hWnd, 0, pos.x, pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        }
    }

    int GLApp::run()
    {
        if (! d->registerClass()) return -1;
        if (! d->createWnd()) return -2;
        if (! d->createGLContext(GLContext::GetFormatForMsaa(8))) return -3;

        SetWindowLongPtr(d->hWnd, GWL_USERDATA, (LONG)(LONG_PTR)this);

        onCreate();

        UpdateWindow(d->hWnd);
        ShowWindow(d->hWnd, SW_SHOW);

        SetFocus(d->hWnd);

        Timer timer;
        timer.elapsed();
        
        MSG     msg = { 0 };
        while (WM_QUIT != msg.message)
        {
            if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                float elapsed = timer.elapsed();
                // Rendering Game
                onRender(elapsed);
                
                // Rendering UI
                ImGui::SetCurrentContext(d->guiContext);
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplWin32_NewFrame();
                ImGui::NewFrame();
                onRenderUI(elapsed);
                ImGui::EndFrame();
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				d->glContext->SwapBuffers();
            }
        }

        onDestory();

        d->destoryGLContext();
        d->destroyWnd();
        d->unregisterClass();
        return 0;
    }

    void GLApp::setVisible(bool visibility)
    {
        if (d->hWnd)
        {
            ShowWindow(d->hWnd, visibility ? SW_SHOW : SW_HIDE);
        }
    }

    GLContext* GLApp::getGLContext() const
    {
        return d->glContext;
    }

    void GLApp::destroy()
    {
        if (d->hWnd)
        {
            DestroyWindow(d->hWnd);
        }
    }

    HWND GLApp::getHWND() const
    {
        return d ? d->hWnd : NULL;
    }

    LRESULT GLApp::wndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msgId, wParam, lParam))
        {
            return S_OK;
        }

        ImGuiIO& io = ImGui::GetIO();
        if (!io.WantCaptureMouse
            && !io.WantCaptureKeyboard 
            && !io.WantTextInput)

        switch (msgId)
        {
        /// key event
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
            KeyEvent kevt;
            kevt.type = (KeyEvent::EventType)(msgId - WM_KEYDOWN);
            kevt.keyCode = wParam;
            if (onKeyEvent(kevt)) return 0;
        } break;
        
        /// mouse event
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        {
            MouseEvent mevt;
            mevt.type = (MouseEvent::EventType)(msgId - WM_MOUSEMOVE);
            mevt.pos.x = ((int)(short)LOWORD(lParam));
            mevt.pos.y = ((int)(short)HIWORD(lParam));
            if (onMouseEvent(mevt)) return 0;
        } break;
        case WM_MOUSEWHEEL:
        {
            MouseEvent mevt;
            mevt.type = MouseEvent::MouseWheel;
            mevt.pos.x = mevt.pos.y = GET_WHEEL_DELTA_WPARAM(wParam);
            if (onMouseEvent(mevt)) return 0;
        }break;

        /// size event
        case WM_SIZE:
        {
            d->attr->size.x = LOWORD(lParam);
            d->attr->size.y = HIWORD(lParam);
            onSizeChanged(d->attr->size.x, d->attr->size.y);
        } break;
        
        /// close event
        case WM_CLOSE:
        {
            if (!onClose()) destroy();
        } break;
        case WM_DESTROY:
        {
            ::PostQuitMessage(0);
        } break;

        } // !end switch
        
        return  ::DefWindowProc(hWnd, msgId, wParam, lParam);
    }
}


#endif