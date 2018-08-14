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

#ifndef SGE_FILE_READER_H
#define SGE_FILE_READER_H

#include <sge.h>
#include <sgeSteamReader.h>

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
            _file = fopen(fileName, "rb");
            if (ret) *ret = (NULL != _file);
            else assert(NULL != _file);
        }

        /**
         * Destructor, release the file handle
         */
        ~FileReader()
        {
            if (_file) fclose(_file);
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
        bool seek(long offset, int seek) override { return 0 == fseek(_file, offset, seek); }

        /**
         * get the file length, count of bytes
         * @return the file length, error while return = unsigned(-1)
         */
        size_t length() override
        {
            size_t ret = unsigned(-1);
            size_t cur = tell();
            if (seek(0, SEEK_SET))
            {
                if (seek(0, SEEK_END)) ret = tell();
                seek(cur, SEEK_SET);
            }
            return ret;
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
        
    private:
        FILE*       _file;
        DISABLE_COPY(FileReader)
    };

}

#endif //!SGE_FILE_READER_H
