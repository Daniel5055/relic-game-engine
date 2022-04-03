#pragma once

namespace jinny
{
    class GameSystem
    {

    public:
        virtual ~GameSystem() = default;

        // Update method is the only required method for GameSystem
        void update()
        {
            doUpdates();
        };

    private:
        // Encapsulating virtual methods
        virtual void doUpdates() = 0;
    };
}


