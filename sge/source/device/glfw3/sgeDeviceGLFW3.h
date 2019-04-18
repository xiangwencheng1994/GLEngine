#pragma once

#include <device/sgeDeviceModule.h>
#include <GLFW/glfw3.h>

namespace sge
{

    class DeviceGLFW3 : public DeviceModule
    {
    public:
        virtual ModuleType moduleType() const { return ModuleType::kModuleTypeDevice; }
        virtual int initialize();
        virtual void finalize();
        virtual void tick();

        virtual void setInputModule(InputSystem* inputSystem) { _inputSystem = inputSystem; }
        virtual InputSystem* getInputModule() const { return _inputSystem; }

    protected:
        GLFWwindow*     _window;
        sgeString       _title;
        int             _samples;
        bool            _resizable;
        int             _width;
        int             _height;
        int             _glMAJOR;
        int             _glMINOR;
        InputSystem*    _inputSystem;
        
        static void _onGLFWError(int code, const char* msg);
        static void _onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void _onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void _onScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
        static void _onCursorPosCallback(GLFWwindow* window, double x, double y);
        static void _onFramebufferSizeCallback(GLFWwindow* window, int w, int h);
        static void _onWindowCloseCallback(GLFWwindow* window);
    };

}