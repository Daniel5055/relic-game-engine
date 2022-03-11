#include "GameObject.h"

#include "NullGraphicsComponent.h"
#include "NullInputComponent.h"
#include "NullPhysicsComponent.h"
#include "NullCoreComponent.h"

#include "ObjectEvent.h"

#include "InputMessage.h"
#include "GraphicsMessage.h"
#include "PhysicsMessage.h"
#include "CoreMessage.h"



Jinny::GameObject::GameObject(std::string name, Framework::Shape shape, GraphicsComponent* graphics, InputComponent* input, PhysicsComponent* physics, CoreComponent* core)
    :m_name(name)
{
    // Shape Initializtion;
    m_shape = shape;
    shape.is_screen_bound = false;

    // Null ID, set later
    m_ID = -1;

    // Order of components best goes as: Input -> Physics -> Animation -> Graphic -> Audio
    if (input != nullptr)
    {
        m_input.push_back(input);
    }
    if (physics != nullptr)
    {
        m_physics.push_back(physics);
    }
    if (graphics != nullptr)
    {
        m_graphics.push_back(graphics);
    }
    if (core != nullptr)
    {
        m_core.push_back(core);
    }
}

void Jinny::GameObject::addGraphicsComponent(GraphicsComponent* g_component)
{
    m_graphics.push_back(g_component);
}

void Jinny::GameObject::addInputComponent(InputComponent* i_component)
{
    m_input.push_back(i_component);
}

void Jinny::GameObject::addPhysicsComponent(PhysicsComponent* p_component)
{
    m_physics.push_back(p_component);
}

void Jinny::GameObject::addCoreComponent(CoreComponent* c_component)
{
    m_core.push_back(c_component);
}

void Jinny::GameObject::addComponent(Component* component)
{
    m_components.push_back(component);
}

void Jinny::GameObject::initialize()
{
    m_event_queue.push_back({ EventType::OBJECT_INITIALIZATION_SHAPE, &m_shape });

    for (InputComponent* input : m_input)
    {
        input->initialize(*this);
    }
    for (PhysicsComponent* physics : m_physics)
    {
        physics->initialize(*this);
    }
    for (GraphicsComponent* graphics : m_graphics)
    {
        graphics->initialize(*this);
    }
    for (CoreComponent* core : m_core)
    {
        core->initialize(*this);
    }

    for (Component* component : m_components)
    {
        component->initialize(*this);
    }
}


void Jinny::GameObject::update()
{
    for (InputComponent* input : m_input)
    {
        input->update();
    }
    for (PhysicsComponent* physics : m_physics)
    {
        physics->update();
    }
    for (GraphicsComponent* graphics : m_graphics)
    {
        graphics->update();
    }
    for (CoreComponent* core : m_core)
    {
        core->update();
    }

    for (Component* component : m_components)
    {
        component->update();
    }

    // Clear Messages
    m_event_queue.clear();
}

void Jinny::GameObject::close()
{
    for (InputComponent* input : m_input)
    {
        input->close();
    }
    for (PhysicsComponent* physics : m_physics)
    {
        physics->close();
    }
    for (GraphicsComponent* graphics : m_graphics)
    {
        graphics->close();
    }
    for (CoreComponent* core : m_core)
    {
        core->close();
    }

    for (Component* component : m_components)
    {
        component->close();
    }
}

void Jinny::GameObject::recieveGraphicsMessage(GraphicsMessage g_msg)
{
    for (GraphicsComponent* graphics : m_graphics)
    {
        graphics->recieveMessage(g_msg);
    }
}

void Jinny::GameObject::recieveInputMessage(InputMessage i_msg)
{
    for (InputComponent* input : m_input)
    {
        input->recieveMessage(i_msg);
    }
}

void Jinny::GameObject::recievePhysicsMessage(PhysicsMessage p_msg)
{
    for (PhysicsComponent* physics : m_physics)
    {
        physics->recieveMessage(p_msg);
    }
}

Jinny::EventQueue::const_iterator Jinny::GameObject::getQueueIterator() const
{
    return m_event_queue.begin();
}

Jinny::EventQueue::const_iterator Jinny::GameObject::getQueueEnd() const
{
    return m_event_queue.end();
}

void Jinny::GameObject::pushEvent(const ObjectEvent& o_event)
{
    m_event_queue.push_back(o_event);
}

int Jinny::GameObject::getObjectID() const
{
    return m_ID;
}

void Jinny::GameObject::setObjectID(int ID)
{
    m_ID = ID;
}

const std::string Jinny::GameObject::getObjectName() const
{
    return m_name;
}

void Jinny::GameObject::toggleHUD()
{
    if (m_shape.is_screen_bound == false)
    {
        m_shape.is_screen_bound = true;
    }
    else
    {
        m_shape.is_screen_bound = false;
    }
}
