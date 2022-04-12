#include "ScoreCounterComponent.h"

relic::pong::ScoreCounterComponent::ScoreCounterComponent(const framework::Shape shape, std::string font, const framework::Colour colour)
    :TextGraphicsComponent(shape, "0 - 0", font, colour), MessageReceiver<PongType>(getId()), m_font(
         std::move(font)), m_colour(colour)
{
}

void relic::pong::ScoreCounterComponent::doUpdates()
{
    TextGraphicsComponent::doUpdates();
    MessageReceiver<PongType>::handleMessages();
}

void relic::pong::ScoreCounterComponent::handleMessage(const relic::Message<PongType>& msg)
{
    if (msg.type == PongType::left_win || msg.type == PongType::right_win)
    {
        if (msg.type == PongType::left_win)
        {
            ++m_left_score;
        }
        else
        {
            ++m_right_score;
        }

        Message m { GraphicsSystemType::assign_text };
        m.value = std::make_any<std::pair<std::pair<std::string, std::string>, std::pair<framework::Colour, framework::Graphic*>>>
            (std::pair<std::string, std::string>(std::to_string(m_left_score) + " - " + std::to_string(m_right_score), m_font),
                std::pair<framework::Colour, framework::Graphic*>(m_colour, &getGraphic()));
        MessageSender<GraphicsSystemType>::sendMessage(m);
    }
}
