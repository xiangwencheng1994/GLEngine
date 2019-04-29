#include <input/sgeInputSystem.h>

namespace sge
{

    // keybord
    inline void InputSystem::onKeyDown(int keyCode) {}
    inline void InputSystem::onKeyUp(int keyCode) {}
    inline void InputSystem::onKeyPress(int keyCode) {}

    // mouse
    inline void InputSystem::onLeftButtonDown() {}
    inline void InputSystem::onRightButtonDown() {}
    inline void InputSystem::onMiddleButtonDown() {}
    inline void InputSystem::onLeftButtonUp() {}
    inline void InputSystem::onRightButtonUp() {}
    inline void InputSystem::onMiddleButtonUp() {}
    inline void InputSystem::onScroll(double xoffset, double yoffset) {}
    inline void InputSystem::onCursorPos(double x, double y) {}

    // window event
    inline void InputSystem::onSizeChange(int w, int h) {}
    inline void InputSystem::onCloseEvent() {}

    // get status
    inline bool InputSystem::isLeftButtonPressed() { return false; }
    inline bool InputSystem::isRightButtonPressed() { return false; }
    inline bool InputSystem::isMiddleButtonPressed() { return false; }
    inline bool InputSystem::isKeyPressed(int keyCode) { return false; }
    
    inline int  InputSystem::initialize() { return 0; }
    inline void InputSystem::finalize() {}
    inline void InputSystem::tick() {}

}

