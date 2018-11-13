/** 
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeMath.h
 * date: 2017/12/01
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

 /************************************************************************/
 /*This file copy can copy to everywhere, it does not include other file */
 /************************************************************************/


#ifndef SGE_MATH_H
#define SGE_MATH_H

#pragma warning (disable: 4251)

#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2 0.707106781186547524401
#endif

#ifndef MAX
#   define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#   define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifdef FLT_EPSILON
#undef FLT_EPSILON
#define FLT_EPSILON     0.0000001f
#endif // FLT_EPSILON
#ifdef FLT_EPSILON
#undef DBL_EPSILON
#define DBL_EPSILON     0.0000000000000001
#endif // FLT_EPSILON
#ifdef max
#   undef max
#endif
#ifdef min
#   undef min
#endif
#ifndef MATH_TOLERANCE
#   define MATH_TOLERANCE       2e-37f
#endif

namespace sge {

#pragma pack(push, 1)

    typedef unsigned char   uchar;
    typedef unsigned char   byte;
    typedef unsigned short  ushort;
    typedef unsigned int    uint;

    //-------------[ overload math functions ]-------------

    // Convert angle from degree to radian ,eg: 180 --> M_PI(3.14***)
    inline float DEG2RAD(int x) { return x * ((float)M_PI / (float)180); }
    inline float DEG2RAD(float x) { return x * ((float)M_PI / (float)180); }
    inline double DEG2RAD(double x) { return x * ((double)M_PI / (double)180); }

    // Convert angle from radian to degree ,eg: M_PI(3.14***) --> 180
    inline float RAD2EDG(int x) { return (x) * ((float)180 / (float)M_PI); }
    inline float RAD2EDG(float x) { return (x) * ((float)180 / (float)M_PI); }
    inline double RAD2EDG(double x) { return (x) * ((double)180 / (double)M_PI); }

    // Equal test,"x==y" for integer, "fabs(x - y) < epsilon" for float
    inline bool equal(int x, int y) { return x == y; }
    inline bool equal(float x, float y) { return std::fabsf(x - y) < FLT_EPSILON; }
    inline bool equal(double x, double y) { return std::fabs(x - y) < DBL_EPSILON; }

    // Less test, "x<y" for int,"y - x > epsilon" for float
    inline bool less(int x, int y) { return x < y; }
    inline bool less(float x, float y) { return y - x > FLT_EPSILON; }
    inline bool less(double x, double y) { return y - x > DBL_EPSILON; }
    
    // sin(x),sine
    inline float sin(float x) { return std::sinf(x); }
    inline double sin(double x) { return std::sin(x); }

    // cos(x),cos
    inline float cos(float x) { return std::cosf(x); }
    inline double cos(double x) { return std::cos(x); }

    // sincos(x), *_S=sin(_X),*_C=cos(_X) 
    inline void sincos(float _X, float *_S, float *_C) { *_S = sin(_X); *_C = cos(_X); }
    inline void sincos(double _X, double *_S, double *_C) { *_S = sin(_X); *_C = cos(_X); }

    // tan(x),tan
    inline float tan(float x) { return std::tanf(x); }
    inline double tan(double x) { return std::tan(x); }

    // asin(x), arcsin
    inline float asin(float x) { return std::asinf(x); }
    inline double asin(double x) { return std::asin(x); }

    // acos(x), arccos
    inline float acos(float x) { return std::acosf(x); }
    inline double acos(double x) { return std::acos(x); }

    // atan(x), arctan
    inline float atan(float x) { return std::atanf(x); }
    inline double atan(double x) { return std::atan(x); }

    // atan2(x), arctan2
    inline float atan2(float x, float y) { return std::atan2f(x, y); }
    inline double atan2(double x, double y) { return std::atan2(x, y); }

    // sqrt(x), square
    inline float sqrt(int x) { return std::sqrtf((float)x); }
    inline float sqrt(float x) { return std::sqrtf(x); }
    inline double sqrt(double x) { return std::sqrt(x); }

    // abs
    inline long abs(long x) { return std::abs(x); }
    inline long long abs(long long x) { return std::abs(x); }
    inline int abs(int x) { return std::abs(x); }
    inline float abs(float x) { return std::fabsf(x); }
    inline double abs(double x) { return std::fabs(x); }
    

    template<typename T> class Vector2;
    template<typename T> class Vector3;
    template<typename T> class Vector4;
    template<typename T> class Matrix3;
    template<typename T> class Matrix4;
    template<typename T> class Quaternion;
    template<typename T> class Sphere;
    template<typename T> class Ray;

    /**
     * Class for two dimensional vector
     */
    template<typename T>
    class Vector2
    {
    public:
        T x;
        T y;

    public:

        /**
         * Creates and sets to (0,0)
         */
        Vector2()
            : x(0), y(0)
        {
        }

        /**
         * Creates and sets to (x,y)
         * @param x initial x-coordinate value
         * @param y initial y-coordinate value
         */
        Vector2(T x, T y)
            : x(x), y(y) 
        {
        }

        /**
         * Copy constructor
         * @param src Source of data for new created instance
         */
        Vector2(const Vector2<T> &src)
            : x(src.x), y(src.y) 
        {
        }

        /**
         * Copy casting constructor
         * @param src Source of data for new created instance
         */
        template<class FromT>
        Vector2(const Vector2<FromT>& src)
            : x(static_cast<T>(src.x)), y(static_cast<T>(src.y))
        {
        }

        /**
         * Copy operator
         * @param rhs Right side argument of binary operator
         */
        Vector2<T>& operator=(const Vector2<T> &rhs) 
        {
            x = rhs.x;
            y = rhs.y;
            return *this;
        }

        /**
         * Copy casting operator
         * @param rhs Right side argument of binary operator
         */
        template<class FromT>
        Vector2<T>& operator=(const Vector2<FromT>& rhs)
        {
            x = static_cast<T>(rhs.x);
            y = static_cast<T>(rhs.y);
            return *this;
        }
        
        /**
         * Array access operator
         * @param n Array index
         * @return x if n = 0, else return y
         */
        T& operator[](int n)
        {
            assert(n >= 0 && n <= 1);
            if (0 == n)
                return x;
            else
                return y;
        }

        /**
        * Constant array access operator
        * @param n Array index
        * @return x if n = 0, else return y
        */
        const T& operator[](int n) const
        {
            assert(n >= 0 && n <= 1);
            if (0 == n)
                return x;
            else
                return y;
        }

        /**
         * Get negate vector
         */
        friend Vector2<T> operator-(const Vector2 &v)
        {
            return Vector2<T>( -v.x, -v.y);
        }

        /**
         * Operator for add with a scalar
         * @param rhs Right side scalar.
         */
        Vector2<T> operator+(T rhs) const
        {
            return Vector2<T>(x + rhs, y + rhs);
        }

        /**
         * Operator for add with a vector
         * @param rhs Right side vector.
         */
        Vector2<T> operator+(const Vector2<T>& rhs) const
        {
            return Vector2<T>(x + rhs.x, y + rhs.y);
        }

        /**
         * Operator for add with a scalar
         * @param rhs Right side scalar.
         */
        Vector2<T>& operator+=(T rhs)
        {
            x += rhs;
            y += rhs;
            return *this;
        }

