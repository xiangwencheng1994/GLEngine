#pragma once

#include <core/sgeDefs.h>

#ifdef SGE_ANDROID
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
    class SGE_API  Guid
    {
    public:
        /**
         * Constructor with 16 bytes
         */
        explicit Guid(const std::array<unsigned char, 16> &bytes);
        
        /**
         * Constructor with 16 bytes ref
         */
        explicit Guid(std::array<unsigned char, 16> &&bytes);
    
        /**
         * Constructor with string
         */
        explicit Guid(std::string fromString);

        /**
         * Constructor with empty
         */
        Guid();
    
        /**
         * Constructor with other object
         */
        Guid(const Guid &other) = default;
        
        /**
         * Copy from other object
         */
        Guid &operator=(const Guid &other) = default;
        
        /**
         * Constructor with other object
         */
        Guid(Guid &&other) = default;
        
        /**
         * Copy from other object
         */
        Guid &operator=(Guid &&other) = default;
    
        /**
         * Check equal with other object
         */
        bool operator==(const Guid &other) const;
        
        /**
         * Check not equal with other object
         */
        bool operator!=(const Guid &other) const;
    

        /**
         * To string
         */
        std::string str() const;

        
        /**
         * To string auto
         */
        operator std::string() const;

        
        /**
         * To bytes array auto
         */
        const std::array<unsigned char, 16>& bytes() const;

        /**
         * Swap with other object
         */
        void swap(Guid &other);

        /**
         * Check is valid
         */
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

#ifdef SGE_ANDROID
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

