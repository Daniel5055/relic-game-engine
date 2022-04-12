#include "AnimationComponent.h"

#include "GraphicsComponent.h"

#include "Point.h"
#include "Texture.h"

relic::AnimationComponent::AnimationComponent(int texture_width, int texture_height, int tpf, int start, int end,
    const Identifier& graphics_component_id)
    : MessageSender<relic::GraphicsObjectType>(getId(), true), MessageReceiver<relic::GraphicsObjectType>(getId(), true),
      m_tick_per_frame(tpf), m_clip_start(start), m_clip_end(end), m_texture_width(texture_width),
      m_texture_height(texture_height)
{
    Message msg{ GraphicsObjectType::query_graphic };
    msg.to = graphics_component_id;

    // Query for the graphic to use, if id provided is null then will take the first query back and send a warning
    sendImmediateMessage(msg);

    // Making sure there is at least  something
    m_clips.emplace_back(0, 0, 0, 0);
}

void relic::AnimationComponent::createClipGrid()
{
    m_clips.clear();
    int width = m_current_clip.w;
    int height = m_current_clip.h;

    const int w_max = m_texture_width / width;
    const int h_max = m_texture_height / height;

    // Dividing the texture into clips of equal size, send warning if not equal size
    for (int y = 0; y < h_max; y++)
    {
        for (int x = 0; x < w_max; x++)
        {
            m_clips.emplace_back(x * width, y * height, width, height);
        }
    }
}

void relic::AnimationComponent::doUpdates()
{
    Component::doUpdates();
    MessageReceiver<GraphicsObjectType>::handleMessages();

    // Iterate through 
    m_tick++;
    if (m_tick >= m_tick_per_frame)
    {
        m_tick = 0;

        m_clip_index++;
        if (m_clip_index >= m_clip_end)
        {
            m_clip_index = m_clip_start;
        }

        changeCurrentClip(m_clip_index);
    }
}

void relic::AnimationComponent::changeCurrentClip(const int index)
{
    // Changes location of current clip pointer based from clips
    m_current_clip.x = m_clips[index].x;
    m_current_clip.y = m_clips[index].y;
}

int relic::AnimationComponent::getTextureWidth() const
{
    return m_texture_width;
}

int relic::AnimationComponent::getTextureHeight() const
{
    return m_texture_height;
}

void relic::AnimationComponent::handleMessage(const Message<GraphicsObjectType>& msg)
{
    switch (msg.type)
    {
    case GraphicsObjectType::sent_graphic:
        // If was sent back to right the component 
        if (msg.to.getSubId() == getId().getSubId())
        {
            // Setting the reference of the clipper
            const auto graphic = std::any_cast<framework::Graphic*>(msg.value);
            m_current_clip = graphic->getShape();
            graphic->setClip(&m_current_clip);

            createClipGrid();
            changeCurrentClip(m_clip_start);
            break;
        }
    }
}
