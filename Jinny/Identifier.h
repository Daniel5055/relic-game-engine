#pragma once
#include <string>

namespace relic
{
    /**
     * \brief Class used for identification in all aspects of the program
     */
    class Identifier
    {
    public:
        static const Identifier null;


        // Constructor
        Identifier(int id, std::string name, std::string type, int sub_id = 0);
        Identifier(const Identifier& id, int sub_id);

        // Accessors
        int getId() const;
        std::string getName() const;
        std::string getType() const;

        void setSubId(int id);
        int getSubId() const;

        bool operator==(const Identifier& id) const;
        bool operator!=(const Identifier& id) const;
        bool operator<(const Identifier& id) const;

    private:
        // Key Identification
        int m_id;
        std::string m_name;
        std::string m_type;

        // Mini id (for parts of the target identity) (Like for components)
        // Not used when comparing ids, rather used as an after thought
        int m_sub_id;

    };
}