        /**
         * Operator for add with a vector
         * @param rhs Right side vector.
         */
        Vector2<T>& operator+=(const Vector2<T>& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        /**
         * Operator for subtract with a scalar
         * @param rhs Right side scalar.
         */
        Vector2<T> operator-(T rhs) const
        {
            return Vector2<T>(x - rhs, y - rhs);
        }

        /**
         * Operator for subtract with a vector
         * @param rhs Right side vector.
         */
        Vector2<T> operator-(const Vector2<T>& rhs) const
        {
            return Vector2<T>(x - rhs.x, y - rhs.y);
        }

        /**
         * Operator for subtract with a scalar
         * @param rhs Right side scalar.
         */
        Vector2<T>& operator-=(T rhs)
        {
            x -= rhs;
            y -= rhs;
            return *this;
        }

        /**
         * Operator for subtract with a vector
         * @param rhs Right side vector.
         */
        Vector2<T>& operator-=(const Vector2<T>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        /**
         * Operator for multiply with a scalar
         * @param rhs Right side scalar.
         */
        Vector2<T> operator*(T rhs) const
        {
            return Vector2<T>(x * rhs, y * rhs);
        }

        /**
        * Operator for multiply with a vector
        * @param rhs Right side vector.
        */
        Vector2<T> operator*(const Vector2<T>& rhs) const
        {
            return Vector2<T>(x * rhs.x, y * rhs.y);
        }

        /**
         * Operator for multiply with a scalar
         * @param rhs Right side scalar.
         */
        Vector2<T>& operator*=(T rhs)
        {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        /**
         * Operator for multiply with a vector
         * @param rhs Right side vector.
         */
        Vector2<T>& operator*=(const Vector2<T>& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            return *this;
        }

        /**
         * Operator for divide with a scalar
         * @param rhs Right side scalar.
         */
        Vector2<T> operator/(T rhs) const
        {
            return Vector2<T>(x / rhs, y / rhs);
        }

        /**
         * Operator for divide with a vector
         * @param rhs Right side vector.
         */
        Vector2<T> operator/(const Vector2<T>& rhs) const
        {
            return Vector2<T>(x / rhs.x, y / rhs.y);
        }

        /**
         * Operator for divide with a scalar
         * @param rhs Right side scalar.
         */
        Vector2<T>& operator/=(T rhs)
        {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        /**
         * Operator for divide with a vector
         * @param rhs Right side vector.
         */
        Vector2<T>& operator/=(const Vector2<T>& rhs)
        {
            x /= rhs.x;
            y /= rhs.y;
            return *this;
        }

        /**
         * Equal test operator
         * @param rhs Right side vector.
         * @note Test of equality is based of equal fun.
         */
        bool operator==(const Vector2<T>& rhs) const
        {
            return equal(x, rhs.x) && equal(y, rhs.y);
        }

        /**
         * Not equal test operator
         * @param rhs Right side vector.
         * @note Test of equality is based of equal fun.
         */
        bool operator!=(const Vector2<T>& rhs) const
        {
            return !(*this == rhs);
        }

        /**
         * Get length of vector
         */
        T length() const
        {
            return (T)sqrt(x * x + y * y);
        }

        /**
         * Return square of length.
         * @return length ^ 2
         */
        T lengthSq() const
        {
            return x * x + y * y;
        }

        /**
         * Normalize vector
         */
        void normalize()
        {
            T s = length();
            x /= s;
            y /= s;
        }

        /**
         * Conversion to pointer operator
         */
        operator T*()
        {
            return (T*)this;
        }

        /**
         * Conversion to constant pointer operator
         */
        operator const T*() const
        {
            return (const T*)this;
        }

        /**
         * Output to stream operator
         */
        friend std::ostream& operator<<(std::ostream& lhs, const Vector2<T>& rhs)
        {
            lhs << rhs.toString();
            return lhs;
        }

        /**
         * To string operator.
         */
        std::string toString() const
        {
            char buffer[32];
            sprintf(buffer, "%f,%f", x, y);
            return buffer;
        }

        /**
         * Linear interpolation of two vectors
         * @param fact Factor of interpolation. For translation from positon
         * of this vector to vector r, values of factor goes from 0.0 to 1.0.
         * @param v1 First Vector for interpolation
         * @param v2 Second Vector for interpolation
         */
        static Vector2<T> lerp(const Vector2<T>& v1, const Vector2<T>& v2, T fact)
        {
            return v1 + (v2 - v1) * fact;
        }

        /**
         * Gets vector containing minimal values of @a a and @a b coordinates.
         * @return Vector of minimal coordinates.
         */
        static Vector2<T> min(const Vector2<T>& a, const Vector2<T>& b)
        {
            return Vector2<T>(MIN(a.x, b.x), MIN(a.y, b.y));
        }

        /**
         * Gets vector containing maximal values of @a a and @a b coordinates.
         * @return Vector of maximal coordinates.
         */
        static Vector2<T> max(const Vector2<T>& a, const Vector2<T>& b)
        {
            return Vector2<T>(MAX(a.x, b.x), MAX(a.y, b.y));
        }

    };
    
    /**
     * Get a normalized vector2
     */
    template<typename T>
    Vector2<T> normalize(const Vector2<T>& v)
    {
        Vector2<T> ret = v;
        ret.normalize();
        return ret;
    }

    /**
     * Rect
     */
    template<typename T>
    struct Rect
    {
        Vector2<T>  pos;
        Vector2<T>  size;
    };

    typedef Vector2<int>    vec2i;
    typedef Vector2<int>    int2;
    typedef Vector2<short>  short2;
    typedef Vector2<ushort> ushort2;
    typedef Vector2<uint>   uint2;
    typedef Vector2<float>  vec2f;
    typedef Vector2<float>  float2;
    typedef Vector2<double> vec2r;
    typedef Vector2<double> real2;
    typedef Rect<int>       rect2i;
    typedef Rect<float>     rect2f;
    typedef Rect<double>    rect2r;

    /**
     * Dot product of two vectors.
     * @param a left side vector
     * @param b right side vector
     */
    template<typename T>
    T dot(const Vector2<T>& a, const Vector2<T>& b)
    {
        return a.x * b.x + a.y * b.y;
    }
    
    /**
     * Calc the lengh of vector P project on vector Q dir
     * @param P vector
     * @param Q vector
     */
    template<typename T>
    T projLength(const Vector2<T>& p, const Vector2<T>& q)
    {
        return dot(p, q) / q.length();
    }
    
    /**
     * Calc the vecotr of vector P project on vector Q dir
     * @param P vector
     * @param Q vector
     */
    template<typename T>
    Vector2<T> proj(const Vector2<T>& p, const Vector2<T>& q)
    {
        return q * (dot(p, q) / q.lengthSq());
    }
    

    /**
     * Class for three dimensional vector
     */
    template<typename T>
    class Vector3
    {
    public:
        union
        {
            struct
            {
                T x;
                T y;
                T z;
            };
            Vector2<T> xy;
        };
        
    public:

        /**
         * Creates and sets to (0,0,0)
         */
        Vector3()
            : x(0), y(0), z(0)
        {
        }

        /**
         * Creates and sets to (x,y,z)
         * @param x initial x-coordinate value
         * @param y initial y-coordinate value
         * @param z initial z-coordinate value
         */
        Vector3(T x, T y, T z)
            : x(x), y(y), z(z)
        {
        }

        /**
         * Copy constructor
         * @param src Source of data for new created instance
         */
        Vector3(const Vector3<T> &src)
            : x(src.x), y(src.y), z(src.z)
        {
        }

        /**
         * Copy casting constructor
         * @param src Source of data for new created instance
         */
        template<class FromT>
        Vector3(const Vector3<FromT>& src)
            : x(static_cast<T>(src.x))
            , y(static_cast<T>(src.y))
            , z(static_cast<T>(src.z))
        {
        }

        /**
         * Copy operator
         * @param rhs Right side argument of binary operator
         */
        Vector3<T>& operator=(const Vector3<T> &rhs)
        {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            return *this;
        }

        /**
         * Copy casting operator
         * @param rhs Right side argument of binary operator
         */
        template<class FromT>
        Vector3<T>& operator=(const Vector3<FromT>& rhs)
        {
            x = static_cast<T>(rhs.x);
            y = static_cast<T>(rhs.y);
            z = static_cast<T>(rhs.z);
            return *this;
        }

        /**
         * Array access operator
         * @param n Array index
         * @return x if n = 0, return y if n = 1, else return z
         */
        T& operator[](int n)
        {
            assert(n >= 0 && n <= 2);
            if (0 == n)
                return x;
            else if (1 == n)
                return y;
            else
                return z;
        }

        /**
         * Constant array access operator
         * @param n Array index
         * @return x if n = 0, return y if n = 1, else return z
         */
        const T& operator[](int n) const
        {
            assert(n >= 0 && n <= 2);
            if (0 == n)
                return x;
            else if (1 == n)
                return y;
            else
                return z;
        }

        /**
         * Get negate vector
         */
        friend Vector3<T> operator-(const Vector3& v)
        {
            return Vector3<T>(-v.x, -v.y, -v.z);
        }

        /**
         * Operator for add with a scalar
         * @param rhs Right side scalar.
         */
        Vector3<T> operator+(T rhs) const
        {
            return Vector3<T>(x + rhs, y + rhs, z + rhs);
        }

        /**
         * Operator for add with a vector
         * @param rhs Right side vector.
         */
        Vector3<T> operator+(const Vector3<T>& rhs) const
        {
            return Vector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        /**
         * Operator for add with a scalar
         * @param rhs Right side scalar.
         */
        Vector3<T>& operator+=(T rhs)
        {
            x += rhs;
            y += rhs;
            z += rhs;
            return *this;
        }

        /**
         * Operator for add with a vector
         * @param rhs Right side vector.
         */
        Vector3<T>& operator+=(const Vector3<T>& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        /**
         * Operator for subtract with a scalar
         * @param rhs Right side scalar.
         */
        Vector3<T> operator-(T rhs) const
        {
            return Vector3<T>(x - rhs, y - rhs, z - rhs);
        }

        /**
         * Operator for subtract with a vector
         * @param rhs Right side vector.
         */
        Vector3<T> operator-(const Vector3<T>& rhs) const
        {
            return Vector3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        /**
         * Operator for subtract with a scalar
         * @param rhs Right side scalar.
         */
        Vector3<T>& operator-=(T rhs)
        {
            x -= rhs;
            y -= rhs;
            z -= rhs;
            return *this;
        }

        /**
         * Operator for subtract with a vector
         * @param rhs Right side vector.
         */
        Vector3<T>& operator-=(const Vector3<T>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        /**
         * Operator for multiply with a scalar
         * @param rhs Right side scalar.
         */
        Vector3<T> operator*(T rhs) const
        {
            return Vector3<T>(x * rhs, y * rhs, z * rhs);
        }

        /**
         * Operator for multiply with a vector
         * @param rhs Right side vector.
         */
        Vector3<T> operator*(const Vector3<T>& rhs) const
        {
            return Vector3<T>(x * rhs.x, y * rhs.y, z * rhs.z);
        }

        /**
         * Operator for multiply with a scalar
         * @param rhs Right side scalar.
         */
        Vector3<T>& operator*=(T rhs)
        {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }

        /**
         * Operator for multiply with a vector
         * @param rhs Right side vector.
         */
        Vector3<T>& operator*=(const Vector3<T>& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            return *this;
        }

        /**
         * Operator for divide with a scalar
         * @param rhs Right side scalar.
         */
        Vector3<T> operator/(T rhs) const
        {
            return Vector3<T>(x / rhs, y / rhs, z / rhs);
        }

        /**
         * Operator for divide with a vector
         * @param rhs Right side vector.
         */
        Vector3<T> operator/(const Vector3<T>& rhs) const
        {
            return Vector3<T>(x / rhs.x, y / rhs.y, z / rhs.z);
        }

        /**
         * Operator for divide with a scalar
         * @param rhs Right side scalar.
         */
        Vector3<T>& operator/=(T rhs)
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }

        /**
         * Operator for divide with a vector
         * @param rhs Right side vector.
         */
        Vector3<T>& operator/=(const Vector3<T>& rhs)
        {
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            return *this;
        }

        /**
         * Equal test operator
         * @param rhs Right side vector.
         * @note Test of equality is based of equal fun.
         */
        bool operator==(const Vector3<T>& rhs) const
        {
            return equal(x, rhs.x) && equal(y, rhs.y) && equal(z, rhs.z);
        }

        /**
         * Not equal test operator
         * @param rhs Right side vector.
         * @note Test of equality is based of equal fun.
         */
        bool operator!=(const Vector3<T>& rhs) const
        {
            return !(*this == rhs);
        }

        /**
         * Get length of vector
         */
        T length() const
        {
            return (T)sqrt(x * x + y * y + z * z);
        }

        /**
         * Return square of length.
         * @return length ^ 2
         */
        T lengthSq() const
        {
            return x * x + y * y + z * z;
        }

        /**
         * Normalize vector
         */
        void normalize()
        {
            T s = length();
            x /= s;
            y /= s;
            z /= s;
        }

        /**
         * Conversion to pointer operator
         */
        operator T*()
        {
            return (T*)this;
        }

        /**
         * Conversion to constant pointer operator
         */
        operator const T*() const
        {
            return (const T*)this;
        }

        /**
         * Output to stream operator
         */
        friend std::ostream& operator<<(std::ostream& lhs, const Vector3<T>& rhs)
        {
            lhs << rhs.toString();
            return lhs;
        }

        /**
         * To string operator.
         */
        std::string toString() const
        {
            char buffer[48];
            sprintf(buffer, "%f,%f,%f", x, y, z);
            return buffer;
        }

        /**
         * Linear interpolation of two vectors
         * @param fact Factor of interpolation. For translation from positon
         * of this vector to vector r, values of factor goes from 0.0 to 1.0.
         * @param v1 First Vector for interpolation
         * @param v2 Second Vector for interpolation
         */
        static Vector3<T> lerp(const Vector3<T>& v1, const Vector3<T>& v2, T fact)
        {
            return v1 + (v2 - v1) * fact;
        }

        /**
         * Gets vector containing minimal values of @a a and @a b coordinates.
         * @return Vector of minimal coordinates.
         */
        static Vector3<T> min(const Vector3<T>& a, const Vector3<T>& b)
        {
            return Vector3<T>(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z));
        }

        /**
         * Gets vector containing maximal values of @a a and @a b coordinates.
         * @return Vector of maximal coordinates.
         */
        static Vector3<T> max(const Vector3<T>& a, const Vector3<T>& b)
        {
            return Vector3<T>(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z));
        }

        /**
         * Rotate a vector around X-axis.
         * @param v The target vector
         * @param angle The angle in degree
         * @return the vector after around
         */
        static Vector3<T> rotateX(const Vector3<T>& v, T angle)
        {
            Vector3<T> res(v);
            T c, s;
            sincos(DEG2RAD(angle), &s, &c);
            res.y = v.y * c - v.z * s;
            res.z = v.y * s + v.z * c;
            return res;
        }

        /**
         * Rotate a vector around Y-axis.
         * @param v The target vector
         * @param angle The angle in degree
         * @return the vector after around
         */
        static Vector3<T> rotateY(Vector3<T> const & v, T angle)
        {
            Vector3<T> res = v;
            T c, s;
            sincos(DEG2RAD(angle), &s, &c);
            res.x = v.x * c + v.z * s;
            res.z = -v.x * s + v.z * c;
            return res;
        }

        /**
         * Rotate a vector around Z-axis.
         * @param v The target vector
         * @param angle The angle in degree
         * @return the vector after around
         */
        static Vector3<T> rotateZ(Vector3<T> const & v, T angle)
        {
            Vector3<T> res = v;
            T c, s;
            sincos(DEG2RAD(angle), &s, &c);
            res.x = v.x * c - v.y * s;
            res.y = v.x * s + v.y * c;
            return res;
        }
    };

    /**
     * Get a normalized vector3
     */
    template<typename T>
    Vector3<T> normalize(const Vector3<T>& v)
    {
        Vector3<T> ret = v;
        ret.normalize();
        return ret;
    }

    typedef Vector3<char>   char3;
    typedef Vector3<uchar>  uchar3;
    typedef Vector3<uchar>  rgb;
    typedef Vector3<int>    vec3i;
    typedef Vector3<int>    int3;
    typedef Vector3<short>  short3;
    typedef Vector3<ushort> ushort3;
    typedef Vector3<uint>   uint3;
    typedef Vector3<float>  vec3f;
    typedef Vector3<float>  float3;
    typedef Vector3<double> vec3r;
    typedef Vector3<double> real3;
        
    /**
     * Dot product of two vectors.
     * @param a left side vector
     * @param b right side vector
     */
    template<typename T>
    T dot(const Vector3<T>& a, const Vector3<T>& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    
    /**
     * Cross product of two vectors.
     * @param a left side vector
     * @param b right side vector
     */
    template<typename T>
    Vector3<T> cross(const Vector3<T>& a, const Vector3<T>& b)
    {
        return Vector3<T>(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y);
    }
    
    
    /**
     * Calc the lengh of vector P project on vector Q dir
     * @param P vector
     * @param Q vector
     */
    template<typename T>
    T projLength(const Vector3<T>& p, const Vector3<T>& q)
    {
        return dot(p, q) / q.length();
    }
    
    /**
     * Calc the vecotr of vector P project on vector Q dir
     * @param P vector
     * @param Q vector
     */
    template<typename T>
    Vector3<T> proj(const Vector3<T>& p, const Vector3<T>& q)
    {
        return q * (dot(p, q) / q.lengthSq());
    }
    

    /**
     * Class for four dimensional vector
     */
    template<typename T>
    class Vector4
    {
    public:

        union
        {
            struct
            {
                T   x;
                T   y;
                T   z;
                T   w;
            };
            Vector3<T>  xyz;
        };


    public:

        /**
         * Creates and sets to (0,0,0,0)
         */
        Vector4()
            : x(0), y(0), z(0), w(0)
        {
        }

        /**
         * Creates and sets to (x,y,z,w)
         * @param x initial x-coordinate value
         * @param y initial y-coordinate value
         * @param z initial z-coordinate value
         * @param w initial w-coordinate value
         */
        Vector4(T x, T y, T z, T w)
            : x(x), y(y), z(z), w(w)
        {
        }

        /**
         * Creates from vector3 and sets to (v.x,v.y,v.z,w)
         * @param v initial vector3
         * @param w initial w-coordinate value
         */
        Vector4(const Vector3<T>& v, T w = 1)
            : x(v.x), y(v.y), z(v.z), w(w)
        {
        }

        /**
         * Copy constructor
         * @param src Source of data for new created instance
         */
        Vector4(const Vector4<T> &src)
            : x(src.x), y(src.y), z(src.z), w(src.w)
        {
        }

        /**
         * Copy casting constructor
         * @param src Source of data for new created instance
         */
        template<class FromT>
        Vector4(const Vector4<FromT>& src)
            : x(static_cast<T>(src.x))
            , y(static_cast<T>(src.y))
            , z(static_cast<T>(src.z))
            , w(static_cast<T>(src.w))
        {
        }

        /**
         * Copy operator
         * @param rhs Right side argument of binary operator
         */
        Vector4<T>& operator=(const Vector4<T> &rhs)
        {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            w = rhs.w;
            return *this;
        }

        /**
         * Copy casting operator
         * @param rhs Right side argument of binary operator
         */
        template<class FromT>
        Vector4<T>& operator=(const Vector4<FromT>& rhs)
        {
            x = static_cast<T>(rhs.x);
            y = static_cast<T>(rhs.y);
            z = static_cast<T>(rhs.z);
            w = static_cast<T>(rhs.w);
            return *this;
        }

        /**
         * Array access operator
         * @param n Array index
         * @return x if n = 0, return y if n = 1, return z if n = 2,else return w
         */
        T& operator[](int n)
        {
            assert(n >= 0 && n <= 3);
            if (0 == n)
                return x;
            else if (1 == n)
                return y; 
            else if (2 == n)
                return z;
            else
                return w;
        }

        /**
         * Array access operator
         * @param n Array index
         * @return x if n = 0, return y if n = 1, return z if n = 2,else return w
         */
        const T& operator[](int n) const
        {
            assert(n >= 0 && n <= 3);
            if (0 == n)
                return x;
            else if (1 == n)
                return y; 
            else if (2 == n)
                return z;
            else
                return w;
        }
        
        /**
         * Get negate vector
         */
        friend Vector4<T> operator-(const Vector4& v)
        {
            return Vector4<T>(-v.x, -v.y, -v.z, -v.w);
        }

        /**
         * Operator for add with a scalar
         * @param rhs Right side scalar.
         */
        Vector4<T> operator+(T rhs) const
        {
            return Vector4<T>(x + rhs, y + rhs, z + rhs, w + rhs);
        }

        /**
         * Operator for add with a vector
         * @param rhs Right side vector.
         */
        Vector4<T> operator+(const Vector4<T>& rhs) const
        {
            return Vector4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
        }

        /**
         * Operator for add with a scalar
         * @param rhs Right side scalar.
         */
        Vector4<T>& operator+=(T rhs)
        {
            x += rhs;
            y += rhs;
            z += rhs;
            w += rhs;
            return *this;
        }

        /**
         * Operator for add with a vector
         * @param rhs Right side vector.
         */
        Vector4<T>& operator+=(const Vector4<T>& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }

        /**
         * Operator for subtract with a scalar
         * @param rhs Right side scalar.
         */
        Vector4<T> operator-(T rhs) const
        {
            return Vector4<T>(x - rhs, y - rhs, z - rhs, w - rhs);
        }

        /**
         * Operator for subtract with a vector
         * @param rhs Right side vector.
         */
        Vector4<T> operator-(const Vector4<T>& rhs) const
        {
            return Vector4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
        }

        /**
         * Operator for subtract with a scalar
         * @param rhs Right side scalar.
         */
        Vector4<T>& operator-=(T rhs)
        {
            x -= rhs;
            y -= rhs;
            z -= rhs;
            w -= rhs;
            return *this;
        }

        /**
         * Operator for subtract with a vector
         * @param rhs Right side vector.
         */
        Vector4<T>& operator-=(const Vector4<T>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;
            return *this;
        }

        /**
         * Operator for multiply with a scalar
         * @param rhs Right side scalar.
         */
        Vector4<T> operator*(T rhs) const
        {
            return Vector4<T>(x * rhs, y * rhs, z * rhs, w * rhs);
        }

        /**
         * Operator for multiply with a vector
         * @param rhs Right side vector.
         */
        Vector4<T> operator*(const Vector4<T>& rhs) const
        {
            return Vector4<T>(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
        }

        /**
         * Operator for multiply with a scalar
         * @param rhs Right side scalar.
         */
        Vector4<T>& operator*=(T rhs)
        {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            w *= rhs;
            return *this;
        }

        /**
         * Operator for multiply with a vector
         * @param rhs Right side vector.
         */
        Vector4<T>& operator*=(const Vector4<T>& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            w *= rhs.w;
            return *this;
        }

        /**
         * Operator for divide with a scalar
         * @param rhs Right side scalar.
         */
        Vector4<T> operator/(T rhs) const
        {
            return Vector4<T>(x / rhs, y / rhs, z / rhs, w / rhs);
        }

        /**
         * Operator for divide with a vector
         * @param rhs Right side vector.
         */
        Vector4<T> operator/(const Vector4<T>& rhs) const
        {
            return Vector4<T>(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
        }

        /**
         * Operator for divide with a scalar
         * @param rhs Right side scalar.
         */
        Vector4<T>& operator/=(T rhs)
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            w /= rhs;
            return *this;
        }

        /**
         * Operator for divide with a vector
         * @param rhs Right side vector.
         */
        Vector4<T>& operator/=(const Vector4<T>& rhs)
        {
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            w /= rhs.w;
            return *this;
        }

        /**
         * Equal test operator
         * @param rhs Right side vector.
         * @note Test of equality is based of equal fun.
         */
        bool operator==(const Vector4<T>& rhs) const
        {
            return equal(x, rhs.x) && equal(y, rhs.y) && equal(z, rhs.z) && equal(w, rhs.w);
        }

        /**
         * Not equal test operator
         * @param rhs Right side vector.
         * @note Test of equality is based of equal fun.
         */
        bool operator!=(const Vector4<T>& rhs) const
        {
            return !(*this == rhs);
        }

        /**
         * Get length of vector
         */
        T length() const
        {
            return (T)sqrt(x * x + y * y + z * z + w * w);
        }

        /**
         * Return square of length.
         * @return length ^ 2
         */
        T lengthSq() const
        {
            return x * x + y * y + z * z + w * w;
        }

        /**
         * Normalize vector
         */
        void normalize()
        {
            T s = length();
            x /= s;
            y /= s;
            z /= s;
            w /= s;
        }

        /**
         * Conversion to pointer operator
         */
        operator T*()
        {
            return (T*)this;
        }

        /**
         * Conversion to constant pointer operator
         */
        operator const T*() const
        {
            return (const T*)this;
        }

        /**
         * Output to stream operator
         */
        friend std::ostream& operator<<(std::ostream& lhs, const Vector4<T>& rhs)
        {
            lhs << rhs.toString();
            return lhs;
        }

        /**
         * To string operator.
         */
        std::string toString() const
        {
            char buffer[64];
            sprintf(buffer, "%f,%f,%f,%f", x, y, z, w);
            return buffer;
        }

        /**
         * Linear interpolation of two vectors
         * @param fact Factor of interpolation. For translation from positon
         * of this vector to vector r, values of factor goes from 0.0 to 1.0.
         * @param v1 First Vector for interpolation
         * @param v2 Second Vector for interpolation
         */
        static Vector4<T> lerp(const Vector4<T>& v1, const Vector4<T>& v2, T fact)
        {
            return v1 + (v2 - v1) * fact;
        }

        /**
         * Gets vector containing minimal values of @a a and @a b coordinates.
         * @return Vector of minimal coordinates.
         */
        static Vector4<T> min(const Vector4<T>& a, const Vector4<T>& b)
        {
            return Vector4<T>(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z), MIN(a.w, b.w));
        }

        /**
         * Gets vector containing maximal values of @a a and @a b coordinates.
         * @return Vector of maximal coordinates.
         */
        static Vector4<T> max(const Vector4<T>& a, const Vector4<T>& b)
        {
            return Vector4<T>(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z), MAX(a.w, b.w));
        }
    };
    
    typedef Vector4<uchar>  char4;
    typedef Vector4<uchar>  uchar4;
    typedef Vector4<uchar>  rgba;
    typedef Vector4<short>  short4;
    typedef Vector4<ushort> ushort4;
    typedef Vector4<int>    vec4i;
    typedef Vector4<int>    int4;
    typedef Vector4<uint>   uint4;
    typedef Vector4<float>  vec4f;
    typedef Vector4<float>  float4;
    typedef Vector4<double> vec4r;
    typedef Vector4<double> real4;

    /**
     * Class for matrix 3x3.
     * @note Data stored in this matrix are in column major order. This arrangement suits OpenGL.
     * If you're using row major matrix, consider using fromRowMajorArray as way for construction
     * Matrix3<T> instance.
     */
    template<typename T>
    class Matrix3
    {
    public:
        union
        {
            T cel[3][3];
            T data[9];
            Vector3<T> row[3];
        };

    public:

        /**
         * Creates identity matrix
         */
        Matrix3()
        {
        }

        /**
         * Copy matrix values from array 
         * @param dt data array (these data must be in column major order!)
         */
        Matrix3(const T * dt)
        {
            memcpy(data, dt, sizeof(T) * 9);
        }

        /**
         * Copy constructor.
         * @param src Data source for new created instance of Matrix3
         */
        Matrix3(const Matrix3<T>& src)
        {
            memcpy(data, src.data, sizeof(T) * 9);
        }

        /**
         * Copy casting constructor.
         * @param src Data source for new created instance of Matrix3
         */
        template<class FromT>
        Matrix3(const Matrix3<FromT>& src)
        {
            for (int i = 0; i < 9; i++)
            {
                data[i] = static_cast<T>(src.data[i]);
            }
        }

        /**
         * Copy operator
         * @param rhs source matrix.
         */
        Matrix3<T>& operator=(const Matrix3<T>& rhs)
        {
            memcpy(data, rhs.data, sizeof(T) * 9);
            return *this;
        }

        /**
         * Copy casting operator
         * @param rhs source matrix.
         */
        template<class FromT>
        Matrix3<T>& operator=(const Matrix3<FromT>& rhs)
        {
            for (int i = 0; i < 9; i++)
            {
                data[i] = static_cast<T>(rhs.data[i]);
            }
            return *this;
        }

        /**
         * Copy operator
         * @param rhs source array.
         */
        Matrix3<T>& operator=(const T* rhs)
        {
            memcpy(data, rhs, sizeof(T) * 9);
            return *this;
        }

        /**
         * Resets matrix to be identity matrix
         */
        void identity()
        {
            for (int i = 0; i < 9; i++)
                data[i] = (i % 4) ? (T)0 : (T)1;
        }

        /**
         * Creates rotation matrix by rotation around axis.
         * @param xDeg Angle (in degrees) of rotation around axis X.
         * @param yDeg Angle (in degrees) of rotation around axis Y.
         * @param zDeg Angle (in degrees) of rotation around axis Z.
         */
        static Matrix3<T> createRotationAroundAxis(T xDeg, T yDeg, T zDeg)
        {
            T xRads(DEG2RAD(xDeg));
            T yRads(DEG2RAD(yDeg));
            T zRads(DEG2RAD(zDeg));

            Matrix3<T> ma, mb, mc;
            T ac, as, bc, bs, cc, cs;
            sincos(xRads, &as, &ac);
            sincos(yRads, &bs, &bc);
            sincos(zRads, &cs, &cc);

            ma.identity();
            ma.cel[1][1] = ac;
            ma.cel[2][1] = as;
            ma.cel[1][2] = -as;
            ma.cel[2][2] = ac;

            mb.identity();
            mb.cel[0][0] = bc;
            mb.cel[2][0] = -bs;
            mb.cel[0][2] = bs;
            mb.cel[2][2] = bc;

            mc.identity();
            mc.cel[0][0] = cc;
            mc.cel[1][0] = cs;
            mc.cel[0][1] = -cs;
            mc.cel[1][1] = cc;

            Matrix3<T> ret = ma * mb * mc;
            return ret;
        }

        /**
         * Create scale matrix with @a sx, @a sy, and @a sz
         * being values of matrix main diagonal.
         * @param sx Scale in X-axis
         * @param sy Scale in Y-axis
         * @param sz Scale in Z-axis
         * @return Transform matrix 4x4 with scale transformation.
         */
        static Matrix3<T> createScale(T sx, T sy, T sz)
        {
            Matrix3<T> ret;
            ret.identity();
            ret.cel[0][0] = sx;
            ret.cel[1][1] = sy;
            ret.cel[2][2] = sz;
            return ret;
        }

        /**
         * Creates new matrix 3x3 from a array in row major order.
         * @param arr An array of elements for 3x3 matrix in row major order.
         * @return An instance of Matrix3<T> representing @a arr
         */
        template<class FromT>
        static Matrix3<T> fromRowMajorArray(const FromT* arr)
        {
            const T retData[] =
            { 
                static_cast<T>(arr[0]), static_cast<T>(arr[3]), static_cast<T>(arr[6]),
                static_cast<T>(arr[1]), static_cast<T>(arr[4]), static_cast<T>(arr[7]),
                static_cast<T>(arr[2]), static_cast<T>(arr[5]), static_cast<T>(arr[8])
            };
            return retData;
        }

        /**
         * Creates new matrix 3x3 from a array in column major order.
         * @param arr An array of elements for 3x3 matrix in column major order.
         * @return An instance of Matrix3<T> representing @a arr
         */
        template<class FromT>
        static Matrix3<T> fromColumnMajorArray(const FromT* arr)
        {
            const T retData[] =
            { 
                static_cast<T>(arr[0]), static_cast<T>(arr[1]), static_cast<T>(arr[2]),
                static_cast<T>(arr[3]), static_cast<T>(arr[4]), static_cast<T>(arr[5]),
                static_cast<T>(arr[6]), static_cast<T>(arr[7]), static_cast<T>(arr[8]) 
            };
            return retData;
        }

        /**
         * Equal operator
         * @param rhs right side matirx.
         * @return true if all data[i] equal with rhs.data[i]
         * @note Test of equality is based of equal function.
         */
        bool operator==(const Matrix3<T>& rhs) const
        {
            for (int i = 0; i < 9; i++)
            {
                if (! equal(data[i], rhs.data[i]))
                    return false;
            }
            return true;
        }

        /**
         * Not equal operator
         * @param rhs right side matirx.
         * @return not (lhs == rhs) :-P
         */
        bool operator!=(const Matrix3<T>& rhs) const
        {
            return !(*this == rhs);
        }

        /**
         * Operator for add with a scalar
         * @param rhs Right side scalar.
         */
        Matrix3<T> operator+(T rhs) const
        {
            Matrix3<T> ret;
            for (int i = 0; i < 9; i++)
                ret.data[i] = data[i] + rhs;
            return ret;
        }

        /**
         * Operator for add with a matrix
         * @param rhs Right side matrix.
         */
        Matrix3<T> operator+(const Matrix3<T>& rhs) const
        {
            Matrix3<T> ret;
            for (int i = 0; i < 9; i++)
                ret.data[i] = data[i] + rhs.data[i];
            return ret;
        }

        /**
         * Operator for subtract with a scalar
         * @param rhs Right side scalar.
         */
        Matrix3<T> operator-(T rhs) const
        {
            Matrix3<T> ret;
            for (int i = 0; i < 9; i++)
                ret.data[i] = data[i] - rhs;
            return ret;
        }

        /**
         * Operator for subtract with a matrix
         * @param rhs Right side matrix.
         */
        Matrix3<T> operator-(const Matrix3<T>& rhs) const
        {
            Matrix3<T> ret;
            for (int i = 0; i < 9; i++)
                ret.data[i] = data[i] - rhs.data[i];
            return ret;
        }

        /**
         * Operator for multiply with a scalar
         * @param rhs Right side scalar.
         */
        Matrix3<T> operator*(T rhs) const
        {
            Matrix3<T> ret;
            for (int i = 0; i < 9; i++)
                ret.data[i] = data[i] * rhs;
            return ret;
        }

        /**
         * Operator for divide with a scalar
         * @param rhs Right side scalar.
         */
        Matrix3<T> operator/(T rhs) const
        {
            Matrix3<T> ret;
            for (int i = 0; i < 9; i++)
                ret.data[i] = data[i] / rhs;
            return ret;
        }

        /**
         * Operator for multiply with a vector
         * @param rhs Right side vector.
         */
        Vector3<T> operator*(const Vector3<T>& rhs) const
        {
            return Vector3<T>(data[0] * rhs.x + data[3] * rhs.y + data[6] * rhs.z,
                data[1] * rhs.x + data[4] * rhs.y + data[7] * rhs.z,
                data[2] * rhs.x + data[5] * rhs.y + data[8] * rhs.z);
        }

        /**
         * Operator for multiply with a matrix
         * @param rhs Right side matrix.
         */
        Matrix3<T> operator*(Matrix3<T> rhs) const
        {
            Matrix3<T> w;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    T n = 0;
                    for (int k = 0; k < 3; k++)
                        n += rhs.cel[i][k] * cel[k][j];
                    w.cel[i][j] = n;
                }
            }
            return w;
        }

        /**
         * Transpose matrix.
         */
        Matrix3<T> transpose()
        {
            Matrix3<T> ret;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    ret.cel[i][j] = cel[j][i];
                }
            }
            return ret;
        }

        /**
         * Get determinant of matrix
         * @return Determinant of matrix.
         */
        T det()
        {
            return +cel[0][0] * cel[1][1] * cel[2][2]
                + cel[0][1] * cel[1][2] * cel[2][0]
                + cel[0][2] * cel[1][0] * cel[2][1]
                - cel[0][0] * cel[1][2] * cel[2][1]
                - cel[0][1] * cel[1][0] * cel[2][2]
                - cel[0][2] * cel[1][1] * cel[2][0];
        }

        /**
         * Get inverse matrix
         * @return Inverse matrix of this matrix.
         */
        Matrix3<T> inverse()
        {
            Matrix3<T> ret;
            ret.cel[0][0] = cel[1][1] * cel[2][2] - cel[2][1] * cel[1][2];
            ret.cel[0][1] = cel[2][1] * cel[0][2] - cel[0][1] * cel[2][2];
            ret.cel[0][2] = cel[0][1] * cel[1][2] - cel[1][1] * cel[0][2];
            ret.cel[1][0] = cel[2][0] * cel[1][2] - cel[1][0] * cel[2][2];
            ret.cel[1][1] = cel[0][0] * cel[2][2] - cel[2][0] * cel[0][2];
            ret.cel[1][2] = cel[1][0] * cel[0][2] - cel[0][0] * cel[1][2];
            ret.cel[2][0] = cel[1][0] * cel[2][1] - cel[2][0] * cel[1][1];
            ret.cel[2][1] = cel[2][0] * cel[0][1] - cel[0][0] * cel[2][1];
            ret.cel[2][2] = cel[0][0] * cel[1][1] - cel[1][0] * cel[0][1];
            return ret / det();
        }

        /**
         * Conversion to pointer
         * @return Data pointer
         */
        operator T*()
        {
            return (T*)data;
        }

        /**
         * Conversion to pointer
         * @return Constant Data pointer
         */
        operator const T*() const
        {
            return (const T*)data;
        }

        /**
         * Output to stream operator
         */
        friend std::ostream& operator <<(std::ostream& lhs, const Matrix3<T>& rhs)
        {            
            lhs << rhs.toString();
            return lhs;
        }

        /**
         * To string operator.
         */
        std::string toString() const
        {
            char buffer[16 * 4 * 4];
            sprintf(buffer, "\n\t\t|%f,%f,%f|\n"
                            "\t\t|%f,%f,%f|\n"
                            "\t\t|%f,%f,%f|\n",
                data[0], data[1], data[2], 
                data[3], data[4], data[5], 
                data[6], data[7], data[8]);
            return buffer;
        }

    };

