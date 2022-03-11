#pragma once

#include <string>
#include <vector>

// Framework Dependencies
#include "Shape.h"
#include "ObjectEvent.h"

namespace Jinny
{
	// Components
	class Component;
	class CoreComponent;
	class GraphicsComponent;
	class InputComponent;
	class PhysicsComponent;

	// Event Container
	typedef std::vector<ObjectEvent> EventQueue;
	typedef std::vector<Component*> ComponentList;

	// Message based
	struct GraphicsMessage;
	struct InputMessage;
	struct PhysicsMessage;

	// Base Class for any game object
	class GameObject
	{
	public:
		// Constructor
		GameObject(std::string name, Framework::Shape shape,
			GraphicsComponent* graphics = nullptr,
			InputComponent* input = nullptr,
			PhysicsComponent* physics = nullptr,
			CoreComponent* core = nullptr);

		// Add Components
		void addGraphicsComponent(GraphicsComponent* g_component);
		void addInputComponent(InputComponent* i_component);
		void addPhysicsComponent(PhysicsComponent* p_component);
		void addCoreComponent(CoreComponent* c_component);

		void addComponent(Component* component);

		// Initialization
		void initialize();

		// Update
		void update();

		// Close
		void close();

		// Recieving messages
		void recieveGraphicsMessage(GraphicsMessage g_msg);
		void recieveInputMessage(InputMessage i_msg);
		void recievePhysicsMessage(PhysicsMessage p_msg);


		// --- Component Functions ---
		// So Components get the iterator and go through until queue end

		// For Event handling
		EventQueue::const_iterator getQueueIterator() const;

		// Gets Queue end in instance
		EventQueue::const_iterator getQueueEnd() const;

		// Push Event 
		void pushEvent(const ObjectEvent& o_event);

		// Get ID
		int getObjectID() const;
		void setObjectID(int ID);

		// Get name
		const std::string getObjectName() const;

		// Toggles whether object is A HUD object or not
		void toggleHUD();

	private:
		// --- Data ---

		// Identification
		const std::string m_name;
		int m_ID;

		// Core Data
		Framework::Shape m_shape;

		// Event Queue of object
		EventQueue m_event_queue;

		// System Components (Components connected to systems)
		std::vector<GraphicsComponent*> m_graphics;
		std::vector<InputComponent*> m_input;
		std::vector<PhysicsComponent*> m_physics;
		std::vector<CoreComponent*> m_core;

		// Other Components, which do not have system messaging features
		ComponentList m_components;
	};
}


