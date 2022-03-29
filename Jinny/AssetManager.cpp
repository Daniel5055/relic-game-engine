#include "AssetManager.h"

// Framework Includes
#include "Texture.h"
#include "Font.h"

void Jinny::AssetManager::addTexture(std::string name, Framework::Texture* texture_ptr)
{
    m_textures[name] = texture_ptr;
}

void Jinny::AssetManager::addFont(std::string name, Framework::Font* font_ptr)
{
    m_fonts[name] = font_ptr;
}

Framework::Texture* Jinny::AssetManager::getTexture(std::string name)
{
    if (m_textures.find(name) != m_textures.end())
    {
        return m_textures[name];
    }

    return nullptr;

}

Framework::Font* Jinny::AssetManager::getFont(std::string name)
{
    if (m_fonts.find(name) != m_fonts.end())
    {
        return m_fonts[name];
    }

    return nullptr;
}

