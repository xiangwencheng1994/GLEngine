/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeScene.cpp
 * date: 2018/12/08
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

#include <core/sgeScene.h>
#include <core/sgeApplication.h>
#include <core/sgeRenderer.h>
#include <ui/sgeView.h>
#include <ui/sgeViewGroup.h>
#include <core/sgeTimer.h>

namespace sge
{
    class ScenePrivate
    {
    public:
        Application*        mApp;
        RefPtr<ui::View>    mDecor;
        int2                mSize;
        float4              mBrushColor;

        ScenePrivate(Application* app)
            : mApp(app)
            , mDecor(NULL)
            , mSize(1, 1)
            , mBrushColor(0.2f, 0.2f, 0.2f, 1.0f)
        {}

        ~ScenePrivate()
        {
        }
    };

    Scene::Scene(Application* app_not_null)
        : d(new ScenePrivate(app_not_null))
    {
        ASSERT(app_not_null && "can not be null");
    }

    Scene::~Scene()
    {
        if (d)
        {
            delete d;
            d = NULL;
        }
    }

    inline const float4 & Scene::getBrushColor() { return d->mBrushColor; }

    inline void Scene::setBrushColor(const float4 & color) { d->mBrushColor = color; }

    void Scene::onLoad()
    {
        PlatformNative* platform = d->mApp->getPlatform();
        ResizeEvent event = { platform->getWindowSize() };
        onResizeEvent(event);
        platform->mOnLeftButtonDownEvent.bind<Scene>(this, &Scene::onLeftButtonDownEvent);
        platform->mOnLeftButtonUpEvent.bind<Scene>(this, &Scene::onLeftButtonUpEvent);
        platform->mOnLeftButtonClickEvent.bind<Scene>(this, &Scene::onLeftButtonClickEvent);
        platform->mOnRightButtonDownEvent.bind<Scene>(this, &Scene::onRightButtonDownEvent);
        platform->mOnRightButtonUpEvent.bind<Scene>(this, &Scene::onRightButtonUpEvent);
        platform->mOnRightButtonClickEvent.bind<Scene>(this, &Scene::onRightButtonClickEvent);
        platform->mOnMiddleButtonDownEvent.bind<Scene>(this, &Scene::onMiddleButtonDownEvent);
        platform->mOnMiddleButtonUpEvent.bind<Scene>(this, &Scene::onMiddleButtonUpEvent);
        platform->mOnMiddleButtonClickEvent.bind<Scene>(this, &Scene::onMiddleButtonClickEvent);
        platform->mOnMouseMoveEvent.bind<Scene>(this, &Scene::onMouseMoveEvent);
        platform->mOnMouseWheelEvent.bind<Scene>(this, &Scene::onMouseWheelEvent);
        platform->mOnKeyDownEvent.bind<Scene>(this, &Scene::onKeyDownEvent);
        platform->mOnKeyUpEvent.bind<Scene>(this, &Scene::onKeyUpEvent);
        platform->mOnResizeEvent.bind<Scene>(this, &Scene::onResizeEvent);
    }

    void Scene::onUnLoad()
    {
        PlatformNative* platform = d->mApp->getPlatform();
        platform->mOnLeftButtonDownEvent.bind(NULL);
        platform->mOnLeftButtonUpEvent.bind(NULL);
        platform->mOnLeftButtonClickEvent.bind(NULL);
        platform->mOnRightButtonDownEvent.bind(NULL);
        platform->mOnRightButtonUpEvent.bind(NULL);
        platform->mOnRightButtonClickEvent.bind(NULL);
        platform->mOnMiddleButtonDownEvent.bind(NULL);
        platform->mOnMiddleButtonUpEvent.bind(NULL);
        platform->mOnMiddleButtonClickEvent.bind(NULL);
        platform->mOnMouseMoveEvent.bind(NULL);
        platform->mOnMouseWheelEvent.bind(NULL);
        platform->mOnKeyDownEvent.bind(NULL);
        platform->mOnKeyUpEvent.bind(NULL);
        platform->mOnResizeEvent.bind(NULL);
    }

