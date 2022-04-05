#include "AssetLoaderGraphicsComponent.h"

relic::AssetLoaderGraphicsComponent::AssetLoaderGraphicsComponent(
	std::map<std::string, std::pair<std::string, unsigned int>> asset_paths)
	:m_asset_paths(std::move(asset_paths))
{
	// Send Messages to graphics system to load assets
	for (auto it = m_asset_paths.begin(); it != m_asset_paths.end(); ++it)
	{
		GraphicsMessage msg;
		// Set name and path of asset
		msg.string_1 = it->first;
		msg.string_2 = it->second.first;

		// Check type of asset
		if (it->second.second == 0)
		{
			// Then texture
			msg.type = GMessageType::load_texture;
		}
		else
		{
			// Then Font
			msg.type = GMessageType::load_font;
			msg.num = static_cast<int>(it->second.second);
		}

		sendMessage(msg);
	}
}

void relic::AssetLoaderGraphicsComponent::loadFont(const std::string& font_name, const std::string& font_path, unsigned int font_size)
{
	m_asset_paths[font_name] = { font_path, font_size };
}

void relic::AssetLoaderGraphicsComponent::loadTexture(const std::string& texture_name, const std::string& texture_path)
{
	m_asset_paths[texture_name] = { texture_path, 0 };
}