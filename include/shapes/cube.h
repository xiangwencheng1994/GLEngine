/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeCamera.h
 * date: 2018/6/2
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

#ifndef SGE_CUBE_H
#define SGE_CUBE_H

#include <sgeMath.h>

namespace sge
{
    /**
     * The vertices of cube
     *    v6----- v5
     *   /|      /|
     *  v1------v0|
     *  | |     | |
     *  | |v7---|-|v4
     *  |/      |/
     *  v2------v3
     */
    const float3 CubeVertices[8] = 
    {
        { +0.5f, +0.5f, -0.5 },
        { -0.5f, +0.5f, -0.5 },
        { -0.5f, -0.5f, -0.5 },
        { +0.5f, -0.5f, -0.5 },
        { +0.5f, -0.5f, +0.5 },
        { +0.5f, +0.5f, +0.5 },
        { -0.5f, +0.5f, +0.5 },
        { -0.5f, -0.5f, +0.5 },
    };

    /**
     * The draw triangles indices of cube
     */
    const byte  CubeTrianglesIndices[36] =
    {
        0, 3, 1, 1, 3, 2, // front
        1, 2, 6, 6, 2, 7, // left
        5, 4, 0, 0, 4, 3, // right
        6, 7, 5, 5, 7, 4, // back
        5, 0, 6, 6, 0, 1, // top
        7, 2, 4, 4, 2, 3, // bottom
    };

    /**
     * The draw lines indices of cube
     */
    const byte CubeLinesIndices[24] =
    {
        0, 3, 3, 2, 2, 1, 1, 0,
        6, 7, 7, 4, 4, 5, 5, 6,
        6, 1, 2, 7, 4, 3, 0, 5
    };

}

#endif // !SGE_CUBE_H
