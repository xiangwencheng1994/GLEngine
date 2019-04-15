/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeFileReader.h
 * date: 2018/5/30
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

#ifndef SGE_FILE_READER_H
#define SGE_FILE_READER_H

#include <core/sgePlatform.h>
#include <core/sgeSteamReader.h>

namespace sge
{

    /**
     * Class FileReader inline, to help read the file
     */
    class FileReader : public StreamReader
    {
    public:
        /**
         * Constructor
         * @param fileName The fileName for open wanted 
         * @param ret The result of open the file
         */
        FileReader(const char* fileName, bool* ret)
        {
            errno_t error = fopen_s(&_file, fileName, "rb");
            if (ret)
            {
                *ret = (error == 0);
            }
            else
            {
                ASSERT(error == 0);
            }
        }

        /**
         * Destructor, release the file handle
         */
        ~FileReader()
        {
            if (_file)
            {
                fclose(_file);
                _file = NULL;
            }
        }

        /**
         * get the current cursor of file
         */
        size_t tell() override { return ftell(_file); }

        /**
         * seek the cursor of file
         * @param offset The offset the pointer, if offset < 0 will seek on back
         * @param seek Must be SEEK_SET | SEEK_CUR | SEEK_END
         * @return true if seek success
         */
        bool seek(long offset, SeekOrigin seek) override { return 0 == fseek(_file, offset, seek); }

        /**
         * get the file length, count of bytes
         * @return the file length, error while return = unsigned(-1)
         */
        size_t length() override
        {
            size_t ret = unsigned(-1);
            size_t cur = tell();
            if (seek(0, SeekSet))
            {
                if (seek(0, SeekEnd)) ret = tell();
                seek(cur, SeekSet);
            }
            return ret;
        }
        
        /**
         * Check the stream is eof
         * @return true if eof
         */
        bool isEOF() override
        {
            return 0 != feof(_file);
        }

        /**
         * read bytes to buff for some elements
         * @param buff To output the bytes
         * @param elementSize Byte count for each element
         * @param elementCount The count of element wanted
         * @return The count of element has readed, error while return > elementCount
         */
        size_t read(void* buff, size_t elementSize, size_t elementCount)  override
        {
            return fread(buff, elementSize, elementCount, _file);
        }
        
        /**
         * read a line to buff
         * @param buff To output the bytes
         * @param bufferSize The max sizeof bytes
         * @return True if has readed success, but the max read count is bufferSize - 1
         */
        bool getLine(char* buff, size_t bufferSize) override
        {
            return fgets(buff, (int)bufferSize, _file) != NULL;
        }

    private:
        FILE*       _file;
        DISABLE_COPY(FileReader)
    };

}

#endif //!SGE_FILE_READER_H
