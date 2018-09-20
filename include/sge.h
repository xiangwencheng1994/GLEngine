/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sge.h
 * date: 2017/12/04
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

#ifndef SGE_H
#define SGE_H

#ifdef _WIN32
    #include <Windows.h>
    #if sge_EXPORTS
        #define SGE_API     _declspec(dllexport)
        #define GLEW_BUILD
    #else
        #define SGE_API     _declspec(dllimport)
        #pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")
    #endif
#else
    #define SGE_API
#endif

#include <glew/glew.h>

#ifdef _DEBUG
    #include <assert.h>
    #ifdef WIN32
        #define ASSERT(x)   if (!(x)) __debugbreak()
    #else
        #define ASSERT(x)   assert(x)
    #endif
#else
    #define ASSERT(x)   x
#endif

// from sgeGLX.h
SGE_API bool glCheckError(const char* function, const char* file, int line);
SGE_API void glClearError();

#ifdef _DEBUG
    // clear errors before call, check errors after call
    #define GLCall(x)   glClearError();\
                        x;\
                        ASSERT(glCheckError(#x, __FILE__, __LINE__))
#else
    #define GLCall(x)   x
#endif

// disable copy object of this class
#define DISABLE_COPY(Class) \
		Class(const Class &) = delete; \
		Class &operator=(const Class &) = delete;

#include <string>
#include <memory>
#define SharedPtr   std::shared_ptr 
#define ScopedPtr   std::scoped_ptr 
#define UniquePtr   std::unique_ptr 

#endif



