#include "ButtonAnimationComponent.h"

Jinny::ButtonAnimationComponent::ButtonAnimationComponent(GraphicsComponent* graphics_component, int texture_width, int texture_height)
    :AnimationComponent(graphics_component, texture_width, texture_height)
{

}

void Jinny::ButtonAnimationComponent::initialize(GameObject& object)
{
    AnimationComponent::initialize(object);

    // Button Order Goes
    // 0 -> normal
    // 1 -> over
    // 2 -> push

    createClipGrid();

}

void Jinny::ButtonAnimationComponent::update()
{
    handleEvents();
}

void Jinny::ButtonAnimationComponent::close()
{
    AnimationComponent::close();
}

void Jinny::ButtonAnimationComponent::handleEvents()
{
    for (auto it = getObject()->getQueueIterator(); it != getObject()->getQueueEnd(); it++)
    {
        switch (it->type)
        {
        case EventType::INPUT_TRIGGERED:

            // Check for mouse input
            switch (it->input.type)
            {
            case ObjectInputType::MOUSE_OVER:
                changeCurrentClip(1);
                break;

            case ObjectInputType::MOUSE_OFF:
                changeCurrentClip(0);
                break;

            case ObjectInputType::LEFT_MOUSE_DOWN:
                changeCurrentClip(2);
                break;

            case ObjectInputType::LEFT_MOUSE_UP:
                changeCurrentClip(1);
                break;
            }
        }
    }
}
