#include <components/Viewport.hpp>

#include <string>
#include <vector>

// Default constructor
Viewport::Viewport() : x_size(0), y_size(0)
{
	
}

Viewport::Viewport(int x_size, int y_size) : x_size(x_size), y_size(y_size)
{
	// Assume our viewport starts at (0, 0) (Top left? Middle?)
	this->x_origin = 0;
	this->y_origin = 0;

	// Setup frame of viewport
	this->outline.push_back("//" + std::string(x_size, '=') + "\\\\");

	for (int y = 0; y < y_size; y++)
	{
		this->outline.push_back("||" + std::string(x_size, ' ') + "||");
	}

	this->outline.push_back("\\\\" + std::string(x_size, '=') + "//");
}

Viewport::~Viewport()
{


}

std::vector<std::string> Viewport::getVisual()
{
	return outline;
}