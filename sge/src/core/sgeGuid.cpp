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
 
#include <core/sgeGuid.h>
#include <cstring>

#if(SGE_TARGET_PLATFORM == SGE_PLATFORM_LINUX)
#include <uuid/uuid.h>
#endif

#if(SGE_TARGET_PLATFORM == SGE_PLATFORM_MAC_IOS)
#include <CoreFoundation/CFUUID.h>
#endif

#if(SGE_TARGET_PLATFORM == SGE_PLATFORM_WIN32)
#include <objbase.h>
#endif

#if(SGE_TARGET_PLATFORM == SGE_PLATFORM_ANDROID)
#include <jni.h>
#include <cassert>
#endif

namespace sge
{

    #if(SGE_TARGET_PLATFORM == SGE_PLATFORM_ANDROID)
    AndroidGuidInfo androidInfo;
    
    AndroidGuidInfo AndroidGuidInfo::fromJniEnv(JNIEnv *env)
    {
        AndroidGuidInfo info;
        info.env = env;
        auto localUuidClass = env->FindClass("java/util/UUID");
        info.uuidClass = (jclass)env->NewGlobalRef(localUuidClass);
        env->DeleteLocalRef(localUuidClass);
        info.newGuidMethod = env->GetStaticMethodID(
            info.uuidClass, "randomUUID", "()Ljava/util/UUID;");
        info.mostSignificantBitsMethod = env->GetMethodID(
            info.uuidClass, "getMostSignificantBits", "()J");
        info.leastSignificantBitsMethod = env->GetMethodID(
            info.uuidClass, "getLeastSignificantBits", "()J");
        info.initThreadId = std::this_thread::get_id();
        return info;
    }
    
    void initJni(JNIEnv *env)
    {
        androidInfo = AndroidGuidInfo::fromJniEnv(env);
    }
    #endif
    
    // overload << so that it's easy to convert to a string
    std::ostream &operator<<(std::ostream &s, const Guid &guid)
    {
        std::ios_base::fmtflags f(s.flags()); // politely don't leave the ostream in hex mode
        s << std::hex << std::setfill('0')
            << std::setw(2) << (int)guid._bytes[0]
            << std::setw(2) << (int)guid._bytes[1]
            << std::setw(2) << (int)guid._bytes[2]
            << std::setw(2) << (int)guid._bytes[3]
            << "-"
            << std::setw(2) << (int)guid._bytes[4]
            << std::setw(2) << (int)guid._bytes[5]
            << "-"
            << std::setw(2) << (int)guid._bytes[6]
            << std::setw(2) << (int)guid._bytes[7]
            << "-"
            << std::setw(2) << (int)guid._bytes[8]
            << std::setw(2) << (int)guid._bytes[9]
            << "-"
            << std::setw(2) << (int)guid._bytes[10]
            << std::setw(2) << (int)guid._bytes[11]
            << std::setw(2) << (int)guid._bytes[12]
            << std::setw(2) << (int)guid._bytes[13]
            << std::setw(2) << (int)guid._bytes[14]
            << std::setw(2) << (int)guid._bytes[15];
        s.flags(f);
        return s;
    }
    
    bool operator<(const sge::Guid &lhs, const sge::Guid &rhs)
    {
        return lhs.bytes() < rhs.bytes();
    }
    
    bool Guid::isValid() const
    {
        sge::Guid empty;
        return *this != empty;
    }
    
    // convert to string using std::snprintf() and std::string
    std::string Guid::str() const
    {
        char one[10], two[6], three[6], four[6], five[14];
    
        snprintf(one, 10, "%02x%02x%02x%02x",
            _bytes[0], _bytes[1], _bytes[2], _bytes[3]);
        snprintf(two, 6, "%02x%02x",
            _bytes[4], _bytes[5]);
        snprintf(three, 6, "%02x%02x",
            _bytes[6], _bytes[7]);
        snprintf(four, 6, "%02x%02x",
            _bytes[8], _bytes[9]);
        snprintf(five, 14, "%02x%02x%02x%02x%02x%02x",
            _bytes[10], _bytes[11], _bytes[12], _bytes[13], _bytes[14], _bytes[15]);
        const std::string sep("-");
        std::string out(one);
    
        out += sep + two;
        out += sep + three;
        out += sep + four;
        out += sep + five;
    
        return out;
    }
    
