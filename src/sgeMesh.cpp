/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeMesh.cpp
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

#include <sgeMesh.h>
#include <sgeFileReader.h>
#include <sgeUtils.h>

namespace sge
{
    MemMesh::~MemMesh()
    {
    }

    SharedPtr<MemMesh> MemMesh::FromObj(const char * objFile)
    {
        bool ret = false;
        FileReader reader(objFile, &ret);
        if (!ret)
        {
            Log::error("cannot read file: %s", objFile);
            return SharedPtr<MemMesh>(0);
        }

        char line[1024], cmd[32], argv[1024 - 32 - 1];

        std::vector<std::string> ingoreCmds;

        std::vector<vec3f>      vertexs;
        std::vector<vec3f>      normals;
        std::vector<vec2f>      uvCords;
        std::vector<vec3i>      vertArr;
        std::vector<ushort3>    faces;
        aabb3f                  aabb;
        Material                material;
        ArrayString             mtllibs;
        bool kaSeted = false;

#define RETURN_NULL_LOG(format, ...) { Log::error(format, __VA_ARGS__); return NULL; }

        int lineCount = 0;
        while (!reader.IsEOF())
        {
            ++lineCount;
            line[0] = cmd[0] = argv[0] = '\0';
            if (! reader.GetLine(line, sizeof(line)))
                break;

            if (sscanf_s(line, "%s %[^\n]", cmd, sizeof(cmd), argv, sizeof(argv)) > 0)
            {
                if (0 == stricmp("v", cmd))
                {
                    vec3f vertex;
                    int ret = sscanf(argv, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
                    if (ret != 3)
                        RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);
                    aabb << vertex; // push vertex to aabb
                    vertexs.push_back(vertex);
                }
                else if (0 == stricmp("vn", cmd))
                {
                    vec3f normal;
                    int ret = sscanf(argv, "%f %f %f", &normal.x, &normal.y, &normal.z);
                    if (ret != 3)
                        RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);
                    normals.push_back(normal);
                }
                else if (0 == stricmp("vt", cmd))
                {
                    vec2f uvCord;
                    int ret = sscanf(argv, "%f %f", &uvCord.x, &uvCord.y);
                    if (ret != 2)
                        RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);
                    uvCords.push_back(uvCord);
                }
                else if (0 == stricmp("f", cmd))
                {
                    char arg1[32], arg2[32], arg3[32], arg4[32];
                    int argCount = sscanf(argv, "%s %s %s %s", arg1, arg2, arg3, arg4);
                    if (argCount != 3 && argCount != 4)
                        RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);

                    int3 v1, v2, v3;
                    int ret = sscanf(arg1, "%d/%d/%d", &v1.x, &v1.y, &v1.z);
                    if (ret == 1) v1.y = v1.z = v1.x;
                    else if (ret != 3) RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);
                    ret = sscanf(arg2, "%d/%d/%d", &v2.x, &v2.y, &v2.z);
                    if (ret == 1) v2.y = v2.z = v2.x;
                    else if (ret != 3) RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);
                    ret = sscanf(arg3, "%d/%d/%d", &v3.x, &v3.y, &v3.z);
                    if (ret == 1) v3.y = v3.z = v3.x;
                    else if (ret != 3) RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);

                    ushort3 face1;
                    auto itr = find(vertArr.begin(), vertArr.end(), v1);                    
                    if (itr == vertArr.end())
                    {
                        face1.x = (ushort)vertArr.size();
                        vertArr.push_back(v1);
                    }
                    else face1.x = std::distance(vertArr.begin(), itr);
                    itr = find(vertArr.begin(), vertArr.end(), v2);
                    if (itr == vertArr.end())
                    {
                        face1.y = (ushort)vertArr.size();
                        vertArr.push_back(v2);
                    }
                    else face1.y = std::distance(vertArr.begin(), itr);
                    itr = find(vertArr.begin(), vertArr.end(), v3);
                    if (itr == vertArr.end())
                    {
                        face1.z = (ushort)vertArr.size();
                        vertArr.push_back(v3);
                    }
                    else face1.z = std::distance(vertArr.begin(), itr);

                    faces.push_back(face1);

                    if (argCount == 4)
                    {
                        int3 v4;
                        ret = sscanf(arg4, "%d/%d/%d", &v4.x, &v4.y, &v4.z);
                        if (ret == 1) v4.y = v4.z = v4.x;
                        else if (ret != 3) RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);

                        ushort3 face2;
                        face2.x = face1.y;
                        face2.y = face1.z;

                        itr = find(vertArr.begin(), vertArr.end(), v4);
                        if (itr == vertArr.end())
                        {
                            face2.z = (ushort)vertArr.size();
                            vertArr.push_back(v4);
                        }
                        else face2.z = std::distance(vertArr.begin(), itr);

                        faces.push_back(face2);
                    }
                }
                else if (0 == stricmp("Ka", cmd))
                {
                    int ret = sscanf(argv, "%f %f %f", &material.Ka.x, &material.Ka.y, &material.Ka.z);                    
                    if (ret != 3)
                        RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);
                    kaSeted = true;
                }
                else if (0 == stricmp("mtllib", cmd))
                {
                    if (argv[0] == '\0')
                        RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);
                    if (Util::IsAbsolutePath(argv))  mtllibs.push_back(argv);
                    else mtllibs.push_back(Util::GetFileDir(objFile) + argv);
                }                
                else if (0 == stricmp("Kd", cmd))
                {
                    int ret = sscanf(argv, "%f %f %f", &material.Kd.x, &material.Kd.y, &material.Kd.z);
                    if (ret != 3)
                        RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);
                    if (!kaSeted) material.Ka = material.Kd;
                }
                else if (0 == stricmp("Ks", cmd))
                {
                    int ret = sscanf(argv, "%f %f %f", &material.Ks.x, &material.Ks.y, &material.Ks.z);
                    if (ret != 3)
                        RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);
                }
                else if (0 == stricmp("Ns", cmd))
                {
                    int ret = sscanf(argv, "%f", &material.Ns);
                    if (ret != 1)
                        RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);
                }
                else if (0 == stricmp("map_Kd", cmd))
                {
                    if (argv[0] == '\0')
                        RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);
                    //if (Util::IsAbsolutePath(argv)) material.texture = argv;
                    //else material.texture = Util::GetFileDir(objFile) + argv;
                }
                else if (0 == stricmp("map_bump", cmd))
                {
                    if (argv[0] == '\0')
                        RETURN_NULL_LOG("read faild:[%s:%d]error argv", objFile, lineCount, line);
                    //if (Util::IsAbsolutePath(argv)) material.bumpTexture = argv;
                    //else material.bumpTexture = Util::GetFileDir(objFile) + argv;
                }
                else if ('#' == cmd[0])
                {
                    Log::info("[ObjInfo]: %s", argv);
                }
                else
                {
                    if (find(ingoreCmds.begin(), ingoreCmds.end(), cmd) == ingoreCmds.end())
                    {
                        ingoreCmds.push_back(cmd);
                        Log::info("read faild:[%s:%d]ingore commad: %s", objFile, lineCount, cmd);
                    }
                }
            }
        }
                
        SharedPtr<MemMesh> mesh(new MemMesh());

        size_t vertexCount = vertArr.size();
        mesh->_vertexs.resize(vertexCount);
        
        bool hasNormal = normals.size() > 0;
        bool hasTexUV = uvCords.size() > 0;
        for (size_t i = 0; i < vertexCount; i++)
        {
            mesh->_vertexs[i].pos = vertexs[vertArr[i].x - 1];
            //if (hasTexUV) mesh->_vertexs[i].texCoord = uvCords[vertArr[i].y - 1];
            if (hasNormal) mesh->_vertexs[i].normal = normals[vertArr[i].z - 1];
        }

        mesh->_material = material;
        mesh->_mtllibs = mtllibs;

        mesh->_aabb = aabb;
        mesh->_faces = faces;

        return mesh;
    }
    
}
