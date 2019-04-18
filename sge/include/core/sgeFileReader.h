#pragma once

#include <core/sgeDefs.h>
#include <core/sgeStreamReader.h>

namespace sge
{

    /**
     * Class FileReader inline, to help read the file
     */
    class FileReader : public StreamReader
    {
    public:
        /**
         * Constructor
         * @param fileName The fileName for open wanted 
         * @param ret The result of open the file
         */
        FileReader(const char* fileName, bool* ret)
        {
            errno_t error = fopen_s(&_file, fileName, "rb");
            if (ret)
            {
                *ret = (error == 0);
            }
            else
            {
                ASSERT(error == 0);
            }
        }

        /**
         * Destructor, release the file handle
         */
        ~FileReader()
        {
            if (_file)
            {
                fclose(_file);
                _file = NULL;
            }
        }

        /**
         * get the current cursor of file
         */
        size_t tell() override { return ftell(_file); }

        /**
         * seek the cursor of file
         * @param offset The offset the pointer, if offset < 0 will seek on back
         * @param seek Must be SEEK_SET | SEEK_CUR | SEEK_END
         * @return true if seek success
         */
        bool seek(long offset, SeekOrigin seek) override { return 0 == fseek(_file, offset, seek); }

        /**
         * get the file length, count of bytes
         * @return the file length, error while return = unsigned(-1)
         */
        size_t length() override
        {
            size_t ret = unsigned(-1);
            size_t cur = tell();
            if (seek(0, SeekSet))
            {
                if (seek(0, SeekEnd)) ret = tell();
                seek(cur, SeekSet);
            }
            return ret;
        }
        
        /**
         * Check the stream is eof
         * @return true if eof
         */
        bool isEOF() override
        {
            return 0 != feof(_file);
        }

        /**
         * read bytes to buff for some elements
         * @param buff To output the bytes
         * @param elementSize Byte count for each element
         * @param elementCount The count of element wanted
         * @return The count of element has readed, error while return > elementCount
         */
        size_t read(void* buff, size_t elementSize, size_t elementCount)  override
        {
            return fread(buff, elementSize, elementCount, _file);
        }
        
        /**
         * read a line to buff
         * @param buff To output the bytes
         * @param bufferSize The max sizeof bytes
         * @return True if has readed success, but the max read count is bufferSize - 1
         */
        bool getLine(char* buff, size_t bufferSize) override
        {
            return fgets(buff, (int)bufferSize, _file) != NULL;
        }

    private:
        FILE*       _file;
        DISABLE_COPY(FileReader)
    };

}

