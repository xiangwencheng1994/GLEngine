/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeContext.h
 * date: 2019/03/28
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

#ifndef SGE_CONTEXT_H
#define SGE_CONTEXT_H

#include <core/sgePlatform.h>
#include <core/sgeMath.h>

namespace sge
{
    class   Application;
    class   GUIRenderer;
    class   TextureManager;
    class   ShaderManager;

    struct SGE_API Context
    {
    public:
        Application*    app() const { return _app; }
        GUIRenderer*    guiRenderer() const { return _guiRenderer; }
        TextureManager* textureManager() const { return _textureManager; }
        ShaderManager*  shaderManager() const { return _shaderManager; }
        int             frameBufferWidth() const { return _frameBufferWidth; }
        int             frameBufferHeight() const { return _frameBufferHeight; }
        double          frameTime() const { return _frameTime; }

    protected:
        Application*    _app;
        GUIRenderer*    _guiRenderer;
        TextureManager* _textureManager;
        ShaderManager*  _shaderManager;
        int             _frameBufferWidth;
        int             _frameBufferHeight;
        double          _frameTime;
        
    protected:

        friend class Application;
        
        Context()
            : _app(NULL)
            , _guiRenderer(NULL)
            , _textureManager(NULL)
            , _shaderManager(NULL)
            , _frameBufferWidth(0)
            , _frameBufferHeight(0)
            , _frameTime(0)
        {}

        ~Context()
        {
            ASSERT(_app == NULL);
            ASSERT(_guiRenderer == NULL);
            ASSERT(_textureManager == NULL);
            ASSERT(_shaderManager == NULL);
        }
    };

}

#endif // !SGE_CONTEXT_H