    typedef Matrix3<float> mat3f;
    typedef Matrix3<double> mat3r;

    /**
     * Class for matrix 4x4.
     * @note Data stored in this matrix are in column major order. This arrangement suits OpenGL.
     * If you're using row major matrix, consider using fromRowMajorArray as way for construction
     * Matrix4<T> instance.
     */
    template<typename T>
    class Matrix4
    {
    public:
        /**
         * Data stored in column major order
         */
        union
        {
            T           cel[4][4];
            T           data[16];
            Vector4<T>  row[4];
        };

    public:

        /**
         * Creates identity matrix
         */
        Matrix4()
        {
        }

        /**
         * Copy matrix values from array 
         * @param dt data array (these data must be in column major order!)
         */
        Matrix4(const T * dt)
        {
            memcpy(data, dt, sizeof(T) * 16);
        }

        /**
         * Copy constructor.
         * @param src Data source for new created instance of Matrix3
         */
        Matrix4(const Matrix4<T>& src)
        {
            memcpy(data, src.data, sizeof(T) * 16);
        }

        /**
         * Copy casting constructor.
         * @param src Data source for new created instance of Matrix3
         */
        template<class FromT>
        Matrix4(const Matrix4<FromT>& src)
        {
            for (int i = 0; i < 16; i++)
            {
                data[i] = static_cast<T>(src.data[i]);
            }
        }

