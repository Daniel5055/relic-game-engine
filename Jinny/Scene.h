#pragma once

#include <string>
#include <map>
#include <utility>

#include "GameObjectManager.h"
#include "GameObject.h"

namespace Framework
{
	struct Shape;

}
namespace Jinny
{

	class Scene
	{
	public:
		// Constrcutor
		Scene();

		// Initializing all the objects etc.
		virtual void initialize() = 0;

		// For establishing ability to create objects
		static void setObjectManager(GameObjectManager* object_manager);
		static void setWindowSize(unsigned int width, unsigned int height);
	protected:

		// For setting scope of object creation (within scene or global)
		void setScope(bool is_global);

		// For creating new objects yourself in some scene
		void addWorldObject(GameObject* object);
		void addHUDObject(GameObject* object);

		// Accessing Window size
		unsigned int getWindowWidth() const;
		unsigned int getWindowHeight() const;

		// Functions for preinitialization stuff
		void loadAssets(std::map<std::string, std::pair<std::string, unsigned int>> assets);

		// Functions to create general objects
		GameObject* createButtonSkeleton(std::string name, Framework::Shape shape, std::string texture_name);
		GameObject* createCamera(Framework::Shape camera_boundaries);
		
	private:
		static GameObjectManager* m_object_manager;

		static unsigned m_window_width;
		static unsigned m_window_height;

		bool m_is_global_scope;
	};
}
