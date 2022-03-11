#pragma once

#include <map>

#include "GameObject.h"

// Predefine State class
class State;

namespace Jinny
{
	class GameObjectManager
	{
	public:
		// Constructor
		GameObjectManager();

		// For updates
		void updateObjects();

		// For Adding and Getting objects
		// A Global object remains after scene clear
		void addGlobalWorldObject(GameObject* obj);
		void addSceneWorldObject(GameObject* obj);

		void addGlobalHUDObject(GameObject* obj);
		void addSceneHUDObject(GameObject* obj);


		int nextID() const;

		GameObject* getObject(int ID);

		// Deletion
		void deleteObject(int ID);

		// Clear entire object list, size reset
		void clearSceneObjects();
		void clearGlobalObjects();

	private:
		std::map<int, GameObject*> m_scene_object_ptrs;
		std::map<int, GameObject*> m_global_object_ptrs;

		int m_next_index;
	};
}
