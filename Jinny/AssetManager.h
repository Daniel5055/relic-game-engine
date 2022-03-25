#pragma once

#include <map>
#include <string>

// Framework dependencies
namespace Framework
{
    class Texture;
    class Font;
}


namespace Jinny
{
    class AssetManager
    {
    public:

        // Adds texture or font to assets
        void addTexture(std::string name, Framework::Texture* texture_ptr);
        void addFont(std::string name, Framework::Font* font_ptr);

        // Return reference to font or texture
        Framework::Texture* getTexture(std::string name);
        Framework::Font* getFont(std::string name);
    private:

        // Map to store assets by name 
        std::map<std::string, Framework::Texture*> m_textures;
        std::map<std::string, Framework::Font*> m_fonts;
    };
}
