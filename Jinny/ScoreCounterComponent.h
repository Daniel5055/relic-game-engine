#pragma once

#include "TextGraphicsComponent.h"
#include "MessageReceiver.h"
#include "PongType.h"

namespace relic::pong
{
    class ScoreCounterComponent
        : public TextGraphicsComponent
        , public MessageReceiver<PongType>
    {
    public:
        ScoreCounterComponent(framework::Shape shape, std::string font, framework::Colour colour);

    protected:
        void doUpdates() override;

    private:
        void handleMessage(const Message<PongType>& msg) override;

        int m_left_score{ 0 };
        int m_right_score{ 0 };

        const std::string m_font;
        const framework::Colour m_colour;
    };
}
