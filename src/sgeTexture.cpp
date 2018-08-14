/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeTexture.cpp
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

#include <sgeTexture.h>
#include <sgeLog.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace sge
{
    GLuint SGE_API loadTexture2DFromFile(const char* filename, int* outW, int* outH)
    {
        assert(filename);
        int comp = 0;
        int width, height;
        byte* data = stbi_load(filename, &width, &height, &comp, 4);
        if (!data)
        {
            Log::error("stbi_load %s failed: %s", filename, stbi_failure_reason());
            return -1;
        }
        if (outW) *outW = width;
        if (outH) *outH = height;
        GLuint tex = loadTexture2DFromRGBA(data, width, height);
        stbi_image_free(data);
        return tex;
    }


    GLuint SGE_API loadTexture2DFromFile(byte* buffer, size_t len, int* outW, int* outH)
    {
        assert(buffer && len > 0);
        int comp = 0;
        int width, height;
        byte* data = stbi_load_from_memory(buffer, len, &width, &height, &comp, 4);
        if (!data)
        {
            Log::error("stbi_load_from_memory failed: %s", stbi_failure_reason());
            return -1;
        }
        if (outW) *outW = width;
        if (outH) *outH = height;
        GLuint tex = loadTexture2DFromRGBA(data, width, height);
        stbi_image_free(data);
        return tex;
    }

    GLuint SGE_API loadTexture2DFromRGBA(byte * data, int w, int h)
    {
        GLuint tex = 0;
        glGenTextures(1, &tex);
        assert(tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        return tex;
    }

    GLuint SGE_API loadTextureCubeFromFile(TexureCubeFile texFile)
    {
        int comp = 0;
        int width, height;
        GLuint tex;
        glEnable(GL_TEXTURE_CUBE_MAP);
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
        for (int i = 0; i < 6; ++i)
        { 
            byte* data = stbi_load(texFile.face[i], &width, &height, &comp, 3);
            if (!data)
            {
                Log::error("stbi_load %s failed: %s", texFile.face[i], stbi_failure_reason());
                continue;
            }
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        return tex;
    }
}