    // conversion operator for std::string
    Guid::operator std::string() const
    {
        return str();
    }
    
    // Access underlying bytes
    const std::array<unsigned char, 16>& Guid::bytes() const
    {
        return _bytes;
    }
    
    // create a guid from vector of bytes
    Guid::Guid(const std::array<unsigned char, 16> &bytes) : _bytes(bytes)
    { }
    
    // create a guid from vector of bytes
    Guid::Guid(std::array<unsigned char, 16> &&bytes) : _bytes(std::move(bytes))
    { }
    
    // converts a single hex char to a number (0 - 15)
    unsigned char hexDigitToChar(char ch)
    {
        // 0-9
        if (ch > 47 && ch < 58)
            return ch - 48;
    
        // a-f
        if (ch > 96 && ch < 103)
            return ch - 87;
    
        // A-F
        if (ch > 64 && ch < 71)
            return ch - 55;
    
        return 0;
    }
    
    bool isValidHexChar(char ch)
    {
        // 0-9
        if (ch > 47 && ch < 58)
            return true;
    
        // a-f
        if (ch > 96 && ch < 103)
            return true;
    
        // A-F
        if (ch > 64 && ch < 71)
            return true;
    
        return false;
    }
    
    // converts the two hexadecimal characters to an unsigned char (a byte)
    unsigned char hexPairToChar(char a, char b)
    {
        return hexDigitToChar(a) * 16 + hexDigitToChar(b);
    }
    
    // create a guid from string
    Guid::Guid(std::string fromString)
    {
        char charOne = '\0';
        char charTwo = '\0';
        bool lookingForFirstChar = true;
        unsigned nextByte = 0;
    
        for (const char &ch : fromString)
        {
            if (ch == '-')
                continue;
    
            if (nextByte >= 16 || !isValidHexChar(ch))
            {
                // Invalid string so bail
                zeroify();
                return;
            }
    
            if (lookingForFirstChar)
            {
                charOne = ch;
                lookingForFirstChar = false;
            }
            else
            {
                charTwo = ch;
                auto byte = hexPairToChar(charOne, charTwo);
                _bytes[nextByte++] = byte;
                lookingForFirstChar = true;
            }
        }
    
        // if there were fewer than 16 bytes in the string then guid is bad
        if (nextByte < 16)
        {
            zeroify();
            return;
        }
    }
    
    // create empty guid
    Guid::Guid() : _bytes{ {0} }
    { }
    
    // set all bytes to zero
    void Guid::zeroify()
    {
        std::fill(_bytes.begin(), _bytes.end(), static_cast<unsigned char>(0));
    }
    
    // overload equality operator
    bool Guid::operator==(const Guid &other) const
    {
        return _bytes == other._bytes;
    }
    
    // overload inequality operator
    bool Guid::operator!=(const Guid &other) const
    {
        return !((*this) == other);
    }
    
    // member swap function
    void Guid::swap(Guid &other)
    {
        _bytes.swap(other._bytes);
    }
    
    // This is the linux friendly implementation, but it could work on other
    // systems that have libuuid available
    #if(SGE_TARGET_PLATFORM == SGE_PLATFORM_LINUX)
    Guid newGuid()
    {
        std::array<unsigned char, 16> data;
        static_assert(std::is_same<unsigned char[16], uuid_t>::value, "Wrong type!");
        uuid_generate(data.data());
        return Guid{ std::move(data) };
    }
    #endif
    
