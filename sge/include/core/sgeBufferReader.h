#pragma once

#include <core/sgeDefs.h>
#include <core/sgeStreamReader.h>

namespace sge
{

    /**
     * Class BufferReader inline, to help read the buffer
     */
    class BufferReader : public StreamReader
    {
    public:

        /**
         * Constructor
         * @param buffer The buffer pointer for read wanted 
         * @param len The buffer length
         */
        BufferReader(const byte* buffer, size_t len)
            : _buffer(buffer)
            , _len(len)
            , _curPos(0)
        {
            ASSERT(buffer && "buffer can not be null");
        }


        /**
         * get the current cursor of file
         */
        size_t  tell() override { return _curPos; }

        /**
         * seek the cursor of buffer
         * @param offset The offset the pointer, if offset < 0 will seek on back
         * @param seek Must be SEEK_SET | SEEK_CUR | SEEK_END
         * @return true if seek success
         */
        bool    seek(long offset, SeekOrigin seek) override
        {
            bool    ret =   true;
            long    pos =   0;
            switch(seek)
            {
            case SeekOrigin::SEEK_SET:
                pos =   offset;
                break;
            case SeekOrigin::SEEK_CUR:
                pos =   offset + _curPos;
                break;
            case SeekOrigin::SEEK_END:
                pos =   offset + _len;
                break;
            default:
                ret =   false;
                break;
            }
            if (ret)
            {
                if (pos >= 0 && pos < _len)
                {
                    _curPos =   (size_t)pos;
                }
                else
                {
                    ret =   false;
                }
            }
            return ret;
        }

        /**
         * get the buffer length, count of bytes
         * @return the buffer length
         */
        size_t  length() override { return _len; }

        /**
         * Check the stream is eof
         * @return true if eof
         */
        bool    isEOF() override { return _curPos >= _len; }

        /**
         * read bytes to buff for some elements
         * @param buff To output the bytes
         * @param elementSize Byte count for each element
         * @param elementCount The count of element wanted
         * @return The count of element has readed
         */
        size_t  read(void* buff, size_t elementSize, size_t elementCount) override
        {
            ASSERT(buff && "read buff can not be null");
            size_t  readCount   =   (_len - _curPos) / elementSize;
            if (readCount > elementCount) readCount = elementCount;
            if (readCount > 0)
            {
                size_t  readSize    =   elementSize * readCount;
                memcpy(buff, _buffer + _curPos, readSize);
                _curPos =   readSize;
            }
            return readCount;
        }

        /**
         * read a line to buff
         * @param buff To output the bytes
         * @param bufferSize The max sizeof bytes
         * @return True if has readed success, but the max read count is bufferSize - 1
         */            
        bool    getLine(char* buff, size_t bufferSize) override
        {
            if (_curPos >= _len)
                return false;
            
            size_t  maxCount    =   bufferSize - 1;
            
            for (size_t i = 0; i < maxCount && _curPos < _len; ++i)
            {
                if (_buffer[_curPos] != '\n')
                {
                    buff[i] =   _buffer[_curPos];
                    ++_curPos;
                }
                else
                {
                    ++_curPos;
                    buff[i] =   '\0';
                    return  true;
                }
            }
            buff[maxCount]  =   '\0';
            return  true;
        }

        /**
         * Get the data pointer of buffer
         */
        const   byte* data() { return _buffer; }

    private:
        const byte*     _buffer;
        size_t          _curPos;
        size_t          _len;
        DISABLE_COPY(BufferReader)
    };

}

