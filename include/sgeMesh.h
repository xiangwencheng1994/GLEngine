/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeMesh.h
 * date: 2018/8/19
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

#ifndef SGE_MESH_H
#define SGE_MESH_H

#include <sge.h>
#include <sgeMath.h>

#include <sgeMaterial.h>
#include <sgeGLX.h>

#include <vector>
#include <map>

namespace sge
{
    #define MAX_LOD_LEV     3

    /**
     * The base vertex of mesh
     */
    struct MeshVertex
    {
        vec3f   pos;        // position
        vec3f   normal;     // normal
        //vec2f   texCoord; // texture coord
    };
    typedef std::vector<MeshVertex>     ArrayMeshVertex;
    typedef std::vector<ushort3>        ArrayMeshFace;
    typedef std::vector<std::string>    ArrayString;

    /**
     * The memory mesh, vertex storage in memory
     */
    class SGE_API MemMesh
    {
    public:
        /**
         * The vertexs
         */
        ArrayMeshVertex         _vertexs;
        
        /**
         * The face indices of vertexs using GL_TRIANGLES
         */
        ArrayMeshFace           _faces;
        
        /**
         * The default material
         */
        Material                _material;
        ArrayString             _mtllibs;

        /**
         * The axes-aligned bounding-box
         */
        aabb3f                  _aabb;

    public:
        /**
         * Release this mesh, do not use this ptr after called
         */
        virtual ~MemMesh();

    public:
        /**
         * Load a mesh from a obj file
         * The obj file can has only a matrial include, we not read mtllib file
         * only "v","vt","vn","f","Ka","Kd","Ks","Ns","map_Kd","map_bump" can used.
         * @param objFile The .obj File
         * @return null if read failed, otherwise return a MemMesh pointer, you should call 'Release' when you not used later
         */
        static SharedPtr<MemMesh> FromObj(const char* objFile);

    private:
        MemMesh() {}
        DISABLE_COPY(MemMesh)
    };

}

#endif // !SGE_MESH_H