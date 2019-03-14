/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeLibrary.cpp
 * date: 2018/11/14
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

#include <core/sgeLibrary.h>
#include <string.h>

namespace sge
{

    sgeLibrary::sgeLibrary(const char* file)
        : mModule(NULL), mNeedDelete(false)
    {
        strcpy(mPath, file);

#if (SGE_TARGET_PLATFORM == SGE_PLATFORM_WIN32)
        mModule =   LoadLibraryA(mPath);
#else
        mModule =   dlopen(mPath, RTLD_NOW);
#endif
    }

    sgeLibrary::~sgeLibrary()
    {
        unload();
    }

    sgeLibrary* sgeLibrary::load(const char* file)
    {
        sgeLibrary* lib = new sgeLibrary(file);
        lib->mNeedDelete = true;
        if (! lib->isLoaded())
        {
            lib->release();
            lib =   NULL;
        }
        return lib;
    }

    bool sgeLibrary::unload()
    {
        bool ret = true;
        if (mModule)
        {            
#if (SGE_TARGET_PLATFORM == SGE_PLATFORM_WIN32)
            ret = (TRUE == FreeLibrary(mModule));
#else
            dlclose(mModule); //TODO: check return            
#endif

            mModule =   NULL;
        }
        return ret;
    }

    void* sgeLibrary::getFunction(const char* funName)
    {
        if (NULL == mModule)
            return NULL;

#if (SGE_TARGET_PLATFORM == SGE_PLATFORM_WIN32)
        return GetProcAddress(mModule, funName);
#else
        return dlsym(mModule, funName);
#endif
    }

    void sgeLibrary::release()
    {
        if (mNeedDelete)
        {
            delete this;
        }
    }

}