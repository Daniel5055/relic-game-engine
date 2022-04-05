#pragma once

#include "CoreComponent.h"
#include "ObjectInput.h"

namespace relic
{
    class Scene;

    /**
     * \brief Component that sends a message to the game to change scene given an input passed to object
     */
    class SceneChangeCoreComponent final : public CoreComponent
    {
    public:

        // Constructor
        SceneChangeCoreComponent(ObjectInput trigger_input, Scene* new_scene);

    private:

        // Event handling
        void handleEvent(ObjectEvent e) override;

        // --- Data ---

        // Scene to change to
        Scene* m_next_scene;

        // Input that causes scene change
        const ObjectInput m_trigger_input;

    };
}