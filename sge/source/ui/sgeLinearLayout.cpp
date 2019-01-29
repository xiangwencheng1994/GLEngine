#include <ui/sgeLinearLayout.h>

namespace sge
{


    namespace ui
    {

        LinearLayout::LinearLayout(Application * app_not_null)
            : ViewGroup(app_not_null)
        {
        }

        LinearLayout::~LinearLayout()
        {
        }
        
        void LinearLayout::onMeasureChild(int limtsWidth, int limtsHeight)
        {
            const int count = getChildCount();

            int space = limtsWidth;
            int maxHeight = 0;

            for (int i = 0; i < count; ++i)
            {
                RefPtr<View> view = getChildAt(i);
                RefPtr<LayoutParams> p = view->getLayoutParams();
                LinearLayoutParams* param = (LinearLayoutParams*)(p.get());
                if (param->mWidth != MATCH_PARENT || limtsWidth < 0)
                {
                    view->doMeasure(MeasureMode::UNSPECIFIED, limtsWidth, MeasureMode::UNSPECIFIED, limtsHeight);
                    space -= view->getMeasuredWidth();
                    int childHeight = view->getMeasuredHeight();
                    if (maxHeight < childHeight) maxHeight = childHeight;
                }
            }

            if (limtsWidth > 0)
            {
                float perWeight = 0.0f;
                for (int i = 0; i < count; ++i)
                {
                    RefPtr<View> view = getChildAt(i);
                    RefPtr<LayoutParams> p = view->getLayoutParams();
                    LinearLayoutParams* param = dynamic_cast<LinearLayoutParams*>(p.get());
                    if (param->mWidth == MATCH_PARENT)
                    {
                        perWeight += param->mWeight;
                    }
                }
                perWeight = (float)space / perWeight;

                for (int i = 0; i < count; ++i)
                {
                    RefPtr<View> view = getChildAt(i);
                    RefPtr<LayoutParams> p = view->getLayoutParams();
                    LinearLayoutParams* param = dynamic_cast<LinearLayoutParams*>(p.get());
                    if (param->mWidth == MATCH_PARENT)
                    {
                        view->doMeasure(MeasureMode::EXACTLY, param->mWeight * perWeight, MeasureMode::UNSPECIFIED, limtsHeight);
                        int childHeight = view->getMeasuredHeight();
                        if (maxHeight < childHeight) maxHeight = childHeight;
                    }
                }
            }

            if (limtsHeight == WRAP_CONTENT)
            {
                for (int i = 0; i < count; ++i)
                {
                    RefPtr<View> view = getChildAt(i);
                    RefPtr<LayoutParams> p = view->getLayoutParams();
                    LinearLayoutParams* param = dynamic_cast<LinearLayoutParams*>(p.get());
                    if (param->mHeight == MATCH_PARENT && view->getMeasuredHeight() < maxHeight)
                    {
                        view->requestMeasure();
                        view->doMeasure(MeasureMode::EXACTLY, view->getMeasuredWidth(), MeasureMode::AT_MOST, maxHeight);
                    }
                }
            }

        }

        void LinearLayout::onLayout(bool changed, int left, int top, int right, int bottom)
        {
            int count = getChildCount();
            for (int i = 0; i < count; ++i)
            {
                RefPtr<View> view = getChildAt(i);
                if (changed)
                {
                    RefPtr<LayoutParams> params = view->getLayoutParams();
                    if (params->mWidth < 0 || params->mHeight < 0)
                        view->requestMeasure();
                }
                int childWidth = view->getMeasuredWidth();
                int childHeight = view->getMeasuredHeight();
                view->doLayout(left, top, childWidth, childHeight);
                left += childWidth;
            }
        }

        RefPtr<LayoutParams> LinearLayout::generateDefaultLayoutParams()
        {
            return RefPtr<LayoutParams>(new LinearLayoutParams(WRAP_CONTENT, WRAP_CONTENT, 1.0f));
        }

        bool LinearLayout::acceptChildLayoutParams(LayoutParams * params)
        {
            if (dynamic_cast<LinearLayoutParams*>(params))
                return true;
        }

    }

}