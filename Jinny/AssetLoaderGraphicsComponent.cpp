#include "AssetLoaderGraphicsComponent.h"

Jinny::AssetLoaderGraphicsComponent::AssetLoaderGraphicsComponent(const std::map<std::string, std::pair<std::string, unsigned int>>& asset_paths)
{
	m_asset_paths = std::map<std::string, std::pair<std::string, unsigned int>>(asset_paths);
}

void Jinny::AssetLoaderGraphicsComponent::initialize(GameObject& object)
{
	GraphicsMessage g_msg;

	// Send Messages to graphics system to load assets
	for (auto it = m_asset_paths.begin(); it != m_asset_paths.end(); it++)
	{
		// Set name and path of asset
		g_msg.string_1 = it->first;
		g_msg.string_2 = it->second.first;

		// Check type of asset
		if (it->second.second == 0)
		{
			// Then texture
			g_msg.type = GMessageType::LOAD_TEXTURE;
		}
		else
		{
			// Then Font
			g_msg.type = GMessageType::LOAD_FONT;
			g_msg.num = it->second.second;
		}

		pushMessage(g_msg);
	}
}

void Jinny::AssetLoaderGraphicsComponent::loadFont(std::string font_name, std::string font_path, unsigned int font_size)
{
	m_asset_paths[font_name] = { font_path, font_size };
}

void Jinny::AssetLoaderGraphicsComponent::loadTexture(std::string texture_name, std::string texture_path)
{
	m_asset_paths[texture_name] = { texture_path, 0 };
}

