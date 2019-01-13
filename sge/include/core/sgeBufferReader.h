/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeBufferReader.h
 * date: 2018/05/30
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

#ifndef SGE_BUFFER_READER_H
#define SGE_BUFFER_READER_H

#include <core/sgePlatform.h>
#include <core/sgeSteamReader.h>

namespace sge
{

    /**
     * Class BufferReader inline, to help read the buffer
     */
    class BufferReader : public StreamReader
    {
    public:

        /**
         * Constructor
         * @param buffer The buffer pointer for read wanted 
         * @param len The buffer length
         */
        BufferReader(const byte* buffer, size_t len)
            : mBuffer(buffer), mLen(len), mCurPos(0)
        {
            ASSERT(buffer && "buffer can not be null");
        }


        /**
         * get the current cursor of file
         */
        size_t tell() override { return mCurPos; }

        /**
         * seek the cursor of buffer
         * @param offset The offset the pointer, if offset < 0 will seek on back
         * @param seek Must be SEEK_SET | SEEK_CUR | SEEK_END
         * @return true if seek success
         */
        bool seek(long offset, SeekOrigin seek) override
        {
            bool ret = true;
            long pos = 0;
            switch(seek)
            {
            case SeekOrigin::SEEK_SET:
                pos = offset;
                break;
            case SeekOrigin::SEEK_CUR:
                pos = offset + mCurPos;
                break;
            case SeekOrigin::SEEK_END:
                pos = offset + mLen;
                break;
            default:
                ret = false;
                break;
            }
            if (ret)
            {
                if (pos >= 0 && pos < mLen)
                {
                    mCurPos = (size_t)pos;
                }
                else
                {
                    ret = false;
                }
            }
            return ret;
        }

        /**
         * get the buffer length, count of bytes
         * @return the buffer length
         */
        size_t length() override { return mLen; }

        /**
         * Check the stream is eof
         * @return true if eof
         */
        bool isEOF() override
        {
            return mCurPos >= mLen;
        }

        /**
         * read bytes to buff for some elements
         * @param buff To output the bytes
         * @param elementSize Byte count for each element
         * @param elementCount The count of element wanted
         * @return The count of element has readed
         */
        size_t read(void* buff, size_t elementSize, size_t elementCount) override
        {
            ASSERT(buff && "read buff can not be null");
            size_t readCount = (mLen - mCurPos) / elementSize;
            if (readCount > elementCount) readCount = elementCount;
            if (readCount > 0)
            {
                size_t readSize = elementSize * readCount;
                memcpy(buff, mBuffer + mCurPos, readSize);
                mCurPos = readSize;
            }
            return readCount;
        }

        /**
         * read a line to buff
         * @param buff To output the bytes
         * @param bufferSize The max sizeof bytes
         * @return True if has readed success, but the max read count is bufferSize - 1
         */            
        bool getLine(char* buff, size_t bufferSize) override
        {
            if (mCurPos >= mLen)
                return false;
            
            size_t maxCount = bufferSize - 1;
            
            for (size_t i = 0; i < maxCount && mCurPos < mLen; ++i)
            {
                if (mBuffer[mCurPos] != '\n')
                {
                    buff[i] = mBuffer[mCurPos];
                    ++mCurPos;
                }
                else
                {
                    ++mCurPos;
                    buff[i] = '\0';
                    return true;
                }
            }
            buff[maxCount] = '\0';
            return true;
        }

        /**
         * Get the data pointer of buffer
         */
        const byte*   data() { return mBuffer; }

    private:
        const byte*     mBuffer;
        size_t          mCurPos;
        size_t          mLen;
        DISABLE_COPY(BufferReader)
    };

}

#endif //!SGE_BUFFER_READER_H
