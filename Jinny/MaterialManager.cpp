#include "MaterialManager.h"

#include <vector>

void Framework::MaterialManager::initialize()
{

	int num_of_materials = 7;
	// Data for coefficient of restitutions, maybe I should move to text files
	std::vector<double> coeff_of_r_data = {

		//   0	  1    2    3    4    5	   6
			1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, // Nullium = 0
				 0.6, 0.4, 0.7, 0.4, 0.9, 0.2, // Metal = 1
					  0.3, 0.4, 0.3, 0.8, 0.1, // Brick = 2
						   0.5, 0.4, 0.9, 0.2, // Wood = 3
								0.3, 0.8, 0.1, // Ice = 4
									 1.0, 0.7, // Trampoline = 5
										  0.1, // Entity = 6
	};

	// Iteratre through data to assign to material pairs
	int it_tracker = 0;
	for (int m_1 = 0; m_1 < num_of_materials; m_1++)
	{
		for (int m_2 = m_1; m_2 < num_of_materials; m_2++)
		{
			m_materials[{(Material)m_1, (Material)m_2}] = coeff_of_r_data[it_tracker + m_2 - m_1];
		}

		it_tracker += num_of_materials - m_1;
	}

	// Data for static friction, maybe I should move to text files
	std::vector<double> static_friction_data = {

		//   0	  1    2    3    4    5	   6
			0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, // Nullium = 0
				 0.4, 0.5, 0.5, 0.2, 0.4, 0.9, // Metal = 1
					  0.5, 0.6, 0.3, 0.5, 0.9, // Brick = 2
						   0.5, 0.3, 0.5, 0.9, // Wood = 3
								0.1, 0.2, 0.3, // Ice = 4
									 0.4, 0.5, // Trampoline = 5
										  0.9, // Entity = 6
	};

	// Iteratre through data to assign to material pairs
	it_tracker = 0;
	for (int m_1 = 0; m_1 < num_of_materials; m_1++)
	{
		for (int m_2 = m_1; m_2 < num_of_materials; m_2++)
		{
			m_static_friction_coefficients[{(Material)m_1, (Material)m_2}] = static_friction_data[it_tracker + m_2 - m_1];
		}

		it_tracker += num_of_materials - m_1;
	}

	// Data for static friction, maybe I should move to text files
	std::vector<double> dynamic_friction_data = {

		//   0	  1    2    3    4    5	   6
			0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, // Nullium = 0
				 0.3, 0.4, 0.4, 0.1, 0.3, 0.7, // Metal = 1
					  0.4, 0.5, 0.2, 0.4, 0.8, // Brick = 2
						   0.4, 0.2, 0.4, 0.8, // Wood = 3
							   0.05, 0.1, 0.1, // Ice = 4
									 0.3, 0.4, // Trampoline = 5
										  0.9, // Entity = 6
	};

	// Iteratre through data to assign to material pairs
	it_tracker = 0;
	for (int m_1 = 0; m_1 < num_of_materials; m_1++)
	{
		for (int m_2 = m_1; m_2 < num_of_materials; m_2++)
		{
			m_dynamic_friction_coefficients[{(Material)m_1, (Material)m_2}] = dynamic_friction_data[it_tracker + m_2 - m_1];
		}

		it_tracker += num_of_materials - m_1;
	}
}

double Framework::MaterialManager::getCoefficientOfRestitution(Framework::Material material_1, Framework::Material material_2) 
{
	if ((int)material_1 >= (int)material_2)
	{
		return m_materials[{material_2, material_1}];
	}
	else
	{
		return m_materials[{material_1, material_2}];
	}
}

double Framework::MaterialManager::getStaticFrictionCoefficient(Material material_1, Material material_2)
{
	if ((int)material_1 >= (int)material_2)
	{
		return m_static_friction_coefficients[{material_2, material_1}];
	}
	else
	{
		return m_static_friction_coefficients[{material_1, material_2}];
	}
}

double Framework::MaterialManager::getDynamicFrictionCoefficient(Material material_1, Material material_2)
{
	if ((int)material_1 >= (int)material_2)
	{
		return m_dynamic_friction_coefficients[{material_2, material_1}];
	}
	else
	{
		return m_dynamic_friction_coefficients[{material_1, material_2}];
	}
}
