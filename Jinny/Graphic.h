#pragma once

namespace Framework
{
	struct Shape;
	struct Point;

	class Texture;

	class Graphic
	{
	public:

		// Graphics is friend class to access variables personally
		friend class Graphics;

		// Constructors
		Graphic(Shape* shape_ptr = nullptr);

		//
		Shape* getShape();
		void setShape(Shape* shape);

		void setSize(int w, int h);


		Shape* getClip();
		void setClip(Shape* clip);


		Texture* getTexture();

	private:
		
		// --- Functions for Graphics

		void setTexture(Texture* texture);


		// --- Data --- 
		Shape* m_shape_ptr;
		Shape* m_clip_ptr;

		Texture* m_texture_ptr;


	};
}


