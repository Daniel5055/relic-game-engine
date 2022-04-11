#pragma once

#include "Identifier.h"

namespace relic
{
    /**
     * \brief Base class for all game systems
     */
    class GameSystem
    {
    public:
        virtual ~GameSystem() = default;

        // Update method is the only required method for GameSystem
        void update()
        {
            doUpdates();
        }
    protected:
        explicit GameSystem(std::string&& system_name);

        const Identifier& getId() const;
    private:
        // Encapsulating virtual methods
        virtual void doUpdates() = 0;

        // Id
        Identifier m_id;

        static int m_next_id_num;
        const static std::string k_id_type_name;
    };
}

