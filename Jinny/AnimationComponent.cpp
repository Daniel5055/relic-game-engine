#include "AnimationComponent.h"

#include <cassert>
#include <stdexcept>

#include "GraphicsComponent.h"
#include "Texture.h"

relic::AnimationComponent::AnimationComponent(unsigned texture_width, unsigned texture_height, bool auto_create_clip,
    const Identifier& graphics_component_id)
    : MessageSender<relic::GraphicsObjectType>(getId(), true), MessageReceiver<relic::GraphicsObjectType>(getId(), true)
    , m_auto_clip(auto_create_clip), m_texture_width(texture_width), m_texture_height(texture_height)
{
    // If null then used a component that hadn't been added to the object
    assert(graphics_component_id != Identifier::null);

    Message msg{ GraphicsObjectType::query_graphic };
    msg.to = graphics_component_id;

    // Query for the graphic to use, if id provided is null then will take the first query back and send a warning
    MessageSender<GraphicsObjectType>::sendImmediateMessage(msg);

    // Making sure there is at least  something
    m_clips.emplace_back(0, 0, 0, 0);
}

void relic::AnimationComponent::createClipGrid(const unsigned int texture_width, const unsigned int texture_height)
{
    m_clips.clear();
    unsigned int width = m_current_clip.w;
    unsigned int height = m_current_clip.h;

    const unsigned int w_max = texture_width / width;
    const unsigned int h_max = texture_height / height;

    // Dividing the texture into clips of equal size, send warning if not equal size
    for (unsigned int y = 0; y < h_max; y++)
    {
        for (unsigned int x = 0; x < w_max; x++)
        {
            m_clips.emplace_back(x * width, y * height, width, height);
        }
    }
}

void relic::AnimationComponent::doUpdates()
{
    MessageReceiver<GraphicsObjectType>::handleMessages();
}

void relic::AnimationComponent::changeCurrentClip(const unsigned int index)
{
    // Making sure that index is within bounds
        // Changes location of current clip pointer based from clips
    try
    {
        m_current_clip.x = m_clips[index].x;
        m_current_clip.y = m_clips[index].y;
    }
    catch ([[maybe_unused]] std::out_of_range& e)
    {
        MessageSender<LoggingType>::sendMessage({ LoggingType::error_number_out_of_bounds,
            std::make_any<std::string>("Index to change graphic clip is larger than number of clips") });
    }
}

void relic::AnimationComponent::handleMessage(const Message<GraphicsObjectType>& msg)
{
    switch (msg.type)
    {
    case GraphicsObjectType::sent_graphic:
    {
        // If was sent back to right the component 
            // Setting the reference of the clipper
        const auto graphic = std::any_cast<framework::Graphic*>(msg.value);
        m_current_clip = graphic->getShape();
        graphic->setClip(&m_current_clip);

        if (m_auto_clip)
        {
            createClipGrid(m_texture_width, m_texture_height);
            changeCurrentClip(0);
        }
        break;

    }
    case GraphicsObjectType::change_clip:
    {
        const auto clip_id = std::any_cast<int>(msg.value);
        changeCurrentClip(clip_id);
        break;

    }
    case GraphicsObjectType::insert_clip:
    {
        const auto clip_pair = std::any_cast<std::pair<int, framework::Shape>>(msg.value);

        try
        {
            m_clips[clip_pair.first] = clip_pair.second;
        }
        catch ([[maybe_unused]] std::out_of_range& e)
        {
            MessageSender<LoggingType>::sendMessage({ LoggingType::error_number_out_of_bounds,
                std::make_any<std::string>("Index to change graphic clip is larger than number of clips") });
        }

        break;

    }
    case GraphicsObjectType::push_back_clip:
    {
        const auto clip = std::any_cast<framework::Shape>(msg.value);
        m_clips.push_back(clip);

        break;

    }
    }
}
