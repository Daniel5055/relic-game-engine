
#include "SolidColourGraphicsComponent.h"

relic::SolidColourGraphicsComponent::SolidColourGraphicsComponent(const framework::Shape shape, const framework::Colour colour)
{
    // Create Graphic
    setGraphic(new framework::Graphic(shape));
    getGraphic().setColour(colour);

    // If texture path not provided then send a message to load the from the path
    const Message msg{ GraphicsSystemType::show_graphic, std::make_any<framework::Graphic*>(&getGraphic()) };
    sendMessage(msg);
}
