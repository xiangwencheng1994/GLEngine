#pragma once

#include <core/sgeDefs.h>

namespace sge
{

    //////////////////////////////////////////////////////////////////////////
    // The IDelegate* Clas is the interface to invoke
    // {N} is the parameter count
    // The Delegate{N}Impl is the implement of object-method
    // The Delegate{N}StaticImpl is the implement of gloal method
    // You usually only used Delegat{N} class
    //////////////////////////////////////////////////////////////////////////

    template<typename R>
    class IDelegate0
    {
    public:
        virtual R invoke() = 0;
    };

    template<typename R, typename A1>
    class IDelegate1
    {
    public:
        virtual R invoke(A1 arg1) = 0;
    };

    template<typename R, typename A1, typename A2>
    class IDelegate2
    {
    public:
        virtual R invoke(A1 arg1, A2 arg2) = 0;
    };

    template<typename R, typename A1, typename A2, typename A3>
    class IDelegate3
    {
    public:
        virtual R invoke(A1 arg1, A2 arg2, A3 arg3) = 0;
    };

    template<typename R, typename A1, typename A2, typename A3, typename A4>
    class IDelegate4
    {
    public:
        virtual R invoke(A1 arg1, A2 arg2, A3 arg3, A4 arg4) = 0;
    };

    template<class T, typename R>
    class Delegate0Impl : public IDelegate0<R>
    {
    public:
        typedef R(T::*Method)();

        Delegate0Impl(T* object, Method method)
            : obj(object), fun(method)
        {
        }

        R invoke()
        {
            return (obj->*fun)();
        }

    protected:
        T*      obj;
        Method  fun;
    };

    template<class T, typename R, typename A1>
    class Delegate1Impl : public IDelegate1<R, A1>
    {
    public:
        typedef R(T::*Method)(A1);

        Delegate1Impl(T* object, Method method)
            : obj(object), fun(method)
        {
        }

        R invoke(A1 arg1)
        {
            return (obj->*fun)(arg1);
        }

    protected:
        T*      obj;
        Method  fun;
    };

    template<class T, typename R, typename A1, typename A2>
    class Delegate2Impl : public IDelegate2<R, A1, A2>
    {
    public:
        typedef R(T::*Method)(A1, A2);

        Delegate2Impl(T* object, Method method)
            : obj(object), fun(method)
        {
        }

        R invoke(A1 arg1, A2 arg2)
        {
            return (obj->*fun)(arg1, arg2);
        }

    protected:
        T*      obj;
        Method  fun;
    };

    template<class T, typename R, typename A1, typename A2, typename A3>
    class Delegate3Impl : public IDelegate3<R, A1, A2, A3>
    {
    public:
        typedef R(T::*Method)(A1, A2, A3);

        Delegate3Impl(T* object, Method method)
            : obj(object), fun(method)
        {
        }

        R invoke(A1 arg1, A2 arg2, A3 arg3)
        {
            return (obj->*fun)(arg1, arg2, arg3);
        }

    protected:
        T*      obj;
        Method  fun;
    };

    template<class T, typename R, typename A1, typename A2, typename A3, typename A4>
    class Delegate4Impl : public IDelegate4<R, A1, A2, A3, A4>
    {
    public:
        typedef R(T::*Method)(A1, A2, A3, A4);

        Delegate4Impl(T* object, Method method)
            : obj(object), fun(method)
        {
        }

        R invoke(A1 arg1, A2 arg2, A3 arg3, A4 arg4)
        {
            return (obj->*fun)(arg1, arg2, arg3, arg4);
        }

    protected:
        T*      obj;
        Method  fun;
    };

    template<typename R>
    class Delegate0StaticImpl : public IDelegate0<R>
    {
    public:
        typedef R(*Method)();

        Delegate0StaticImpl(Method method)
            : fun(method)
        {
        }

        R invoke()
        {
            return (*fun)();
        }

    protected:
        Method  fun;
    };

    template<typename R, typename A1>
    class Delegate1StaticImpl : public IDelegate1<R, A1>
    {
    public:
        typedef R(*Method)(A1);

        Delegate1StaticImpl(Method method)
            : fun(method)
        {
        }

        R invoke(A1 arg1)
        {
            return (*fun)(arg1);
        }

    protected:
        Method  fun;
    };

    template<typename R, typename A1, typename A2>
    class Delegate2StaticImpl : public IDelegate2<R, A1, A2>
    {
    public:
        typedef R(*Method)(A1, A2);

        Delegate2StaticImpl(Method method)
            : fun(method)
        {
        }

        R invoke(A1 arg1, A2 arg2)
        {
            return (*fun)(arg1, arg2);
        }

    protected:
        Method  fun;
    };

    template<typename R, typename A1, typename A2, typename A3>
    class Delegate3StaticImpl : public IDelegate3<R, A1, A2, A3>
    {
    public:
        typedef R(*Method)(A1, A2, A3);

        Delegate3StaticImpl(Method method)
            : fun(method)
        {
        }

        R invoke(A1 arg1, A2 arg2, A3 arg3)
        {
            return (*fun)(arg1, arg2, arg3);
        }

    protected:
        Method  fun;
    };

    template<typename R, typename A1, typename A2, typename A3, typename A4>
    class Delegate4StaticImpl : public IDelegate4<R, A1, A2, A3, A4>
    {
    public:
        typedef R(*Method)(A1, A2, A3, A4);

        Delegate4StaticImpl(Method method)
            : fun(method)
        {
        }

        R invoke(A1 arg1, A2 arg2, A3 arg3, A4 arg4)
        {
            return (*fun)(arg1, arg2, arg3, arg4);
        }

    protected:
        Method  fun;
    };

}

