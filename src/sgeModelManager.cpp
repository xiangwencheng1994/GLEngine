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

#include <sgeModelManager.h>
#include <sgeLog.h>
#include <sgeUtils.h>

namespace sge
{

    #define DEFAULT_INSTANCE_GROW_SIZE  1024
    #define MAX_INSTANCE_UPDATE_COUNT   128

    ModelManager::ModelManager(std::string meshLibPath)
        : _meshLibPath(meshLibPath)
    {
    }

    ModelManager::~ModelManager()
    {
    }

    bool ModelManager::Create()
    {
        std::vector<std::string> files;        
        
        // load materials
        Util::GetAllFiles(_meshLibPath, files, ".mtl");
        for (size_t i = 0; i < files.size(); ++i)
        {
            LoadMaterial(files[i].c_str());
        }
        files.clear();
        UpdateMaterials();

        // load mesh
        Util::GetAllFiles(_meshLibPath, files, ".objx");        
        for (size_t i = 0; i < files.size(); ++i)
        {
            SharedPtr<MemMesh> memMesh = MemMesh::FromObj(files[i].c_str());
            
            if (!memMesh)
            {
                Log::info("objx read failed: %s", files[i].c_str());
                continue;
            }
            
            MeshDesc mesh;
            mesh._aabb = memMesh->_aabb;
            mesh._baseVertex = _vertexs.size();
            mesh._baseIndex = _faces.size() * 3;
            mesh._vertexCount = memMesh->_faces.size() * 3;
            _meshes.push_back(mesh);

            char name[_MAX_FNAME];
            _splitpath(files[i].c_str(), 0, 0, name, 0);
            ASSERT(_meshNames.find(name) == _meshNames.end());
            _meshNames[name] = _meshNames.size();
           
            _vertexs.insert(_vertexs.end(), memMesh->_vertexs.begin(), memMesh->_vertexs.end());
            _faces.insert(_faces.end(), memMesh->_faces.begin(), memMesh->_faces.end());
        }

        GLX::DeleteBuffer(_meshesUBO);
        _meshesUBO = GLX::CreateBuffer<UniformBuffer>(sizeof(MeshDesc) * 256, NULL, GL_STATIC_DRAW);
        GLX::UpdateBuffer(_meshesUBO, 0, sizeof(MeshDesc) * _meshes.size(), &_meshes.front());

        GLX::DeleteBuffer(_vertexsVBO);
        _vertexsVBO = GLX::CreateBuffer<VertexBuffer>(sizeof(MeshVertex) * _vertexs.size()
            , &_vertexs.front(), GL_STATIC_DRAW);
        GLX::DeleteBuffer(_facesIBO);
        _facesIBO = GLX::CreateBuffer<ElementBuffer>(sizeof(ushort3) * _faces.size()
            , &_faces.front(), GL_STATIC_DRAW);
        
        return true;
    }


    bool ModelManager::LoadMaterial(const char* mtlFile)
    {
        //TODO: 
        

        return false;
    }


    void ModelManager::UpdateMaterials()
    {
        if (_materialUBO.IsValid())
        {
            _materialUBO = GLX::CreateBuffer<UniformBuffer>(sizeof(Material) * 256, NULL, GL_STATIC_DRAW);
        }
        if (_materials.size() > 0)
        {
            GLX::UpdateBuffer(_materialUBO, 0, sizeof(Material) * _materials.size(), &_materials.front());
        }
    }

    void ModelManager::Destory()
    {
        _instances.clear();
        GLX::DeleteBuffer(_materialUBO);
        GLX::DeleteBuffer(_instancesVBO);
        GLX::DeleteBuffer(_drawCmdBO);
    }

    int sge::ModelManager::GetFactoryIdByName(const char * name)
    {
        NameMap::iterator it = _meshNames.find(name);
        if (it != _meshNames.end())
        {
            return it->second;
        }
        return 0;
    }

    void ModelManager::Reserve(size_t count)
    {
        if (_instances.capacity() >= count)
            return;

        _instances.reserve(count);
        
        GLX::DeleteBuffer(_instancesVBO);
        GLX::DeleteBuffer(_drawCmdBO);
    }

    uint ModelManager::AddInstance(uint meshId)
    {
        if (meshId >= _meshes.size())
            return uint(-1);
        
        uint id = uint(-1);

        while(!_emptyInstId.empty())
        {
            uint item = _emptyInstId.front();
            _emptyInstId.pop_front();
            if (item >= _instances.size())
            {
                continue;
            }
            ASSERT(_instances[item]._meshId == 0xFF);
            id = item;
            break;
        }

        // Append new instance if not find empty item
        if (id == uint(-1))
        {
            if (_instances.capacity() <= _instances.size())
                Reserve(_instances.capacity() + DEFAULT_INSTANCE_GROW_SIZE);
            id = _instances.size();
            _instances.push_back(Instance());
        }
        
        // Set data for instance
        _instances[id]._meshId = meshId;
        _instances[id]._flag = InstFlag::VISIBLE;
        _instances[id]._local.identity();
        _instances[id]._matIndex = 0;
        InstanceNeedUpdate(id);

        return id;
    }
    
