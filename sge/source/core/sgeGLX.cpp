/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGLX.h
 * date: 2018/05/31
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

#include <core/sgeGLX.h>
#define STB_IMAGE_IMPLEMENTATION
#include <image/stb_image.h>

void glClearError()
{
    while (GLenum error = glGetError());
}

bool glCheckError(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        sge::Log::error("[GLError:%#04X]%s(%d) %s", error, file, line, function);
        return false;
    }
    return true;
}

namespace sge
{
    
    bool Texture2D::loadFromFile(const char* file)
    {
        ASSERT(file);
        bool ret = false;
        int comp = 0;
        byte* data = stbi_load(file, &mSize.x, &mSize.y, &comp, 0);
        if (data)
        {
            if (comp == 3) ret = loadFromRGB(data, mSize.x, mSize.y);
            else if (comp == 4) ret = loadFromRGBA(data, mSize.x, mSize.y);
            else
            {
                Log::error("cannot create texture from comp %d", comp);
            }
            stbi_image_free(data);
        }
        else
        {
            Log::error("stbi_load %s failed: %s", file, stbi_failure_reason());
        }
        return ret;
    }

    bool Texture2D::loadFromStream(byte* stream, size_t len)
    {
        ASSERT(stream);
        bool ret = false;
        int comp = 0;
        byte* data = stbi_load_from_memory(stream, len, &mSize.x, &mSize.y, &comp, 0);
        if (data)
        {
            if (comp == 3) ret = loadFromRGB(data, mSize.x, mSize.y);
            else if (comp == 4) ret = loadFromRGBA(data, mSize.x, mSize.y);
            else
            {
                Log::error("cannot create texture from comp %d", comp);
            }
            stbi_image_free(data);
        }
        else
        {
            Log::error("stbi_load_from_memory failed: %s", stbi_failure_reason());
        }
        return ret;
    }

    bool Texture2D::loadFromRGB(byte* data, int w, int h)
    {
        ASSERT(data);
        if (!isValid())
        {
            GLCall(glGenTextures(1, &mTexID));
            bind();
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        }
        else bind();
        mSize.x = w;
        mSize.y = h;
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        unbind();
        return true;
    }

    bool Texture2D::loadFromRGBA(byte* data, int w, int h)
    {
        ASSERT(data);
        if (!isValid())
        {
            GLCall(glGenTextures(1, &mTexID));
            bind();
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        }
        else bind();
        mSize.x = w;
        mSize.y = h;
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
        unbind();
        return true;
    }

}