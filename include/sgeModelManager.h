/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeModelManager.h
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

#ifndef SGE_MANAGER_H
#define SGE_MANAGER_H

#include <sge.h>
#include <sgeMesh.h>
#include <sgeMaterial.h>
#include <sgeGLSLUtil.h>
#include <sgeGlobalResources.h>
#include <sgeCamera.h>
#include <vector>
#include <map>
#include <set>
#include <list>

namespace sge
{
    enum InstFlag
    {
        VISIBLE     =   1 << 0,
    };

    /**
     * The instance data
     */
    struct Instance
    {
        byte        _meshId;
        byte        _flag;
        ushort      _matIndex;
        mat4f       _local;
    };
    typedef std::vector<Instance>       InstanceArray;
    
    /**
     * Buffered Mesh desc
     */
    struct  MeshDesc
    {
        aabb3f      _aabb;
        int         _baseVertex;
        int         _baseIndex;
        int         _vertexCount;
    };
    
    class SGE_API ModelManager
    {
    public:
        typedef std::vector<Material>                           MaterialArray;
        typedef std::vector<DrawElementsIndirectCommand>        DrawElementsCommands;
        typedef std::vector<MeshDesc>                           MeshDescArray;
        typedef std::map<std::string, int>                      NameMap;
    public:
        ModelManager(std::string meshLibPath);
        virtual ~ModelManager();

        bool        Create();
        void        Destory();

        void        OnUpdate();
        void        BuildDrawCommands(GlobalResources& resource);
        void        OnRender(GlobalResources& resource, Camera& camera);

        int         GetFactoryIdByName(const char* name);

        void            Reserve(size_t count);

        bool            LoadMesh(const char* name, const char* objxFile);
        void            UpdateMesh();

        bool            LoadMaterial(const char* mtlFile);
        void            UpdateMaterials();

        uint            AddInstance(uint meshId);
        const mat4f&    GetInstanceLocal(uint instId) const;
        void            SetInstanceLocal(uint instId, const mat4f& local);
        bool            GetInstanceVisible(uint instId) const;
        void            SetInstanceVisible(uint instId, bool visible);
        ushort          GetInstanceMatId(uint instId) const;
        void            SetInstanceMatId(uint instId, ushort matId);
        void            DeleteInstance(uint instId);

    protected:
        NameMap         _meshNames;
        MeshDescArray   _meshes;
        UBO             _meshesUBO;
        ArrayMeshVertex _vertexs;
        VBO             _vertexsVBO;
        ArrayMeshFace   _faces;
        IBO             _facesIBO;
        
        MaterialArray   _materials;
        UBO             _materialUBO;
        
        InstanceArray   _instances;
        std::list<uint> _emptyInstId;
        VBO             _instancesVBO;

        CmdBO           _drawCmdBO;
        
        std::string     _meshLibPath;

        void            InstanceNeedUpdate(uint instId);
        std::set<uint>  _updateList;
    private:
        DISABLE_COPY(ModelManager)
    };    

}

#endif // !SGE_MANAGER_H
