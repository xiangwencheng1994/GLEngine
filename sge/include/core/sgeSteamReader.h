/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeSteamReader.h
 * date: 2018/5/30
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

#ifndef SGE_STEAM_READER_H
#define SGE_STEAM_READER_H

#include <sge.h>
#include <sgeMath.h>

#ifndef SEEK_SET
#   define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#   define SEEK_CUR 1
#endif
#ifndef SEEK_END
#   define SEEK_END 2
#endif

namespace sge
{

    /**
     * Class StreamReader
     */
    class StreamReader
    {
    public:
        /**
         * virtual destructor to release object
         */
        virtual ~StreamReader(){};

        /**
         * get the current cursor offset from SEEK_SET
         */
        virtual size_t Tell() = 0;

        /**
         * seek the cursor
         * @param offset The offset the pointer, if offset < 0 will seek on back
         * @param seek Must be SEEK_SET | SEEK_CUR | SEEK_END
         * @return true if seek success
         */
        virtual bool Seek(long offset, int seek) = 0;

        /**
         * get the stream length, count of bytes
         * @return the stream length, error while return = unsigned(-1)
         */
        virtual size_t Length() = 0;

        /**
         * Check the stream is eof
         * @return true if eof
         */
        virtual bool IsEOF() = 0;

        /**
         * read bytes to buff for some elements
         * @param buff To output the bytes
         * @param elementSize Byte count for each element
         * @param elementCount The count of element wanted
         * @return The count of element has readed, error while return > elementCount
         */
        virtual size_t Read(void* buff, size_t elementSize, size_t elementCount) = 0;

        /**
         * read a line to buff
         * @param buff To output the bytes
         * @param bufferSize The max sizeof bytes
         * @return True if has readed success, but the max read count is bufferSize - 1
         */            
        virtual bool GetLine(char* buff, size_t bufferSize) = 0;

        /**
         * read a struct data
         * @param out The output object
         * @return true if read success
         */
        template<typename T> bool Read(T& out) { return 1 == read(&out, sizeof(T), 1); }

        /**
         * read all  data as text
         */
        virtual std::string ReadAll() 
        {
            size_t len = Length();
            std::string data(len, 0);
            len = Read((void*)data.c_str(), len, 1);
            assert(len == 1);
            return data;
        }
    };


}

#endif //!SGE_STEAM_READER_H
