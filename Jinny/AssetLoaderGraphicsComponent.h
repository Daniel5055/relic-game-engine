#pragma once

#include <map>
#include <string>
#include <utility>

#include "Component.h"
#include "MessageReceiver.h"
#include "MessageSender.h"
#include "GraphicsType.h"

namespace relic
{
    /**
     * \brief Takes all assets and passes them to game system to be assigned
     */
    class AssetLoaderGraphicsComponent final
        : public Component
        , public MessageSender<GraphicsSystemType>
    {
    public:
        // Constructor
        explicit AssetLoaderGraphicsComponent(std::map<std::string, std::pair<std::string, unsigned int>> asset_paths = {});

    private:

        // Map of assets to be loaded
        std::map<std::string, std::pair<std::string, unsigned int>> m_asset_paths;
    };
}
