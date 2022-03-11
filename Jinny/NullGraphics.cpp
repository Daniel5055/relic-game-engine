#include "NullGraphics.h"

#include "Window.h"
#include "Color.h"
#include "Graphic.h"
#include "Font.h"

bool Framework::NullGraphics::initialize(Window* window)
{
	return false;
}

void Framework::NullGraphics::close()
{
}


void Framework::NullGraphics::clear(Color clear_color)
{
}


void Framework::NullGraphics::draw(Graphic* graphic)
{
}

void Framework::NullGraphics::display()
{
}

Framework::Font* Framework::NullGraphics::createFont(std::string path, int font_size)
{
	return nullptr;
}

Framework::Texture* Framework::NullGraphics::createTexture(std::string path)
{
	return nullptr;
}

Framework::Texture* Framework::NullGraphics::createTextTexture(std::string text, Font* font, Color color)
{
	return nullptr;
}
