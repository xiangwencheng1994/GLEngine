/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeTextureManager.cpp
 * date: 2018/12/08
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

#include <core/sgeTextureManager.h>

namespace sge
{
    Texture2DRef::Texture2DRef()
        : _mgr(NULL)
        , _refCount(NULL)
    {
    }

    Texture2DRef::~Texture2DRef()
    {
        destory();
    }

    Texture2DRef::Texture2DRef(const Texture2DRef & rhs)
        : _mgr(rhs._mgr)
        , _refCount(rhs._refCount)
    {
        if (rhs._mgr)
        {
            ASSERT(rhs._refCount && rhs.isValid());
            ++(*rhs._refCount);
            _mgr->addRefItem(this);
            _texId  =   rhs._texId;
        }
        else
        {
            ASSERT(rhs._texId == unsigned(-1 ) &&
                "Not allowed copy Texture2DRef object without TextureManager");
        }
    }

    Texture2DRef& Texture2DRef::operator=(const Texture2DRef& rhs)
    {
        if (rhs._mgr)
        {
            ASSERT(rhs._refCount && rhs.isValid());
            ++(*rhs._refCount);
        }

        destory();

        _mgr    =   rhs._mgr;
        _refCount   =    rhs._refCount;
        _texId  =   rhs._texId;
        if (_mgr)
        {
            _mgr->addRefItem(this);
        }
        return  *this;
    }
    
    void Texture2DRef::destory()
    {
        if (_mgr)
        {
            ASSERT(_refCount && isValid());
            if (--(*_refCount) == 0)
            {
                _mgr->removeTex(_texId);
            }
            _texId  =   unsigned(-1);
            _mgr->removeRefItem(this);
            ASSERT(_mgr == NULL && _refCount == NULL);
        }
    }

    TextureManager::TextureManager()
    {
    }

    TextureManager::~TextureManager()
    {
        for (List<Texture2DRef*>::iterator it = _items.begin();
            it != _items.end(); ++it)
        {
            (*it)->_mgr     =   NULL;
            (*it)->_refCount    =   NULL;
            (*it)->_texId   =   NULL;
        }
        _items.clear();
        for (Map<GLuint, TextureDesc>::iterator it = _texRefMap.begin();
            it != _texRefMap.end(); ++it)
        {
            GLCall(glDeleteTextures(1, &it->first));
        }
        _texRefMap.clear();
    }

    Texture2DRef TextureManager::LoadTexture(const char* file)
    {
        Texture2DRef    ref;

        // find in loaded map
        for (Map<GLuint, TextureDesc>::iterator it = _texRefMap.begin();
            it != _texRefMap.end(); ++it)
        {
            if (0 == strcmp(it->second.file.c_str(), file))
            {
                ref._mgr    =   this;
                ref._refCount   =   &it->second.refCount;
                ref._texId  =   it->first;
                ++it->second.refCount;
                addRefItem(&ref);
                return  ref;
            }
        }

        if (ref.loadFromFile(file))
        {
            TextureDesc desc    =   _texRefMap[ref._texId];
            desc.file   =   file;
            desc.refCount   =   1;
            desc.size.x =   ref.getWidth();
            desc.size.y =   ref.getHeight();
            addRefItem(&ref);
        }

        return ref;
    }

    void TextureManager::removeTex(GLuint tex)
    {
        Map<GLuint, TextureDesc>::iterator it = _texRefMap.find(tex);
        if (it != _texRefMap.end())
        {
            _texRefMap.erase(it);
            for (List<Texture2DRef*>::iterator jt = _items.begin();
                jt != _items.end(); ++jt)
            {
                Texture2DRef*   ref =   *jt;
                if (ref->_texId == tex)
                {
                    ref->_mgr   =   NULL;
                    ref->_refCount  =   NULL;
                    ref->_texId =   unsigned(-1);
                }
            }
            GLCall(glDeleteTextures(1, &tex));
        }
    }
    
    void TextureManager::addRefItem(Texture2DRef* item)
    {
        ASSERT(item);
        ASSERT(_items.end() == std::find(_items.begin(), _items.end(), item));
        _items.push_back(item);
    }

    void TextureManager::removeRefItem(Texture2DRef* item)
    {
        List<Texture2DRef*>::iterator it = std::find(_items.begin(), _items.end(), item);
        ASSERT(it != _items.end());
        if (it != _items.end())
        {
            item->_mgr  =   NULL;
            item->_refCount =   NULL;
            item->_texId    =   unsigned(-1);
            _items.erase(it);
            ASSERT(_items.end() == std::find(_items.begin(), _items.end(), item));
        }
    }
}