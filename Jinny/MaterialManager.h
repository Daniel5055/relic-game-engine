#pragma once

#include <map>
#include <utility>

#include "Material.h"

namespace Framework
{
    /**
     * Class for managing materials and how they interact with each other.
     */
    class MaterialManager
    {
    public:

        // Constructor
        MaterialManager();

        // Accessors
        double getCoefficientOfRestitution(Material m_1, Material m_2) const;
        double getStaticFrictionCoefficient(Material m_1, Material m_2) const;
        double getDynamicFrictionCoefficient(Material m_1, Material m_2) const;
    private:

        // Coefficients of Restitutions for different materials
        std::map<std::pair<Material, Material>, double> m_materials;


        // friction coefficients
        std::map<std::pair<Material, Material>, double> m_static_friction_coefficients;
        std::map<std::pair<Material, Material>, double> m_dynamic_friction_coefficients;
    };
}
