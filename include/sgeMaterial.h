/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeMaterial.h
 * date: 2018/8/17
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

#ifndef SGE_MATERIAL_H
#define SGE_MATERIAL_H

#include <sge.h>
#include <sgeMath.h>

#include <string>

namespace sge
{
    /**
     * The struct material 
     */
    struct Material
    {
        /**
         * The ambient and ambimet map
         */
        vec3f   Ka;        float    MapKa;

        /**
         * The diffuse and diffuse map
         */
        vec3f   Kd;        float    MapKd;
        
        /**
         * The specular and shinness
         */
        vec3f   Ks;        float    Ns;
        
        Material() : MapKa(0), MapKd(0), Ns(0) {}
    };

    /**
     * The material manager for all drawable objects
     */
    class MaterialManager
    {
    public:
        //TODO: Material Map to gpu

    };

}

#endif // !SGE_MATERIAL_H