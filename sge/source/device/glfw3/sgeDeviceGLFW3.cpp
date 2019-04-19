#include "sgeDeviceGLFW3.h"
#include <core/sgeLog.h>

namespace sge
{
    static int deviceCount = 0;

    DeviceGLFW3::DeviceGLFW3()
        : _window(NULL)
        , _title("sge.device.glfw3")
        , _samples(4)
        , _resizable(true)
        , _width(800)
        , _height(600)
        , _glMAJOR(4)
        , _glMINOR(3)
        , _inputSystem(NULL)
    {
    }

    int DeviceGLFW3::initialize()
    {
        if (deviceCount == 0)
        {
            if (GLFW_TRUE != glfwInit())
            {
                Log::error("glfwInit faild");
                return -1;
            }
            glfwSetErrorCallback(_onGLFWError);
        }

        glfwWindowHint(GLFW_SAMPLES, _samples);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _glMAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _glMINOR);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // mac os needed.
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, _resizable ? GLFW_TRUE : GLFW_FALSE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif // _DEBUG

        _window =   glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
        if (NULL == _window)
        {
            Log::error("glfwCreateWindow failed");
            return -2;
        }

        glfwSetWindowUserPointer(_window, this);
        glfwSetKeyCallback(_window, _onKeyCallback);
        glfwSetMouseButtonCallback(_window, _onMouseButtonCallback);
        glfwSetScrollCallback(_window, _onScrollCallback);
        glfwSetCursorPosCallback(_window, _onCursorPosCallback);
        glfwSetFramebufferSizeCallback(_window, _onFramebufferSizeCallback);
        glfwSetWindowCloseCallback(_window, _onWindowCloseCallback);

        glfwMakeContextCurrent(_window);

        ++deviceCount;
        return 0;
    }

    void DeviceGLFW3::finalize()
    {
        --deviceCount;
        if (deviceCount == 0)
        {
            glfwTerminate();
        }
    }
    
    void DeviceGLFW3::tick()
    {
        glfwPollEvents();
    }

    void DeviceGLFW3::_onGLFWError(int code, const char* msg)
    {
        Log::error("glfw error(%d): %s", code, msg);
    }

    void DeviceGLFW3::_onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        DeviceGLFW3* module = (DeviceGLFW3*)glfwGetWindowUserPointer(window);
        if (module->_inputSystem) 
        {
            switch (action)
            {
                case GLFW_PRESS:
                    module->_inputSystem->onKeyDown(key);
                    break;
                case GLFW_RELEASE:
                    module->_inputSystem->onKeyUp(key);
                    break;
                case GLFW_REPEAT:
                    module->_inputSystem->onKeyPress(key);
                    break;
                default:
                    break;
            }
        }
    }

    void DeviceGLFW3::_onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        DeviceGLFW3* module = (DeviceGLFW3*)glfwGetWindowUserPointer(window);
        if (module->_inputSystem) 
        {
            switch (action)
            {
                case GLFW_PRESS:
                    switch (button)
                    {
                        case GLFW_MOUSE_BUTTON_LEFT:
                            module->_inputSystem->onLeftButtonDown();
                            break;
                        case GLFW_MOUSE_BUTTON_RIGHT:
                            module->_inputSystem->onRightButtonDown();
                            break;
                        case GLFW_MOUSE_BUTTON_MIDDLE:
                            module->_inputSystem->onMiddleButtonDown();
                            break;
                        default:
                            break;
                    }
                    break;
                case GLFW_RELEASE:
                    switch (button)
                    {
                        case GLFW_MOUSE_BUTTON_LEFT:
                            module->_inputSystem->onLeftButtonUp();
                            break;
                        case GLFW_MOUSE_BUTTON_RIGHT:
                            module->_inputSystem->onRightButtonUp();
                            break;
                        case GLFW_MOUSE_BUTTON_MIDDLE:
                            module->_inputSystem->onMiddleButtonUp();
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    void DeviceGLFW3::_onScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        DeviceGLFW3* module = (DeviceGLFW3*)glfwGetWindowUserPointer(window);
        if (module->_inputSystem) 
        {
            module->_inputSystem->onScroll(xoffset, yoffset);
        }
    }

    void DeviceGLFW3::_onCursorPosCallback(GLFWwindow* window, double x, double y)
    {
        DeviceGLFW3* module = (DeviceGLFW3*)glfwGetWindowUserPointer(window);
        if (module->_inputSystem)
        {
            module->_inputSystem->onCursorPos(x, y);
        }
    }

    void DeviceGLFW3::_onFramebufferSizeCallback(GLFWwindow* window, int w, int h)
    {
        DeviceGLFW3* module = (DeviceGLFW3*)glfwGetWindowUserPointer(window);
        if (module->_inputSystem)
        {
            module->_inputSystem->onSizeChange(w, h);
        }
    }

    void DeviceGLFW3::_onWindowCloseCallback(GLFWwindow* window)
    {
        DeviceGLFW3* module = (DeviceGLFW3*)glfwGetWindowUserPointer(window);
        if (module->_inputSystem)
        {
            module->_inputSystem->onCloseEvent();
        }
    }

    SGE_DEVICE_API DeviceModule* newDeviceModule()
    {
        return new DeviceGLFW3();
    }

    SGE_DEVICE_API void deleteDeviceModule(DeviceModule* object)
    {
        DeviceGLFW3* myImpl = dynamic_cast<DeviceGLFW3*>(object);
        if (myImpl)
        {
            delete myImpl;
        }
    }

}

