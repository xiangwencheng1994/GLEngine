/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeTextureManager.h
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

#ifndef SGE_TEXTURE_MANAGER_H
#define SGE_TEXTURE_MANAGER_H

#include <core/sgePlatform.h>
#include <core/sgeGLX.h>

namespace sge
{
    class   TextureManager;
    
    /**
     * The references texture2d
     */
    class SGE_API   Texture2DRef : public Texture2D
    {
    public:
        /**
         * Construtor while a null texture
         */
        Texture2DRef();

        /**
         * Destructor
         */
        ~Texture2DRef();

        /**
         * Copy constructor
         */
        Texture2DRef(const Texture2DRef& rhs);

        /**
         * Reset texture form rhs
         */
        Texture2DRef&   operator=(const Texture2DRef& rhs);

        /**
         * Destory object
         */
        void    destory();
    protected:
        friend class    TextureManager;
        TextureManager* _mgr;
        size_t*         _refCount;
    };

    /**
     * Class TextureManager
     */
    class SGE_API   TextureManager
    {
    public:
        /**
         * Constructor
         */
        TextureManager();

        /**
         * Destructor, will release all texture
         */
        ~TextureManager();

        /**
         * Load a texture form file
         */
        Texture2DRef    LoadTexture(const char* file);

    protected:
        friend class    Texture2DRef;
        void    removeTex(GLuint tex); // unload tex
        void    addRefItem(Texture2DRef* item); // add a item to manager
        void    removeRefItem(Texture2DRef* item); // remove item from nanager
    private:
        struct TextureDesc
        {
            String  file;
            vec2i   size;
            size_t  refCount;
        };
        Map<GLuint, TextureDesc>    _texRefMap;
        List<Texture2DRef*>         _items;
    };

}

#endif // !SGE_TEXTURE_MANAGER_H
