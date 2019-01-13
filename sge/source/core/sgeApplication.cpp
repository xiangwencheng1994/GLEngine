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
 * Copyright (c) 2017-2019, Xiang Wencheng <xiangwencheng@outlook.com>
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
#include <core/sgePlatformNative.h>
#include <core/sgeScene.h>
#include <core/sgeRenderer.h>
#include <core/sgeGLContext.h>
#include <core/sgeLog.h>

#if SGE_TARGET_PLATFORM == SGE_PLATFORM_WIN32
#include <win32/sgePlatformNativeWin32.h>
#endif // SGE_TARGET_PLATFORM

namespace sge
{

    class ApplicationPrivate
    {
    public:
        Scene*              mCurScene;
        PlatformWin32Native mPlatform;
        GLContext           mGLContext;
        Renderer*           mRenderer;

        ApplicationPrivate()
            : mCurScene(NULL)
            , mPlatform(0, 800, 600)
            , mRenderer(NULL)
        {}

        ~ApplicationPrivate()
        {
            ASSERT(mCurScene == NULL && "not released");
            ASSERT(mRenderer == NULL && "not released");
        }
    };


    Application::Application()
        : d(new ApplicationPrivate())
    {        
        bool ret = d->mGLContext.initialize(d->mPlatform.getWindow(), 0, 0);
        if (!ret)
        {
            Log::error("Application init gl context failed");
        }
        d->mGLContext.setEnableVSYNC(false);
        d->mRenderer = new Renderer();
        d->mPlatform.mOnCloseEvent.bind<Application>(this, &Application::onClose);
        
        // load fonts
        d->mRenderer->loadFont("default", "fonts/YaHei.Consolas.ttf");
    }


    Application::~Application()
    {
        if (d)
        {
            if (d->mCurScene)
            {
                loadScene(NULL);
            }
            if (d->mRenderer)
            {
                delete d->mRenderer;
                d->mRenderer = NULL;
            }
            delete d;
            d = NULL;
        }
    }


    void Application::run()
    {
        while (!d->mPlatform.isClosed())
        {
            if (!d->mPlatform.processEvents())
            {
                if (d->mCurScene)
                {
                    d->mCurScene->onRender();
                    d->mGLContext.swapBuffer();
                }
            }
        }
    }


    void Application::loadScene(Scene* scene)
    {        
        Scene* oldScene = d->mCurScene;
        if (scene)
        {
            scene->onLoad();
        }
        d->mCurScene = scene;

        if (oldScene)
        {
            oldScene->onUnLoad();
            //TODO: check all oldScene resouces released.
            oldScene->release();
        }
    }


    void Application::quit()
    {
        if (getPlatform()->isClosed())
        {
            getPlatform()->close();
        }
    }

    inline bool Application::onClose()
    {
        // unload the scene
        loadScene(NULL);
        return false;
    }

    inline PlatformNative * Application::getPlatform() { return &d->mPlatform; }
    
    inline Renderer * Application::getRenderer() { return d->mRenderer; }

    inline Scene * Application::getCurrentScene() { return d->mCurScene; }

}