#include "Identifier.h"

const relic::Identifier relic::Identifier::null_identifier = Identifier(0, "", "");

relic::Identifier::Identifier(const int id, std::string name, std::string type)
    : m_id(id), m_name(std::move(name)), m_type(std::move(type))
{

}

int relic::Identifier::getId() const
{
    return m_id;
}

std::string relic::Identifier::getName() const
{
    return m_name;
}

std::string relic::Identifier::getType() const
{
    return m_type;
}

bool relic::Identifier::operator==(const Identifier& id) const
{
    return this->m_name == id.m_name && this->m_id == id.m_id && this->m_type == id.m_type;
}

bool relic::Identifier::operator!=(const Identifier& id) const
{
    return !operator==(id);
}

bool relic::Identifier::operator<(const Identifier& id) const
{
    return this->m_id < id.m_id;
}
