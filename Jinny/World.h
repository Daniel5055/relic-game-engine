#pragma once

#include "Identifier.h"

namespace relic
{
    class World
    {
    public:
        // Constructor
        explicit World(std::string name);

        // Possibly add functionality into derived classes of world by adding virtual method?

        // Maybe world will store pointers to objects also?

    private:
        const Identifier m_id;

        static int m_next_id_num;

        // Static consts
        const static std::string k_object_id_type;
    };
}
