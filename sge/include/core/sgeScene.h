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

#include <core/sgeContext.h>

namespace sge
{

    /**
     * Class scene, execute by Application
     * @note must use 'new' method to create instance, it will be deleted after unload.
     */
    class SGE_API   Scene
    {
    public:
        /**
         * Constructor
         */
        explicit    Scene();
        
        /**
         * Destructor
         */
        virtual     ~Scene() {}

        /**
         * Get the background brush color
         */
        const vec4f& getBrushColor() { return _brushColor; }

        /**
         * Set the background brush color
         */
        void    setBrushColor(const vec4f& color) { _brushColor = color; }

    protected:

        /**
         * Load the base scene
         */
        virtual void    onLoad(Context& context) {}

        /**
         * Unload the base scene
         */
        virtual void    onUnLoad(Context& context) {}

        /**
         * Render the base scene
         */
        void    onRender(Context& context);
        
        /**
         * Callback while need render models
         */
        virtual void    onRenderModel(Context& context);

        /**
         * Callback while need render ui
         */
        virtual void    onRenderUI(Context& context);

        /**
         * Release this object
         * delete this by default
         */
        virtual void    release() { delete this; }

        virtual void    onResizeEvent(int w, int h);
        virtual void    onKeyEvent(int key, int scancode, int action, int mods);
        virtual void    onMouseButtonEvent(int button, int action, int mods);
        virtual void    onMouseMoveEvent(double x, double y);
        virtual void    onMouseScrollEvent(double dx, double dy);
        virtual bool    onCloseEvent();

        friend class    Application;
    private:
        vec4f               _brushColor;
    };

}

#endif // !SGE_SCENE_H
