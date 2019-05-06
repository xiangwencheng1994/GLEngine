#pragma once

#include <graphics/sgeGraphicsDevice.h>
#include <core/sgeFileReader.h>

namespace sge
{
    
    /**
     * Class Texture
     */
    class Texture
    {
    public:
        /**
         * Constructor with image file
         */
        Texture(GraphicsDevice& device, const char* imgFile)
            : _device(device)
            , _pixelFormat(PixelFormat::NONE)
            , _width(0)
            , _height(0)
        {
            FileReader file(imgFile);
            if (file.isGood())
            {
                size_t len = file.length();
                if (len > 0)
                {
                    void* data = malloc(len);
                    if (1 == file.read(data, len, 1))
                    {
                        _id = device.createTexture2D(data, len, PixelFormat::AUTO, auto);
                    }
                    free(data);
                }
            }
            _id = device.createTexture2D(imgFile, &_pixelFormat, &_width, &_height);
        }

        /**
         * Constructor with image data
         * @param device The GraphicsDevice device
         * @param data The image data
         * @param format The image data format
         * @param dataLen The count of image data bytes
         */
        Texture(GraphicsDevice& device, const byte* data, PixelFormat format, size_t dataLen)
        {
            
        }

        /**
         * Destructor
         */
        ~Texture()
        {
            if (isValid())
            {
                _device.destoryTexture(_id);
            }
        }

        /**
         * Check progrom valid status
         */
        bool isValid() const { return _id != kInvalidTextureId; }

        /**
         * Get the native texture id
         */
        NativeTextureId getId() const { return _id; }

        /**
         * Get the PixelFormat
         */
        PixelFormat     getPixelFormat() const { return _pixelFormat; }

        /**
         * Get the texture width
         */
        int             getWidth() const { return _width; }

        /**
         * Get the texture height
         */
        int             getHeight() const { return _height; }

    protected:
        GraphicsDevice& _device;
        NativeTextureId _id;
        PixelFormat     _pixelFormat;
        int             _width;
        int             _height;

        DISABLE_COPY(Texture)
    };

}
