#pragma once

#include <core/sgeDefs.h>
#include <core/sgeMath.h>

namespace sge
{
    
    /**
     * Enum buffer type
     */
    enum BufferType
    {
        /**
         * Unknown buffer type
         */
        kUnknownBufferType,

        /**
         * vertex buffer type
         */
        kVertexBufferType,

        /**
         * index buffer type
         */
        kIndexBufferType,

        //TODO: more buffer types
    };

    /**
     * Enum buffer place
     */
    enum BufferPlace
    {
        /**
         * the buffer wanted place in cpu memory
         */
        kNoCarePlace,

        /**
         * the buffer wanted place in gpu memory
         */
        kGPUPlace,

        /**
         * the buffer wanted place in agp memory
         */
        kAGPPlace
    };

    class NativeBuffer;
    using NativeBufferId = NativeBuffer*;
    constexpr NativeBufferId kInvalidBufferId = NULL;


    class NativeShaderProgram;
    using NativeShaderProgramId = NativeShaderProgram*;
    constexpr NativeShaderProgramId kInvalidProgramId = NULL;


    /**
     * Enum PixelFormat
     * Possible texture pixel formats
     * @seealso https://github.com/cocos2d/cocos2d-x/blob/v3/cocos/renderer/CCTexture2D.h
     */
    enum PixelFormat
    {
        //! auto detect the type
        AUTO,
        //! 32-bit texture: BGRA8888
        BGRA8888,
        //! 32-bit texture: RGBA8888
        RGBA8888,
        //! 24-bit texture: RGBA888
        RGB888,
        //! 16-bit texture without Alpha channel
        RGB565,
        //! 8-bit textures used as masks
        A8,
        //! 8-bit intensity texture
        I8,
        //! 16-bit textures used as masks
        AI88,
        //! 16-bit textures: RGBA4444
        RGBA4444,
        //! 16-bit textures: RGB5A1
        RGB5A1,
        //! 4-bit PVRTC-compressed texture: PVRTC4
        PVRTC4,
        //! 4-bit PVRTC-compressed texture: PVRTC4 (has alpha channel)
        PVRTC4A,
        //! 2-bit PVRTC-compressed texture: PVRTC2
        PVRTC2,
        //! 2-bit PVRTC-compressed texture: PVRTC2 (has alpha channel)
        PVRTC2A,
        //! ETC-compressed texture: ETC
        ETC,
        //! S3TC-compressed texture: S3TC_Dxt1
        S3TC_DXT1,
        //! S3TC-compressed texture: S3TC_Dxt3
        S3TC_DXT3,
        //! S3TC-compressed texture: S3TC_Dxt5
        S3TC_DXT5,
        //! ATITC-compressed texture: ATC_RGB
        ATC_RGB,
        //! ATITC-compressed texture: ATC_EXPLICIT_ALPHA
        ATC_EXPLICIT_ALPHA,
        //! ATITC-compressed texture: ATC_INTERPOLATED_ALPHA
        ATC_INTERPOLATED_ALPHA,
        //! Default texture format: AUTO
        DEFAULT = AUTO,

        NONE = -1
    };

    /**
     * The wrap parameter for texture
     */
    enum TextureWrapType
    {
        //! repeat texture, igore integer part
        kTextureRepeat,
        //! use edge of texture if out of range [0, 1]
        kTextureClamp,
        //! wrap with border
        kTextureBorder,
        //! wrap with mirror
        kTextureMirror,
    };

    /**
     * The magnification filter type
     */
    enum TextureMagnification
    {
        //! The nearest neighbor point
        kTextureNearest,
        //! The linear interpolate
        kTextureLinear,
    };

    /**
     * The minification filter type
     */
    enum TextureMinification
    {
        //! The nearest neighbor point, with nearest mipmap layer
        kTextureNearestMipmapNearest,
        //! The linear interpolate, with nearest mipmap layer
        kTextureLinearMipmapNearest,
        //! The nearest neighbor point, with linear interpolate mipmap layer in two mipmap
        kTextureNearestMipmapLinear,
        //! The linear interpolate, with linear interpolate mipmap layer in two mipmap
        kTextureLinearMipmapLinear,
    };

    /**
     * The mipmap data info
     */
    struct MipmapInfo
    {
        //! The mipmap data memory address
        const byte* address;
        //! The data size
        int         len;
    };

    class NativeTexture;
    using NativeTextureId = NativeTexture*;
    constexpr NativeTextureId kInvalidTextureId = NULL;


    /**
     * Class GraphicsDevice, the graphics interface
     */
    class SGE_API GraphicsDevice
    {
    public:
        /**
         * Destructor
         */
        ~GraphicsDevice();

        /**
         * Initialize the graphics context
         */
        bool initialize();

