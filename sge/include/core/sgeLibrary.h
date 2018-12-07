/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeLibrary.h
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


#ifndef SGE_LIBRARY_H
#define SGE_LIBRARY_H

#include <core/sgePlatform.h>
#include <string>

#if (SGE_TARGET_PLATFORM != SGE_PLATFORM_WIN32)
#include <dlfcn.h>
typedef void*   HMODULE;
#endif

namespace sge
{

    /**
     *  ��̬���ӿ�
     */
    class SGE_API sgeLibrary
    {
    public:
        sgeLibrary(const char* file);
        ~sgeLibrary();

        /**
         *  ����һ����̬���ӿ�
         * @return ʧ�ܷ���NULL
         */
        static sgeLibrary* load(const char* file);
        
        /**
         *  ��ȡ���ļ�·��
         */
        const char* getPathName() { return _path; }

        /**
         *  ��ȡ����
         */
        HMODULE  getModule() { return _module; }

        /**
         *  �жϿ��Ƿ���سɹ�
         */
        bool     isLoaded() { return getModule() != 0; }

        /**
         *  ж�ؿ�
         */
        bool            unload();

        /**
         *  ���Һ���
         */
        void*           getFunction(const char* funName);

        /**
         *  �ͷ��Լ�
         */
        void            release();
    private:
        char            _path[MAX_PATH];
        HMODULE         _module;
        bool            _needDelete;

        DISABLE_COPY(sgeLibrary)
    };

}

#endif // !CELL_LIBRARY_H