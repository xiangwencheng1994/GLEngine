/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGlobalResources.h
 * date: 2018/9/5
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

#ifndef GLOBAL_RESOURCES_H
#define GLOBAL_RESOURCES_H

#include <sgeGLApp.h>
#include <sgeGLSLUtil.h>

namespace sge
{

    class GlobalResources
    {
    public:
        // Application
        GLApp * _App;

        // Shaders
        PROGRAM_P3C4       _PROGRAM_P3C4;
        PROGRAM_MODEL      _PROGRAM_MODEL;
        PROGRAM_FEEDBACK_CALC_INST_CMD     _PROGRAM_FEEDBACK_CALC_INST_CMD;

        // For i18n string resources.
        const char* GetStr(const char*str) { return str; }

    public:
        GlobalResources(sge::GLApp* app)
            : _App(app)
        {
        }

        bool Init()
        {
            bool ret = true;

            // shaders
            ret &= _PROGRAM_P3C4.Create();
            ret &= _PROGRAM_MODEL.Create();
            ret &= _PROGRAM_FEEDBACK_CALC_INST_CMD.Create();

            return ret;
        }

        void Destory()
        {
            // shaders
            _PROGRAM_P3C4.Destory();
            _PROGRAM_MODEL.Destory();
            _PROGRAM_FEEDBACK_CALC_INST_CMD.Destory();
        }
    };

}

#endif // !GLOBAL_RESOURCES_H