        /**
         * Copy operator
         * @param rhs source matrix.
         */
        Matrix4<T>& operator=(const Matrix4<T>& rhs)
        {
            memcpy(data, rhs.data, sizeof(T) * 16);
            return *this;
        }

        /**
         * Copy casting operator
         * @param rhs source matrix.
         */
        template<class FromT>
        Matrix4<T>& operator=(const Matrix4<FromT>& rhs)
        {
            for (int i = 0; i < 16; i++)
            {
                data[i] = static_cast<T>(rhs.data[i]);
            }
            return *this;
        }

        /**
         * Copy operator
         * @param rhs source array.
         */
        Matrix4<T>& operator=(const T* rhs)
        {
            memcpy(data, rhs, sizeof(T) * 16);
            return *this;
        }

        /**
         * Resets matrix to be identity matrix
         */
        void identity()
        {
            for (int i = 0; i < 16; i++)
                data[i] = (i % 5) ? (T)0 : (T)1;
        }

        /**
         * Creates rotation matrix by rotation around axis.
         * @param xDeg Angle (in degrees) of rotation around axis X.
         * @param yDeg Angle (in degrees) of rotation around axis Y.
         * @param zDeg Angle (in degrees) of rotation around axis Z.
         */
        static Matrix4<T> createRotationAroundAxis(T xDeg, T yDeg, T zDeg) 
        {
            Matrix4<T> mat;
            mat.toRotationAroundAxis(xDeg, yDeg, zDeg);
            return mat;
        }

        /**
         * Change matrix to rotation matrix by rotation around axis.
         * @param xDeg Angle (in degrees) of rotation around axis X.
         * @param yDeg Angle (in degrees) of rotation around axis Y.
         * @param zDeg Angle (in degrees) of rotation around axis Z.
         */
        void toRotationAroundAxis(T xDeg, T yDeg, T zDeg)
        {
            T xRads(DEG2RAD(xDeg));
            T yRads(DEG2RAD(yDeg));
            T zRads(DEG2RAD(zDeg));

            Matrix4<T> ma, mb, mc;
            T ac, as, bc, bs, cc, cs;
            sincos(xRads, &as, &ac);
            sincos(yRads, &bs, &bc);
            sincos(zRads, &cs, &cc);

            ma.identity();
            ma.cel[1][1] = ac;
            ma.cel[2][1] = as;
            ma.cel[1][2] = -as;
            ma.cel[2][2] = ac;

            mb.identity();
            mb.cel[0][0] = bc;
            mb.cel[2][0] = -bs;
            mb.cel[0][2] = bs;
            mb.cel[2][2] = bc;

            mc.identity();
            mc.cel[0][0] = cc;
            mc.cel[1][0] = cs;
            mc.cel[0][1] = -cs;
            mc.cel[1][1] = cc;

            *this = ma * mb * mc;
        }

        /**
         * Creates rotation matrix to rotation around the axis
         * @param angle The around angle (in degrees)
         * @param axis The axis of rotation
         */
        static Matrix4<T> createRotationAroundAxis(T angle, Vector3<T> axis)
        {
            Matrix4<T> mat;
            mat.toRotationAroundAxis(angle, axis);
            return mat;
        }

        /**
         * Change matrix to rotation around the axis.
         * @param angle The around angle (in degrees)
         * @param axis The axis of rotation
         */
        void toRotationAroundAxis(T angle, Vector3<T> axis) 
        {
            // Make sure the input axis is normalized.
            axis.normalize();

            T c = cos(DEG2RAD(angle));
            T s = sin(DEG2RAD(angle));

            T t = T(1) - c;
            T tx = t * axis.x;
            T ty = t * axis.y;
            T tz = t * axis.z;
            T txy = tx * axis.y;
            T txz = tx * axis.z;
            T tyz = ty * axis.z;
            T sx = s * axis.x;
            T sy = s * axis.y;
            T sz = s * axis.z;
            
            data[0] = c + tx * axis.x;
            data[1] = txy + sz;
            data[2] = txz - sy;
            data[3] = T(0);

            data[4] = txy - sz;
            data[5] = c + ty * axis.y;
            data[6] = tyz + sx;
            data[7] = T(0);

            data[8] = txz + sy;
            data[9] = tyz - sx;
            data[10] = c + tz * axis.z;
            data[11] = T(0);

            data[12] = T(0);
            data[13] = T(0);
            data[14] = T(0);
            data[15] = T(1);
        }

        /**
         * Creates translation matrix.
         * @param x X-direction translation
         * @param y Y-direction translation
         * @param z Z-direction translation
         * @param w for W-coordinate translation (implicitly set to 1)
         */
        static Matrix4<T> createTranslation(T x, T y, T z, T w = 1)
        {
            Matrix4<T> mat;
            mat.identity();
            mat.setTranslation(x, y, z, w);
            return mat;
        }

        /**
         * Creates translation matrix.
         * @param v The translation Vector
         */
        static Matrix4<T> createTranslation(const Vector3<T>& v, T w = 1)
        {
            Matrix4<T> mat;
            mat.identity();
            mat.setTranslation(v.x, v.y, v.z, w);
            return mat;
        }

        /**
         * Set translation.
         * @param x X-direction translation
         * @param y Y-direction translation
         * @param z Z-direction translation
         * @param w for W-coordinate translation (implicitly set to 1)
         */
        void setTranslation(T x, T y, T z, T w = 1)
        {
            cel[3][0] = x;
            cel[3][1] = y;
            cel[3][2] = z;
            cel[3][3] = w;
        }

        /**
         * Create scale matrix with @a sx, @a sy, and @a sz
         * being values of matrix main diagonal.
         * @param sx Scale in X-axis
         * @param sy Scale in Y-axis
         * @param sz Scale in Z-axis
         * @return Transform matrix 4x4 with scale transformation.
         */
        static Matrix4<T> createScale(T sx, T sy, T sz)
        {
            Matrix4<T> mat;
            mat.identity();
            mat.cel[0][0] = sx;
            mat.cel[1][1] = sy;
            mat.cel[2][2] = sz;
            return mat;
        }

        /**
         * Creates new view matrix to look from specified position @a eyePos to specified position @a centerPos
         * @param eyePos A position of camera
         * @param centerPos A position where camera looks-at
         * @param upDir Direction of up vector
         * @return Resulting view matrix that looks from and at specific position.
         */
        static Matrix4<T> createLookAt(const Vector3<T>& eyePos, const Vector3<T>& centerPos, const Vector3<T>& upDir)
        {
            Vector3<T> forward, side, up;
            Matrix4<T> m;

            forward = centerPos - eyePos;
            up = upDir;

            forward.normalize();

            // Side = forward x up
            side = cross(forward, up);
            side.normalize();

            // Recompute up as: up = side x forward
            up = cross(side, forward);

            m.identity();

            m.cel[0][0] = side.x;
            m.cel[1][0] = side.y;
            m.cel[2][0] = side.z;

            m.cel[0][1] = up.x;
            m.cel[1][1] = up.y;
            m.cel[2][1] = up.z;

            m.cel[0][2] = -forward.x;
            m.cel[1][2] = -forward.y;
            m.cel[2][2] = -forward.z;

            m = m * createTranslation(-eyePos.x, -eyePos.y, -eyePos.z);
            return m;
        }

        /**
         * Creates perspective projection according specified frustum parameters.
         * @param left Specify the coordinate for the left vertical clipping plane,
         * @param right Specify the coordinate for the right vertical clipping plane.
         * @param bottom Specify the coordinate for the bottom horizontal clipping plane,
         * @param top Specify the coordinate for the top horizontal clipping plane.
         * @param zNear Specify the distance to the near clipping plane.  Distance must be positive.
         * @param zFar Specify the distance to the far depth clipping plane.  Distance must be positive.
         * @return Projection matrix for specified frustum.
         */
        static Matrix4<T> createFrustum(T left, T right, T bottom, T top, T zNear, T zFar)
        {
            /*
            |-------------------------------------------------------|
            |      2 zNear                                          |
            |   ------------        0           0           0       |
            |   right - left                                        |
            |                                                       |
            |                     2 zNear                           |
            |        0         ------------     0           0       |
            |                  top - bottom                         |
            |                                                       |
            |        A              B           C          -1       |
            |                                                       |
            |        0              0           D           0       |
            |-------------------------------------------------------|
                    A = (right + left) / (right - left)
                    B = (top + bottom) / (top - bottom)
                    C = - (zFar + zNear) / (zFar - zNear)
                    D = - (2 zFar zNear) / (zFar - zNear)
            */
            Matrix4<T> ret;

            const T invWidth = 1 / (right - left);
            const T invHeight = 1 / (top - bottom);
            const T invDepth = 1 / (zFar - zNear);

            const T twoZNear = 2 * zNear;

            ret.identity();

            ret.cel[0][0] = twoZNear * invWidth;
            ret.cel[1][1] = twoZNear * invHeight;

            ret.cel[2][0] = (right + left) * invWidth;
            ret.cel[2][1] = (top + bottom) * invHeight;
            ret.cel[2][2] = -(zFar + zNear) * invDepth;
            ret.cel[2][3] = -1;

            ret.cel[3][2] = -twoZNear * zFar * invDepth;

            return ret;
        }

        /**
         * Creates perspective projection.
         * @param fovy The degree angle of view, such the open angle of the eye
         * @param aspect The aspect ratio of view width and height, usually us screen aspect ratio
         * @param zNear Specify the distance to the near clipping plane.  Distance must be positive
         * @param zFar Specify the distance to the far depth clipping plane.  Distance must be positive
         * @return Projection matrix for specified frustum
         */
        static Matrix4<T> createPerspective(T fovy, T aspect, T zNear, T zFar)
        {
            T k = tan(DEG2RAD(fovy) / 2);
            T r = zNear * k * aspect;
            T t = zNear * k;
            return createFrustum(-r, r, -t, t, zNear, zFar);
        }

        /**
         * Creates OpenGL compatible orthographic projection matrix.
         * @param left Specify the coordinate for the left vertical clipping plane,
         * @param right Specify the coordinate for the right vertical clipping plane.
         * @param bottom Specify the coordinate for the bottom horizontal clipping plane,
         * @param top Specify the coordinate for the top horizontal clipping plane.
         * @param zNear Specify the distance to the nearer depth clipping plane.
         *       This value is negative if the plane is to be behind the viewer,
         * @param zFar Specify the distance to the farther depth clipping plane.
         *       This value is negative if the plane is to be behind the viewer.
         * @return Othrographic projection matrix.
         */
        static Matrix4<T> createOrtho(T left, T right, T bottom, T top, T zNear, T zFar)
        {
            /*
            |--------------------------------------------------------------|
            |         2                                                    |
            |   ------------        0               0               0      |
            |   right - left                                               |
            |                                                              |
            |                       2                                      |
            |         0       ------------          0               0      |
            |                 top - bottom                                 |
            |                                                              |
            |                                       -2                     |
            |         0             0          ------------         0      |
            |                                   zFar-zNear                 |
            |                                                              |
            |        tx             ty              tz              1      |
            |--------------------------------------------------------------|
                    tx = - (right + left) / (right - left)
                    ty = - (top + bottom) / (top - bottom)
                    tz = - (zFar + zNear) / (zFar - zNear)
            */

            const T invWidth = 1 / (right - left);
            const T invHeight = 1 / (top - bottom);
            const T invDepth = 1 / (zFar - zNear);

            Matrix4<T> ret;

            ret.identity();

            ret.cel[0][0] = 2 * invWidth;
            ret.cel[1][1] = 2 * invHeight;
            ret.cel[2][2] = -2 * invDepth;

            ret.cel[3][0] = -(right + left) * invWidth;
            ret.cel[3][1] = -(top + bottom) * invHeight;
            ret.cel[3][2] = -(zFar + zNear) * invDepth;

            return ret;
        }


        /**
         * Creates new matrix 4x4 from a array in row major order.
         * @param arr An array of elements for 4x4 matrix in row major order.
         * @return An instance of Matrix4<T> representing @a arr
         */
        template<class FromT>
        static Matrix4<T> fromRowMajorArray(const FromT* arr)
        {
            const T retData[] =
            { 
                static_cast<T>(arr[0]), static_cast<T>(arr[4]), static_cast<T>(arr[8]), static_cast<T>(arr[12]),
                static_cast<T>(arr[1]), static_cast<T>(arr[5]), static_cast<T>(arr[9]), static_cast<T>(arr[13]),
                static_cast<T>(arr[2]), static_cast<T>(arr[6]), static_cast<T>(arr[10]), static_cast<T>(arr[14]),
                static_cast<T>(arr[3]), static_cast<T>(arr[7]), static_cast<T>(arr[11]), static_cast<T>(arr[15]) 
            };
            return retData;
        }

        /**
         * Creates new matrix 4x4 from a array in column major order.
         * @param arr An array of elements for 4x4 matrix in column major order.
         * @return An instance of Matrix4<T> representing @a arr
         */
        template<class FromT>
        static Matrix4<T> fromColumnMajorArray(const FromT* arr)
        {
            const T retData[] =
            { 
                static_cast<T>(arr[0]), static_cast<T>(arr[1]), static_cast<T>(arr[2]), static_cast<T>(arr[3]),
                static_cast<T>(arr[4]), static_cast<T>(arr[5]), static_cast<T>(arr[6]), static_cast<T>(arr[7]),
                static_cast<T>(arr[8]), static_cast<T>(arr[9]), static_cast<T>(arr[10]), static_cast<T>(arr[11]),
                static_cast<T>(arr[12]), static_cast<T>(arr[13]), static_cast<T>(arr[14]), static_cast<T>(arr[15])
            };
            return retData;
        }

        /**
         * Equal operator
         * @param rhs right side matirx.
         * @return true if all data[i] equal with rhs.data[i]
         * @note Test of equality is based of equal function.
         */
        bool operator==(const Matrix4<T>& rhs) const
        {
            for (int i = 0; i < 16; i++)
            {
                if (! equal(data[i], rhs.data[i]))
                    return false;
            }
            return true;
        }

        /**
         * Not equal operator
         * @param rhs right side matirx.
         * @return not (lhs == rhs) :-P
         */
        bool operator!=(const Matrix4<T>& rhs) const
        {
            return !(*this == rhs);
        }

        /**
         * Operator for add with a scalar
         * @param rhs Right side scalar.
         */
        Matrix4<T> operator+(T rhs) const
        {
            Matrix4<T> ret;
            for (int i = 0; i < 16; i++)
                ret.data[i] = data[i] + rhs;
            return ret;
        }

        /**
         * Operator for add with a matrix
         * @param rhs Right side matrix.
         */
        Matrix4<T> operator+(const Matrix4<T>& rhs) const
        {
            Matrix4<T> ret;
            for (int i = 0; i < 16; i++)
                ret.data[i] = data[i] + rhs.data[i];
            return ret;
        }

        /**
         * Operator for subtract with a scalar
         * @param rhs Right side scalar.
         */
        Matrix4<T> operator-(T rhs) const
        {
            Matrix4<T> ret;
            for (int i = 0; i < 16; i++)
                ret.data[i] = data[i] - rhs;
            return ret;
        }

