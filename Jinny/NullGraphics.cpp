#include "NullGraphics.h"

#include "Window.h"
#include "Colour.h"
#include "Graphic.h"
#include "Font.h"

bool framework::NullGraphics::initialize(Window* window)
{
    return false;
}

void framework::NullGraphics::close()
{
}


void framework::NullGraphics::clear(Colour clear_color)
{
}


void framework::NullGraphics::draw(Graphic* graphic)
{
}

void framework::NullGraphics::display()
{
}

framework::Font* framework::NullGraphics::createFont(std::string path, int font_size)
{
    return nullptr;
}

framework::Texture* framework::NullGraphics::createTexture(std::string path)
{
    return nullptr;
}

framework::Texture* framework::NullGraphics::createTextTexture(std::string text, Font* font, Colour color)
{
    return nullptr;
}
