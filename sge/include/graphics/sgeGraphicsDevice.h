#pragma once

#include <core/sgeDefs.h>

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
        UNKNOWN,

        /**
         * vertex buffer type
         */
        VBO,

        /**
         * index buffer type
         */
        IBO

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
        NOCARE,

        /**
         * the buffer wanted place in gpu memory
         */
        GPU,

        /**
         * the buffer wanted place in agp memory
         */
        AGP
    };

    class NativeBuffer;
    using NativeBufferId    =   NativeBuffer*;
    constexpr NativeBufferId    InvalidBufferId =   NULL;

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
         * Create vertex buffer
         * @param size must biger than 0
         * @param data the data fill buffer, use NULL for not fill buffer now
         * @param place The buffer wanted place
         * @return InvalidVBOId if failed
         */
        NativeBufferId createBuffer(BufferType type, size_t size, const void* data, BufferPlace place);

        /**
         * Destory vertex buffer
         * @param buffer must be a valid buffer id
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

        //TODO: size_t queryBufferSize(NativeBufferId buffer);

    protected:
        friend class GraphicsSystem;
        friend class GraphicsDevicePrivate;
        GraphicsDevice();

        GraphicsDevicePrivate* d;
        DISABLE_COPY(GraphicsDevice)
    };

}
