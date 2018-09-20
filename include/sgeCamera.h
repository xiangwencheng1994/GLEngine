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
        Camera(const vec3f& pos, const vec3f& dir, const vec3f& worldUp = vec3f(0.0f, 1.0f, 0.0f))
            : _position(pos), _frontDir(dir), WorldUp(worldUp), _needUpdateView(true)
        {
            _frontDir.normalize();
            _matWorld.identity();
        }

        /**
         * Get the camera position
         */
        const vec3f& Position() const { return _position; }

        /**
         * Get the front direction of camera
         */
        const vec3f& FrontDir() const { return _frontDir; }

        /**
         * Get the camera up direction
         */
        const vec3f& UpDir() { if (_needUpdateView) updateCamera(); return _upDir; }

        /**
         * Set the camera position
         * @param pos New camera position
         */
        const void SetPosition(const vec3f& pos) { _position = pos, _needUpdateView = true; }

        /**
         * Set the camera view direction
         * @param dir New view direction, Must not parallel to WorldUp
         */
        const void SetFrontDir(const vec3f& dir) { _frontDir = dir, _needUpdateView = true; }

        /**
         * Get the view matrix
         */
        const mat4f& ViewMatrix() { if (_needUpdateView) updateCamera(); return _matView; }

        /**
         * Get the projection matrix that we created by setPerpective or setOrtho.
         */
        const mat4f& ProjectionMatrix() { return _matProjection; }

        /**
         * Get the world-view-projection matrix compose
         */
        const mat4f& MatWVP() { if (_needUpdateView) updateCamera(); return _matWVP; }

        /**
         * Get the inverse martrix of MatWVP
         */
        const mat4f& MatWVP_Inv() { if (_needUpdateView) updateCamera(); return _matWVP_Inv; }

        /**
         * Set the projection matrix by perspective
         * @params seealso mat4f::createPerspective
         */
        void SetPerspective(float fovy, float aspectRatio, float zNear, float zFar) { _matProjection = mat4f::createPerspective(fovy, aspectRatio, zNear, zFar); _needUpdateView = true; }

        /**
         * Set the projection matrix by ortho
         * @params seealso mat4f::createOrtho
         */
        void SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar) { _matProjection = mat4f::createOrtho(left, right, bottom, top, zNear, zFar); _needUpdateView = true; }

        /**
         * World position to screen position
         */
        bool    Project(const vec4f& world, vec4f& screen, const vec2i& viewSize)
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
        vec2f  WorldToScreen(const vec3f& world, const vec2i& viewSize)
        {
            vec4f  worlds(world.x, world.y, world.z, 1);
            vec4f  screens;
            Project(worlds, screens, viewSize);
            return  vec2f(screens.x, screens.y);
        }

        /**
         * Screen position to world position
         */
        vec3f  ScreenToWorld(const vec2f& screen, const vec2i& viewSize)
        {
            vec4f  screens(screen.x, screen.y, 0, 1);
            vec4f  world;
            UnProject(screens, world, viewSize);
            return  vec3f(world.x, world.y, world.z);
        }

        /**
         * Screen position to world position
         */
        vec3f  ScreenToWorld(float x, float y, const vec2i& viewSize)
        {
            float4  screens(x, y, 0, 1);
            float4  world;
            UnProject(screens, world, viewSize);
            return  float3(world.x, world.y, world.z);
        }

        /**
         * Screen position to world position
         */
        bool    UnProject(const vec4f& screen, vec4f& world, const vec2i& viewSize)
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
            
            v = _matWVP_Inv * v;
            if (v.w == 0.0f)
            {
                return false;
            }
            world = v / v.w;
            return true;
        }

        /**
         * Create ray from screen point down
         */
        rayf CreateRayFromScreen(int x, int y, const vec2i& viewSize)
        {
            vec4f  minWorld;
            vec4f  maxWorld;

            vec4f  screen(float(x), float(y), 0, 1);
            vec4f  screen1(float(x), float(y), 1, 1);

            UnProject(screen, minWorld, viewSize);
            UnProject(screen1, maxWorld, viewSize);
            rayf     ray;
            ray.setOrigin(vec3f(minWorld.x, minWorld.y, minWorld.z));

            vec3f  dir(maxWorld.x - minWorld.x, maxWorld.y - minWorld.y, maxWorld.z - minWorld.z);
            ray.setDirection(normalize(dir));
            return  ray;
        }

        /**
         * Create ray from screen point down
         */
        rayf CreateRayFromScreen(const vec2i& pt, const vec2i& viewSize)
        {
            return CreateRayFromScreen(pt.x, pt.y, viewSize);
        }
        
        /**
         * Rotate camera by center on axis-X
         */
        void    rotateViewXByCenter(float angle, const vec3f& center)
        {
            vec3f vDir = center - _position;
            float len = vDir.length();
            vDir.normalize();

            vec3f right = cross(_frontDir, _upDir);
            right.normalize();

            mat4f mat = mat4f::createRotationAroundAxis(angle, right);

            vDir = mat * vDir;
            _frontDir = mat * _frontDir;
            _upDir = mat * _upDir;
            
            _position = center - vDir * len;
            
            right = cross(_frontDir, WorldUp);
            _upDir = cross(right, _frontDir);
            _upDir.normalize();
            
            _needUpdateView = true;
        }

        /**
         * Rotate camera by center on axis-Y
         */
        void    rotateViewYByCenter(float angle, const vec3f& center)
        {
            vec3f vDir = center - _position;
            float len = vDir.length();
            vDir.normalize();
            
            mat4f mat = mat4f::createRotationAroundAxis(angle, WorldUp);
            
            vDir = mat * vDir;
            _frontDir = mat * _frontDir;
            _upDir = mat * _upDir;

            _position = center - vDir * len;
            
            vec3f right = cross(_frontDir, _upDir);
            _upDir = cross(right, _frontDir);
            _upDir.normalize();

            _needUpdateView = true;
        }


        /**
         * Move camera by offset point in screen
         */
        void    moveScene(const vec3f& worldPickup, const int2& ofScreen, const int2& viewSize)
        {
            vec3f right = cross(_frontDir, _upDir);
            right.normalize();

            vec3f pos1 = worldPickup + right * 1000.0f;

            vec2f screen0 = WorldToScreen(worldPickup, viewSize);
            vec2f screen1 = WorldToScreen(pos1, viewSize);
            float pixelU = 1000.0f / (screen1.x - screen0.x);

            vec3f offset = right * (-pixelU * (float)ofScreen.x);

            offset += _upDir * (pixelU * (float)ofScreen.y);

            _position += offset;

            _needUpdateView = true;
        }

    protected:
        /**
         * The camera position
         */
        vec3f       _position;

        /**
         * The front direction which we want look at
         */
        vec3f       _frontDir;

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
         * The projection-world matrix, inverse of _matWVP
         */
        mat4f       _matWVP_Inv;

        /**
         * Update the up direction and view matrix
         */
        void updateCamera()
        {
            vec3f rightDir = cross(_frontDir, WorldUp);
            assert(rightDir.length() > 0); // not zero
            _upDir = cross(rightDir, _frontDir);
            _upDir.normalize();
            
            _matView = mat4f::createLookAt(_position, _position + _frontDir, _upDir);
            _matWVP = _matProjection * _matView * _matWorld;
            _matWVP_Inv = _matWVP;
            _matWVP_Inv.inverse();
            _needUpdateView = false;
        }
    };

}

#endif //!SGE_CAMERA_H
