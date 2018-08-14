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

#ifndef SGE_CAMERA_H
#define SGE_CAMERA_H

#include <sgeMath.h>

namespace sge
{

    /**
    * Class Camera
    */
    class Camera
    {
    public:
        /**
        * Constructor
        * @param pos The camera pos
        * @param dir The camera view direction
        * @param worldUp Define the worldUp direction
        */
        Camera(const vec3f& pos, const vec3f& _target, const vec3f& worldUp = vec3f(0.0f, 1.0f, 0.0f))
            : _position(pos), _target(_target), WorldUp(worldUp), _needUpdateView(true)
        {
            _matWorld.identity();
            this->_isDraging = false;
        }

        /**
        * Get the camera position
        */
        const vec3f& Position() const { return _position; }

        /**
        * Get the target position
        */
        const vec3f& Target() const { return _target; }

        /**
        * Get the camera up direction
        */
        const vec3f& UpDir() { if (_needUpdateView) updateCamera(); return _upDir; }

        /**
        * Set the camera position
        * @param pos New camera position
        */
        const void setPosition(const vec3f& pos) { _position = pos, _needUpdateView = true; }

        /**
        * Set the camera view direction
        * @param dir New view direction, Must not parallel to WorldUp
        */
        const void setTarget(const vec3f& target) { _target = target, _needUpdateView = true; }

        /**
        * Get the view matrix
        */
        const mat4f& ViewMatrix() { if (_needUpdateView) updateCamera(); return _matView; }

        /**
        * Get the projection matrix that we created by setPerpective or setOrtho.
        */
        const mat4f& ProjectionMatrix() { return _matProjection; }

        /**
        * Set the projection matrix by perspective
        * @params seealso mat4f::createPerspective
        */
        void setPerspective(float fovy, float aspectRatio, float zNear, float zFar) { _matProjection = mat4f::createPerspective(fovy, aspectRatio, zNear, zFar); }

        /**
        * Set the projection matrix by ortho
        * @params seealso mat4f::createOrtho
        */
        void setOrtho(float left, float right, float bottom, float top, float zNear, float zFar) { _matProjection = mat4f::createOrtho(left, right, bottom, top, zNear, zFar); }


        /**
        * World position to screen position
        */
        bool    project(const vec4f& world, vec4f& screen, const vec2i& viewSize)
        {
            screen = _matWVP * world;
            if (screen.w == 0.0f)
            {
                return false;
            }
            screen.x /= screen.w;
            screen.y /= screen.w;
            screen.z /= screen.w;

            // map to range 0 - 1
            screen.x = screen.x * 0.5f + 0.5f;
            screen.y = screen.y * 0.5f + 0.5f;
            screen.z = screen.z * 0.5f + 0.5f;

            // map to viewport
            screen.x = screen.x * viewSize.x;
            screen.y = viewSize.y - (screen.y * viewSize.y);
            return  true;
        }


        /**
        * World position to screen position
        */
        vec2f  worldToScreen(const vec3f& world, const vec2i& viewSize)
        {
            vec4f  worlds(world.x, world.y, world.z, 1);
            vec4f  screens;
            project(worlds, screens, viewSize);
            return  vec2f(screens.x, screens.y);
        }

        /**
        * Screen position to world position
        */
        vec3f  screenToWorld(const vec2f& screen, const vec2i& viewSize)
        {
            vec4f  screens(screen.x, screen.y, 0, 1);
            vec4f  world;
            unProject(screens, world, viewSize);
            return  vec3f(world.x, world.y, world.z);
        }

        float3  screenToWorld(float x, float y, const vec2i& viewSize)
        {
            float4  screens(x, y, 0, 1);
            float4  world;
            unProject(screens, world, viewSize);
            return  float3(world.x, world.y, world.z);
        }


        /**
        *   窗口坐标转化为世界坐标
        */
        bool    unProject(const vec4f& screen, vec4f& world, const vec2i& viewSize)
        {
            vec4f v;
            v.x = screen.x;
            v.y = screen.y;
            v.z = screen.z;
            v.w = 1.0;

            // map from viewport to 0 - 1
            v.x = (v.x) / viewSize.x;
            v.y = (viewSize.y - v.y) / viewSize.y;
            //v.y = (v.y - viewSize.Y) / _viewPort.Height;

            // map to range -1 to 1
            v.x = v.x * 2.0f - 1.0f;
            v.y = v.y * 2.0f - 1.0f;
            v.z = v.z * 2.0f - 1.0f;

            mat4f inverse = _matWVP;
            inverse.inverse();

            v = inverse * v;
            if (v.w == 0.0f)
            {
                return false;
            }
            world = v / v.w;
            return true;
        }

