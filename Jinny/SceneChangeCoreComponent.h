#pragma once

#include "Component.h"
#include "ObjectInput.h"
#include "GameType.h"
#include "MessageReceiver.h"
#include "MessageSender.h"
#include "ObjectType.h"

namespace relic
{
    class Scene;

    /**
     * \brief Component that sends a message to the game to change scene given an input passed to object
     */
    class SceneChangeCoreComponent final
        : public Component
        , public MessageReceiver<ObjectType>
        , public MessageSender<GameSystemType>
    {
    public:

        // Constructor
        SceneChangeCoreComponent(ObjectInput trigger_input, Scene* new_scene);
    private:
        void handleMessage(Message<ObjectType> msg) override;

        // --- Data ---

        // Scene to change to
        Scene* m_next_scene;

        // Input that causes scene change
        const ObjectInput m_trigger_input;

    };
}