    // this is the mac and ios version
    #if(SGE_TARGET_PLATFORM == SGE_PLATFORM_MAC_IOS)
    Guid newGuid()
    {
        auto newId = CFUUIDCreate(NULL);
        auto bytes = CFUUIDGetUUIDBytes(newId);
        CFRelease(newId);
    
        std::array<unsigned char, 16> byteArray =
        { {
            bytes.byte0,
            bytes.byte1,
            bytes.byte2,
            bytes.byte3,
            bytes.byte4,
            bytes.byte5,
            bytes.byte6,
            bytes.byte7,
            bytes.byte8,
            bytes.byte9,
            bytes.byte10,
            bytes.byte11,
            bytes.byte12,
            bytes.byte13,
            bytes.byte14,
            bytes.byte15
        } };
        return Guid{ std::move(byteArray) };
    }
    #endif
    
    // obviously this is the windows version
    #if(SGE_TARGET_PLATFORM == SGE_PLATFORM_WIN32)
    Guid newGuid()
    {
        GUID newId;
        CoCreateGuid(&newId);
    
        std::array<unsigned char, 16> bytes =
        {
            (unsigned char)((newId.Data1 >> 24) & 0xFF),
            (unsigned char)((newId.Data1 >> 16) & 0xFF),
            (unsigned char)((newId.Data1 >> 8) & 0xFF),
            (unsigned char)((newId.Data1) & 0xff),
    
            (unsigned char)((newId.Data2 >> 8) & 0xFF),
            (unsigned char)((newId.Data2) & 0xff),
    
            (unsigned char)((newId.Data3 >> 8) & 0xFF),
            (unsigned char)((newId.Data3) & 0xFF),
    
            (unsigned char)newId.Data4[0],
            (unsigned char)newId.Data4[1],
            (unsigned char)newId.Data4[2],
            (unsigned char)newId.Data4[3],
            (unsigned char)newId.Data4[4],
            (unsigned char)newId.Data4[5],
            (unsigned char)newId.Data4[6],
            (unsigned char)newId.Data4[7]
        };
    
        return Guid{ std::move(bytes) };
    }
    #endif
    
    // android version that uses a call to a java api
    #if(SGE_TARGET_PLATFORM == SGE_PLATFORM_ANDROID)
    Guid newGuid(JNIEnv *env)
    {
        assert(env != androidInfo.env || std::this_thread::get_id() == androidInfo.initThreadId);
    
        jobject javaUuid = env->CallStaticObjectMethod(
            androidInfo.uuidClass, androidInfo.newGuidMethod);
        jlong mostSignificant = env->CallLongMethod(javaUuid,
            androidInfo.mostSignificantBitsMethod);
        jlong leastSignificant = env->CallLongMethod(javaUuid,
            androidInfo.leastSignificantBitsMethod);
    
        std::array<unsigned char, 16> bytes =
        {
            (unsigned char)((mostSignificant >> 56) & 0xFF),
            (unsigned char)((mostSignificant >> 48) & 0xFF),
            (unsigned char)((mostSignificant >> 40) & 0xFF),
            (unsigned char)((mostSignificant >> 32) & 0xFF),
            (unsigned char)((mostSignificant >> 24) & 0xFF),
            (unsigned char)((mostSignificant >> 16) & 0xFF),
            (unsigned char)((mostSignificant >> 8) & 0xFF),
            (unsigned char)((mostSignificant) & 0xFF),
            (unsigned char)((leastSignificant >> 56) & 0xFF),
            (unsigned char)((leastSignificant >> 48) & 0xFF),
            (unsigned char)((leastSignificant >> 40) & 0xFF),
            (unsigned char)((leastSignificant >> 32) & 0xFF),
            (unsigned char)((leastSignificant >> 24) & 0xFF),
            (unsigned char)((leastSignificant >> 16) & 0xFF),
            (unsigned char)((leastSignificant >> 8) & 0xFF),
            (unsigned char)((leastSignificant) & 0xFF)
        };
    
        env->DeleteLocalRef(javaUuid);
    
        return Guid{ std::move(bytes) };
    }
    
    Guid newGuid()
    {
        return newGuid(androidInfo.env);
    }
    #endif
    
}

// Specialization for std::swap<Guid>() --
// call member swap function of lhs, passing rhs
namespace std
{
    template <>
    void swap(sge::Guid &lhs, sge::Guid &rhs) noexcept
    {
        lhs.swap(rhs);
    }
}