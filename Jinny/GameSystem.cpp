#include "GameSystem.h"

int relic::GameSystem::m_next_id_num = 1;
const std::string relic::GameSystem::k_id_type_name = "System";

relic::GameSystem::GameSystem(std::string&& system_name)
    :m_id(m_next_id_num, std::move(system_name), k_id_type_name)
{
    ++m_next_id_num;
}

const relic::Identifier& relic::GameSystem::getId() const
{
    return m_id;
}
