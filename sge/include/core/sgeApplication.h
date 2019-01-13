/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * Application.h
 * date: 2018/11/23
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

#ifndef SGE_APP_BASE_H
#define SGE_APP_BASE_H

#include <core/sgePlatform.h>

namespace sge
{
    class Scene;
    class PlatformNative;
    class Renderer;
    class GLContext;   

    /**
     * Class Application, to drive the application system
     */
    class SGE_API  Application
    {
    public:

        /**
         * Constructor
         */
        Application();


        /**
         * Destructor
         */
        virtual ~Application();


        /**
         * Get the native platform interface
         */
        PlatformNative* getPlatform();


        /**
         * Get the gui renderer
         */
        Renderer* getRenderer();

        /**
         * Get the current scene
         */
        Scene* getCurrentScene();


        /**
         * Load a scene instead of current scene, old scene will unloaded and deleted
         * @param scene The new scene
         */
        void loadScene(Scene* scene);


        /**
         * Run the application util quit
         */
        void run();


        /**
         * Send a quit message to platform
         */
        void quit();

    protected:

        /**
         * Callback on get close event
         * @return true if you dont want to close
         */
        virtual bool onClose();

    private:
        friend class ApplicationPrivate;
        ApplicationPrivate  *d;
        DISABLE_COPY(Application)
    };

}

#endif // !SGE_APP_BASE_H
