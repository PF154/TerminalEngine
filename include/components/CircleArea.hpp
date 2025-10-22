#pragma once

#include <components/Area.hpp>

#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include <optional>

class GameObject;

class CircleArea: public Area
{	
	// Vector an position are no different functionally, but should have diff name for clarity

	public:
		ShapeType shape_type = ShapeType::CIRCLE;

		std::optional<Vec> overlaps_with(std::shared_ptr<Area> other_area) override
		{
			// Let's start by getting baseline normals
			std::vector<Vec> normals = other_area->get_normals();
			
			// Since this object is a circle, we need to add a normal either way
			Position endpoint = other_area->get_normal_endpoint_from_center(origin);
			// Do we actually need to fnd the orthogonal vector here?
			normals.push_back(Vec{origin.x - endpoint.x, origin.y - endpoint.y});


			double best_overlap_amount = 100000000.0;
			Vec best_norm = Vec{0.0, 0.0};
			for (Vec norm : normals)
			{
				Extent this_proj = get_projection(norm);
				Extent other_proj = other_area->get_projection(norm);

				// Check if the extents do not overlap
				bool no_overlap = this_proj.min > other_proj.max || other_proj.min > this_proj.max;
				if (no_overlap)
				{
					return std::optional<Vec>{};
				}
				else
				{
					double overlap_amount = this_proj.get_overlap_amount(other_proj);
					if (overlap_amount < best_overlap_amount)
					{
						best_overlap_amount = overlap_amount;
						best_norm = norm;
					}
				}
			}
			return std::optional<Vec>{best_norm};
		}

	private:
		Extent get_projection(Vec norm) override
		{
			// normalize vector
			norm.x = norm.x / sqrt(norm.x * norm.x + norm.y * norm.y);
			norm.y = norm.y / sqrt(norm.x * norm.x + norm.y * norm.y);

			// Get the dot product of center
			double c = norm.x * origin.x + norm.y * origin.y;

			// Get extent
			return {c - radius, c + radius};
		}

		Vec get_normal_from_closest_point(Position point);

		std::vector<Vec> get_normals() override
		{
			return {};
		}

		double radius;


};