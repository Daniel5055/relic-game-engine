#include "ButtonAnimationComponent.h"

/*
relic::ButtonAnimationComponent::ButtonAnimationComponent(GraphicsComponent* graphics_component, int texture_width, int texture_height)
    :AnimationComponent(graphics_component, texture_width, texture_height)
{

}

void relic::ButtonAnimationComponent::initialize(GameObject& object)
{
    AnimationComponent::initialize(object);

    // Button Order Goes
    // 0 -> normal
    // 1 -> over
    // 2 -> push

    createClipGrid();

}

void relic::ButtonAnimationComponent::update()
{
    handleEvents();
}

void relic::ButtonAnimationComponent::close()
{
    AnimationComponent::close();
}

void relic::ButtonAnimationComponent::handleEvents()
{
    for (auto it = getObject()->getQueueIterator(); it != getObject()->getQueueEnd(); it++)
    {
        switch (it->type)
        {
        case EventType::input_triggered:

            // Check for mouse input
            switch (it->input.type)
            {
            case ObjectInputType::mouse_over:
                changeCurrentClip(1);
                break;

            case ObjectInputType::mouse_off:
                changeCurrentClip(0);
                break;

            case ObjectInputType::left_mouse_down:
                changeCurrentClip(2);
                break;

            case ObjectInputType::left_mouse_up:
                changeCurrentClip(1);
                break;
            }
        }
    }
}
*/
