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
    template<typename T>
    class Camera
    {
    protected:
        /** For camera space **/
        Vector3<T>  _eye;
        Vector3<T>  _target;
        Vector3<T>  _up;
        Matrix4<T>  _matView;
        bool        _matViewUpdate;

        /** For projection space **/
        Vector2<T>  _viewSize;
        Matrix4<T>  _matProjection;
        bool        _matProjectionUpdate;
    public:
        Camera(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up)
            : _eye(eye), _target(target), _up(up), _matViewUpdate(true), _matProjectionUpdate(true)
        {
        }

        const Vector3<T>& getEye() const { return _eye; }
        const Vector3<T>& getTarget() const { return _target; }
        const Vector3<T>& getUp() const { return _up; }
        const Vector2<T>& getViewSize() const { return _viewSize; }

        void setEye(const Vector3<T>& eye) 
        {
            _eye = eye;
            _matViewUpdate = true; 
        }

        void setTarget(const Vector3<T>& target)
        {
            _target = target;
            _matViewUpdate = true;
        }

        void setUp(const Vector3<T>& up)
        {
            _up = up;
            _matViewUpdate = true;
        }

        void setViewSize(const Vector2<T> viewSize) {
            _viewSize = viewSize;
            _matProjectionUpdate = true;
        }

        const Matrix4<T>& getViewMatrix()
        {
            if (_matViewUpdate)
            {
                assert(_eye != _target);
                _matView = Matrix4<T>::createLookAt(_eye, _target, _up);
                _matViewUpdate = false;
            }
            return _matView;
        }

        virtual const Matrix4<T>& getProjectionMatrix() = 0;

    public:
        void    rotateViewY(T angle)
        {
            Vector3<T>  dir = _target - _eye;
            T   len =   dir.length();
            dir.normalize();
            dir =   Vector3<T>::rotateY(dir, angle);
            _up  =   Vector3<T>::rotateY(_up, angle);
            _eye = _target - dir * len;
            _matViewUpdate = true;
        }

        void    rotateViewX(float angle)
        {
            Vector3<T> dir = _target - _eye;
            float len = dir.length();
            dir.normalize();
            Vector3<T> right = math::cross(dir, _up);
            right.normalize();
            Quaternion<T> quat = Quaternion<float>::fromAxisRot(right, angle);
            dir = quat * dir;
            _up = quat * _up;
            _eye = _target - dir * len;
            _matViewUpdate = true;
        }
    };

    template<typename T>
    class PerspectiveCamera : public Camera<T>
    {
    private:
        T       _fovy;
        T       _zNear;
        T       _zFar;

    public:
        PerspectiveCamera(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up)
            : Camera(eye, target, up)
        {
        }

        T getFovy() const { return _fovy; }
        T getZNear() const { return _zNear; }
        T getZFar() const { return _zFar; }

        void    setFovy(T fovy)
        {
            _fovy = fovy;
            _matProjectionUpdate = true;
        }

        void    setZNear(T zNear)
        {
            _zNear = zNear;
            _matProjectionUpdate = true;
        }

        void    setZFar(T zFar)
        {
            _zFar = zFar;
            _matProjectionUpdate = true;
        }

        virtual const Matrix4<T>& getProjectionMatrix() override
        {
            if (_matProjectionUpdate)
            {
                _matProjection = Matrix4<T>::createPerspective(_fovy, _viewSize.x / _viewSize.y, _zNear, _zFar);
                _matProjectionUpdate = false;
            }
            return _matProjection;
        }        
    };

    template<typename T>
    class OrthoCamera : public Camera<T>
    {
    private:
        T       _left;
        T       _right;
        T       _top;
        T       _bottom;
        T       _zNear;
        T       _zFar;

    public:

        T getLeft() const { return _left; }
        T getRight() const { return _right; }
        T getTop() const { return _top; }
        T getBottom() const { return _bottom; }
        T getZNear() const { return _zNear; }
        T getZFar() const { return _zFar; }
        
        void set(T left, T right, T top, T bottom, T zNear, T zFar)
        {
            _left = left;
            _right = right;
            _top = top;
            _bottom = bottom;
            _zNear = zNear;
            _zFar = zFar;
            _matProjectionUpdate = true;
        }

        virtual const Matrix4<T>& getProjectionMatrix() override
        {
            if (_matProjectionUpdate)
            {
                _matProjection = Matrix4<T>::createOrtho(_left, _right, _bottom, _top, _zNear, _zFar);
                _matProjectionUpdate = false;
            }
            return _matProjection;
        }
    };

}

#endif //!SGE_CAMERA_H
