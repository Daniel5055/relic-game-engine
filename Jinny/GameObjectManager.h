#pragma once

#include <memory>
#include <vector>

#include "World.h"
#include "GameObject.h"

namespace relic
{
    /*
     * \brief Creates and manages game objects
     */
    class GameObjectManager
    {
    public:
        // Update method to be called by Game
        void updateObjects();

        // Expected to be called by object within constructor and destructor
        GameObject& createObject(std::string name, bool is_global = false);
        void deleteObject(const Identifier& id);

        // Clear entire object list, size reset
        void clearSceneObjects();
        void clearGlobalObjects();
    private:
        // Store object pointers
        std::vector<std::unique_ptr<GameObject>> m_scene_objects{};
        std::vector<std::unique_ptr<GameObject>> m_global_objects{};
    };
}
