

#ifndef SGE_LINEAR_LAYOUT_H
#define SGE_LINEAR_LAYOUT_H

#include <ui/sgeViewGroup.h>

namespace sge
{

    namespace ui
    {
        
        class SGE_API LinearLayoutParams : public LayoutParams
        {
        public:
            LinearLayoutParams(int width = MATCH_PARENT, int height = MATCH_PARENT, float weight = 1.0f)
                : LayoutParams(width, height)
                , mWeight(weight)
            {
            }

            float mWeight;
        protected:
            friend class LinearLayout;
        };

        class SGE_API LinearLayout : public ViewGroup
        {
        public:
            LinearLayout(Application* app_not_null);
            virtual ~LinearLayout();

        protected:
            
            /**
             * Callback while need measure all children by onMeasure()
             * @param limtsWidth The limted width size, will be < 0 if not limted
             * @param limtsHeight The limted height size, will be < 0 if not limted
             */
            virtual void onMeasureChild(int limtsWidth, int limtsHeight);

            /**
             * Callback on layout content and all child content
             * @seealse ui.View.onLayout()
             */
            virtual void onLayout(bool changed, int left, int top, int right, int bottom) override;

            /**
             * Generate a default LayoutParams for this layout
             * @return a referenced LayoutParams
             */
            virtual RefPtr<LayoutParams> generateDefaultLayoutParams() override;

            /**
             * Try accept a LayoutParams for a view in this layout
             * @return ture if veiw can set params in this layout
             */
            virtual bool acceptChildLayoutParams(LayoutParams* params) override;

        };

    }

}

#endif // !SGE_LINEAR_LAYOUT_H