        /**
         * Operator for subtract with a matrix
         * @param rhs Right side matrix.
         */
        Matrix4<T> operator-(const Matrix4<T>& rhs) const
        {
            Matrix4<T> ret;
            for (int i = 0; i < 16; i++)
                ret.data[i] = data[i] - rhs.data[i];
            return ret;
        }

        /**
         * Operator for multiply with a scalar
         * @param rhs Right side scalar.
         */
        Matrix4<T> operator*(T rhs) const
        {
            Matrix4<T> ret;
            for (int i = 0; i < 16; i++)
                ret.data[i] = data[i] * rhs;
            return ret;
        }

        /**
         * Operator for divide with a scalar
         * @param rhs Right side scalar.
         */
        Matrix4<T> operator/(T rhs) const
        {
            Matrix4<T> ret;
            for (int i = 0; i < 16; i++)
                ret.data[i] = data[i] / rhs;
            return ret;
        }

        /**
         * Operator for multiply with a vector
         * @param rhs Right side vector.
         */
        Vector3<T> operator*(const Vector3<T>& rhs) const
        {
            Vector4<T> ret = operator*(Vector4<T>(rhs, 1));
            return ret.xyz / ret.w;
        }

        /**
         * Operator for multiply with a vector
         * @param rhs Right side vector.
         */
        Vector4<T> operator*(const Vector4<T>& rhs) const
        {
            return Vector4<T>(data[0] * rhs.x + data[4] * rhs.y + data[8] * rhs.z + data[12] * rhs.w,
                data[1] * rhs.x + data[5] * rhs.y + data[9] * rhs.z + data[13] * rhs.w,
                data[2] * rhs.x + data[6] * rhs.y + data[10] * rhs.z + data[14] * rhs.w,
                data[3] * rhs.x + data[7] * rhs.y + data[11] * rhs.z + data[15] * rhs.w);
        }

        /**
         * Operator for multiply with a matrix
         * @param rhs Right side matrix.
         */
        Matrix4<T> operator*(Matrix4<T> rhs) const
        {
            Matrix4<T> w;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    T n = 0;
                    for (int k = 0; k < 4; k++)
                        n += rhs.cel[i][k] * cel[k][j];
                    w.cel[i][j] = n;
                }
            }
            return w;
        }

        /**
         * Sets translation part of matrix.
         *
         * @param v Vector of translation to be set.
         */
        void setTranslation(const Vector3<T>& v)
        {
            cel[3][0] = v.x;
            cel[3][1] = v.y;
            cel[3][2] = v.z;
            cel[3][3] = 1;
        }

        /**
         * Get translation part of matrix.
         */
        Vector3<T> getTranslation() const
        {
            return row[3].xyz;
        }

