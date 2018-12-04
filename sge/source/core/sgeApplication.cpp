/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeApplication.cpp
 * date: 2018/12/05
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

#include <core/sgeApplication.h>
#include <core/sgeScene.h>

#if SGE_TARGET_PLATFORM == SGE_PLATFORM_WIN32
#include <win32/sgePlatformNativeWin32.h>
#endif // SGE_TARGET_PLATFORM

namespace sge
{
    Application::Application()
        : _curScene(NULL), _platform(NULL)
    {
#ifdef OPENGLES
        PlatformWin32Native* p = new PlatformWin32Native(0);
        _platform = p;
        _glContext.Init(p->getWindow(), p->getDisplay());
        _glContext.EnableVSYNC(false);
#elif SGE_TARGET_PLATFORM == SGE_PLATFORM_WIN32
        PlatformWin32Native* p = new PlatformWin32Native(0);
        _platform = p;
        _glContext.Init(p->getHWnd(), GetDC(p->getHWnd()), 0);
        _glContext.EnableVSYNC(false);
#endif
    }

    Application::~Application()
    {
        _glContext.Shutdown();
        if (_platform)
        {
            delete _platform;
            _platform = NULL;
        }
    }

    void Application::Run()
    {
        ASSERT(_platform);
        while (!_platform->IsClosed())
        {
            if (!_platform->ProcessEvents())
            {
                if (_curScene)
                {                   
                    _curScene->OnRender(this);
                    _glContext.SwapBuffer();
                }
            }
        }
    }

    void Application::LoadScene(Scene* scene)
    {
        Scene* oldScene = _curScene;
        if (scene)
        {
            scene->OnLoad(this);
        }
        _curScene = scene;

        if (oldScene)
        {
            oldScene->OnUnLoad(this);
            //TODO: check all oldScene resouces released.
            delete oldScene;
        }
    }

}