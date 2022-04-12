#pragma once

namespace relic
{
    enum class GraphicsSystemType
    {
        load_texture,
        load_font,
        assign_texture,
        assign_text,

        show_graphic,
        hide_graphic,
    };

    enum class GraphicsObjectType
    {
        query_graphic,
        sent_graphic,
        
    };
}
