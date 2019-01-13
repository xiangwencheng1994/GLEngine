/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgePlatform.h
 * date: 2017/12/04
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

#ifndef SGE_PLATFORM_H
#define SGE_PLATFORM_H

#define SGE_PLATFORM_UNKNOWN    0
#define SGE_PLATFORM_WIN32      1
#define SGE_PLATFORM_ANDROID    2
#define SGE_PLATFORM_LINUX      3

#define SGE_TARGET_PLATFORM SGE_PLATFORM_UNKNOWN

// android
#if defined(ANDROID)
    #define SGE_ANDROID
    #define SGE_LINUX
    #undef  SGE_TARGET_PLATFORM
    #define SGE_TARGET_PLATFORM SGE_PLATFORM_ANDROID
#endif

// win32
#if defined(_WIN32) || defined(WIN32) || defined(_WINDOWS_)
    #define SGE_WIN32
    #undef  SGE_TARGET_PLATFORM
    #define SGE_TARGET_PLATFORM SGE_PLATFORM_WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    #undef WIN32_LEAN_AND_MEAN
#endif

// linux
#if defined(LINUX) || defined(__linux__) || defined(__linux)
    #define SGE_LINUX
    #undef  SGE_TARGET_PLATFORM
    #define SGE_TARGET_PLATFORM CC_PLATFORM_LINUX
#endif


// setup export and inport for win32
#ifdef SGE_WIN32
    #define SGE_EXPORT _declspec(dllexport)
    #define SGE_IMPORT _declspec(dllimport)
    #ifdef sge_EXPORTS
        #define SGE_API SGE_EXPORT
    #else
        #define SGE_API SGE_IMPORT
        #pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")
    #endif
#elif SGE_LINUX
#define SGE_API
#define SGE_EXPORT
#define SGE_IMPORT
#endif


// define ASSERT for debugger
#include <assert.h>
#define ASSERT(x)   assert(x)


// define GLCall for debugger
#ifdef _DEBUG
// from core/sgeGLX.h
SGE_API bool glCheckError(const char*, const char*, int);
SGE_API void glClearError();
// clear errors before call, check errors after call
#define GLCall(x)   glClearError();\
                    x;\
                    ASSERT(glCheckError(#x, __FILE__, __LINE__))
#else
#define GLCall(x)   x
#endif


// define disable copy object of Class
#define DISABLE_COPY(Class) \
		Class(const Class &) = delete; \
		Class &operator=(const Class &) = delete;

#include <string>
#include <vector>
#include <list>
#include <map>
#define String  std::string
#define Vector  std::vector
#define List    std::list
#define Map     std::map

#endif
