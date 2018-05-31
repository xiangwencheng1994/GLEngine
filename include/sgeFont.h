/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeFont.h
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

#ifndef SGE_FONT_H
#define SGE_FONT_H

#include <sge.h>
#include <sgeMath.h>

namespace sge
{
    class FontPrivate;

    /**
     * The Font character description struct
     */
    struct CharDesc
    {
        /**
         * The appearance part
         */
        struct CharBaseDesc
        {
            uint2   size;
            int2    bearing;
            uint    advance;
        } base;

        /**
         * The texture description of this character
         */
        struct CharTexDesc
        {
            uint    texId;
            uint2   texSize;
            float2  startUV;
            float2  endUV;
        } tex;

        /*
         * Constructor, set texture id invalid
         */
        CharDesc() { tex.texId = -1; }
    };

    /**
     * Class Font
     */
    class SGE_API  Font
    {
    public:
        /**
         * Constructor
         * @note this constructor make a null font
         */
        Font();

        /**
         * Constructor
         * @param file The font file supported by freetype2
         */
        Font(const char* file);

        /**
         * Copy Constructor
         * @param other The other font
         */
        Font(const Font &other);

        /**
         * Copy operator
         * @param rhs The right side font.
         */
        Font &operator=(const Font & rhs);

        /**
         * Destructor, relase this font.
         */
    	~Font();

        /**
         * Set the font size
         * @return false if set failed
         */
        bool setSize(int size);

        /**
         * Get font line height
         */
        uint lineHeight() const;

        /**
         * Get the character description from this font
         * @param ch The char
         */
        const CharDesc& getChar(const wchar_t ch);

        /**
         * Null test
         * @return true if font disabled
         */
        bool isNull();
    private:
        FontPrivate* d;
    };

}

#endif //!SGE_FONT_H