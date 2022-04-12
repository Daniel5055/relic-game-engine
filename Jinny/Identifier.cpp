#include "Identifier.h"

const relic::Identifier relic::Identifier::null = Identifier(0, "", "");

relic::Identifier::Identifier(const int id, std::string name, std::string type, const int sub_id)
    : m_id(id), m_name(std::move(name)), m_type(std::move(type)), m_sub_id(sub_id)
{

}

relic::Identifier::Identifier(const Identifier& id, const int sub_id)
    :m_id(id.m_id), m_name(id.m_name), m_type(id.m_type), m_sub_id(sub_id)
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

void relic::Identifier::setSubId(const int id)
{
    m_sub_id = id;
}

int relic::Identifier::getSubId() const
{
    return m_sub_id;
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
