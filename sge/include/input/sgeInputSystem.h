#pragma once

#include <core/sgeIInputHandler.h>

namespace sge
{

    /**
     * Class input module
     */
    class SGE_API InputSystem : public IInputHandler
    {
    public:
        // keybord
        virtual void onKeyDown(int keyCode);
        virtual void onKeyUp(int keyCode);
        virtual void onKeyPress(int keyCode);

        // mouse
        virtual void onLeftButtonDown();
        virtual void onRightButtonDown();
        virtual void onMiddleButtonDown();
        virtual void onLeftButtonUp();
        virtual void onRightButtonUp();
        virtual void onMiddleButtonUp();
        virtual void onScroll(double xoffset, double yoffset);
        virtual void onCursorPos(double x, double y);

        // window event
        virtual void onSizeChange(int w, int h);
        virtual void onCloseEvent();

        // get status
        virtual bool isLeftButtonPressed();
        virtual bool isRightButtonPressed();
        virtual bool isMiddleButtonPressed();
        virtual bool isKeyPressed(int keyCode);

    public:
        ModuleType moduleType() const { return ModuleType::kModuleTypeInput; }

        /**
         * Initialize system
         */
        int initialize();

        /**
         * Finalize system
         */
        void finalize();

        /**
         * Do a tick
         */
        void tick();
    };

}