    const mat4f& ModelManager::GetInstanceLocal(uint instId) const
    {
        ASSERT(instId < _instances.size() && "Instance Id out of range");
        return _instances[instId]._local;
    }

    void ModelManager::SetInstanceLocal(uint instId, const mat4f& local)
    {
        if (instId < _instances.size())
        {
            _instances[instId]._local = local;
            InstanceNeedUpdate(instId);
        }
        else
        {
            ASSERT("Instance Id out of range");
        }
    }
    
    bool ModelManager::GetInstanceVisible(uint instId) const
    {
        if (instId < _instances.size())
        {
            return _instances[instId]._flag & InstFlag::VISIBLE;
        }
        else
        {
            ASSERT("Instance Id out of range");
        }
        return false;
    }

    void ModelManager::SetInstanceVisible(uint instId, bool visible)
    {
        if (instId < _instances.size())
        {
            if (visible != (_instances[instId]._flag & InstFlag::VISIBLE))
            {
                visible ? _instances[instId]._flag |= InstFlag::VISIBLE
                    : _instances[instId]._flag &= ~InstFlag::VISIBLE;
                InstanceNeedUpdate(instId);
            }
        }
        else
        {
            ASSERT("Instance Id out of range");
        }
    }
    
    ushort ModelManager::GetInstanceMatId(uint instId) const
    {
        if (instId < _instances.size())
        {
            return _instances[instId]._matIndex;
        }
        return ushort(-1);
    }

    void ModelManager::SetInstanceMatId(uint instId, ushort matId)
    {
        if (instId < _instances.size())
        {
            if (matId != _instances[instId]._matIndex)
            {
                _instances[instId]._matIndex = matId;
                InstanceNeedUpdate(instId);
            }
        }
        else
        {
            ASSERT("Instance Id out of range");
        }
    }

    void ModelManager::DeleteInstance(uint instId)
    {
        if (instId < _instances.size())
        {
            _instances[instId]._meshId = 0xFF;
            _emptyInstId.push_back(instId);
            InstanceNeedUpdate(instId);
        }
    }

    void ModelManager::InstanceNeedUpdate(uint instId)
    {
        ASSERT(instId < _instances.size());

        if (_updateList.size() < MAX_INSTANCE_UPDATE_COUNT)
        {
            _updateList.insert(instId);
        }
    }

    void ModelManager::OnUpdate()
    {
        if (_updateList.size() < MAX_INSTANCE_UPDATE_COUNT && _instancesVBO.IsValid())
        {
            for (std::set<uint>::iterator it = _updateList.begin();
                it != _updateList.end(); ++it)
            {
                GLX::UpdateBuffer(_instancesVBO, sizeof(Instance) * (*it),
                    sizeof(Instance), &_instances[*it]);
            }
        }
        else
        {
            if (!_instancesVBO.IsValid())
            {
                _instancesVBO = GLX::CreateBuffer<VertexBuffer>(sizeof(Instance) * _instances.capacity()
                    , NULL, GL_STATIC_DRAW);
                GLX::DeleteBuffer(_drawCmdBO);
                _drawCmdBO = GLX::CreateBuffer<IndirectBuffer>(sizeof(DrawElementsIndirectCommand) * _instances.capacity()
                    , NULL, GL_STATIC_DRAW);
            }
            GLX::UpdateBuffer(_instancesVBO, 0,
                    sizeof(Instance) * _instances.size(), &_instances.front());
        }
        _updateList.clear();
    }

    void ModelManager::BuildDrawCommands(GlobalResources& resource)
    {
        PROGRAM_FEEDBACK_CALC_INST_CMD& prg = resource._PROGRAM_FEEDBACK_CALC_INST_CMD;
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, _drawCmdBO.id);

