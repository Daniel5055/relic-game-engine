#pragma once

#include <string>

// SDL Dependencies
struct SDL_Renderer;

namespace Framework
{
	// Other Dependencies
	class Graphic;
	class Texture;
	class Window;
	class Font;
	struct Color;
	struct Shape;

	class Graphics
	{
	public:
		// Constructor
		Graphics();

		// Initialization and Closing
		virtual bool initialize(Window* window);
		virtual void close();

		// Rendering functions
		
		virtual void clear(Color clear_color);
		virtual void draw(Graphic* graphic);
		virtual void draw(Graphic* graphic, int x_shift, int y_shift);
		virtual void display();


		// Creation of textures and font
		virtual Font* createFont(std::string path, int font_size);
		virtual Texture* createTexture(std::string path);
		virtual Texture* createTextTexture(std::string text, Font* font, Color color);
		virtual Texture* createWrappedTextTexture(std::string text, Font* font, Color color, Shape* shape);

		// Assigning of Textures
		virtual void assignTexture(Graphic* graphic, Texture* texture);

	private:

		// --- Data ---

		// Renderer
		SDL_Renderer* m_renderer_ptr;
		
	};
}


