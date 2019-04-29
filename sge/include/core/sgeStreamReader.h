#pragma once

#include <core/sgeDefs.h>

namespace sge
{

    /**
     * Enum seek origin
     */
    enum SeekOrigin
    {
        /**
         * Seek from begin 
         */
        SeekSet = 0,

        /**
         * Seek from cur pos
         */
        SeekCur = 1,

        /**
         * Seek from end
         */
        SeekEnd = 2,
    };


    /**
     * Class StreamReader
     */
    class StreamReader
    {
    public:
        /**
         * virtual destructor to release object
         */
        virtual ~StreamReader(){};

        /**
         * Check stream is good
         */
        virtual bool isGood() const = 0;

        /**
         * Check stream is bad
         */
        bool isBad() const { return ! isGood(); }

        /**
         * get the current cursor offset from SEEK_SET
         */
        virtual size_t  tell() = 0;

        /**
         * seek the cursor
         * @param offset The offset the pointer, if offset < 0 will seek on back
         * @param seek Must be SeekOrigin
         * @return true if seek success
         */
        virtual bool    seek(long offset, SeekOrigin seek) = 0;

        /**
         * get the stream length, count of bytes
         * @return the stream length, error while return = unsigned(-1)
         */
        virtual size_t  length() = 0;

        /**
         * Check the stream is eof
         * @return true if eof
         */
        virtual bool    isEOF() = 0;

        /**
         * read bytes to buff for some elements
         * @param buff To output the bytes
         * @param elementSize Byte count for each element
         * @param elementCount The count of element wanted
         * @return The count of element has readed, error while return > elementCount
         */
        virtual size_t  read(void* buff, size_t elementSize, size_t elementCount) = 0;

        /**
         * read a line to buff
         * @param buff To output the bytes
         * @param bufferSize The max sizeof bytes
         * @return True if has readed success, but the max read count is bufferSize - 1
         */            
        virtual bool    getLine(char* buff, size_t bufferSize) = 0;

        /**
         * read a struct data
         * @param out The output object
         * @return true if read success
         */
        template<typename T> bool read(T& out) { return 1 == read(&out, sizeof(T), 1); }

        /**
         * read all  data as text
         */
        virtual String  readAll() 
        {
            size_t len = length();
            String data(len, 0);
            len = read((void*)data.c_str(), len, 1);
            ASSERT(len == 1);
            return  data;
        }
    };


}

