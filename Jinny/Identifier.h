#pragma once
#include <string>

namespace relic
{
    /**
     * \brief Class used for identification
     */
    class Identifier
    {
    public:
        static const Identifier null;


        // Constructor
        Identifier(int id, std::string name, std::string type);

        // Accessors
        int getId() const ;
        std::string getName() const;
        std::string getType() const;

        bool operator==(const Identifier& id) const;
        bool operator!=(const Identifier& id) const;
        bool operator<(const Identifier& id) const;

    private:
        int m_id;
        std::string m_name;
        std::string m_type;
        
    };
}
