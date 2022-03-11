#pragma once
#include "Graphics.h"



namespace Framework
{
	class Logger;

	class LoggedGraphics : public Graphics
	{
	public:

		// Logged Initialization
		bool initialize(Window* window) override;
		void close() override;


		// Logged creation of textures and font
		Font* createFont(std::string path, int font_size) override;
		Texture* createTexture(std::string path) override;
		Texture* createTextTexture(std::string text, Font* font, Color color);

	private:
		Logger* m_logger_ptr;
	};


}


