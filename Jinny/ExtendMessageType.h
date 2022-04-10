#pragma once

namespace relic
{
    /**
     * \brief A template class used to create enum extension, used from https://www.codeproject.com/Articles/16150/Inheriting-a-C-enum-type
     * \tparam EnumT The derived enum
     * \tparam BaseEnumT The base enum
     */
    template <typename EnumT, typename BaseEnumT>
    class ExtendMessageType
    {
    public:
        ExtendMessageType() {}
        ExtendMessageType(EnumT e)
            : m_enum(e)
        {}

        ExtendMessageType(BaseEnumT e)
            : m_base_enum(e)
        {}

        explicit ExtendMessageType(int val)
            : m_enum(static_cast<EnumT>(val))
        {}

        operator EnumT() const { return m_enum; }
    private:
        // Note - the value is declared as a union mainly for as a debugging aid. If 
        // the union is undesired and you have other methods of debugging, change it
        // to either of EnumT and do a cast for the constructor that accepts BaseEnumT.
        union
        {
            EnumT m_enum;
            BaseEnumT m_base_enum;
        };
    };
}
