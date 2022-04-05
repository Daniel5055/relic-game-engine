#pragma once

#include <map>
#include <string>

// Framework dependencies
namespace framework
{
    class Texture;
    class Font;
}


namespace relic
{
    class AssetManager
    {
    public:

        // Adds texture or font to assets
        void addTexture(std::string name, framework::Texture* texture_ptr);
        void addFont(std::string name, framework::Font* font_ptr);

        // Return reference to font or texture
        framework::Texture* getTexture(std::string name);
        framework::Font* getFont(std::string name);
    private:

        // Map to store assets by name 
        std::map<std::string, framework::Texture*> m_textures;
        std::map<std::string, framework::Font*> m_fonts;
    };
}
