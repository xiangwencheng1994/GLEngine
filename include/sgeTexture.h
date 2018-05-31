/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeTexture.h
 * date: 2017/12/21
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

#ifndef SGE_TEXTURE_H
#define SGE_TEXTURE_H

#include <sge.h>
#include <glew/glew.h>

namespace sge
{
    /**
     * Load 2D Texture from file
     * @param filename The file
     * @param outW Where output the image width, can be NULL
     * @param outH where output the image height, can be NULL
     * @return the Texture Id, return 0 if failed
     */
    GLuint SGE_API loadTexture2DFromFile(const char* filename, int* outW = NULL, int* outH = NULL);
    
    /**
     * Load 2D Texture from buffered file
     * @param buffer The buffer
     * @param len The buffer length
     * @param outW Where output the image width, can be NULL
     * @param outH where output the image height, can be NULL
     * @return the Texture Id, return 0 if failed
     */
    GLuint SGE_API loadTexture2DFromFile(byte* buffer, size_t len, int* outW = NULL, int* outH = NULL);
    
    /**
     * Load 2D Texture from a RGBA buffer
     * @param data The buffer data
     * @param w The image width
     * @param h The image height
     * @return the Texture Id, return 0 if failed
     */
    GLuint SGE_API loadTexture2DFromRGBA(byte* data, int w, int h);

    /**
     * Description for cube texture file
     */
    struct TexureCubeFile
    {
        // order: PX,NX, PY, NY, PZ, NZ
        const char* face[6];
    };

    /**
     * Load Cube Texture from files
     * @param texFile The cube file description
     * @return the Texture Id, return 0 if failed
     */
    GLuint SGE_API loadTextureCubeFromFile(TexureCubeFile texFile);
}

#endif //!SGE_TEXTURE_H