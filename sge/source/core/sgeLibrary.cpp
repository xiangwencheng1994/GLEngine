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

#include <core/sgeLibrary.h>

namespace sge
{

    sgeLibrary::sgeLibrary(const char* file)
        : _module(NULL), _needDelete(false)
    {
        strcpy_s(_path, file);

#if (CELL_PLATFORM == CELL_PLATFORM_WIN32)
        _module =   LoadLibraryA(_path);
#else
        _module =   dlopen(_path, RTLD_NOW);
#endif
    }

    sgeLibrary::~sgeLibrary()
    {
        unload();
    }

    sgeLibrary* sgeLibrary::load(const char* file)
    {
        sgeLibrary* lib = new sgeLibrary(file);
        lib->_needDelete = true;
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
        if (_module)
        {            
#if (CELL_PLATFORM == CELL_PLATFORM_WIN32)
            ret = (TRUE == FreeLibrary(_module));
#else
            dlclose(_module); //TODO: check return            
#endif

            _module =   NULL;
        }
        return ret;
    }

    void* sgeLibrary::getFunction(const char* funName)
    {
        if (NULL == _module)
            return NULL;

#if (CELL_PLATFORM == CELL_PLATFORM_WIN32)
        return GetProcAddress(_module, funName);
#else
        return dlsym(_module, funName);
#endif
    }

    void sgeLibrary::release()
    {
        if (_needDelete)
        {
            delete this;
        }
    }

}