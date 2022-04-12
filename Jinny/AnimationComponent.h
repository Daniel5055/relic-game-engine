#pragma once

#include <vector>

#include "Component.h"

#include "Shape.h"

#include "MessageReceiver.h"
#include "MessageSender.h"

#include "GraphicsType.h"

namespace framework
{
    class Graphic;
    struct Point;
}

namespace relic
{

    class GraphicsComponent;

    //TODO: will repair later

    class AnimationComponent : public Component
        , MessageSender<GraphicsObjectType>
        , MessageReceiver<GraphicsObjectType>

    {

    public:
        // Constructor
        AnimationComponent(int texture_width, int texture_height, int tpf, int start, int end, const Identifier& graphics_component_id = Identifier::null);

    protected:
        // --- Inherited functions ---
        void createClipGrid();

        void doUpdates() override;

        // Get current clip
        void changeCurrentClip(int index);

        // Get Texture size
        int getTextureWidth() const;
        int getTextureHeight() const;

    private:
        // virtual overrides
        void handleMessage(const Message<GraphicsObjectType>& msg) override;

        int m_tick{0};
        int m_tick_per_frame;

        framework::Shape m_current_clip;

        std::vector<framework::Shape> m_clips;

        int m_clip_start{0};
        int m_clip_end{0};
        int m_clip_index{0};

        const int m_texture_width;
        const int m_texture_height;
    };
}

