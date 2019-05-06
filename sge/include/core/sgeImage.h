#pragma once

#include <core/sgeDefs.h>

namespace sge
{
    /**
     * Enum PixelFormat
     * Possible pixel formats
     */
    enum PixelFormat
    {
        //! 32-bit texture: BGRA8888
        PF_BGRA8888,
        //! 32-bit texture: RGBA8888
        PF_RGBA8888,
        //! 24-bit texture: RGBA888
        PF_RGB888,
        //! 16-bit texture without Alpha channel
        PF_RGB565,
        //! 8-bit textures used as masks
        PF_A8,
        //! 8-bit intensity texture
        PF_I8,
        //! 16-bit textures used as masks
        PF_AI88,
        //! 16-bit textures: RGBA4444
        PF_RGBA4444,
        //! 16-bit textures: RGB5A1
        PF_RGB5A1,
        //! 4-bit PVRTC-compressed texture: PVRTC4
        PF_PVRTC4,
        //! 4-bit PVRTC-compressed texture: PVRTC4 (has alpha channel)
        PF_PVRTC4A,
        //! 2-bit PVRTC-compressed texture: PVRTC2
        PF_PVRTC2,
        //! 2-bit PVRTC-compressed texture: PVRTC2 (has alpha channel)
        PF_PVRTC2A,
        //! ETC-compressed texture: ETC
        PF_ETC,
        //! S3TC-compressed texture: S3TC_Dxt1
        PF_S3TC_DXT1,
        //! S3TC-compressed texture: S3TC_Dxt3
        PF_S3TC_DXT3,
        //! S3TC-compressed texture: S3TC_Dxt5
        PF_S3TC_DXT5,
        //! ATITC-compressed texture: ATC_RGB
        PF_ATC_RGB,
        //! ATITC-compressed texture: ATC_EXPLICIT_ALPHA
        PF_ATC_EXPLICIT_ALPHA,
        //! ATITC-compressed texture: ATC_INTERPOLATED_ALPHA
        PF_ATC_INTERPOLATED_ALPHA,
        //! ERROR Format
        PF_NONE = -1
    };

    /**
     * Class Image resource
     */
    class Image
    {
    public:
        Image(const char* imgFile);
        Image(const byte* data, size_t len);

    private:
        PixelFormat     _pixelFormat;

        DISABLE_COPY(Image)
    };

}