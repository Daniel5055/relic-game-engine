#pragma once

#include <map>
#include <string>
#include <utility>

#include "GraphicsComponent.h"

namespace relic
{
    /**
     * \brief Takes all assets and passes them to game system to be assigned
     */
    class AssetLoaderGraphicsComponent final :public GraphicsComponent
    {
    public:
        // Constructor
        explicit AssetLoaderGraphicsComponent(std::map<std::string, std::pair<std::string, unsigned int>> asset_paths = {});

        // For adding loading new textures (before initialisation)
        void loadTexture(const std::string& texture_name, const std::string& texture_path);
        void loadFont(const std::string& font_name, const std::string& font_path, unsigned int font_size);

    private:

        // Map of assets to be loaded
        std::map<std::string, std::pair<std::string, unsigned int>> m_asset_paths;
    };
}
