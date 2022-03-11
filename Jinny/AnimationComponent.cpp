#include "AnimationComponent.h"

#include "GraphicsComponent.h"

#include "Point.h"
#include "Texture.h"

Jinny::AnimationComponent::AnimationComponent(GraphicsComponent* graphics_component, int texture_width, int texture_height)
	:m_graphics_component(graphics_component), m_texture_width(texture_width), m_texture_height(texture_height)
{
	// Pre - Initializing + additional inititalization
	m_graphics_component = graphics_component;
	m_current_clip_ptr = new Framework::Shape();

	graphics_component->setClipPtr(m_current_clip_ptr);

	m_tick = 0;
}

void Jinny::AnimationComponent::initialize(GameObject& object)
{
	// Initialize Objects
	setObject(&object);

	// Recieve Object shape
	for (auto it = object.getQueueIterator(); it != object.getQueueEnd(); it++)
	{
		switch (it->type)
		{
		case EventType::OBJECT_INITIALIZATION_SHAPE:
			m_current_clip_ptr->w = it->shape->w;
			m_current_clip_ptr->h = it->shape->h;
		}
	}
}

void Jinny::AnimationComponent::update()
{
	m_tick++;
	if (m_tick >= m_tick_per_frame)
	{
		m_tick = 0;

		m_clip_index++;
		if (m_clip_index >= m_clip_end)
		{
			m_clip_index = m_clip_start;
		}

		changeCurrentClip(m_clip_index);
	}


}

void Jinny::AnimationComponent::close()
{
	for (Framework::Shape* shape_ptr : m_clips)
	{
		delete shape_ptr;
	}
	m_clips.clear();

	delete m_current_clip_ptr;
	m_current_clip_ptr = nullptr;

}

void Jinny::AnimationComponent::createClipGrid()
{
	int width = m_current_clip_ptr->w;
	int height = m_current_clip_ptr->h;

	int w_max = m_texture_width / width;
	int h_max = m_texture_height / height;

	

	for (int y = 0; y < h_max; y++)
	{
		for (int x = 0; x < w_max; x++)
		{
			m_clips.push_back(new Framework::Shape(x * width, y * height, width, height));
		}
	}
}

void Jinny::AnimationComponent::changeCurrentClip(int index)
{
	// Changes location of current clip pointer based from clips
	m_current_clip_ptr->x = m_clips[index]->x;
	m_current_clip_ptr->y = m_clips[index]->y;
}

int Jinny::AnimationComponent::getTextureWidth() const
{
	return m_texture_width;
}

int Jinny::AnimationComponent::getTextureHeight() const
{
	return m_texture_height;
}

void Jinny::AnimationComponent::handleEvents()
{
}
