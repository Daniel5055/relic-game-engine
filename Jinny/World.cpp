#include "World.h"

#include <utility>

int relic::World::m_next_id_num = 1;
const std::string relic::World::k_object_id_type = "World";

relic::World::World(std::string name)
    :m_id(m_next_id_num, std::move(name), k_object_id_type)
{
    m_next_id_num++;
}
