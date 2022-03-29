#pragma once

#include <queue>

#include "GameObject.h"
#include "ObjectEvent.h"

namespace Jinny
{
    // Base class for components
    class Component
    {
    public:

        // constructor
        Component();

        // Should usually set game object here
        virtual void initialize(GameObject& object) = 0;

        // Updating
        virtual void update() = 0;

        // Closing
        virtual void close() = 0;

    protected:

        // Event Handling
        virtual void handleEvents() = 0;

        // Accessor for object
        void setObject(GameObject* object);
        GameObject* getObject();

    private:
        // Instance of game object
        GameObject* m_object;
    };
}


