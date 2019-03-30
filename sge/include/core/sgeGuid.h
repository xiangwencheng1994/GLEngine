/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGuid.h
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

#ifndef SGE_GUID_H
#define SGE_GUID_H

#include <core/sgePlatform.h>
#undef String

#if(SGE_TARGET_PLATFORM == SGE_PLATFORM_ANDROID)
#include <thread>
#include <jni.h>
#endif

#include <functional>
#include <iostream>
#include <array>
#include <sstream>
#include <string>
#include <utility>
#include <iomanip>

namespace sge
{

    /**
     * Guid class
     */
    class SGE_API   Guid
    {
    public:
        explicit Guid(const std::array<unsigned char, 16> &bytes);
        explicit Guid(std::array<unsigned char, 16> &&bytes);
    
        explicit Guid(std::string fromString);
        Guid();
    
        Guid(const Guid &other) = default;
        Guid &operator=(const Guid &other) = default;
        Guid(Guid &&other) = default;
        Guid &operator=(Guid &&other) = default;
    
        bool operator==(const Guid &other) const;
        bool operator!=(const Guid &other) const;
    
        std::string str() const;
        operator std::string() const;
        const std::array<unsigned char, 16>& bytes() const;
        void swap(Guid &other);
        bool isValid() const;
    
    private:
        void zeroify();
    
        // actual data
        std::array<unsigned char, 16> _bytes;
    
        // make the << operator a friend so it can access _bytes
        friend std::ostream &operator<<(std::ostream &s, const Guid &guid);
        friend bool operator<(const Guid &lhs, const Guid &rhs);
    };
    
    Guid SGE_API newGuid();

#if(SGE_TARGET_PLATFORM == SGE_PLATFORM_ANDROID)
    struct AndroidGuidInfo
    {
        static AndroidGuidInfo fromJniEnv(JNIEnv *env);
    
        JNIEnv *env;
        jclass uuidClass;
        jmethodID newGuidMethod;
        jmethodID mostSignificantBitsMethod;
        jmethodID leastSignificantBitsMethod;
        std::thread::id initThreadId;
    };
    
    extern AndroidGuidInfo androidInfo;
    
    void initJni(JNIEnv *env);
    
    // overloading for multi-threaded calls
    Guid newGuid(JNIEnv *env);
#endif

    namespace details
    {
        template <typename...> struct hash;
    
        template<typename T>
        struct hash<T> : public std::hash<T>
        {
            using std::hash<T>::hash;
        };
    

        template <typename T, typename... Rest>
        struct hash<T, Rest...>
        {
            inline std::size_t operator()(const T& v, const Rest&... rest) {
                std::size_t seed = hash<Rest...>{}(rest...);
                seed ^= hash<T>{}(v)+0x9e3779b9 + (seed << 6) + (seed >> 2);
                return seed;
            }
        };
    }
    
}

namespace std
{
    // Template specialization for std::swap<Guid>() --
    // See guid.cpp for the function definition
    template <>
    void swap(sge::Guid &guid0, sge::Guid &guid1) noexcept;

    // Specialization for std::hash<Guid> -- this implementation
    // uses std::hash<std::string> on the stringification of the guid
    // to calculate the hash
    template <>
    struct hash<sge::Guid>
    {
        std::size_t operator()(sge::Guid const &guid) const
        {
            const uint64_t* p = reinterpret_cast<const uint64_t*>(guid.bytes().data());
            return sge::details::hash<uint64_t, uint64_t>{}(p[0], p[1]);
        }
    };
}

#endif //!SGE_GUID_H
