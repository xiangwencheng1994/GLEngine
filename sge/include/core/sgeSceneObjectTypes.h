/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeSceneObjectTypes.h
 * date: 2019/03/30
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

#ifndef SGE_SCENE_OBJECT_TYPES_H
#define SGE_SCENE_OBJECT_TYPES_H

#include <core/sgePlatform.h>

namespace sge
{

    /**
     * Enum scene object types
     */
    ENUM(SceneObjectType)
    {
        kSceneObjectTypeMesh = "MESH"_i32,
        kSceneObjectTypeMaterial = "MATL"_i32,
        kSceneObjectTypeTexture = "TXTU"_i32,
        kSceneObjectTypeLightOmni = "LGHO"_i32,
        kSceneObjectTypeLightInfi = "LGHI"_i32,
        kSceneObjectTypeLightSpot = "LGHS"_i32,
        kSceneObjectTypeLightArea = "LGHA"_i32,
        kSceneObjectTypeCamera = "CAMR"_i32,
        kSceneObjectTypeAnimationClip = "ANIM"_i32,
        kSceneObjectTypeClip = "CLIP"_i32,
        kSceneObjectTypeVertexArray = "VARR"_i32,
        kSceneObjectTypeIndexArray = "VARR"_i32,
        kSceneObjectTypeGeometry = "GEOM"_i32,
        kSceneObjectTypeTransform = "TRFM"_i32,
        kSceneObjectTypeTranslate = "TSLT"_i32,
        kSceneObjectTypeRotate = "ROTA"_i32,
        kSceneObjectTypeScale = "SCAL"_i32,
        kSceneObjectTypeTrack = "TRAC"_i32,
        kSceneObjectTypeSkyBox = "SKYB"_i32,
        kSceneObjectTypeTerrain = "TERN"_i32
    };

    /**
     * Enum scene object collision types 
     */
    ENUM(SceneObjectCollisionType) 
    {
        kSceneObjectCollisionTypeNone = "CNON"_i32,
        kSceneObjectCollisionTypeSphere = "CSPH"_i32,
        kSceneObjectCollisionTypeBox = "CBOX"_i32,
        kSceneObjectCollisionTypeCylinder = "CCYL"_i32,
        kSceneObjectCollisionTypeCapsule = "CCAP"_i32,
        kSceneObjectCollisionTypeCone = "CCON"_i32,
        kSceneObjectCollisionTypeMultiSphere = "CMUL"_i32,
        kSceneObjectCollisionTypeConvexHull = "CCVH"_i32,
        kSceneObjectCollisionTypeConvexMesh = "CCVM"_i32,
        kSceneObjectCollisionTypeBvhMesh = "CBVM"_i32,
        kSceneObjectCollisionTypeHeightfield = "CHIG"_i32,
        kSceneObjectCollisionTypePlane = "CPLN"_i32,
    };

    /**
     * Enum index data types
     */
    ENUM(IndexDataType)
    {
        kIndexDataTypeInt8 = "I8  "_i32,
        kIndexDataTypeInt16 = "I16 "_i32,
        kIndexDataTypeInt32 = "I32 "_i32,
        kIndexDataTypeInt64 = "I64 "_i32,
    };

    /**
     * Enum vertex data types
     */
    ENUM(VertexDataType)
    {
        kVertexDataTypeFloat1 = "FLT1"_i32,
        kVertexDataTypeFloat2 = "FLT2"_i32,
        kVertexDataTypeFloat3 = "FLT3"_i32,
        kVertexDataTypeFloat4 = "FLT4"_i32,
        kVertexDataTypeDouble1 = "DUB1"_i32,
        kVertexDataTypeDouble2 = "DUB2"_i32,
        kVertexDataTypeDouble3 = "DUB3"_i32,
        kVertexDataTypeDouble4 = "DUB4"_i32
    };

    /**
     * Enum primitive types
     */
    ENUM(PrimitiveType)
    {
        kPrimitiveTypeNone = "NONE"_i32,        ///< No particular primitive type.
        kPrimitiveTypePointList = "PLST"_i32,   ///< For N>=0, vertex N renders a point.
        kPrimitiveTypeLineList = "LLST"_i32,    ///< For N>=0, vertices [N*2+0, N*2+1] render a line.
        kPrimitiveTypeLineStrip = "LSTR"_i32,   ///< For N>=0, vertices [N, N+1] render a line.
        kPrimitiveTypeTriList = "TLST"_i32,     ///< For N>=0, vertices [N*3+0, N*3+1, N*3+2] render a triangle.
        kPrimitiveTypeTriFan = "TFAN"_i32,      ///< For N>=0, vertices [0, (N+1)%M, (N+2)%M] render a triangle, where M is the vertex count.
        kPrimitiveTypeTriStrip = "TSTR"_i32,    ///< For N>=0, vertices [N*2+0, N*2+1, N*2+2] and [N*2+2, N*2+1, N*2+3] render triangles.
        kPrimitiveTypePatch = "PACH"_i32,       ///< Used for tessellation.
        kPrimitiveTypeLineListAdjacency = "LLSA"_i32,       ///< For N>=0, vertices [N*4..N*4+3] render a line from [1, 2]. Lines [0, 1] and [2, 3] are adjacent to the rendered line.
        kPrimitiveTypeLineStripAdjacency = "LSTA"_i32,      ///< For N>=0, vertices [N+1, N+2] render a line. Lines [N, N+1] and [N+2, N+3] are adjacent to the rendered line.
        kPrimitiveTypeTriListAdjacency = "TLSA"_i32,        ///< For N>=0, vertices [N*6..N*6+5] render a triangle from [0, 2, 4]. Triangles [0, 1, 2] [4, 2, 3] and [5, 0, 4] are adjacent to the rendered triangle.
        kPrimitiveTypeTriStripAdjacency = "TSTA"_i32,       ///< For N>=0, vertices [N*4..N*4+6] render a triangle from [0, 2, 4] and [4, 2, 6]. Odd vertices Nodd form adjacent triangles with indices min(Nodd+1,Nlast) and max(Nodd-3,Nfirst).
        kPrimitiveTypeRectList = "RLST"_i32,    ///< For N>=0, vertices [N*3+0, N*3+1, N*3+2] render a screen-aligned rectangle. 0 is upper-left, 1 is upper-right, and 2 is the lower-left corner.
        kPrimitiveTypeLineLoop = "LLOP"_i32,    ///< Like <c>kPrimitiveTypeLineStrip</c>, but the first and last vertices also render a line.
        kPrimitiveTypeQuadList = "QLST"_i32,    ///< For N>=0, vertices [N*4+0, N*4+1, N*4+2] and [N*4+0, N*4+2, N*4+3] render triangles.
        kPrimitiveTypeQuadStrip = "QSTR"_i32,   ///< For N>=0, vertices [N*2+0, N*2+1, N*2+3] and [N*2+0, N*2+3, N*2+2] render triangles.
        kPrimitiveTypePolygon = "POLY"_i32,     ///< For N>=0, vertices [0, N+1, N+2] render a triangle.
    };


    ENUM(AttenCurveType)
    {
        kNone = 0,
        kLinear = 1,
        kSmooth = 2,
        kInverse = 3,
        kInverseSquare = 4
    };

}

#endif // !SGE_SCENE_OBJECT_TYPES_H
