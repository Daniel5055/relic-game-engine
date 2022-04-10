#include "ImageGraphicsComponent.h"

relic::ImageGraphicsComponent::ImageGraphicsComponent(const framework::Shape shape, const std::string& texture_name, const std::string& texture_path)
{
    // Create Graphic
    setGraphic(new framework::Graphic(shape));

    // If texture path not provided then send a message to load the from the path
    Message <GraphicsSystemType> msg;

    if (!texture_path.empty())
    {
        msg.type = GraphicsSystemType::load_texture;
        msg.value = std::make_any<std::pair<std::string, std::string>>(texture_name, texture_path);
        sendMessage(msg);
    }

    // Then send a message to assign the texture to the graphic
    msg.type = GraphicsSystemType::assign_texture;
    msg.value = std::make_any<std::pair<std::string, framework::Graphic*>>(texture_name, &getGraphic());
    sendMessage(msg);

    // And meanwhile, draw the graphic using the graphics system
    msg.type = GraphicsSystemType::show_graphic;
    msg.value = std::make_any<framework::Graphic*>(&getGraphic());
    sendMessage(msg);
}
