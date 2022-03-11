#pragma once

#include <map>
#include <string>
#include <utility>

#include "GraphicsComponent.h"

namespace Jinny
{
	// This Graphics Component soley takes in any assets given, and sends them to the
	// Graphics System to load upon initialization
	class AssetLoaderGraphicsComponent :public GraphicsComponent
	{
	public:
		// Constructor
		AssetLoaderGraphicsComponent(const std::map<std::string, std::pair<std::string, unsigned int>>& asset_paths = {});

		// Initialization
		void initialize(GameObject& object);

		// For adding loading new textures (before initialization)
		void loadTexture(std::string texture_name, std::string texture_path);
		void loadFont(std::string font_name, std::string font_path, unsigned int font_size);

	private:

		// Map of assetss to be loaded
		std::map<std::string, std::pair<std::string, unsigned int>> m_asset_paths;
	};
}