    void Scene::onRender()
    {
        glClearColor(d->mBrushColor.x, d->mBrushColor.y, d->mBrushColor.z, d->mBrushColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, d->mSize.x, d->mSize.y);

        // draw models
        onRenderModel();

        // draw ui
        Renderer* renderer = d->mApp->getRenderer();
        renderer->beginFrame((float)d->mSize.x, (float)d->mSize.y);
        onRenderUI();
        renderer->endFrame();
    }

    void Scene::onRenderModel()
    {
    }

    void Scene::onRenderUI()
    {
        Renderer* renderer = d->mApp->getRenderer();
        if (d->mDecor.get())
        {
            // do measure the gui
            d->mDecor->doMeasure(ui::UNSPECIFIED, d->mSize.x, ui::UNSPECIFIED, d->mSize.y);
            // do layout the gui
            RefPtr<ui::LayoutParams> params = d->mDecor->getLayoutParams();
            int measuredWidth = d->mDecor->getMeasuredWidth();
            int measuredHeight = d->mDecor->getMeasuredHeight();
            d->mDecor->doLayout(0, 0, measuredWidth, measuredHeight);
            // do draw the gui
            d->mDecor->doDraw(renderer);
        }

#ifdef _DEBUG
        static Timer timer;
        float t = timer.elapsed();
        char fpsStr[256];
        sprintf(fpsStr, "FPS:%4.1f", 1.0f / t);
        renderer->setFont("default");
        renderer->setFontSize(24);
        renderer->setTextAlign(Alignment::TopLeft);
        renderer->setFillColor(0.0f, 1.0f, 0.0f, 1.0f);
        renderer->drawText(10, 10, fpsStr, NULL);
#endif // _DEBUG

    }

    inline void Scene::setRootView(RefPtr<ui::View> view) 
    {
        if (view.get())
        {
            if (!view->getLayoutParams().get())
            {
                RefPtr<ui::LayoutParams> param(new ui::LayoutParams(MATCH_PARENT, MATCH_PARENT));
                view->setLayoutParams(param);
            }
        }
        d->mDecor = view;
    }

    inline RefPtr<ui::View> Scene::getRootView() { return d->mDecor; }

    inline Application * Scene::getApplicaton() { return d->mApp; }

    bool Scene::onLeftButtonDownEvent(const MouseDownEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onLeftButtonDownEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onLeftButtonUpEvent(const MouseUpEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onLeftButtonUpEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onLeftButtonClickEvent(const MouseClickEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onLeftButtonClickEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onRightButtonDownEvent(const MouseDownEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onRightButtonDownEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onRightButtonUpEvent(const MouseUpEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onRightButtonUpEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onRightButtonClickEvent(const MouseClickEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onRightButtonClickEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onMiddleButtonDownEvent(const MouseDownEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onMiddleButtonDownEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onMiddleButtonUpEvent(const MouseUpEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onMiddleButtonUpEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onMiddleButtonClickEvent(const MouseClickEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onMiddleButtonClickEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onMouseMoveEvent(const MouseMoveEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onMouseMoveEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onMouseWheelEvent(const MouseWheelEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onMouseWheelEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onKeyDownEvent(const KeyDownEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onKeyDownEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onKeyUpEvent(const KeyUpEvent & event)
    {
        if (d->mDecor.get() && d->mDecor->onKeyUpEvent(event))
        {
            return true;
        }
        return false;
    }

    bool Scene::onResizeEvent(const ResizeEvent & event)
    {
        bool widthChanged = d->mSize.x != event.size.x;
        bool heightChanged = d->mSize.y != event.size.y;
        d->mSize = event.size;
        if (d->mDecor.get())
        {
            RefPtr<ui::LayoutParams> params = d->mDecor->getLayoutParams();
            if ((widthChanged && params->mWidth == MATCH_PARENT)
                || (heightChanged && params->mHeight == MATCH_PARENT))
            {
                d->mDecor->requestMeasure();
                d->mDecor->doLayout(0, 0, d->mSize.x, d->mSize.y);
            }
        }
        return true;
    }

    void Scene::release()
    {
    }

}