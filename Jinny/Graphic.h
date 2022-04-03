#pragma once
#include "Shape.h"

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

        Texture* m_texture_ptr{nullptr};
    };
}


