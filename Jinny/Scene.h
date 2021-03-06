#pragma once

#include <string>
#include <map>
#include <utility>

#include "GameObject.h"

namespace framework
{
    struct Shape;

}
namespace relic
{

    class Scene
    {
    public:
        // Virtual destructor
        virtual ~Scene() = default;

        void initialise();

        // For establishing ability to create objects
        static void setWindowSize(unsigned int width, unsigned int height);

        static void setObjectManager(GameObjectManager* object_manager);

    protected:

        // For setting scope of object creation (within scene or global)
        void setScope(bool is_global);

        // Accessing Window size
        static unsigned int getWindowWidth();
        static unsigned int getWindowHeight();


        // Functions for initialisation stuff
        void loadAssets(const std::map<std::string, std::pair<std::string, unsigned int>>& assets) const;

        void createCamera(framework::Shape camera) const;

        GameObject& createObject(std::string name, bool is_global = false) const;

    private:
        static unsigned m_window_width;
        static unsigned m_window_height;
        static GameObjectManager* m_object_manager;

        bool m_is_global_scope{ false };

        virtual void doInitialisation() = 0;
    };
}
