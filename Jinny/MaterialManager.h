#pragma once

#include <map>
#include <utility>

#include "Material.h"

namespace Framework
{
	class MaterialManager
	{
	public:

		void initialize();

		double getCoefficientOfRestitution(Material m_1, Material m_2);
		double getStaticFrictionCoefficient(Material m_1, Material m_2);
		double getDynamicFrictionCoefficient(Material m_1, Material m_2);
	private:

		// Coefficients of Restitutions for different materials
		std::map<std::pair<Material, Material>, double> m_materials;

		// friction coefficients
		std::map<std::pair<Material, Material>, double> m_static_friction_coefficients;
		std::map<std::pair<Material, Material>, double> m_dynamic_friction_coefficients;
	};
}
