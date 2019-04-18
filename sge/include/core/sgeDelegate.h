#pragma once

#include <core/sgeDefs.h>
#include <core/sgeDelegatePrivate.h>

namespace sge
{

    /**
     * Class Delegate0
     * Function delegate with none parameter.
     * You can use like:
     *      ClassA  obj;
     *      Delegate1<int> callback;
     *      callback.Bind<ClassA>(obj, &ClassA::Fun); // or callback.bind(globalFun);
     *      int ret = callback();
     */
    template<typename R>
    class Delegate0
    {
    public:

        /**
         * Constructor, set a empty delegate
         */
        Delegate0() : delegateImpl(NULL)
        {
        }

        /**
         * Copy constructor, copy the same delegate
         */
        Delegate0(const Delegate0<R>& rhs)
        {
            if (rhs.delegateImpl)
            {
                memcpy(dreal, rhs.dreal, sizeof(dreal));
                delegateImpl = (IDelegate0<R>*)dreal;
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Copy constructor, copy the same delegate
         */
        Delegate0<R>& operator=(const Delegate0<R>& rhs)
        {
            if (rhs.delegateImpl)
            {
                memcpy(dreal, rhs.dreal, sizeof(dreal));
                delegateImpl = (IDelegate0<R>*)dreal;
            }
            else
            {
                delegateImpl = NULL;
            }
            return *this;
        }

        /**
         * Bind a delegate
         * @typename T The target object type
         * @param method T target function
         */
        template<typename T>
        void bind(T* object, R(T::*method)())
        {
            if (object && method)
            {
                delegateImpl = new(dreal) Delegate0Impl<T, R>(object, method);
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Bind a delegate
         * @param method T target function
         */
        void bind(R(*method)())
        {
            if (method)
            {
                delegateImpl = new(dreal) Delegate0StaticImpl<R>(method);
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Invoke this delegate
         */
        R operator()() const
        {
            if (delegateImpl)
            {
                return delegateImpl->invoke();
            }
            return R(0);
        }

    private:
        IDelegate0<R>* delegateImpl;
        char dreal[sizeof(void*) * 4];
    };

    /**
     * Class Delegate1
     * Function delegate with one parameter.
     * You can use like:
     *      ClassA  obj;
     *      Delegate1<int,int> callback;
     *      callback.Bind<ClassA>(obj, &ClassA::Fun); // or callback.bind(globalFun);
     *      int ret = callback(5);
     */
    template<typename R, typename A1>
    class Delegate1
    {
    public:

        /**
         * Constructor, set a empty delegate
         */
        Delegate1() : delegateImpl(NULL)
        {
        }

        /**
         * Copy constructor, copy the same delegate
         */
        Delegate1(const Delegate1<R, A1>& rhs)
        {
            if (rhs.delegateImpl)
            {
                memcpy(dreal, rhs.dreal, sizeof(dreal));
                delegateImpl = (IDelegate1<R, A1>*)dreal;
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Copy constructor, copy the same delegate
         */
        Delegate1<R, A1>& operator=(const Delegate1<R, A1>& rhs)
        {
            if (rhs.delegateImpl)
            {
                memcpy(dreal, rhs.dreal, sizeof(dreal));
                delegateImpl = (IDelegate1<R, A1>*)dreal;
            }
            else
            {
                delegateImpl = NULL;
            }
            return *this;
        }

        /**
         * Bind a delegate
         * @typename T The target object type
         * @param method T target function
         */
        template<typename T>
        void bind(T* object, R (T::*method)(A1))
        {
            if (object && method)
            {
                delegateImpl = new(dreal) Delegate1Impl<T, R, A1>(object, method);
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Bind a delegate
         * @param method T target function
         */
        void bind(R(*method)(A1))
        {
            if (method)
            {
                delegateImpl = new(dreal) Delegate1StaticImpl<R, A1>(method);
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Invoke this delegate
         */
        R operator()(A1 arg1) const
        {
            if (delegateImpl)
            {
                return delegateImpl->invoke(arg1);
            }
            return R(0);
        }

    private:
        IDelegate1<R, A1>* delegateImpl;
        char dreal[sizeof(void*) * 4];
    };

    /**
     * Class Delegate2
     * Function delegate with two parameters.
     * You can use like:
     *      ClassA  obj;
     *      Delegate2<int,int,int> callback;
     *      callback.Bind<ClassA>(obj, &ClassA::Fun); // or callback.bind(globalFun);
     *      int ret = callback(5��5);
     */
    template<typename R, typename A1, typename A2>
    class Delegate2
    {
    public:

        /**
         * Constructor, set a empty delegate
         */
        Delegate2() : delegateImpl(NULL)
        {
        }

        /**
         * Copy constructor, copy the same delegate
         */
        Delegate2(const Delegate2<R, A1, A2>& rhs)
        {
            if (rhs.delegateImpl)
            {
                memcpy(dreal, rhs.dreal, sizeof(dreal));
                delegateImpl = (IDelegate2<R, A1, A2>*)dreal;
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Copy constructor, copy the same delegate
         */
        Delegate2<R, A1, A2>& operator=(const Delegate2<R, A1, A2>& rhs)
        {
            if (rhs.delegateImpl)
            {
                memcpy(dreal, rhs.dreal, sizeof(dreal));
                delegateImpl = (IDelegate2<R, A1, A2>*)dreal;
            }
            else
            {
                delegateImpl = NULL;
            }
            return *this;
        }

        /**
         * Bind a delegate
         * @typename T The target object type
         * @param method T target function
         */
        template<typename T>
        void bind(T* object, R(T::*method)(A1, A2))
        {
            if (object && method)
            {
                delegateImpl = new(dreal) Delegate2Impl<T, R, A1, A2>(object, method);
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Bind a delegate
         * @param method T target function
         */
        void bind(R(*method)(A1, A2))
        {
            if (method)
            {
                delegateImpl = new(dreal) Delegate2StaticImpl<R, A1, A2>(method);
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Invoke this delegate
         */
        R operator()(A1 arg1, A2 arg2) const
        {
            if (delegateImpl)
            {
                return delegateImpl->invoke(arg1, arg2);
            }
            return R(0);
        }

    private:
        IDelegate2<R, A1, A2>* delegateImpl;
        char dreal[sizeof(void*) * 4];
    };

    /**
     * Class Delegate3
     * Function delegate with three parameters.
     * You can use like:
     *      ClassA  obj;
     *      Delegate3<int,int,int,int> callback;
     *      callback.Bind<ClassA>(obj, &ClassA::Fun); // or callback.bind(globalFun);
     *      int ret = callback(5��5, 5);
     */
    template<typename R, typename A1, typename A2, typename A3>
    class Delegate3
    {
    public:

        /**
         * Constructor, set a empty delegate
         */
        Delegate3() : delegateImpl(NULL)
        {
        }

        /**
         * Copy constructor, copy the same delegate
         */
        Delegate3(const Delegate3<R, A1, A2, A3>& rhs)
        {
            if (rhs.delegateImpl)
            {
                memcpy(dreal, rhs.dreal, sizeof(dreal));
                delegateImpl = (IDelegate3<R, A1, A2, A3>*)dreal;
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Copy constructor, copy the same delegate
         */
        Delegate3<R, A1, A2, A3>& operator=(const Delegate3<R, A1, A2, A3>& rhs)
        {
            if (rhs.delegateImpl)
            {
                memcpy(dreal, rhs.dreal, sizeof(dreal));
                delegateImpl = (IDelegate3<R, A1, A2, A3>*)dreal;
            }
            else
            {
                delegateImpl = NULL;
            }
            return *this;
        }

        /**
         * Bind a delegate
         * @typename T The target object type
         * @param method T target function
         */
        template<typename T>
        void bind(T* object, R(T::*method)(A1, A2, A3))
        {
            if (object && method)
            {
                delegateImpl = new(dreal) Delegate3Impl<T, R, A1, A2, A3>(object, method);
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Bind a delegate
         * @param method T target function
         */
        void bind(R(*method)(A1, A2, A3))
        {
            if (method)
            {
                delegateImpl = new(dreal) Delegate3StaticImpl<R, A1, A2, A3>(method);
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Invoke this delegate
         */
        R operator()(A1 arg1, A2 arg2, A3 arg3) const
        {
            if (delegateImpl)
            {
                return delegateImpl->invoke(arg1, arg2, arg3);
            }
            return R(0);
        }

    private:
        IDelegate3<R, A1, A2, A3>* delegateImpl;
        char dreal[sizeof(void*) * 4];
    };

    /**
     * Class Delegate4
     * Function delegate with four parameters.
     * You can use like:
     *      ClassA  obj;
     *      Delegate4<int,int,int,int,int> callback;
     *      callback.Bind<ClassA>(obj, &ClassA::Fun); // or callback.bind(globalFun);
     *      int ret = callback(5��5, 5, 5);
     */
    template<typename R, typename A1, typename A2, typename A3, typename A4>
    class Delegate4
    {
    public:

        /**
         * Constructor, set a empty delegate
         */
        Delegate4() : delegateImpl(NULL)
        {
        }

        /**
         * Copy constructor, copy the same delegate
         */
        Delegate4(const Delegate4<R, A1, A2, A3, A4>& rhs)
        {
            if (rhs.delegateImpl)
            {
                memcpy(dreal, rhs.dreal, sizeof(dreal));
                delegateImpl = (IDelegate4<R, A1, A2, A3, A4>*)dreal;
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Copy constructor, copy the same delegate
         */
        Delegate4<R, A1, A2, A3, A4>& operator=(const Delegate4<R, A1, A2, A3, A4>& rhs)
        {
            if (rhs.delegateImpl)
            {
                memcpy(dreal, rhs.dreal, sizeof(dreal));
                delegateImpl = (IDelegate4<R, A1, A2, A3, A4>*)dreal;
            }
            else
            {
                delegateImpl = NULL;
            }
            return *this;
        }

        /**
         * Bind a delegate
         * @typename T The target object type
         * @param method T target function
         */
        template<typename T>
        void bind(T* object, R(T::*method)(A1, A2, A3, A4))
        {
            if (object && method)
            {
                delegateImpl = new(dreal) Delegate4Impl<T, R, A1, A2, A3, A4>(object, method);
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Bind a delegate
         * @param method T target function
         */
        void bind(R(*method)(A1, A2, A3, A4))
        {
            if (method)
            {
                delegateImpl = new(dreal) Delegate4StaticImpl<R, A1, A2, A3, A4>(method);
            }
            else
            {
                delegateImpl = NULL;
            }
        }

        /**
         * Invoke this delegate
         */
        R operator()(A1 arg1, A2 arg2, A3 arg3, A4 arg4) const
        {
            if (delegateImpl)
            {
                return delegateImpl->invoke(arg1, arg2, arg3, arg4);
            }
            return R(0);
        }

    private:
        IDelegate4<R, A1, A2, A3, A4>* delegateImpl;
        char dreal[sizeof(void*) * 4];
    };

}