        /**
         * Shutdown the graphics context
         */
        void shutdown();

        /**
         * Get the last error message
         */
        const char* getLastError();

        /**
         * Create vertex buffer
         * @param size must biger than 0
         * @param data the data fill buffer, use NULL for not fill buffer now
         * @param place The buffer wanted place
         * @return kInvalidBufferId if failed
         */
        NativeBufferId createBuffer(BufferType type, size_t size, const void* data, BufferPlace place);

        /**
         * Destory vertex buffer
         * @param buffer must be a valid buffer id,, the buffer will be set invalid
         */
        void destoryBuffer(NativeBufferId& buffer);

        /**
         * Update vertex buffer
         * @param buffer must be a valid buffer id
         * @param offset Specifies the offset into the buffer
         * @param size The data size for update
         * @param data The data for update
         */
        void updateBuffer(NativeBufferId buffer, size_t offset, size_t size, const void* data);

        /**
         * Get vertex buffer data
         * @param buffer must be a valid buffer id
         * @param offset The offset from buffer
         * @param outData To output data, must be a writable address
         * @param size The size of bytes wanted
         */
        void getBufferData(NativeBufferId buffer, size_t offset, void* outData, size_t size);

        /**
         * Copy buffer between two buffers
         * @param dist The dist buffer, must be a valid buffer id
         * @param src The source buffer, must be a valid buffer id
         * @param distOffset The dist buffer offset
         * @param srcOffset The source buffer offset
         * @param size The size of bytes copy, must bigger than 0
         */
        void copyBufferData(NativeBufferId dist, NativeBufferId src, size_t distOffset, size_t srcOffset, size_t size);

        /**
         * Query buffer size
         * @param buffer the target buffer, must be a valid buffer id
         */
        size_t queryBufferSize(NativeBufferId buffer);

        /**
         * Create shader program
         * @param vs The vertex shader source
         * @param ps The pixel shader source
         * @return kInvalidProgramId if create faild, try getLastError() for error message
         */
        NativeShaderProgramId createShaderProgram(const char* vs, const char* ps);

        /**
         * Destory shader program
         * @param program The program, must be a valid shader program, the program will be set invalid
         */
        void destoryShaderProgram(NativeShaderProgramId& program);

        /**
         * Create texture 2d with with data,
         * the texture is warp parameter is kTextureRepeat & kTextureRepeat
         * @param data Specifies a pointer to the image data in memory, not be null
         * @param dataLen The image data length, must bigger than 0
         * @param pixelFormat The image pixelFormat.
         * @param width The image width, must bigger than 0
         * @param height The image height, must bigger than 0
         */
        NativeTextureId createTexture2D(const void *data, size_t dataLen, PixelFormat pixelFormat, int width, int hight);

        /**
         * Create texture 2d with mipmap infos,
         * the texture is warp parameter is kTextureRepeat & kTextureRepeat
         * @param infos The mipmap infos, not be null
         * @param nums The count of infos, must bigger than 0
         */
        NativeTextureId createTexture2D(MipmapInfo* mipmaps, size_t mipmapsNum, PixelFormat pixelFormat, int width, int height);

        /**
         * Update texture warp parameter
         * @param texture The target texture, must be a valid texture
         * @param wrapS The warp parameter for coordinate S
         * @param wrapT The warp parameter for coordinate T
         */
        void updateTextureWarp(NativeTextureId texture, TextureWrapType wrapS, TextureWrapType wrapT);

        /**
         * Update texture the magnification filter
         * @param texture The target texture, must be a valid texture
         * @param mag The magnification filter
         */
        void updateTextureMagnification(NativeTextureId texture, TextureMagnification mag);

        /**
         * Update texture the minification filter
         * @param texture The target texture, must be a valid texture
         * @param min The minification filter
         */
        void updateTextureMinification(NativeTextureId texture, TextureMinification min);

        /**
         * Update texture 2d with data
         * @param texture The target texture, must be a valid texture
         * @param data Specifies a pointer to the image data in memory.
         * @param offsetX Specifies a texel offset in the x direction within the texture array.
         * @param offsetY Specifies a texel offset in the y direction within the texture array.
         * @param width Specifies the width of the texture subimage.
         * @param height Specifies the height of the texture subimage.
         */
        void updateTexture2D(NativeTextureId texture, const void *data, PixelFormat pixelFormat, int offsetX, int offsetY, int width, int height);

        /**
         * Destory texture
         * @param texture The texture, must be a valid texture, the texture will be set invalid
         */
        void destoryTexture(NativeTextureId& texture);

    protected:
        friend class GraphicsSystem;
        friend class GraphicsDevicePrivate;
        GraphicsDevice();

        GraphicsDevicePrivate* d;
        DISABLE_COPY(GraphicsDevice)
    };

}
