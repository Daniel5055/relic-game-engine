#include "Graphic.h"

#include "Shape.h"
#include "Texture.h"
#include "Point.h"

Framework::Graphic::Graphic(Shape* shape_ptr)
{
    m_shape_ptr = shape_ptr;
    m_clip_ptr = nullptr;
    m_texture_ptr = nullptr;
}

Framework::Shape* Framework::Graphic::getShape()
{
    return m_shape_ptr;
}

void Framework::Graphic::setShape(Shape* shape)
{
    m_shape_ptr = shape;
}

void Framework::Graphic::setSize(int w, int h)
{
    m_shape_ptr->w = w;
    m_shape_ptr->h = h;
}

Framework::Shape* Framework::Graphic::getClip()
{
    return m_clip_ptr;
}

void Framework::Graphic::setClip(Shape* clip)
{
    m_clip_ptr = clip;
}

void Framework::Graphic::setTexture(Texture* texture)
{
    m_texture_ptr = texture;
}

Framework::Texture* Framework::Graphic::getTexture()
{
    return m_texture_ptr;
}