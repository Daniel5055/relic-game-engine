#include "ImageGraphicsComponent.h"

relic::ImageGraphicsComponent::ImageGraphicsComponent(framework::Shape shape, const std::string& texture_name, const std::string& texture_path)
{
    // Create Graphic
    setGraphic(new framework::Graphic(shape));

    // If texture path not provided then send a message to load the from the path
    GraphicsMessage msg;

    if (!texture_path.empty())
    {
        msg.type = GMessageType::load_texture;
        msg.string_1 = texture_name;
        msg.string_2 = texture_path;
        sendMessage(msg);
    }

    // Then send a message to assign the texture to the graphic
    msg = GraphicsMessage();
    msg.type = GMessageType::assign_texture;
    msg.string_1 = texture_name;
    msg.graphic = &getGraphic();

    sendMessage(msg);

    // And meanwhile, draw the graphic using the graphics system
    msg = GraphicsMessage();
    msg.type = GMessageType::show_graphic;
    msg.object_id = getObjectId();
    msg.graphic = &getGraphic();
    sendMessage(msg);
}

void relic::ImageGraphicsComponent::handleEvent(const ObjectEvent e)
{
    switch (e.type)
    {
    case ObjectEvent::Type::move:
        getGraphic().getShape().x += e.movement.x;
        getGraphic().getShape().y += e.movement.y;
    }
}
