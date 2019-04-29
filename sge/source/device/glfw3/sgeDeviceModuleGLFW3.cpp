#include <device/sgeDeviceModule.h>
#include <core/sgeLog.h>

#include <GLFW/glfw3.h>

namespace sge
{
    static int deviceCount = 0;

    class DeviceModulePrivate
    {
    public:
        DeviceModulePrivate()
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

    public:
        GLFWwindow*     _window;
        String          _title;
        int             _samples;
        bool            _resizable;
        int             _width;
        int             _height;
        int             _glMAJOR;
        int             _glMINOR;
        IInputHandler*  _inputSystem;

        static void _onGLFWError(int code, const char* msg);
        static void _onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void _onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void _onScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
        static void _onCursorPosCallback(GLFWwindow* window, double x, double y);
        static void _onFramebufferSizeCallback(GLFWwindow* window, int w, int h);
        static void _onWindowCloseCallback(GLFWwindow* window);
    };

    DeviceModule::DeviceModule()
        : d(new DeviceModulePrivate())
    {
    }


    DeviceModule::~DeviceModule()
    {
        delete d;
    }

    int DeviceModule::initialize()
    {
        if (deviceCount == 0)
        {
            if (GLFW_TRUE != glfwInit())
            {
                Log::error("glfwInit faild");
                return -1;
            }
            glfwSetErrorCallback(d->_onGLFWError);
        }

        glfwWindowHint(GLFW_SAMPLES, d->_samples);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, d->_glMAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, d->_glMINOR);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // mac os needed.
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, d->_resizable ? GLFW_TRUE : GLFW_FALSE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif // _DEBUG

        d->_window =   glfwCreateWindow(d->_width, d->_height, d->_title.c_str(), NULL, NULL);
        if (NULL == d->_window)
        {
            Log::error("glfwCreateWindow failed");
            return -2;
        }

        glfwSetWindowUserPointer(d->_window, d);
        glfwSetKeyCallback(d->_window, d->_onKeyCallback);
        glfwSetMouseButtonCallback(d->_window, d->_onMouseButtonCallback);
        glfwSetScrollCallback(d->_window, d->_onScrollCallback);
        glfwSetCursorPosCallback(d->_window, d->_onCursorPosCallback);
        glfwSetFramebufferSizeCallback(d->_window, d->_onFramebufferSizeCallback);
        glfwSetWindowCloseCallback(d->_window, d->_onWindowCloseCallback);

        glfwMakeContextCurrent(d->_window);

        ++deviceCount;
        return 0;
    }

    void DeviceModule::finalize()
    {
        --deviceCount;
        if (deviceCount == 0)
        {
            glfwTerminate();
        }
    }
    
    inline void DeviceModule::tick()
    {
        glfwPollEvents();
    }

    inline void DeviceModule::swapBuffer()
    {
        glfwSwapBuffers(d->_window);
    }

    inline void DeviceModule::setInputModule(IInputHandler* inputSystem)
    {
        d->_inputSystem = inputSystem;
    }

    inline IInputHandler* DeviceModule::getInputModule() const
    {
        return d->_inputSystem;
    }

    void DeviceModulePrivate::_onGLFWError(int code, const char* msg)
    {
        Log::error("glfw error(%d): %s", code, msg);
    }

    void DeviceModulePrivate::_onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        DeviceModulePrivate* module = (DeviceModulePrivate*)glfwGetWindowUserPointer(window);
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

    void DeviceModulePrivate::_onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        DeviceModulePrivate* module = (DeviceModulePrivate*)glfwGetWindowUserPointer(window);
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

    void DeviceModulePrivate::_onScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        DeviceModulePrivate* module = (DeviceModulePrivate*)glfwGetWindowUserPointer(window);
        if (module->_inputSystem) 
        {
            module->_inputSystem->onScroll(xoffset, yoffset);
        }
    }

    void DeviceModulePrivate::_onCursorPosCallback(GLFWwindow* window, double x, double y)
    {
        DeviceModulePrivate* module = (DeviceModulePrivate*)glfwGetWindowUserPointer(window);
        if (module->_inputSystem)
        {
            module->_inputSystem->onCursorPos(x, y);
        }
    }

    void DeviceModulePrivate::_onFramebufferSizeCallback(GLFWwindow* window, int w, int h)
    {
        DeviceModulePrivate* module = (DeviceModulePrivate*)glfwGetWindowUserPointer(window);
        if (module->_inputSystem)
        {
            module->_inputSystem->onSizeChange(w, h);
        }
    }

    void DeviceModulePrivate::_onWindowCloseCallback(GLFWwindow* window)
    {
        DeviceModulePrivate* module = (DeviceModulePrivate*)glfwGetWindowUserPointer(window);
        if (module->_inputSystem)
        {
            module->_inputSystem->onCloseEvent();
        }
    }


}

