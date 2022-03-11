#pragma once

#include "Component.h"

#include "Shape.h"

namespace Framework
{
	class Graphic;
	struct Point;
}

namespace Jinny
{

	class GraphicsComponent;

	class AnimationComponent : public Component
	{

	public:
		// Constructor
		AnimationComponent(GraphicsComponent* graphics_component, int texture_width, int texture_height);

		// --- pure virtual functions ---

			// Initialization
		virtual void initialize(GameObject& object);

		// Updating
		virtual void update();

		// Closing
		virtual void close();

		// --- functions ---
		
	protected:
		// --- Inherited functions ---
		void createClipGrid();

		// Get current clip
		void changeCurrentClip(int index);

		// Get Texture sixe
		int getTextureWidth() const;
		int getTextureHeight() const;

	private:

		// Event Handling
		virtual void handleEvents();


		int m_tick;
		int m_tick_per_frame;


		Framework::Shape* m_current_clip_ptr;

		std::vector<Framework::Shape*> m_clips;

		int m_clip_start;
		int m_clip_end;
		int m_clip_index;

		// Graphics Related
		GraphicsComponent* m_graphics_component;

		int m_texture_width;
		int m_texture_height;

	};
}
