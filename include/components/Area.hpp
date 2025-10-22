#pragma once

#include <components/ComponentUtils.hpp>

#include <memory>
#include <vector>
#include <optional>
#include <algorithm>


// |               |
//          |                 |

struct Extent
{
	double min;
	double max;

	double get_overlap_amount(Extent& other)
	{
		if (min > other.max || other.min > max)
			return 1000000.0;

		return abs(std::min(max - other.min, other.max - min));
	}
};

// This feels like bad practice when I could be doing type checking, but it
// also feels alot simpler than doing a dynamic cast
enum ShapeType
{
	CIRCLE,
	RECT
};

class Area
{
	private:
		/// Brainstorm: What can be shared between CircleArea and RectArea?
		// Both can have a get_projection() function based on an arbitrary norm
		// Rect needs a get_normals function
		// If it's two rects, we can just call get_normals on both
		// If it's a circle and a rect, we call get_normals on the rect and
		// then we need some kind of way to get the normal between the circle center
		// and the closest point of the rect
		// If it's two circles, we need to get the centers of both
		// Maybe we have some function like:
		// get_normal_endpoint_from_center()
		// And if this is called on a circle it just returns the center
		// And it it's called on a rect it returns the closes point
	public:
		virtual Extent get_projection(Vec norm) = 0;


		// Instead of returning a bool, we return an optional vec here
		// No data implies no collision
		// If there is data, it will be the collision normal for the collision
		// between the two object
		virtual std::optional<Vec> overlaps_with(std::shared_ptr<Area> other_area) = 0;

		virtual Position get_normal_endpoint_from_center(Position center) = 0;

		virtual std::vector<Vec> get_normals() = 0;

		ShapeType shape_type;

		Position origin;
};