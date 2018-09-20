/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeUtils.h
 * date: 2018/8/20
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

#ifndef SGE_UTILS_H
#define SGE_UTILS_H

#include <sge.h>
#include <string>
#include <io.h>

namespace sge
{
    
    class SGE_API  Util
    {
    public:

        static bool IsAbsolutePath(const char* file)
        {
            return file[0] == '/' || strchr(file, ':') != NULL;
        }

        static std::string GetFileDir(std::string file)
        {
            size_t lastSplit = file.find_last_of("/\\");
            if (lastSplit != file.npos)
            {
                return file.substr(0, lastSplit);
            }
            return ".";
        }

        static void GetAllFiles(std::string path, std::vector<std::string>& files, const char* subffix = "")
        {
            long  hFile = 0;
            struct _finddata_t fileinfo;
            std::string p;
            if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
            {
                do
                {
                    if ((fileinfo.attrib & _A_SUBDIR))
                    {
                        if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                        {
                            GetAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
                        }
                    }
                    else
                    {
                        int startPos = strlen(fileinfo.name) - strlen(subffix);
                        if (0 == stricmp(fileinfo.name + startPos, subffix))
                        {
                            files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                        }
                    }
                } while (_findnext(hFile, &fileinfo) == 0);
                _findclose(hFile);
            }
        }

    private:
        Util() = delete;
        DISABLE_COPY(Util)
    };

}

#endif
