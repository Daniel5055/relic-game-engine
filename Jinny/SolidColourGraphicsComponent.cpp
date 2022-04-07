
#include "SolidColourGraphicsComponent.h"

relic::SolidColourGraphicsComponent::SolidColourGraphicsComponent(framework::Shape shape, framework::Colour colour)
{
    // Create Graphic
    setGraphic(new framework::Graphic(shape));
    getGraphic().setColour(colour);

    // If texture path not provided then send a message to load the from the path
    GraphicsMessage msg;

    msg.type = GMessageType::show_graphic;
    msg.object_id = getObjectId();
    msg.graphic = &getGraphic();
    sendMessage(msg);
}

void relic::SolidColourGraphicsComponent::handleEvent(const ObjectEvent e)
{
    switch (e.type)
    {
    case ObjectEvent::Type::move:
        getGraphic().getShape().x += e.movement.x;
        getGraphic().getShape().y += e.movement.y;
    }

}
