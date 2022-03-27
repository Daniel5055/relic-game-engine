#pragma once

#include <string>

namespace Jinny
{
    class GameSystem
    {

    public:
        //ctor / dtor
        GameSystem();
        ~GameSystem();

        // Main Public Functions
        virtual void init();
        virtual void update() = 0;
        virtual void close();


    protected:
        // Accessors
    private:


    };
}


