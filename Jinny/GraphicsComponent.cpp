#include "GraphicsComponent.h"

#include "Point.h"

relic::GraphicsComponent::GraphicsComponent()
    :MessageSender(getObjectId()), MessageReceiver<ObjectType>(getObjectId(), true)
{
}

relic::GraphicsComponent::~GraphicsComponent()
{
    sendMessage({ GraphicsSystemType::hide_graphic, std::make_any<framework::Graphic*>(&getGraphic()) });
}

void relic::GraphicsComponent::setClipPtr(const framework::Shape* clip)
{
    m_graphic_ptr->setClip(*clip);
}

void relic::GraphicsComponent::setGraphic(framework::Graphic* graphic_ptr)
{
    m_graphic_ptr = std::unique_ptr<framework::Graphic>(graphic_ptr);
}

void relic::GraphicsComponent::doUpdates()
{
    Component::doUpdates();
    handleMessages();
}

void relic::GraphicsComponent::handleMessage(Message<ObjectType> msg)
{
    switch (msg.type)
    {
    case ObjectType::move:
        const auto movement = std::any_cast<framework::Point>(msg.value);
        getGraphic().getShape().x += movement.x;
        getGraphic().getShape().y += movement.y;
    }
}

framework::Graphic& relic::GraphicsComponent::getGraphic() const
{
    return *m_graphic_ptr;
}
