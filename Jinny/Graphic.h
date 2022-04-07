#pragma once
#include "Shape.h"
#include "Colour.h"

namespace framework
{
    class Texture;

    /**
     * \brief Contains all information related for drawing a texture
     */
    class Graphic
    {
    public:

        // Graphics is friend class to access variables personally
        friend class Graphics;

        // Constructor
        explicit Graphic(Shape shape);

        // Accessors
        Shape& getShape();
        void setShape(Shape shape);

        void setSize(int w, int h);

        void setColour(Colour colour);
        Colour getColour() const;

        const Shape& getClip() const;
        void setClip(Shape clip);

        Texture* getTexture() const;

    private:

        // --- Functions for Graphics ---

        // only accessible by graphics class
        void setTexture(Texture* texture);

        // --- Data --- 
        Shape m_shape;
        Shape m_clip;

        // Either a texture of a colour
        Texture* m_texture_ptr{nullptr};
        Colour m_colour;
    };
}


