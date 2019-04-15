/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeSceneObject.h
 * date: 2019/03/29
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

#ifndef SGE_SCENE_OBJECT_H
#define SGE_SCENE_OBJECT_H

#include <core/sgePlatform.h>
#include <core/sgeSceneObjectTypes.h>
#include <core/sgeGuid.h>

namespace sge
{

    /**
     * The base scene object class
     */
    class SceneObject
    {
    public:
        /**
         * Get the object guid
         */
        const Guid& getGuid() const { return _guid; };

        /**
         * Get the object type
         */
        SceneObjectType getType() const { return _type; }
    protected:
        
        // can only be used as base class
        SceneObject(Guid& guid, SceneObjectType type)
            : _guid(guid)
            , _type(type)
        {}
        
        SceneObject(Guid&& guid, SceneObjectType type)
            : _guid(std::move(guid))
            , _type(type)
        {}

        SceneObject(SceneObject&& obj)
            : _guid(std::move(obj._guid))
            , _type(obj._type)
        {}

        SceneObject& operator=(SceneObject&& obj) {
            this->_guid =   std::move(obj._guid);
            this->_type =   obj._type;
            return  *this;
        };

    protected:
        Guid                _guid;
        SceneObjectType     _type;
    private:
        // no default constructor
        SceneObject() = delete;
        // no copy object
        DISABLE_COPY(SceneObject)
    public:
        friend std::ostream& operator<<(std::ostream& out, const BaseSceneObject& obj)
        {
            out << "SceneObject" << std::endl;
            out << "-----------" << std::endl;
            out << "GUID: " << obj._guid << std::endl;
            out << "Type: " << obj._type << std::endl;
            return  out;
        }
    };
    
}

#endif //!SGE_SCENE_OBJECT_H