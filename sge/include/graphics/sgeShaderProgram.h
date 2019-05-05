#pragma once

#include <core/sgeDefs.h>
#include <graphics/sgeGraphicsDevice.h>

namespace sge
{
    
    /**
     * Graphics Shader Program
     */
    class ShaderProgram
    {
    public:
        /**
         * Constructor with vertex shader source and pixel shader source
         * @param device The target graphics device
         * @param vs The vertex shader source
         * @param ps The pixel shader source
         */
        ShaderProgram(GraphicsDevice& device, const char* vs, const char* ps)
            : _device(device)
        {
            ASSERT(vs && ps && "shader source is empty");
            _programId = device.createShaderProgram(vs, ps);
        }

        /**
         * Destructor
         */
        ~ShaderProgram()
        {
            if (isValid())
            {
                _device.destoryShaderProgram(_programId);
            }
        }

        /**
         * Check progrom valid status
         */
        bool isValid() const { return _programId != kInvalidProgramId; }

        /**
         * Get the native shader program id
         */
        NativeShaderProgramId   getId() const { return _programId; }

    private:
        GraphicsDevice&         _device;
        NativeShaderProgramId   _programId;

        DISABLE_COPY(ShaderProgram)
    };

}
