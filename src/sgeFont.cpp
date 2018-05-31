/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeFont.cpp
 * date: 2018/01/09
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

#include <sgeFont.h>
#include <sgeLog.h>
#include <ft2build.h>
/* if you can not find this file, maybe you not install the freetype2 lib */
#include FT_FREETYPE_H

#include <glew/glew.h>

namespace sge
{
    static FT_Library ft = NULL;
    static unsigned int ftRef = 0;

    #define MAX_CHARACTER   (1 << 16) 

    class FontPrivate
    {
        FT_Face face;
        uint    height;
        CharDesc   chars[MAX_CHARACTER];

        uint    curTex;
        uint2   offset;
        uint2   max;

        size_t  sharedRef;

        friend class Font;
        FontPrivate(const char* file) : face(NULL), height(0), curTex(-1), offset(0, 0), max(1024, 1024), sharedRef(1)
        {
            FT_Error ret;
            if (NULL == ft)
            {
                ret = FT_Init_FreeType(&ft);
                if (ret)
                {
                    Log::error("FT_Init_FreeType failed ret = %d", ret);
                    assert("FT_Init_FreeType failed");
                }
            }

            ++ftRef;

            ret = FT_New_Face(ft, file, 0, &face);
            if (ret)
            {
                Log::error("FT_New_Face failed ret = %d : %s", ret, file);
                assert("FT_New_Face failed");
            }
        }
        ~FontPrivate()
        {
            if (face)
            {
                FT_Done_Face(face);
                face = NULL;
            }
            --ftRef;
            if (ftRef == 0 && ft)
            {
                FT_Done_FreeType(ft);
                ft = NULL;
            }
        }
    };

    Font::Font()
        : d(NULL)
    {
    }

    Font::Font(const char* file)
        : d(new FontPrivate(file))
    {
    }

    Font::Font(const Font & other)
    {
        d = other.d;
        ++d->sharedRef;
    }

    Font & Font::operator=(const Font & rhs)
    {
        if (d && --d->sharedRef <= 0)
        {
            delete d;
            d = NULL;
        }
        d = rhs.d;
        ++d->sharedRef;
        return *this;
    }

    Font::~Font()
    {
        if (d && --d->sharedRef <= 0)
        {
            delete d;
            d = NULL;
        }
    }

    bool Font::setSize(int size)
    {
        bool ret = true;
        FT_Error fterror = FT_Set_Char_Size(d->face, 0, size << 6, 96, 96);
        if (fterror)
        {
            Log::error("FT_Set_Char_Size(%p, %d) failed", d->face, size);
            ret = false;
        }
        uint height = d->face->size->metrics.height >> 6;
        if (height != d->height)    // should update all text
        {
            for (int i = 0; i < MAX_CHARACTER; ++i)
            {
                uint tex = d->chars[i].tex.texId;
                d->chars[i].tex.texId = -1;
                if (glIsTexture(tex))
                {
                    glDeleteTextures(1, &tex);
                }
            }
            d->curTex = -1;
        }
        return ret;
    }

    uint Font::lineHeight() const
    {
        return d->height;
    }

    const CharDesc& Font::getChar(const wchar_t ch)
    {
        CharDesc&   desc = d->chars[ch];
        if (desc.tex.texId == -1)
        {
            FT_Error error = FT_Load_Char(d->face, ch, FT_LOAD_RENDER);
            if (error)
            {
                Log::error("FT_Load_Char failed ret = %d : %x", error, ch);
                assert("FT_Load_Char failed");
            }
            desc.base.size.x = d->face->glyph->bitmap.width;
            desc.base.size.y = d->face->glyph->bitmap.rows;
            desc.base.bearing.x = d->face->glyph->bitmap_left;
            desc.base.bearing.y = d->face->glyph->bitmap_top;
            desc.base.advance = d->face->glyph->advance.x >> 6;

            /// calc pos rightbottem pos
            if ((d->offset.x + desc.base.size.x) >= d->max.x) // move to next row
            {
                d->offset.x = 0;
                d->offset.y += d->height + 1;
            }

            if ((d->offset.y + d->height) >= d->max.y || d->curTex == -1) // should new tex
            {
                d->offset.y = 0;
                glGenTextures(1, &d->curTex);
                glBindTexture(GL_TEXTURE_2D, d->curTex);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, d->max.x, d->max.y, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, d->curTex);
            }

            if (d->face->glyph->bitmap.width != 0 && d->face->glyph->bitmap.rows != 0)
            {
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    d->offset.x, d->offset.y,
                    d->face->glyph->bitmap.width, d->face->glyph->bitmap.rows,
                    GL_RED, GL_UNSIGNED_BYTE,
                    d->face->glyph->bitmap.buffer);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
            }

            desc.tex.texId = d->curTex;
            desc.tex.texSize = d->max;
            desc.tex.startUV.x = (float)d->offset.x / (float)d->max.x;
            desc.tex.startUV.y = (float)d->offset.y / (float)d->max.y;
            desc.tex.endUV.x = (float)(d->offset.x + desc.base.size.x) / (float)d->max.x;
            desc.tex.endUV.y = (float)(d->offset.y + desc.base.size.y) / (float)d->max.y;

            d->offset.x += desc.base.size.x + 1;
        }
        return desc;
    }

    bool Font::isNull()
    {
        return ! (d && d->face);
    }

}