        rayf createRayFromScreen(int x, int y, const vec2i& viewSize)
        {
            vec4f  minWorld;
            vec4f  maxWorld;

            vec4f  screen(float(x), float(y), 0, 1);
            vec4f  screen1(float(x), float(y), 1, 1);

            unProject(screen, minWorld, viewSize);
            unProject(screen1, maxWorld, viewSize);
            rayf     ray;
            ray.setOrigin(vec3f(minWorld.x, minWorld.y, minWorld.z));

            vec3f  dir(maxWorld.x - minWorld.x, maxWorld.y - minWorld.y, maxWorld.z - minWorld.z);
            ray.setDirection(normalize(dir));
            return  ray;
        }

        /**
        * Begin drag
        */
        void beginDrag(vec2i startPos)
        {
            _startPos = startPos;
            _endPos = startPos;
            _isDraging = true;
        }

        /**
        * On Draging
        */
        void onDrag(vec2i pos)
        {
            _endPos = pos;
            _needUpdateView = true;
        }

        /**
        * End Drag
        */
        void endDrag(bool cancel = false)
        {
            if (!cancel)
            {
                vec2i offset = _endPos - _startPos;
                vec3f dir = _position - _target;
                float len = dir.length();
                dir.normalize();
                vec3f right = cross(dir, WorldUp);
                right.normalize();

                quatf rot = quatf::fromAxisRot(right, offset.y * 0.1)
                    * quatf::fromAxisRot(WorldUp, -offset.x * 0.1);

                dir = rot * dir;
                dir.normalize();

                dir = -dir;
                right = cross(dir, WorldUp);
                _upDir = cross(right, dir);
                _upDir.normalize();

                _position = _target - dir * len;
            }
            _isDraging = false;
            _needUpdateView = true;
        }

    private:
        vec2i   _startPos;
        vec2i   _endPos;
        bool    _isDraging;

    protected:
        /**
        * The camera position
        */
        vec3f       _position;

        /**
        * The target position which we want look at
        */
        vec3f       _target;

        /**
        * The camera up dir, it will generated by _frontDir and WorldUp
        */
        vec3f       _upDir;

        /**
        * The world up dir defined
        */
        const vec3f WorldUp;

        /**
        * Flag of _matView need updated
        */
        bool        _needUpdateView;

        /**
        * The world mat matrix.
        */
        mat4f       _matWorld;

        /**
        * The matrix of world space to camera space
        */
        mat4f       _matView;

        /**
        * The matrix of camera space to clip space
        */
        mat4f       _matProjection;

        /**
        * The world-view-projection matrix compose
        */
        mat4f       _matWVP;

        /**
        * Update the up direction and view matrix
        */
        void updateCamera()
        {
            if (_isDraging)
            {
                vec2i offset = _endPos - _startPos;
                vec3f dir = _position - _target;
                float len = dir.length();
                dir.normalize();
                vec3f right = cross(dir, WorldUp);
                right.normalize();

                quatf rot = quatf::fromAxisRot(right, offset.y * 0.1)
                    * quatf::fromAxisRot(WorldUp, -offset.x * 0.1);

                dir = rot * dir;
                dir.normalize();

                dir = -dir;
                right = cross(dir, WorldUp);
                vec3f up = cross(right, dir);
                up.normalize();

                _matView = mat4f::createLookAt(_target - dir * len, _target, up);
                _matWVP = _matProjection * _matView * _matWorld;
                _needUpdateView = false;
                return;
            }

            vec3f dir = _target - _position;
            vec3f rightDir = cross(dir, WorldUp);
            assert(rightDir.length() > 0); // not zero
            _upDir = cross(rightDir, dir);
            _upDir.normalize();

            _matView = mat4f::createLookAt(_position, _target, _upDir);
            _matWVP = _matProjection * _matView * _matWorld;
            _needUpdateView = false;
        }
    };

}

#endif //!SGE_CAMERA_H
