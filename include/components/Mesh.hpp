#pragma once

#include <components/ComponentUtils.hpp>

#include <string>
#include <vector>

class Mesh
{
	public:

		virtual std::vector<std::string> get_current_sprite(double delta) = 0;

		virtual void set_sprite(std::vector<std::string> new_sprite) = 0;
		virtual void set_sprite(std::vector<std::vector<std::string>> new_sprite) = 0;

		void set_size(Size size) { m_size = size; }
		Size get_size() { return m_size; }

	private:
		// Can this be const??
		Size m_size;
};