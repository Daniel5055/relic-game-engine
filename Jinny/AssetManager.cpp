#include "AssetManager.h"

// Framework Includes
#include "Texture.h"
#include "Font.h"

void relic::AssetManager::addTexture(std::string name, framework::Texture* texture_ptr)
{
    m_textures[name] = texture_ptr;
}

void relic::AssetManager::addFont(std::string name, framework::Font* font_ptr)
{
    m_fonts[name] = font_ptr;
}

framework::Texture* relic::AssetManager::getTexture(std::string name)
{
    if (m_textures.find(name) != m_textures.end())
    {
        return m_textures[name];
    }

    return nullptr;

}

framework::Font* relic::AssetManager::getFont(std::string name)
{
    if (m_fonts.find(name) != m_fonts.end())
    {
        return m_fonts[name];
    }

    return nullptr;
}