        prg.Begin();
        {
            //glUniformMatrix4fv(_shader._mvp, 1, false, mvp);
            glUniformBlockBinding(prg.ProgramId(), prg.Meshes.index, 1);
            glBindBufferBase(GL_UNIFORM_BUFFER, 1, _meshesUBO.id);
            GLX::BindBuffer(&_instancesVBO);
            glEnableVertexAttribArray(prg._meshId);
            glEnableVertexAttribArray(prg._flag);
            //glEnableVertexAttribArray(prg._local + 0);
            //glEnableVertexAttribArray(prg._local + 1);
            //glEnableVertexAttribArray(prg._local + 2);
            //glEnableVertexAttribArray(prg._local + 3);
            glVertexAttribIPointer(prg._meshId, 1, GL_UNSIGNED_BYTE, sizeof(Instance), PTR_OFFSET(0));
            glVertexAttribIPointer(prg._flag, 1, GL_UNSIGNED_BYTE, sizeof(Instance), PTR_OFFSET(1));
            //glVertexAttribPointer(prg._local + 0, 4, GL_FLOAT, false, sizeof(Instance), PTR_OFFSET(4));
            //glVertexAttribPointer(prg._local + 1, 4, GL_FLOAT, false, sizeof(Instance), PTR_OFFSET(20));
            //glVertexAttribPointer(prg._local + 2, 4, GL_FLOAT, false, sizeof(Instance), PTR_OFFSET(36));
            //glVertexAttribPointer(prg._local + 3, 4, GL_FLOAT, false, sizeof(Instance), PTR_OFFSET(52));
            glDrawArrays(GL_POINTS, 0, _instances.size());
            glDisableVertexAttribArray(prg._meshId);
            glDisableVertexAttribArray(prg._flag);
            //glDisableVertexAttribArray(prg._local + 0);
            //glDisableVertexAttribArray(prg._local + 1);
            //glDisableVertexAttribArray(prg._local + 2);
            //glDisableVertexAttribArray(prg._local + 3);

            //glFlush();
        }
        prg.End();
    }

    void ModelManager::OnRender(GlobalResources& resource, Camera& camera)
    {
        OnUpdate();
        BuildDrawCommands(resource);

        PROGRAM_MODEL& prg = resource._PROGRAM_MODEL;
        prg.Begin();
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glUniformMatrix4fv(prg.MVP, 1, false, camera.MatWVP()));
        GLCall(glUniform3fv(prg.CameraPos, 1, camera.Position()));
        vec3f lightDir = -camera.FrontDir();
        lightDir.normalize();
        GLCall(glUniform3fv(prg.LightDir, 1, lightDir));
        
        GLCall(glUniformBlockBinding(prg.ProgramId(), prg.Materials.index, 1));
        GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, 1, _materialUBO.id));
        
        GLCall(glEnableVertexAttribArray(prg._position));
        GLCall(glEnableVertexAttribArray(prg._normal));
        GLCall(glEnableVertexAttribArray(prg._local + 0));
        GLCall(glEnableVertexAttribArray(prg._local + 1));
        GLCall(glEnableVertexAttribArray(prg._local + 2));
        GLCall(glEnableVertexAttribArray(prg._local + 3));
        GLCall(glEnableVertexAttribArray(prg._matIndex));
        GLCall(glVertexAttribDivisor(prg._local + 0, 1));
        GLCall(glVertexAttribDivisor(prg._local + 1, 1));
        GLCall(glVertexAttribDivisor(prg._local + 2, 1));
        GLCall(glVertexAttribDivisor(prg._local + 3, 1));
        GLCall(glVertexAttribDivisor(prg._matIndex, 1));
        
        GLX::BindBuffer(&_vertexsVBO);
        GLCall(glVertexAttribPointer(prg._position, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), PTR_OFFSET(0)));
        GLCall(glVertexAttribPointer(prg._normal, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), PTR_OFFSET(12)));
        
        GLX::BindBuffer(&_instancesVBO);
        GLCall(glVertexAttribIPointer(prg._matIndex, 1, GL_UNSIGNED_SHORT, sizeof(Instance), PTR_OFFSET(2)));
        GLCall(glVertexAttribPointer(prg._local + 0, 4, GL_FLOAT, GL_FALSE, sizeof(Instance), PTR_OFFSET(4)));
        GLCall(glVertexAttribPointer(prg._local + 1, 4, GL_FLOAT, GL_FALSE, sizeof(Instance), PTR_OFFSET(20)));
        GLCall(glVertexAttribPointer(prg._local + 2, 4, GL_FLOAT, GL_FALSE, sizeof(Instance), PTR_OFFSET(36)));
        GLCall(glVertexAttribPointer(prg._local + 3, 4, GL_FLOAT, GL_FALSE, sizeof(Instance), PTR_OFFSET(52)));
        
        GLX::BindBuffer(&_facesIBO);
        GLX::BindBuffer(&_drawCmdBO);
        GLCall(glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_SHORT, 0, _instances.size(), 0));

        GLCall(glDisableVertexAttribArray(prg._position));
        GLCall(glDisableVertexAttribArray(prg._normal));
        GLCall(glVertexAttribDivisor(prg._local + 0, 0));
        GLCall(glVertexAttribDivisor(prg._local + 1, 0));
        GLCall(glVertexAttribDivisor(prg._local + 2, 0));
        GLCall(glVertexAttribDivisor(prg._local + 3, 0));
        GLCall(glVertexAttribDivisor(prg._matIndex, 0));
        GLCall(glDisableVertexAttribArray(prg._local + 0));
        GLCall(glDisableVertexAttribArray(prg._local + 1));
        GLCall(glDisableVertexAttribArray(prg._local + 2));
        GLCall(glDisableVertexAttribArray(prg._local + 3));
        GLCall(glDisableVertexAttribArray(prg._matIndex));
        GLCall(glDisable(GL_DEPTH_TEST));
        prg.End();
    }

}