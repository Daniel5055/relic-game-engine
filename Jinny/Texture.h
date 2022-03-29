#pragma once

// SDL Dependencies
struct SDL_Texture;
struct SDL_Point;

namespace Framework
{

    // Just encapsulates texture;
    class Texture
    {
    public:
        // Friend to Graphics as it handles all texture related to stuff
        friend class Graphics;
        // Constructor and Destructor to initialize and free SDL_Texture
        Texture();
        ~Texture();



        SDL_Point getSize();
        int getWidth();
        int getHeight();

    private:
        // --- Functions for Graphics Framework to use ---

        // Accessing Texture
        void setTexture(SDL_Texture* texture_ptr);
        SDL_Texture* getTexture();

        // --- Data ---

        // SDL texture
        SDL_Texture* m_texture_ptr;

        // Texture size (So I don't have to ask later)
        int m_width;
        int m_height;
    };

}

