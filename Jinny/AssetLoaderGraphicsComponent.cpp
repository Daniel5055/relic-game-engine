#include "AssetLoaderGraphicsComponent.h"

relic::AssetLoaderGraphicsComponent::AssetLoaderGraphicsComponent(
	std::map<std::string, std::pair<std::string, unsigned int>> asset_paths)
	:MessageSender<GraphicsSystemType>(getId()), m_asset_paths(std::move(asset_paths))
{
	// Send Messages to graphics system to load assets
	for (auto it = m_asset_paths.begin(); it != m_asset_paths.end(); ++it)
	{
		Message<GraphicsSystemType> msg;
		// Set name and path of asset

		// Check type of asset
		if (it->second.second == 0)
		{
			// Then texture
			msg.type = GraphicsSystemType::load_texture;
			msg.value = std::make_any<std::pair<std::string, std::string>>(it->first, it->second.first);
		}
		else
		{
			// Then Font
			msg.type = GraphicsSystemType::load_font;
			msg.value = std::make_any<std::pair<std::string, std::pair<std::string, unsigned int>>>(it->first, it->second);
		}

		MessageSender<GraphicsSystemType>::sendImmediateMessage(msg);
	}
}
