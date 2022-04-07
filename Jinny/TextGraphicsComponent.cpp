#include "TextGraphicsComponent.h"

relic::TextGraphicsComponent::TextGraphicsComponent(framework::Shape shape, const std::string& text, const std::string&
                                                    font_name, framework::Colour font_colour, const std::string& font_path, int font_size)
{
    // Create Graphic
    setGraphic(new framework::Graphic(shape));

    GraphicsMessage msg;

    if (!font_path.empty())
    {
        msg.type = GMessageType::load_font;
        msg.string_1 = font_name;
        msg.string_2 = font_path;
        msg.num = font_size;
        sendMessage(msg);
    }

    msg = GraphicsMessage();
    msg.type = GMessageType::assign_text;
    msg.string_1 = text;
    msg.string_2 = font_name;
    msg.color = font_colour;
    msg.graphic = &getGraphic();
    sendMessage(msg);

    msg = GraphicsMessage();
    msg.type = GMessageType::show_graphic;
    msg.object_id = getObjectId();
    msg.graphic = &getGraphic();
    sendMessage(msg);
}

void relic::TextGraphicsComponent::handleEvent(ObjectEvent e)
{
    switch (e.type)
    {
    case ObjectEvent::Type::move:
        getGraphic().getShape().x += e.movement.x;
        getGraphic().getShape().y += e.movement.y;
    }
}
