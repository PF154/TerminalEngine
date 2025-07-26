#pragma once

#include <string>
#include <vector>

// What do we want here? We want to store:
//		Size of viewport
//		Location of viewport in world?
//		Draw function?

// Viewport should look like:

//		//===================\\
//		||                   ||
//		||                   ||
//		||                   ||
//		\\===================//

class Viewport
{
	public:
		Viewport();
		Viewport(int x_size, int y_size);
		~Viewport();

		inline int getXSize() {return x_size;};
		inline int getYSize() {return y_size;};
		std::vector<std::string> getVisual();

	private:
		int x_size;
		int y_size;
		int x_origin;
		int y_origin;
		std::vector<std::string> outline;
};