        /**
         * Sets rotation part (matrix 3x3) of matrix.
         *
         * @param m Rotation part of matrix
         */
        void setRotation(const Matrix3<T>& m)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    cel[i][j] = m.cel[i][j];
                }
            }
        }

        /**
         * Sets matrix uniform scale values
         * @param s Uniform scale value
         */
        void setScale(T s)
        {
            cel[0][0] = cel[1][1] = cel[2][2] = s;
        }

        /**
         * Sets matrix scale for all axises.
         * @param sx X-axis scale factor
         * @param sy Y-axis scale factor
         * @param sz Z-axis scale factor
         */
        void setScale(T sx, T sy, T sz)
        {
            cel[0][0] = sx;
            cel[1][1] = sy;
            cel[2][2] = sz;
        }

        /**
         * Sets matrix scale for all axes.
         * @param s Scale factors for X, Y, and Z coordinate.
         */
        void setScale(const Vector3<T>& s)
        {
            cel[0][0] = s.x;
            cel[1][1] = s.y;
            cel[2][2] = s.z;
        }

        /**
         * Gets matrix scale
         * @return Scales (i.e. first three values from matrix diagonal.
         */
        Vector3<T> getScale() const
        {
            return Vector3<T>(cel[0][0], cel[1][1], cel[2][2]);
        }

        /**
         * Transpose matrix.
         */
        Matrix4<T> transpose()
        {
            Matrix4<T> ret;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    ret.cel[i][j] = cel[j][i];
                }
            }
            return ret;
        }

        /**
         * Get determinant of matrix
         * @return Determinant of matrix.
         */
        T det()
        {
            float a0 = data[0] * data[5] - data[1] * data[4];
            float a1 = data[0] * data[6] - data[2] * data[4];
            float a2 = data[0] * data[7] - data[3] * data[4];
            float a3 = data[1] * data[6] - data[2] * data[5];
            float a4 = data[1] * data[7] - data[3] * data[5];
            float a5 = data[2] * data[7] - data[3] * data[6];
            float b0 = data[8] * data[13] - data[9] * data[12];
            float b1 = data[8] * data[14] - data[10] * data[12];
            float b2 = data[8] * data[15] - data[11] * data[12];
            float b3 = data[9] * data[14] - data[10] * data[13];
            float b4 = data[9] * data[15] - data[11] * data[13];
            float b5 = data[10] * data[15] - data[11] * data[14];

            // Calculate the determinant.
            return (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0);
        }

        bool decompose(Vector3<T>* scale, Quaternion<T>* rotation, Vector3<T>* translation) const
        {
            if (translation)
            {
                // Extract the translation.
                translation->x = m[12];
                translation->y = m[13];
                translation->z = m[14];
            }

            // Nothing left to do.
            if (scale == NULL && rotation == NULL)
                return true;

            // Extract the scale.
            // This is simply the length of each axis (row/column) in the matrix.
            Vector3<T> xaxis(m[0], m[1], m[2]);
            T scaleX = xaxis.length();

            Vector3<T> yaxis(m[4], m[5], m[6]);
            T scaleY = yaxis.length();

            Vector3<T> zaxis(m[8], m[9], m[10]);
            T scaleZ = zaxis.length();

            // Determine if we have a negative scale (true if determinant is less than zero).
            // In this case, we simply negate a single axis of the scale.
            T det = det();
            if (det < 0)
                scaleZ = -scaleZ;

            if (scale)
            {
                scale->x = scaleX;
                scale->y = scaleY;
                scale->z = scaleZ;
            }

            // Nothing left to do.
            if (rotation == NULL)
                return true;

            // Scale too close to zero, can't decompose rotation.
            if (scaleX < MATH_TOLERANCE || scaleY < MATH_TOLERANCE || abs(scaleZ) < MATH_TOLERANCE)
                return false;

            T rn;

            // Factor the scale out of the matrix axes.
            rn = (T)1 / scaleX;
            xaxis.x *= rn;
            xaxis.y *= rn;
            xaxis.z *= rn;

            rn = (T)1 / scaleY;
            yaxis.x *= rn;
            yaxis.y *= rn;
            yaxis.z *= rn;

            rn = (T)1 / scaleZ;
            zaxis.x *= rn;
            zaxis.y *= rn;
            zaxis.z *= rn;

            // Now calculate the rotation from the resulting matrix (axes).
            T trace = xaxis.x + yaxis.y + zaxis.z + 1.0f;

            if (trace > FLT_EPSILON)
            {
                T s = (T)0.5 / sqrt(trace);
                rotation->w = (T)0.25 / s;
                rotation->x = (yaxis.z - zaxis.y) * s;
                rotation->y = (zaxis.x - xaxis.z) * s;
                rotation->z = (xaxis.y - yaxis.x) * s;
            }
            else
            {
                // Note: since xaxis, yaxis, and zaxis are normalized, 
                // we will never divide by zero in the code below.
                if (xaxis.x > yaxis.y && xaxis.x > zaxis.z)
                {
                    T s = (T)0.5 / sqrt((T)1 + xaxis.x - yaxis.y - zaxis.z);
                    rotation->w = (yaxis.z - zaxis.y) * s;
                    rotation->x = (T)0.25 / s;
                    rotation->y = (yaxis.x + xaxis.y) * s;
                    rotation->z = (zaxis.x + xaxis.z) * s;
                }
                else if (yaxis.y > zaxis.z)
                {
                    T s = (T)0.5 / sqrt((T)1 + yaxis.y - xaxis.x - zaxis.z);
                    rotation->w = (zaxis.x - xaxis.z) * s;
                    rotation->x = (yaxis.x + xaxis.y) * s;
                    rotation->y = (T)0.25 / s;
                    rotation->z = (zaxis.y + yaxis.z) * s;
                }
                else
                {
                    T s = (T)0.5 / sqrt((T)1 + zaxis.z - xaxis.x - yaxis.y);
                    rotation->w = (xaxis.y - yaxis.x) * s;
                    rotation->x = (zaxis.x + xaxis.z) * s;
                    rotation->y = (zaxis.y + yaxis.z) * s;
                    rotation->z = (T)0.25 / s;
                }
            }

            return true;
        }

        /**
         * Get inverse matrix
         * @return Inverse matrix of this matrix.
         */
        bool inverse()
        {
            T a0 = data[0] * data[5] - data[1] * data[4];
            T a1 = data[0] * data[6] - data[2] * data[4];
            T a2 = data[0] * data[7] - data[3] * data[4];
            T a3 = data[1] * data[6] - data[2] * data[5];
            T a4 = data[1] * data[7] - data[3] * data[5];
            T a5 = data[2] * data[7] - data[3] * data[6];
            T b0 = data[8] * data[13] - data[9] * data[12];
            T b1 = data[8] * data[14] - data[10] * data[12];
            T b2 = data[8] * data[15] - data[11] * data[12];
            T b3 = data[9] * data[14] - data[10] * data[13];
            T b4 = data[9] * data[15] - data[11] * data[13];
            T b5 = data[10] * data[15] - data[11] * data[14];

            // Calculate the determinant.
            T det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

            // Close to zero, can't invert.
            if (abs(det) <= MATH_TOLERANCE)
                return false;

            // Support the case where m == dst.
            Matrix4<T> inverse;
            inverse.data[0] = data[5] * b5 - data[6] * b4 + data[7] * b3;
            inverse.data[1] = -data[1] * b5 + data[2] * b4 - data[3] * b3;
            inverse.data[2] = data[13] * a5 - data[14] * a4 + data[15] * a3;
            inverse.data[3] = -data[9] * a5 + data[10] * a4 - data[11] * a3;

            inverse.data[4] = -data[4] * b5 + data[6] * b2 - data[7] * b1;
            inverse.data[5] = data[0] * b5 - data[2] * b2 + data[3] * b1;
            inverse.data[6] = -data[12] * a5 + data[14] * a2 - data[15] * a1;
            inverse.data[7] = data[8] * a5 - data[10] * a2 + data[11] * a1;

            inverse.data[8] = data[4] * b4 - data[5] * b2 + data[7] * b0;
            inverse.data[9] = -data[0] * b4 + data[1] * b2 - data[3] * b0;
            inverse.data[10] = data[12] * a4 - data[13] * a2 + data[15] * a0;
            inverse.data[11] = -data[8] * a4 + data[9] * a2 - data[11] * a0;

            inverse.data[12] = -data[4] * b3 + data[5] * b1 - data[6] * b0;
            inverse.data[13] = data[0] * b3 - data[1] * b1 + data[2] * b0;
            inverse.data[14] = -data[12] * a3 + data[13] * a1 - data[14] * a0;
            inverse.data[15] = data[8] * a3 - data[9] * a1 + data[10] * a0;

            *this = inverse * (1 / det);
            return true;
        }

        /**
         * Conversion to pointer
         * @return Data pointer
         */
        operator T*()
        {
            return (T*)data;
        }

        /**
         * Conversion to pointer
         * @return Constant Data pointer
         */
        operator const T*() const
        {
            return (const T*)data;
        }

        /**
         * Output to stream operator
         */
        friend std::ostream& operator <<(std::ostream& lhs, const Matrix4<T>& rhs)
        {
            lhs << rhs.toString();
            return lhs;
        }

        /**
         * To string operator.
         */
        std::string toString() const
        {
            char buffer[16 * 4 * 4];
            sprintf(buffer, "\n\t\t|%f,%f,%f,%f|\n"
                            "\t\t|%f,%f,%f,%f|\n"
                            "\t\t|%f,%f,%f,%f|\n"
                            "\t\t|%f,%f,%f,%f|\n",
                data[0], data[1], data[2], data[3],
                data[4], data[5], data[6], data[7],
                data[8], data[9], data[10], data[11],
                data[12], data[13], data[14], data[15]);
            return buffer;
        }
    };

    typedef Matrix4<float> mat4f;
    typedef Matrix4<double> mat4r;

    /**
     * Quaternion class
     */
    template<class T>
    class Quaternion
    {
    public:
        /**
         * Imaginary part of quaternion.
         */
        union
        {
            struct
            {
                T x;
                T y;
                T z;
            };
            Vector3<T> v;
        }; 
        
        /**
         * Real part of quaternion.
         */
        T w;
    public:

        /**
         * Quaternion constructor, sets quaternion to (0 + 0i + 0j + 0k).
         */
        Quaternion()
            : w(1), x(0), y(0), z(0)
        {
        }

        /**
         * Copy constructor.
         */
        Quaternion(const Quaternion<T>& q)
            : w(q.w), x(q.x), y(q.y), z(q.z)
        {
        }

        /**
         * Copy casting constructor.
         */
        template<class FromT>
        Quaternion(const Quaternion<FromT>& q)
            : w(static_cast<T>(q.w)), v(q.v)
        {
        }

        /**
         * Quaternion constructor
         * @param w_ Real part of quaternion.
         * @param v_ Complex part of quaternion (xi + yj + zk).
         */
        Quaternion(T w_, const Vector3<T>& v_)
            : w(w_), v(v_)
        {
        }

        /**
         * Quaternion constructor
         * @param w_ Real part of quaternion.
         * @param x_ Complex coefficient for i complex constant.
         * @param y_ Complex coefficient for j complex constant.
         * @param z_ Complex coefficient for k complex constant.
         */
        Quaternion(T w_, T x_, T y_, T z_)
            : w(w_), x(x_), y(y_), z(z_)
        {
        }

        /**
         * Copy operator
         * @param rhs Right side quaternion.
         */
        Quaternion<T>& operator=(const Quaternion<T>& rhs)
        {            
            w = rhs.w;
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            return *this;
        }

        /**
         * Copy convert operator
         * @param rhs Right side quaternion.
         */
        template<class FromT>
        Quaternion<T>& operator=(const Quaternion<FromT>& rhs)
        {
            w = static_cast<T>(rhs.w);
            v = rhs.v;
            return *this;
        }

        /**
         * Get negate quaternion
         */
        Quaternion<T> operator-() const
        {
            return Quaternion<T>(-w, -x, -y, -z);
        }

        /**
         * Get conjugate quaternion
         */
        Quaternion<T> operator~() const
        {
            return Quaternion<T>(w, -x, -y, -z);
        }

        /**
         * Operator for add with a quaternion
         * @param rhs Right side quaternion.
         */
        Quaternion<T> operator+(const Quaternion<T>& rhs) const
        {
            const Quaternion<T>& lhs = *this;
            return Quaternion<T>(lhs.w + rhs.w, lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
        }

        /**
         * Operator for add with a quaternion
         * @param rhs Right side quaternion.
         */
        Quaternion<T>& operator+=(const Quaternion<T>& rhs)
        {
            w += rhs.w;
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        /**
         * Operator for subtract with a scalar
         * @param rhs Right side scalar.
         */
        Quaternion<T> operator-(const Quaternion<T>& rhs) const
        {
            const Quaternion<T>& lhs = *this;
            return Quaternion<T>(lhs.w - rhs.w, lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
        }

        /**
         * Operator for subtract with a scalar
         * @param rhs Right side scalar.
         */
        Quaternion<T>& operator-=(const Quaternion<T>& rhs)
        {
            w -= rhs.w;
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        /**
         * Operator for multiply with a quaternion
         * @param rhs Right side quaternion.
         */
        Quaternion<T> operator*(const Quaternion<T>& rhs) const
        {
            const Quaternion<T>& lhs = *this;
            return Quaternion<T>(lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
                lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
                lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x,
                lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w);
        }

        /**
         * Operator for multiply with a scalar
         * @param rhs Right side scalar.
         */
        Quaternion<T> operator*(T rhs) const
        {
            return Quaternion<T>(w * rhs, x * rhs, y * rhs, z * rhs);
        }

        /**
         * Transform a vector3
         * @param v The vector
         */
        Vector3<T> operator*(Vector3<T> v) const
        {
            Vector3<T> uv = cross(this->v, v);
            Vector3<T> uuv = cross(this->v, uv);
            uv *= (2 * w);
            uuv *= 2;
            return v + uv + uuv;
        }

        /**
         * Operator for multiply with a quaternion
         * @param rhs Right side quaternion.
         */
        Quaternion<T>& operator*=(const Quaternion<T>& rhs)
        {
            Quaternion q = (*this) * rhs;
            w = q.w;
            x = q.x;
            y = q.y;
            z = q.z;
            return *this;
        }

        /**
         * Operator for multiply with a scalar
         * @param rhs Right side scalar.
         */
        Quaternion<T>& operator*=(T rhs)
        {
            w *= rhs;
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }

        /**
         * Equal test operator
         * @param rhs Right side vector.
         * @note Test of equality is based of equal fun.
         */
        bool operator==(const Quaternion<T>& rhs) const
        {
            const Quaternion<T>& lhs = *this;
            return (equal(lhs.w, rhs.w)) && lhs.v == rhs.v;
        }

        /**
         * Not equal operator
         * @param rhs right side matirx.
         * @return not (lhs == rhs) :-P
         */
        bool operator!=(const Quaternion<T>& rhs) const
        {
            return !(*this == rhs);
        }

        /**
         * Get lenght of quaternion.
         */
        T length() const
        {
            return (T)sqrt(lengthSq());
        }

        /**
         * Return square of length.
         * @return length ^ 2
         */
        T lengthSq() const
        {
            return w * w + x * x + y * y + z * z;
        }

        /**
         * Normalize quaternion
         */
        void normalize()
        {
            T len = length();
            w /= len;
            x /= len;
            y /= len;
            z /= len;
        }

        /**
         * Creates quaternion for eulers angles.
         * @param x Rotation around x axis (in degrees).
         * @param y Rotation around y axis (in degrees).
         * @param z Rotation around z axis (in degrees).
         */
        static Quaternion<T> fromEulerAngles(T x, T y, T z)
        {
            Quaternion<T> ret = fromAxisRot(Vector3<T>(1, 0, 0), x)
                * fromAxisRot(Vector3<T>(0, 1, 0), y)
                * fromAxisRot(Vector3<T>(0, 0, 1), z);
            return ret;
        }

        /**
         * Creates quaternion as rotation around axis.
         * @param axis Unit vector expressing axis of rotation.
         * @param angleDeg Angle of rotation around axis (in degrees).
         */
        static Quaternion<T> fromAxisRot(Vector3<T> axis, T angleDeg)
        {
            T angleRad = (T)DEG2RAD(angleDeg);
            T sa2, ca2;
            sincos(angleRad / 2, &sa2, &ca2);
            return Quaternion<T>(ca2, axis * sa2);
        }

        /**
         * Get the quaternion can transform 'from' vector to 'to' vertor
         */
        static Quaternion<T> fromTwoVectors(const Vector3<T>& from, const Vector3<T>& to)
        {
            T cosTheta = dot(from, to);
            Vector3<T>  rotationAxis;

            if (cosTheta >= static_cast<T>(1) - FLT_EPSILON) {
                // orig and dest point in the same direction
                return Quaternion<T>();
            }

            if (cosTheta < static_cast<T>(-1) + FLT_EPSILON)
            {
                // special case when vectors in opposite directions :
                // there is no "ideal" rotation axis
                // So guess one; any will do as long as it's perpendicular to start
                // This implementation favors a rotation around the Up axis (Y),
                // since it's often what you want to do.
                rotationAxis = cross(Vector3<T>(0, 0, 1), from);
                if (rotationAxis.lengthSq() < FLT_EPSILON) // bad luck, they were parallel, try again!
                    rotationAxis = cross(Vector3<T>(1, 0, 0), from);

                rotationAxis.normalize();
                return Quaternion<T>::fromAxisRot(rotationAxis, M_PI);
            }

            // Implementation from Stan Melax's Game Programming Gems 1 article
            rotationAxis = cross(from, to);

            T s = sqrt((T(1) + cosTheta) * static_cast<T>(2));
            T invs = static_cast<T>(1) / s;

            return Quaternion<T>(
                s * static_cast<T>(0.5f),
                rotationAxis.x * invs,
                rotationAxis.y * invs,
                rotationAxis.z * invs);
        }

        /**
         * Converts quaternion into rotation matrix.
         * @return Rotation matrix expressing this quaternion.
         */
        Matrix3<T> rotMatrix()
        {
            Matrix3<T> ret;

            T xx = x * x;
            T xy = x * y;
            T xz = x * z;
            T xw = x * w;

            T yy = y * y;
            T yz = y * z;
            T yw = y * w;

            T zz = z * z;
            T zw = z * w;

            ret.cel[0][0] = 1 - 2 * (yy + zz);
            ret.cel[1][0] = 2 * (xy - zw);
            ret.cel[2][0] = 2 * (xz + yw);

            ret.cel[0][1] = 2 * (xy + zw);
            ret.cel[1][1] = 1 - 2 * (xx + zz);
            ret.cel[2][1] = 2 * (yz - xw);

            ret.cel[0][2] = 2 * (xz - yw);
            ret.cel[1][2] = 2 * (yz + xw);
            ret.cel[2][2] = 1 - 2 * (xx + yy);

            return ret;
        }

        /**
         * Converts quaternion into transformation matrix.
         * @note This method performs same operation as rotMatrix()
         * conversion method. But returns Matrix of 4x4 elements.
         * @return Transformation matrix expressing this quaternion.
         */
        Matrix4<T> transform() const
        {
            Matrix4<T> ret;

            T xx = x * x;
            T xy = x * y;
            T xz = x * z;
            T xw = x * w;

            T yy = y * y;
            T yz = y * z;
            T yw = y * w;

            T zz = z * z;
            T zw = z * w;

            ret.cel[0][0] = 1 - 2 * (yy + zz);
            ret.cel[1][0] = 2 * (xy - zw);
            ret.cel[2][0] = 2 * (xz + yw);
            ret.cel[3][0] = 0;

            ret.cel[0][1] = 2 * (xy + zw);
            ret.cel[1][1] = 1 - 2 * (xx + zz);
            ret.cel[2][1] = 2 * (yz - xw);
            ret.cel[3][1] = 0;

            ret.cel[0][2] = 2 * (xz - yw);
            ret.cel[1][2] = 2 * (yz + xw);
            ret.cel[2][2] = 1 - 2 * (xx + yy);
            ret.cel[3][2] = 0;

            ret.cel[0][3] = 0;
            ret.cel[1][3] = 0;
            ret.cel[2][3] = 0;
            ret.cel[3][3] = 1;

            return ret;

        }

        /**
         * Output to stream operator
         */
        friend std::ostream& operator <<(std::ostream& oss, const Quaternion<T>& q)
        {
            oss << q.toString();
            return oss;
        }

        /**
         * To string operator.
         */
        std::string toString() const
        {
            char buffer[64];
            sprintf(buffer, "%f,%f,%f,%f", w, x, y, z);
            return buffer;
        }

        /**
         * Creates quaternion from transform matrix.
         *
         * @param m Transform matrix used to compute quaternion.
         * @return Quaternion representing rotation of matrix m.
         */
        static Quaternion<T> fromMatrix(const Matrix4<T>& m)
        {
            Quaternion<T> q;

            T tr, s;
            tr = m.cel[1][1] + m.cel[2][2] + m.cel[3][3];
            if (! less((T)0, tr))
            {
                s = (T)0.5 / (T)sqrt(tr + (T)1.0);
                q.w = (T)0.25 / s;
                q.x = (m.cel[3][2] - m.cel[2][3]) * s;
                q.y = (m.cel[1][3] - m.cel[3][1]) * s;
                q.z = (m.cel[2][1] - m.cel[1][2]) * s;
            }
            else
            {
                T d0 = m.cel[1][1];
                T d1 = m.cel[2][2];
                T d2 = m.cel[3][3];

                char bigIdx = (d0 > d1) ? ((d0 > d2) ? 0 : 2) : ((d1 > d2) ? 1 : 2);

                if (bigIdx == 0)
                {
                    s = (T)2.0 * (T)sqrt((T)1.0 + m.cel[1][1] - m.cel[2][2] - m.cel[3][3]);
                    q.w = (m.cel[3][2] - m.cel[2][3]) / s;
                    q.x = (T)0.25 * s;
                    q.y = (m.cel[1][2] + m.cel[2][1]) / s;
                    q.z = (m.cel[1][3] + m.cel[3][1]) / s;
                }
                else if (bigIdx == 1)
                {
                    s = (T)2.0 * (T)sqrt((T)1.0 + m.cel[2][2] - m.cel[1][1] - m.cel[3][3]);
                    q.w = (m.cel[1][3] - m.cel[3][1]) / s;
                    q.x = (m.cel[1][2] + m.cel[2][1]) / s;
                    q.y = (T)0.25 * s;
                    q.z = (m.cel[2][3] + m.cel[3][2]) / s;
                }
                else
                {
                    s = (T)2.0 * (T)sqrt(1.0 + m.cel[3][3] - m.cel[1][1] - m.cel[2][2]);
                    q.w = (m.cel[2][1] - m.cel[1][2]) / s;
                    q.x = (m.cel[1][3] + m.cel[3][1]) / s;
                    q.y = (m.cel[2][3] + m.cel[3][2]) / s;
                    q.z = (T)0.25 * s;
                }
            }

            return q;
        }

        /**
         * Creates quaternion from rotation matrix.
         *
         * @param m Rotation matrix used to compute quaternion.
         * @return Quaternion representing rotation of matrix m.
         */
        static Quaternion<T> fromMatrix(const Matrix3<T>& m)
        {
            Quaternion<T> q;

            T tr, s;
            tr = m.cel[1][1] + m.cel[2][2] + m.cel[3][3];
            if (!less((T)0, tr))
            {
                s = (T)0.5 / (T)sqrt(tr + (T)1.0);
                q.w = (T)0.25 / s;
                q.x = (m.cel[3][2] - m.cel[2][3]) * s;
                q.y = (m.cel[1][3] - m.cel[3][1]) * s;
                q.z = (m.cel[2][1] - m.cel[1][2]) * s;
            }
            else
            {
                T d0 = m.cel[1][1];
                T d1 = m.cel[2][2];
                T d2 = m.cel[3][3];

                char bigIdx = (d0 > d1) ? ((d0 > d2) ? 0 : 2) : ((d1 > d2) ? 1 : 2);

                if (bigIdx == 0)
                {
                    s = (T)2.0 * (T)sqrt((T)1.0 + m.cel[1][1] - m.cel[2][2] - m.cel[3][3]);
                    q.w = (m.cel[3][2] - m.cel[2][3]) / s;
                    q.x = (T)0.25 * s;
                    q.y = (m.cel[1][2] + m.cel[2][1]) / s;
                    q.z = (m.cel[1][3] + m.cel[3][1]) / s;
                }
                else if (bigIdx == 1)
                {
                    s = (T)2.0 * (T)sqrt((T)1.0 + m.cel[2][2] - m.cel[1][1] - m.cel[3][3]);
                    q.w = (m.cel[1][3] - m.cel[3][1]) / s;
                    q.x = (m.cel[1][2] + m.cel[2][1]) / s;
                    q.y = (T)0.25 * s;
                    q.z = (m.cel[2][3] + m.cel[3][2]) / s;
                }
                else
                {
                    s = (T)2.0 * (T)sqrt(1.0 + m.cel[3][3] - m.cel[1][1] - m.cel[2][2]);
                    q.w = (m.cel[2][1] - m.cel[1][2]) / s;
                    q.x = (m.cel[1][3] + m.cel[3][1]) / s;
                    q.y = (m.cel[2][3] + m.cel[3][2]) / s;
                    q.z = (T)0.25 * s;
                }
            }

            return q;
        }

        /**
         * Get the angle
         */
        T angle() const
        {
            return acos(this->w) * static_cast<T>(2);
        }

        /**
         * Get the rotate axis
         */
        Vector3<T> axis() const
        {
            T tmp1 = static_cast<T>(1) - w * w;
            if (tmp1 <= static_cast<T>(0))
                return Vector3<T>(0, 0, 1);
            T tmp2 = static_cast<T>(1) / sqrt(tmp1);
            return Vector3<T>(x * tmp2, y * tmp2, z * tmp2);
        }


        /**
         * Linear interpolation of two quaternions
         * @param fact Factor of interpolation. For translation from position
         * of this vector to quaternion rhs, values of factor goes from 0.0 to 1.0.
         * @param q1 First Quaternion for interpolation
         * @param q2 Second Quaternion for interpolation
         */
        Quaternion<T> lerp(const Quaternion<T>& q1, const Quaternion<T>& q2, T fact)
        {
            return Quaternion<T>((1 - fact) * q1.w + fact * q2.w, Vector3<T>::lerp(q1.v, q2.v, fact));
        }

        /**
         * Computes spherical interpolation between quaternions (q1, q2)
         * using coefficient of interpolation r (in [0, 1]).
         * @param q1 First quaternion for interpolation.
         * @param q2 Second quaternion for interpolation.
         * @param r The ratio of interpolation form q1 (r = 0) to q2 (r = 1).
         * @return Result of interpolation.
         */
        static Quaternion<T> slerp(const Quaternion<T>& q1, const Quaternion<T>& q2, T r)
        {
            Quaternion<T> ret;
            T cosTheta = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
            T theta = acos(cosTheta);
            if (equal(theta, (T)0))
            {
                ret = q1;
            }
            else
            {
                T sinTheta = sqrt((T)1 - cosTheta * cosTheta);
                if (equal(sinTheta, (T)0))
                {
                    ret.w = (T)0.5 * q1.w + (T)0.5 * q2.w;
                    ret.v = Vector3<T>::lerp(q1.v, q2.v, (T)0.5);
                }
                else
                {
                    T rA = sin(((T)1.0 - r) * theta) / sinTheta;
                    T rB = sin(r * theta) / sinTheta;

                    ret.w = q1.w * rA + q2.w * rB;
                    ret.x = q1.x * rA + q2.x * rB;
                    ret.y = q1.y * rA + q2.y * rB;
                    ret.z = q1.z * rA + q2.z * rB;
                }
            }
            return ret;
        }

    };

    typedef Quaternion<float> quatf;
    typedef Quaternion<double> quatr;

    /**
     * Axes-aligned bounding-box (aka AABB) class.
     */
    template <typename T>
    class Aabb2
    {
    public:
        /**
         * Position of Min corner of bounding box.
         */
        Vector2<T> min;

        /**
         * Position of Max corner of bounding box
         */
        Vector2<T> max;

    public:

        /**
         * Constructs invalid axes-aligned bounding-box.
         * @see valid() for explanation of invalid bounding-box usage.
         */
        Aabb2()
            : min(1, 1), max(-1, -1)
        {
        }

        /**
         * Constructs axes-aligned bound-box containing one point @a point
         * @param point
         */
        template <typename SrcT>
        Aabb2(const Vector2<SrcT>& point)
            : min(point), max(point)
        {
        }

        /**
         * Constructs axes-aligned bounding-box form two corner points (@a x0, @a y0)
         * and (@a x1, @a y1)
         * @param x0 X-coordinate of first point
         * @param y0 Y-coordinate of first point
         * @param x1 X-coordinate of second point
         * @param y1 Y-coordinate of second point
         */
        template <typename SrcT>
        Aabb2(SrcT x0, SrcT y0, SrcT x1, SrcT y1)
            : min(MIN(x0, x1), MIN(y0, y1)),
            max(MAX(x0, x1), MAX(y0, y1))
        {
        }

        /**
         * Constructs axes-aligned bounding-box containing point (@a x, @a y)
         * @param x X-coordinate of point
         * @param y Y-coordinate of point
         */
        template <typename SrcT>
        Aabb2(SrcT x, SrcT y)
            : min(x, y), max(x, y)
        {
        }

        /**
         * Creates copy of axis-aligned bounding-box
         * @param src Source bounding-box
         */
        template <typename SrcT>
        Aabb2(const Aabb2<SrcT>& src)
            : min(src.min), max(src.max)
        {
        }

        /**
         * Assign operator
         * @param rhs source bounding-box
         * @return refenrence to this
         */
        template <typename SrcT>
        Aabb2<T>& operator=(const Aabb2<SrcT>& rhs)
        {
            min = rhs.min;
            max = rhs.max;
            return *this;
        }

        /**
         * Checks if bounding-box is valid. Valid bounding-box has non-negative size.
         * If an invalid bounding-box is extended by point or another bounding-box, the target
         * bounding box becomes valid and contains solely the source point or bounding-box respectively.
         * @return True if box is valid, otherwise false
         */
        bool valid() const
        {
            return min.x <= max.x && min.y <= max.y;
        }

        /**
         * Makes this bounding-box invalid. So calling valid() gets false.
         * @see valid() method for more info on usage of invalid bounding-boxes.
         */
        void invalidate()
        {
            min = Vector2<T>(1, 1);
            max = Vector2<T>(-1, -1);
        }

        /**
         * Extends this bounding-box by a point @a point.
         * @param point A point to extend bounding-box by.
         */
        template <typename SrcT>
        void extend(const Vector2<SrcT>& point)
        {
            if (!valid())
            {
                min = max = point;
            }
            else
            {
                min = Vector2<T>::min(min, point);
                max = Vector2<T>::max(max, point);
            }
        }

        /**
         * Extends this bounding-box by a box @a box.
         * @param box A box to extend this bounding-box by.
         */
        template <typename SrcT>
        void extend(const Aabb2<SrcT>& box)
        {
            if (!valid())
            {
                min = box.min;
                max = box.max;
            }
            else
            {
                min = Vector2<T>::min(min, box.min);
                max = Vector2<T>::max(max, box.max);
            }
        }

        /**
         * Gets a copy of this bounding-box extend by a point @a point.
         * @param point A point to extend the box by
         * @return Copy of extended bounding-box
         */
        template <typename SrcT>
        Aabb2<T> extended(const Vector2<SrcT>& point) const
        {
            Aabb2<T> ret(*this);
            ret.extend(point);
            return ret;
        }

        /**
         * Gets a copy of this bounding-box extnended by box @a box.
         * @param box A box to extend the copy be.
         * @return Copy of extended bounding-box
         */
        template <typename SrcT>
        Aabb2<T> extended(const Aabb2<SrcT>& box) const
        {
            Aabb2<T> ret(*this);
            ret.extend(box);
            return ret;
        }

        /**
         * Tests if the point @a point is within this bounding-box
         * @param point A point to be tested
         * @return True if point @a point lies within bounding-box, otherwise false.
         */
        template <typename SrcT>
        bool intersects(const Vector2<SrcT>& point) const
        {
            if (min.x > point.x || min.y > point.y
                || point.x > max.x || point.y > max.y)
                return false;

            return true;
        }

        /**
         * Tests if other bounding-box @a box intersects (even partially) with this bouding-box.
         * @param box A box to be tested for intersection.
         * @return True if there's intersection between boxes, otherwise false.
         */
        template <typename SrcT>
        bool intersects(const Aabb2<SrcT>& box) const
        {
            if (min.x > box.max.x || min.y > box.max.y
                || max.x < box.min.x || max.y < box.min.y)
                return false;

            return true;
        }

        /**
         * Gets result of intersection of this bounding-box with @a other bounding-box.
         * In case the boxes don't intersect, the returned bounding-box is invalid.
         * @param other Box to be tested
         * @return Result of intersection.
         * @see valid() method for more information on invalid bounding-boxes.
         */
        template <typename SrcT>
        Aabb2<T> intersection(const Aabb2<SrcT>& other) const
        {
            Aabb2<T> ret;
            if (min.x > other.max.x || min.y > other.max.y
                || max.x < other.min.x || max.y < other.min.y)
                return ret;

            ret.min = Vector2<T>::max(min, other.min);
            ret.max = Vector2<T>::min(max, other.max);

            return ret;
        }

        /**
         * Gets center point of bounding-box.
         * @return A center point of bounding-box.
         */
        Vector2<T> center() const
        {
            return (min + max) / 2;
        }

        /**
         * Gets extent of bounding-box.
         * @return Extent of bounding-box.
         */
        Vector2<T> extent() const
        {
            return (max - min) / 2;
        }

        /**
         * Gets diagonal size of bounding-box
         * @return Sizes for particular dimensions.
         */
        Vector2<T> size() const
        {
            return max - min;
        }

        /**
         * Gets all 8 corner-points of bounding box
         * @param i An index of bounding-box corner point. Valid values are 0 .. 7.
         * @return A position of @a i-th corner-point.
         * @note The order of points is as follows (where @c + denotes max-point and @c - min-point):
         * 1. (@c + @c +)
         * 2. (@c - @c +)
         * 3. (@c + @c -)
         * 4. (@c - @c -)
         */
        Vector2<T> point(size_t i) const
        {
            assert(i < 4);
            return Vector2<T>(i & 1 ? min.x : max.x, i & 2 ? min.y : max.y);
        }

        /**
         * Tests if @a rhs is equal to this bounding-box
         * @param rhs Right-hand side
         * @return True if @a rhs and this bounding-boxes are equal, otherwise false
         */
        template <typename RhsT>
        bool operator==(const Aabb2<RhsT>& rhs) const
        {
            return min == rhs.min && max == rhs.max;
        }

        /**
         * Tests if @a rhs is not equal to this bounding-box
         * @param rhs Right-hand side
         * @return True if @a rhs and this bounding-boxes are not equal, otherwise false
         */
        template <typename RhsT>
        bool operator!=(const Aabb2<RhsT>& rhs) const
        {
            return min != rhs.min || max != rhs.max;
        }

        /**
         * Extends this bounding-box by point @a rhs.
         * @param rhs A point to extend this bounding-box by
         * @return Reference to this
         */
        template <typename SrcT>
        Aabb2<T>& operator<<(const Vector2<SrcT>& rhs)
        {
            extend(rhs);
            return *this;
        }

        /**
         * Extends this bounding-box by box @a rhs.
         * @param rhs A box to extend this bounding-box by
         * @return Reference to this
         */
        template <typename SrcT>
        Aabb2<T>& operator<<(const Aabb2<SrcT>& rhs)
        {
            extend(rhs);
            return *this;
        }

        /**
         * Union of this and @a rhs bounding-boxes
         * @param rhs Right-hand side of union
         * @return A resulting bounding-box representing union
         */
        template <typename RhsT>
        Aabb2<T> operator|(const Aabb2<RhsT>& rhs) const
        {
            return extended(rhs);
        }

        /**
         * Intersection of this and @a rhs bounding-boxed
         * @param rhs Right-hand side
         * @return Resulting bouding-box representing the intersection.
         */
        template <typename RhsT>
        Aabb2<T> operator&(const Aabb2<RhsT>& rhs) const
        {
            return intersection(rhs);
        }

        /**
         * Outputs string representation of bounding-box @a rhs to output stream @a lhs
         * @param lhs Output stream to write to
         * @param rhs Bounding-box to write to output stream.
         * @return Reference to output stream @a lhs
         */
        friend std::ostream& operator<<(std::ostream& lhs, const Aabb2<T>& rhs)
        {
            lhs << rhs.toString();
            return lhs;
        }

        /**
         * To string operator.
         */
        std::string toString() const
        {
            char buffer[64];
            sprintf(buffer, "%f,%f,%f,%f", min.x, min.y, max.x, max.y);
            return buffer;
        }

    };

    typedef Aabb2<int> aabb2i;
    typedef Aabb2<float> aabb2f;
    typedef Aabb2<double> aabb2r;

    /**
     * Axes-aligned bounding-box (aka AABB) class.
     */
    template <typename T>
    class Aabb3
    {
    public:
        /**
         * Position of Min corner of bounding box.
         */
        Vector3<T> min;

        /**
         * Position of Max corner of bounding box
         */
        Vector3<T> max;

    public:

        /**
         * Constructs invalid axes-aligned bounding-box.
         * @see valid() for explanation of invalid bounding-box usage.
         */
        Aabb3()
            : min(1, 1, 1), max(-1, -1, -1)
        {
        }

        /**
         * Constructs axes-aligned bound-box containing one point @a point
         * @param point
         */
        template <typename SrcT>
        Aabb3(const Vector3<SrcT>& point)
            : min(point), max(point)
        {
        }

        /**
         * Constructs axes-aligned bounding-box form two corner points (@a x0, @a y0, @a z0)
         * and (@a x1, @a y1, @a z1)
         * @param x0 X-coordinate of first point
         * @param y0 Y-coordinate of first point
         * @param z0 Z-coordinate of first point
         * @param x1 X-coordinate of second point
         * @param y1 Y-coordinate of second point
         * @param z1 Z-coordinate of second point
         */
        template <typename SrcT>
        Aabb3(SrcT x0, SrcT y0, SrcT z0, SrcT x1, SrcT y1, SrcT z1)
            : min(MIN(x0, x1), MIN(y0, y1), MIN(z0, z1)),
            max(MAX(x0, x1), MAX(y0, y1), MAX(z0, z1))
        {
        }

        /**
         * Constructs axes-aligned bounding-box containing point (@a x, @a y, @a z)
         * @param x X-coordinate of point
         * @param y Y-coordinate of point
         * @param z Z-coordinate of point
         */
        template <typename SrcT>
        Aabb3(SrcT x, SrcT y, SrcT z)
            : min(x, y, z), max(x, y, z)
        {
        }

        /**
         * Creates copy of axis-aligned bounding-box
         * @param src Source bounding-box
         */
        template <typename SrcT>
        Aabb3(const Aabb3<SrcT>& src)
            : min(src.min), max(src.max)
        {
        }

        /**
         * Assign operator
         * @param rhs source bounding-box
         * @return refenrence to this
         */
        template <typename SrcT>
        Aabb3<T>& operator=(const Aabb3<SrcT>& rhs)
        {
            min = rhs.min;
            max = rhs.max;
            return *this;
        }

        /**
         * Checks if bounding-box is valid. Valid bounding-box has non-negative size.
         * If an invalid bounding-box is extended by point or another bounding-box, the target
         * bounding box becomes valid and contains solely the source point or bounding-box respectively.
         * @return True if box is valid, otherwise false
         */
        bool valid() const
        {
            return min.x <= max.x && min.y <= max.y && min.z <= max.z;
        }

        /**
         * Makes this bounding-box invalid. So calling valid() gets false.
         * @see valid() method for more info on usage of invalid bounding-boxes.
         */
        void invalidate()
        {
            min = Vector3<T>(1, 1, 1); max = Vector3<T>(-1, -1, -1);
        }

        /**
         * Extends this bounding-box by a point @a point.
         * @param point A point to extend bounding-box by.
         */
        template <typename SrcT>
        void extend(const Vector3<SrcT>& point)
        {
            if (!valid())
            {
                min = max = point;
            }
            else
            {
                min = Vector3<T>::min(min, point);
                max = Vector3<T>::max(max, point);
            }
        }

        /**
         * Extends this bounding-box by a box @a box.
         * @param box A box to extend this bounding-box by.
         */
        template <typename SrcT>
        void extend(const Aabb3<SrcT>& box)
        {
            if (!valid())
            {
                min = box.min;
                max = box.max;
            }
            else
            {
                min = Vector3<T>::min(min, box.min);
                max = Vector3<T>::max(max, box.max);
            }
        }

        /**
         * Gets a copy of this bounding-box extend by a point @a point.
         * @param point A point to extend the box by
         * @return Copy of extended bounding-box
         */
        template <typename SrcT>
        Aabb3<T> extended(const Vector3<SrcT>& point) const
        {
            Aabb3<T> ret(*this);
            ret.extend(point);
            return ret;
        }

        /**
         * Gets a copy of this bounding-box extnended by box @a box.
         * @param box A box to extend the copy be.
         * @return Copy of extended bounding-box
         */
        template <typename SrcT>
        Aabb3<T> extended(const Aabb3<SrcT>& box) const
        {
            Aabb3<T> ret(*this);
            ret.extend(box);
            return ret;
        }

        /**
         * Tests if the point @a point is within this bounding-box
         * @param point A point to be tested
         * @return True if point @a point lies within bounding-box, otherwise false.
         */
        template <typename SrcT>
        bool intersects(const Vector3<SrcT>& point) const
        {
            if (min.x > point.x || min.y > point.y || min.z > point.z
                || point.x > max.x || point.y > max.y || point.z > max.z)
                return false;

            return true;
        }

        /**
         * Tests if other bounding-box intersects (even partially) with this bouding-box.
         * @param box A box to be tested for intersection.
         * @return True if there's intersection between boxes, otherwise false.
         */
        template <typename SrcT>
        bool intersects(const Aabb3<SrcT>& box) const
        {
            if (min.x > box.max.x || min.y > box.max.y || min.z > box.max.z
                || max.x < box.min.x || max.y < box.min.y || max.z < box.min.z)
                return false;

            return true;
        }

        /**
         * Tests if other sphere intersects (even partially) with this bouding-box.
         * @param box A box to be tested for intersection.
         * @return True if there's intersection between boxes, otherwise false.
         */
        bool intersects(const Sphere<T> &sphere) const
        {
            T dmin = 0;

            auto center = sphere.getCenter();
            auto bmin = getMin();
            auto bmax = getMax();

            if (center.x < bmin.x) {
                T d = center.x - bmin.x;
                dmin += d * d;
            }
            else if (center.x > bmax.x) {
                T d = center.x - bmax.x;
                dmin += d * d;
            }

            if (center.y < bmin.y) {
                T d = center.y - bmin.y;
                dmin += d * d;
            }
            else if (center.y > bmax.y) {
                T d = center.y - bmax.y;
                dmin += d * d;
            }

            if (center.z < bmin.z) {
                T d = center.z - bmin.z;
                dmin += d * d;
            }
            else if (center.z > bmax.z) {
                T d = center.z - bmax.z;
                dmin += d * d;
            }

            return dmin <= (sphere.getRadius() * sphere.getRadius());
        }

        /**
         * Gets result of intersection of this bounding-box with a other bounding-box.
         * In case the boxes don't intersect, the returned bounding-box is invalid.
         * @param other Box to be tested
         * @return Result of intersection.
         * @see valid() method for more information on invalid bounding-boxes.
         */
        template <typename SrcT>
        Aabb3<T> intersection(const Aabb3<SrcT>& other) const
        {
            Aabb3<T> ret;
            if (min.x > other.max.x || min.y > other.max.y || min.z > other.max.z
                || max.x < other.min.x || max.y < other.min.y || max.z < other.min.z)
                return ret;

            ret.min = Vector3<T>::max(min, other.min);
            ret.max = Vector3<T>::min(max, other.max);

            return ret;
        }

        /**
         * Gets center point of bounding-box.
         * @return A center point of bounding-box.
         */
        Vector3<T> center() const
        {
            return (min + max) / 2;
        }

        /**
         * Gets extent of bounding-box.
         * @return Extent of bounding-box.
         */
        Vector3<T> extent() const
        {
            return (max - min) / 2;
        }

        /**
         * Gets diagonal size of bounding-box
         * @return Sizes for particular dimensions.
         */
        Vector3<T> size() const
        {
            return max - min;
        }

        /**
         * Gets all 8 corner-points of bounding box
         * @param i An index of bounding-box corner point. Valid values are 0 .. 7.
         * @return A position of @a i-th corner-point.
         * @note The order of points is as follows (where @c + denotes max-point and @c - min-point):
         * 1. (@c + @c + @c +)
         * 2. (@c - @c + @c +)
         * 3. (@c + @c - @c +)
         * 4. (@c - @c - @c +)
         * 5. (@c + @c + @c -)
         * 6. (@c - @c + @c -)
         * 7. (@c + @c - @c -)
         * 8. (@c - @c - @c -)
         */
        Vector3<T> point(size_t i) const
        {
            assert(i < 8);
            return Vector3<T>(i & 1 ? min.x : max.x, i & 2 ? min.y : max.y, i & 4 ? min.z : max.z);
        }

        /**
         * Gets transformed bounding-box by transform @a t
         * @param t A transform matrix
         * @return Transformed bounding-box
         */
        Aabb3<T> transformed(const Matrix4<T>& t) const
        {
            Aabb3<T> ret;
            for (size_t i = 0; i < 8; i++)
            {
                const Vector4<T> p(point(i), 1);
                ret.extend((t * p).xyz());
            }

            return ret;
        }

        /**
         * Tests if @a rhs is equal to this bounding-box
         * @param rhs Right-hand side
         * @return True if @a rhs and this bounding-boxes are equal, otherwise false
         */
        template <typename RhsT>
        bool operator==(const Aabb3<RhsT>& rhs) const
        {
            return min == rhs.min && max == rhs.max;
        }

        /**
         * Tests if @a rhs is not equal to this bounding-box
         * @param rhs Right-hand side
         * @return True if @a rhs and this bounding-boxes are not equal, otherwise false
         */
        template <typename RhsT>
        bool operator!=(const Aabb3<RhsT>& rhs) const
        {
            return min != rhs.min || max != rhs.max;
        }

        /**
         * Gets transformed bounding-box by transform @a rhs.
         * @param rhs Matrix 4x4 representing the transform
         * @return Transformed bounding-box
         */
        Aabb3<T> operator*(const Matrix4<T>& rhs) const
        {
            return transformed(rhs);
        }

        /**
         * Apply transform @a rhs to this bounding-box
         * @param rhs A transform to be applied
         * @return Reference to this
         */
        Aabb3<T>& operator*=(const Matrix4<T>& rhs)
        {
            *this = transformed(rhs);
            return *this;
        }

        /**
         * Extends this bounding-box by point @a rhs.
         * @param rhs A point to extend this bounding-box by
         * @return Reference to this
         */
        template <typename SrcT>
        Aabb3<T>& operator<<(const Vector3<SrcT>& rhs)
        {
            extend(rhs);
            return *this;
        }

        /**
         * Extends this bounding-box by box @a rhs.
         * @param rhs A box to extend this bounding-box by
         * @return Reference to this
         */
        template <typename SrcT>
        Aabb3<T>& operator<<(const Aabb3<SrcT>& rhs)
        {
            extend(rhs);
            return *this;
        }

        /**
         * Union of this and @a rhs bounding-boxes
         * @param rhs Right-hand side of union
         * @return A resulting bounding-box representing union
         */
        template <typename RhsT>
        Aabb3<T> operator|(const Aabb3<RhsT>& rhs) const
        {
            return extended(rhs);
        }

        /**
         * Intersection of this and @a rhs bounding-boxed
         * @param rhs Right-hand side
         * @return Resulting bouding-box representing the intersection.
         */
        template <typename RhsT>
        Aabb3<T> operator&(const Aabb3<RhsT>& rhs) const
        {
            return intersection(rhs);
        }

        /**
         * Outputs string representation of bounding-box @a rhs to output stream @a lhs
         * @param lhs Output stream to write to
         * @param rhs Bounding-box to write to output stream.
         * @return Reference to output stream @a lhs
         */
        friend std::ostream& operator<<(std::ostream& lhs, const Aabb3<T>& rhs)
        {
            lhs << rhs.toString();
            return lhs;
        }

        /**
         * To string operator.
         */
        std::string toString() const
        {
            char buffer[96];
            sprintf(buffer, "%f,%f,%f,%f,%f,%f", min.x, min.y, min.z, max.x, max.y, max.z);
            return buffer;
        }

    };

    typedef Aabb3<int> aabb3i;
    typedef Aabb3<float> aabb3f;
    typedef Aabb3<double> aabb3r;

    /**
     * Class Sphera
     */
    template<typename T>
    class Sphere
    {
    public:
        /**
         * Constructor without init
         */
        Sphere() {}

        /**
         * Constructor inti with center and radius
         */
        Sphere(const Vector3<T>&center, T radius)
            : mCenter(center), mRadius(radius)
        {}

        /**
         * Get the redius
         */
        T       getRadius() const { return mRadius; }

        /**
         * Set the redius
         */
        void    setRadius(float radius) { mRadius = radius; }

        /**
         * Get the center
         */
        const Vector3<T>&   getCenter() const { return mCenter; }

        /**
         * Set the center
         */
        void    setCenter(const Vector3<T>& center) { mCenter = center; }

        /**
         * Tests if other AxisAlignedBox intersects (even partially) with this sphere
         */
        bool    intersects(const Aabb3<T> &box) const { return box.intersects(*this); }

        /**
         * Returns true if the ray intersects this sphere
         */
        bool    intersects(const Ray<T> &ray) const
        {
            T   t;
            Vector3<T>  temp = ray.getOrigin() - mCenter;
            T   a = dot(ray.getDirection(), ray.getDirection());
            T   b = 2.0f * dot(temp, ray.getDirection());
            T   c = dot(temp, temp) - mRadius * mRadius;
            T   disc = b * b - 4.0f * a * c;

            if (disc < 0.0f) {
                return false;
            }
            else { // this probably can be optimized
                T e = sqrt(disc);
                T denom = 2.0f * a;
                t = (-b - e) / denom;    // smaller root

                if (t > FLT_EPSILON) {
                    return true;
                }

                t = (-b + e) / denom;    // larger root
                if (t > FLT_EPSILON) {
                    return true;
                }
            }

            return false;
        }

        int	    intersects(const Ray<T> &ray, T *intersection) const
        {
            T   t;
            Vector3<T>  temp = ray.getOrigin() - mCenter;
            T   a = dot(ray.getDirection(), ray.getDirection());
            T   b = 2 * dot(temp, ray.getDirection());
            T   c = dot(temp, temp) - mRadius * mRadius;
            T   disc = b * b - 4 * a * c;

            if (disc < (T)0) {
                return 0;
            }
            else {
                T e = sqrt(disc);
                T denom = (T)2 * a;
                t = (-b - e) / denom;    // smaller root

                if (t > FLT_EPSILON) {
                    *intersection = t;
                    return 1;
                }

                t = (-b + e) / denom;    // larger root
                if (t > FLT_EPSILON) {
                    *intersection = t;
                    return 1;
                }
            }

            return 0;
        }

        /** 
         * Get the closest point on the ray to the Sphere.
         * If the ray intersects then returns the point of nearest intersection.
         */
        Vector3<T> Sphere::closestPoint(const Ray<T> &ray) const
        {
            T   t;
            Vector3<T>  diff = ray.getOrigin() - mCenter;
            T   a = dot(ray.getDirection(), ray.getDirection());
            T   b = 2 * dot(diff, ray.getDirection());
            T   c = dot(diff, diff) - mRadius * mRadius;
            T   disc = b * b - 4 * a * c;

            if (disc > 0) {
                T e = sqrt(disc);
                T denom = 2 * a;
                t = (-b - e) / denom;    // smaller root

                if (t > FLT_EPSILON)
                    return ray.calcPosition(t);

                t = (-b + e) / denom;    // larger root
                if (t > FLT_EPSILON)
                    return ray.calcPosition(t);
            }

            // doesn't intersect; closest point on line
            t = dot(-diff, normalize(ray.getDirection()));
            Vector3<T> onRay = ray.calcPosition(t);
            return mCenter + normalize(onRay - mCenter) * mRadius;

            //return ray.getDirection() * dot( ray.getDirection(), (mCenter - ray.getOrigin() ) );
        }

        void calcProjection(T focalLength, Vector2<T> *outCenter, Vector2<T> *outAxisA, Vector2<T> *outAxisB) const
        {
            Vector3<T> o(-mCenter.x, mCenter.y, mCenter.z);

            T r2 = mRadius * mRadius;
            T z2 = o.z * o.z;
            T l2 = dot(o, o);

            if (outCenter)
                *outCenter = focalLength * o.z * Vector2<T>(o) / (z2 - r2);
            if (abs(z2 - l2) > 0.00001f) {
                if (outAxisA)
                    *outAxisA = focalLength * sqrt(-r2 * (r2 - l2) / ((l2 - z2)*(r2 - z2)*(r2 - z2))) * Vector2<T>(o.x, o.y);

                if (outAxisB)
                    *outAxisB = focalLength * sqrt(abs(-r2 * (r2 - l2) / ((l2 - z2)*(r2 - z2)*(r2 - l2)))) * Vector2<T>(-o.y, o.x);
            }
            else { // approximate with circle
                T radius = focalLength * mRadius / sqrt(z2 - r2);
                if (outAxisA)
                    *outAxisA = Vector2<T>(radius, 0);
                if (outAxisB)
                    *outAxisB = Vector2<T>(0, radius);
            }
        }

        void calcProjection(T focalLength, Vector2<T> screenSizePixels, Vector2<T> *outCenter, Vector2<T> *outAxisA, Vector2<T> *outAxisB) const
        {
            auto toScreenPixels = [=](Vector2<T> v, const Vector2<T> &windowSize) {
                vec2 result = v;
                result.x *= 1 / (windowSize.x / windowSize.y);
                result += Vector2<T>(0.5, 0.5);
                result *= windowSize;
                return result;
            };

            Vector2<T> center, axisA, axisB;
            calcProjection(focalLength, &center, &axisA, &axisB);
            if (outCenter)
                *outCenter = toScreenPixels(center, screenSizePixels);
            if (outAxisA)
                *outAxisA = toScreenPixels(center + axisA * 0.5f, screenSizePixels) - toScreenPixels(center - axisA * 0.5f, screenSizePixels);
            if (outAxisB)
                *outAxisB = toScreenPixels(center + axisB * 0.5f, screenSizePixels) - toScreenPixels(center - axisB * 0.5f, screenSizePixels);
        }

    protected:
        Vector3<T>  mCenter;
        T           mRadius;
    };

    typedef Sphere<float>   spheref;
    typedef Sphere<double>  sphere;

    template<typename T>
    class Ray {
    public:
        Ray() {}
        Ray(const Vector3<T> &aOrigin, const Vector3<T> &aDirection) : mOrigin(aOrigin) { setDirection(aDirection); }

        void                setOrigin(const Vector3<T> &aOrigin) { mOrigin = aOrigin; }
        const Vector3<T>&   getOrigin() const { return mOrigin; }

        void    setDirection(const Vector3<T> &aDirection)
        {
            mDirection = aDirection;
            mInvDirection = Vector3<T>((T)1 / mDirection.x, (T)1 / mDirection.y, (T)1 / mDirection.z);
            mSignX = (mDirection.x < (T)0) ? 1 : 0;
            mSignY = (mDirection.y < (T)0) ? 1 : 0;
            mSignZ = (mDirection.z < (T)0) ? 1 : 0;
        }
        const Vector3<T>&   getDirection() const { return mDirection; }
        const Vector3<T>&   getInverseDirection() const { return mInvDirection; }

        char    getSignX() const { return mSignX; }
        char    getSignY() const { return mSignY; }
        char    getSignZ() const { return mSignZ; }

        void	transform(const Matrix4<T> &matrix)
        {
            mOrigin = Vector3<T>(matrix * Vector4<T>(mOrigin, 1));
            setDirection(Matrix3<T>(matrix) * mDirection);
        }

        Ray<T>  transformed(const Matrix4<T> &matrix) const
        {
            Ray<T>  result;
            result.mOrigin = Vector3<T>(matrix * Vector4<T>(mOrigin, 1));
            result.setDirection(Matrix3<T>(matrix) * mDirection);

            return result;
        }

        Vector3<T>  calcPosition(T t) const { return mOrigin + mDirection * t; }

        bool calcTriangleIntersection(const Vector3<T> &vert0, const Vector3<T> &vert1, const Vector3<T> &vert2, T *result) const
        {
            Vector3<T> edge1, edge2, tvec, pvec, qvec;
            T det;
            T u, v;
            const T epsilon = T(0.000001);

            edge1 = vert1 - vert0;
            edge2 = vert2 - vert0;

            pvec = cross(getDirection(), edge2);
            det = dot(edge1, pvec);

#if 0 // we don't want to backface cull
            if (det < epsilon)
                return false;
            tvec = getOrigin() - vert0;

            u = dot(tvec, pvec);
            if ((u < 0.0f) || (u > det))
                return false;

            qvec = cross(tvec, edge1);
            v = dot(getDirection(), qvec);
            if (v < 0.0f || u + v > det)
                return false;

            *result = dot(edge2, qvec) / det;
            return true;
#else
            if (det > -epsilon && det < epsilon)
                return false;

            T inv_det = T(1) / det;
            tvec = getOrigin() - vert0;
            u = dot(tvec, pvec) * inv_det;
            if (u < T(0) || u > T(1))
                return false;

            qvec = cross(tvec, edge1);

            v = dot(getDirection(), qvec) * inv_det;
            if (v < T(0) || u + v > T(1))
                return 0;

            *result = dot(edge2, qvec) * inv_det;
            return true;
#endif
        }

        bool calcPlaneIntersection(const Vector3<T> &origin, const Vector3<T> &normal, T *result) const
        {
            T denom = dot(planeNormal, getDirection());

            if (denom != T(0)) {
                *result = dot(planeNormal, planeOrigin - getOrigin()) / denom;
                return true;
            }
            return false;
        }

    protected:
        Vector3<T>	mOrigin;
        Vector3<T>	mDirection;
        // these are helpful to certain ray intersection algorithms
        char	mSignX, mSignY, mSignZ;
        Vector3<T>	mInvDirection;
    };

    typedef Ray<float>  rayf;
    typedef Ray<double> ray;

#pragma pack(pop)

} // !namespace sge

#endif // SGE_MATH_H