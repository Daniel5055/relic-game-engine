#include "DynamicAnimationComponent.h"

relic::DynamicAnimationComponent::DynamicAnimationComponent(const unsigned int texture_width, const unsigned int texture_height, const bool auto_create_clips, const int tps, const int start_clip, const int end_clip,
    const Identifier& graphics_component_id)
    :AnimationComponent(texture_width, texture_height, auto_create_clips, graphics_component_id), m_tps(tps), m_start_clip(start_clip), m_end_clip(end_clip), m_clip_index(start_clip)
{
}

void relic::DynamicAnimationComponent::doUpdates()
{
    AnimationComponent::doUpdates();

    // Iterate through 
    m_tick++;
    if (m_tick >= m_tps)
    {
        m_tick = 0;

        m_clip_index++;
        if (m_clip_index >= m_end_clip)
        {
            m_clip_index = m_start_clip;
        }

        changeCurrentClip(m_clip_index);
    }
}

void relic::DynamicAnimationComponent::handleMessage(const Message<GraphicsObjectType>& msg)
{
    switch (msg.type)
    {
    case GraphicsObjectType::change_clip_range:
    {
        const auto range = std::any_cast<std::pair<int, int>>(msg.value);

        m_start_clip = range.first;
        m_end_clip = range.second;

        if (m_start_clip > m_end_clip)
        {
            MessageSender<LoggingType>::sendMessage({ LoggingType::error_number_out_of_bounds,
                std::make_any<std::string>("The starting graphic clip cannot be greater than the end graphic clip") });
        }

        break;

    }
    default:
        AnimationComponent::handleMessage(msg);
    }
}
