#pragma

#include <components/GameObject.hpp>

#include <memory>
#include <vector>


class Area
{
	public:
		virtual std::vector<std::shared_ptr<GameObject>> get_last_frame_intersections() = 0;
};