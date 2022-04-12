#include "GraphicsComponent.h"

#include "Point.h"

relic::GraphicsComponent::GraphicsComponent()
    : MessageSender<GraphicsSystemType>(getId())
    , MessageReceiver<ObjectType>(getId(), true)
    , MessageReceiver<GraphicsObjectType>(getId(), true)
    , MessageSender<GraphicsObjectType>(getId(), true)
{
}

relic::GraphicsComponent::~GraphicsComponent()
{
    MessageSender<GraphicsSystemType>::sendImmediateMessage({ GraphicsSystemType::hide_graphic, std::make_any<framework::Graphic*>(&getGraphic()) });
}

void relic::GraphicsComponent::setGraphic(framework::Graphic* graphic_ptr)
{
    m_graphic_ptr = std::unique_ptr<framework::Graphic>(graphic_ptr);
}

void relic::GraphicsComponent::doUpdates()
{
    Component::doUpdates();
    MessageReceiver<ObjectType>::handleMessages();
    MessageReceiver<GraphicsObjectType>::handleMessages();
}

void relic::GraphicsComponent::handleMessage(const relic::Message<ObjectType>& msg)
{
    switch (msg.type)
    {
    case ObjectType::move:
        const auto movement = std::any_cast<framework::Point>(msg.value);
        getGraphic().getShape().x += movement.x;
        getGraphic().getShape().y += movement.y;
    }
}

void relic::GraphicsComponent::handleMessage(const Message<GraphicsObjectType>& msg)
{
    switch (msg.type)
    {
    case GraphicsObjectType::query_graphic:
        // Checking that the query is relevant
        if (msg.to.getSubId() == getId().getSubId() || msg.to.getSubId() == 0)
        {
            Message m{ GraphicsObjectType::sent_graphic, std::make_any<framework::Graphic*>(&getGraphic()) };
            m.to = msg.from;
            MessageSender<GraphicsObjectType>::sendImmediateMessage(m);
        }
    }
}

framework::Graphic& relic::GraphicsComponent::getGraphic() const
{
    return *m_graphic_ptr;
}
