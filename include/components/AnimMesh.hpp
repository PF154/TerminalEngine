#pragma once

#include <components/Mesh.hpp>

#include <iostream>
#include <string>
#include <vector>

class AnimMesh : public Mesh
{
	public:

		void update(double delta);

		std::vector<std::string> get_current_sprite(double delta) override
		{
			return {"X"};
		}

		virtual void set_sprite(std::vector<std::string> new_sprite) {};
		virtual void set_sprite(std::vector<std::vector<std::string>> new_sprite) {};

	private:

		// SomeType m_anim_clock -- based on how long anim is? made to keep track of where we are frame wise
		// Could also just have an int representing frames, and a frametimeclock. when frametimeclock reaches
		// the desired frametime, we set it to zero again and increment the frame int

		// Do we want some kind of size guarantee on all of these?
		// Could save memory by just doing an array?
		std::vector<std::vector<std::string>> m_anim_mesh;
};