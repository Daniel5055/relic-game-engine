#include "Graphic.h"

#include "Texture.h"

framework::Graphic::Graphic(const Shape shape)
    :m_shape(shape)
{

}

framework::Shape& framework::Graphic::getShape()
{
    return m_shape;
}

void framework::Graphic::setShape(const Shape shape)
{
    m_shape = shape;
}

void framework::Graphic::setSize(const int w, const int h)
{
    m_shape.w = w;
    m_shape.h = h;
}

void framework::Graphic::setColour(const Colour colour)
{
    m_colour = colour;
}

framework::Colour framework::Graphic::getColour() const
{
    return m_colour;
}

const framework::Shape* framework::Graphic::getClip() const
{
    return m_clip;
}


void framework::Graphic::setClip(Shape* clip)
{
    m_clip = clip;
}

void framework::Graphic::setTexture(Texture* texture)
{
    m_texture_ptr = texture;
}

framework::Texture* framework::Graphic::getTexture() const
{
    return m_texture_ptr;
}
