#pragma once

#include <components/Mesh.hpp>

#include <string>
#include <vector>
#include <iostream>

class StaticMesh : public Mesh 
{
	public:
		std::vector<std::string> get_current_sprite(double delta) override 
		{
			if (m_static_mesh.size() == 0)
			{
				std::cout << "Attempted to get current sprite from an empty mesh object, please set mesh first!" << std::endl;
				return std::vector<std::string>({"x"});
			}
			return m_static_mesh;
		}

		virtual void set_sprite(std::vector<std::string> new_sprite)
		{
			m_static_mesh = new_sprite;
		}

		virtual void set_sprite(std::vector<std::vector<std::string>> new_sprite)
		{
			std::cout << "attempted to set multi-frame sprite on static mesh -- incompatible" << std::endl;
		}

	private:
		std::vector<std::string> m_static_mesh;

};