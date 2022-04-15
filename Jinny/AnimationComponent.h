#pragma once

#include <vector>

#include "Component.h"

#include "Shape.h"

#include "MessageReceiver.h"
#include "MessageSender.h"

#include "GraphicsType.h"

namespace relic
{
    //TODO: will repair later

    class AnimationComponent : public Component
        , MessageSender<GraphicsObjectType>
        , MessageReceiver<GraphicsObjectType>

    {

    public:
        // Constructor
        explicit AnimationComponent(unsigned int texture_width, unsigned int texture_height, bool auto_create_clip = true, const Identifier& graphics_component_id = Identifier::any);

    protected:
        // --- Inherited functions ---

        // Automatically splits the texture into a grid
        void createClipGrid(unsigned int texture_width, unsigned int texture_height);

        // overriding virtual update method
        void doUpdates() override;

        // Get current clip
        void changeCurrentClip(unsigned int index);

        // virtual overrides
        void handleMessage(const Message<GraphicsObjectType>& msg) override;

    private:

        framework::Shape m_current_clip;
        std::vector<framework::Shape> m_clips;

        bool m_auto_clip;

        const unsigned int m_texture_width;
        const unsigned int m_texture_height;
    };
}

