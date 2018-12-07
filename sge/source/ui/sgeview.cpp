#include <ui/sgeView.h>

namespace sge
{
    namespace ui
    {

        View::View()
            : _bgView(NULL)
        {
        }

        View::~View()
        {
            if (_bgView)
            {
                delete _bgView;
                _bgView = NULL;
            }
        }

        void View::OnRender()
        {
            if (_bgView && _bgView->Visible())
            {
                _bgView->OnRender();
            }
        }

        bool View::SetSize(const int2 & size)
        {
            if (_bgView)
            {
                _bgView->SetSize(size);
            }
            _size = size;
            return true;
        }

        void View::BackgroundView(IView * view)
        {
            if (_bgView)
            {
                delete _bgView;
                _bgView = NULL;
            }
            _bgView = view;
            if (_bgView)
            {
                _bgView->SetSize(_size);
            }
        }

        bool View::OnLeftButtonDownEvent(const MouseDownEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnLeftButtonDownEvent(event);
            return false;
        }

        bool View::OnLeftButtonUpEvent(const MouseUpEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnLeftButtonUpEvent(event);
            return false;
        }

        bool View::OnLeftButtonClickEvent(const MouseClickEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnLeftButtonClickEvent(event);
            return false;
        }

        bool View::OnRightButtonDownEvent(const MouseDownEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnRightButtonDownEvent(event);
            return false;
        }

        bool View::OnRightButtonUpEvent(const MouseUpEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnRightButtonUpEvent(event);
            return false;
        }

        bool View::OnRightButtonClickEvent(const MouseClickEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnRightButtonClickEvent(event);
            return false;
        }

        bool View::OnMiddleButtonDownEvent(const MouseDownEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnMiddleButtonDownEvent(event);
            return false;
        }

        bool View::OnMiddleButtonUpEvent(const MouseUpEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnMiddleButtonUpEvent(event);
            return false;
        }

        bool View::OnMiddleButtonClickEvent(const MouseClickEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnMiddleButtonClickEvent(event);
            return false;
        }

        bool View::OnMouseMoveEvent(const MouseMoveEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnMouseMoveEvent(event);
            return false;
        }

        bool View::OnMouseWheelEvent(const MouseWheelEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnMouseWheelEvent(event);
            return false;
        }

        bool View::OnKeyDownEvent(const KeyDownEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnKeyDownEvent(event);
            return false;
        }

        bool View::OnKeyUpEvent(const KeyUpEvent & event)
        {
            if (_bgView && _bgView->Visible() && _bgView->Enable())
                return _bgView->OnKeyUpEvent(event);
            return false;
        }

    }
}