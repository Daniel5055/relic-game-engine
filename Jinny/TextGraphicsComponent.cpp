#include "TextGraphicsComponent.h"

relic::TextGraphicsComponent::TextGraphicsComponent(const framework::Shape shape, const std::string& text, const std::string&
    font_name, framework::Colour font_colour, const std::string& font_path, unsigned int font_size)
{
    // Create Graphic
    setGraphic(new framework::Graphic(shape));

    Message<GraphicsSystemType> msg;

    if (!font_path.empty())
    {
        msg.type = GraphicsSystemType::load_font;
        msg.value = std::make_any<std::pair<std::string, std::pair<std::string, unsigned int>>>(font_name, std::pair<std::string, unsigned int>(font_path, font_size));
        sendMessage(msg);
    }

    msg.type = GraphicsSystemType::assign_text;
    msg.value = std::make_any<std::pair<std::pair<std::string, std::string>, std::pair<framework::Colour, framework::Graphic*>>>
        (std::pair<std::string, std::string>(text, font_name), std::pair<framework::Colour, framework::Graphic*>(font_colour, &getGraphic()));
    sendMessage(msg);

    msg.type = GraphicsSystemType::show_graphic;
    msg.value = std::make_any<framework::Graphic*>(&getGraphic());
    sendMessage(msg);
}
