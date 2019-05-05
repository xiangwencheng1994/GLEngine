#pragma once

#include <graphics/sgeGraphicsDevice.h>

namespace sge
{
    
    /**
     * Class Texture
     */
    class Texture
    {
    public:
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


    protected:
        GraphicsDevice& _device;
        NativeTextureId _id;

        DISABLE_COPY(Texture)
    };

}
