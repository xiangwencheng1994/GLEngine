/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeScene.h
 * date: 2018/12/04
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

#ifndef SGE_SCENE_H
#define SGE_SCENE_H

#include <core/sgePlatform.h>
#include <core/sgePlatformNative.h>
#include <core/sgeRefPtr.h>

namespace sge
{
    class Application;

    namespace ui
    {
        class View;
    }

    /**
     * Class scene, execute by Application
     * @note must use 'new' method to create instance, it will be deleted after unload.
     */
    class SGE_API Scene
    {
    public:
        /**
         * Constructor
         */
        explicit Scene(Application* app_not_null);
        
        /**
         * Destructor
         */
        virtual ~Scene();

        /**
         * Get the background brush color
         */
        const float4& getBrushColor();

        /**
         * Set the background brush color
         */
        void setBrushColor(const float4& color);

        /**
         *  Set root view
         */
        void setRootView(RefPtr<ui::View> view);

        /**
         * Get root view
         */
        RefPtr<ui::View> getRootView();

        /**
         * Get the context
         */
        Application* getApplicaton();

    protected:

        /**
         * Load the base scene
         */
        virtual void onLoad();

        /**
         * Unload the base scene
         */
        virtual void onUnLoad();

        /**
         * Render the base scene
         */
        void onRender();
        
        /**
         * Callback while need render models
         */
        virtual void onRenderModel();

        /**
         * Callback while need render ui
         */
        virtual void onRenderUI();

        /**
         * Callback while mouse left button down
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onLeftButtonDownEvent(const MouseDownEvent& event);

        /**
         * Callback while mouse left button up
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onLeftButtonUpEvent(const MouseUpEvent& event);

        /**
         * Callback while mouse left button click
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onLeftButtonClickEvent(const MouseClickEvent& event);

        /**
         * Callback while mouse right button down
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onRightButtonDownEvent(const MouseDownEvent& event);

        /**
         * Callback while mouse right button up
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onRightButtonUpEvent(const MouseUpEvent& event);

        /**
         * Callback while mouse right button click
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onRightButtonClickEvent(const MouseClickEvent& event);

        /**
         * Callback while mouse middle button down
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onMiddleButtonDownEvent(const MouseDownEvent& event);

        /**
         * Callback while mouse middle button up
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onMiddleButtonUpEvent(const MouseUpEvent& event);

        /**
         * Callback while mouse middle button click
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onMiddleButtonClickEvent(const MouseClickEvent& event);

        /**
         * Callback while mouse move
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onMouseMoveEvent(const MouseMoveEvent& event);

        /**
         * Callback while mouse wheel wheeled
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onMouseWheelEvent(const MouseWheelEvent& event);

        /**
         * Callback while key down
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onKeyDownEvent(const KeyDownEvent& event);

        /**
         * Callback while key up
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onKeyUpEvent(const KeyUpEvent& event);

        /**
         * Callback while wanted set size
         * @param event The event data
         * @return true if you has processed this event
         */
        virtual bool onResizeEvent(const ResizeEvent& event);

        /**
         * Release this object
         */
        virtual void release();

    private:
        friend class Application;
        friend class ScenePrivate;
        ScenePrivate* d;
    };

}

#endif // !SGE_SCENE_H
