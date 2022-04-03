#pragma once

#include <string>

// SDL Dependencies
struct SDL_Renderer;

namespace framework
{
    // Other Dependencies
    class Graphic;
    class Texture;
    class Window;
    class Font;
    struct Color;
    struct Shape;

    /**
     * Framework class containing all function related to drawing to the window using SDL.
     */
    class Graphics
    {
    public:
        // Constructor
        explicit Graphics(const Window& window);

        virtual ~Graphics();

        // Rendering functions

        virtual void clear(Color clear_colour) const;
        virtual void draw(Graphic* graphic) const;
        virtual void draw(Graphic* graphic, int x_shift, int y_shift) const;
        virtual void display() const;


        // Creation of textures and font
        virtual Font* createFont(std::string path, int font_size) const;
        virtual Texture* createTexture(std::string path) const;
        virtual Texture* createTextTexture(std::string text, Font* font, Color color) const;
        virtual Texture* createWrappedTextTexture(std::string text, Font* font, Color color, Shape* shape) const;

        // Assigning of Textures
        virtual void assignTexture(Graphic* graphic, Texture* texture) const;

    private:

        // --- Data ---

        // Renderer using pointer due to SDL
        SDL_Renderer* m_renderer_ptr;
    };
}


