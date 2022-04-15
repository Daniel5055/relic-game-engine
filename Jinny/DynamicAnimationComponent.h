#pragma once

#include "AnimationComponent.h"

namespace relic
{
    class DynamicAnimationComponent
        : public AnimationComponent
    {
    public:
        DynamicAnimationComponent(unsigned int texture_width, unsigned int texture_height, bool auto_create_clips, int tps, int start_clip, int end_clip, const Identifier& graphics_component_id = Identifier::any);

    protected:
        void doUpdates() override;

        void handleMessage(const Message<GraphicsObjectType>& msg) override;
    private:
        int m_tps;
        int m_start_clip;
        int m_end_clip;
        int m_tick{ 0 };
        int m_clip_index;

    };
}
