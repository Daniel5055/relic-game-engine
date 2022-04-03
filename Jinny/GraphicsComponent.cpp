#include "GraphicsComponent.h"

void jinny::GraphicsComponent::setClipPtr(const framework::Shape* clip)
{
    m_graphic_ptr->setClip(*clip);
}

void jinny::GraphicsComponent::setGraphic(framework::Graphic* graphic_ptr)
{
    m_graphic_ptr = std::unique_ptr<framework::Graphic>(graphic_ptr);
}

void jinny::GraphicsComponent::prepareMessage(GraphicsMessage& msg)
{
    if (msg.object_id == k_unset_id)
    {
        msg.object_id = getObjectId();
    }
}

framework::Graphic& jinny::GraphicsComponent::getGraphic()
{
    return *m_graphic_ptr;
}
