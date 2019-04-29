#pragma once

#include <core/sgeRuntimeModule.h>

namespace sge
{
    
    /**
     * Interface input handler
     */
    class SGE_API IInputHandler : public IRuntimeModule
    {
    public:
        // keybord
        virtual void onKeyDown(int keyCode) = 0;
        virtual void onKeyUp(int keyCode) = 0;
        virtual void onKeyPress(int keyCode) = 0;
        
        // mouse
        virtual void onLeftButtonDown() = 0;
        virtual void onRightButtonDown() = 0;
        virtual void onMiddleButtonDown() = 0;
        virtual void onLeftButtonUp() = 0;
        virtual void onRightButtonUp() = 0;
        virtual void onMiddleButtonUp() = 0;
        virtual void onScroll(double xoffset, double yoffset) = 0;
        virtual void onCursorPos(double x, double y) = 0;

        // window event
        virtual void onSizeChange(int w, int h) = 0;
        virtual void onCloseEvent() = 0;

        // get status
        virtual bool isLeftButtonPressed() = 0;
        virtual bool isRightButtonPressed() = 0;
        virtual bool isMiddleButtonPressed() = 0;
        virtual bool isKeyPressed(int keyCode) = 0;
    };

}