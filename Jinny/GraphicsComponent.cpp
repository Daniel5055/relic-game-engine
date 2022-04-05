#include "GraphicsComponent.h"

void relic::GraphicsComponent::setClipPtr(const framework::Shape* clip)
{
    m_graphic_ptr->setClip(*clip);
}

void relic::GraphicsComponent::setGraphic(framework::Graphic* graphic_ptr)
{
    m_graphic_ptr = std::unique_ptr<framework::Graphic>(graphic_ptr);
}

void relic::GraphicsComponent::prepareMessage(GraphicsMessage& msg)
{
    if (msg.object_id == k_unset_id)
    {
        msg.object_id = getObjectId();
    }
}

framework::Graphic& relic::GraphicsComponent::getGraphic()
{
    return *m_graphic_ptr;
}
