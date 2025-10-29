#pragma once

#include <components/Area.hpp>
#include <components/ComponentUtils.hpp>

#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include <array>
#include <optional>
#include <limits>

#include <fstream>

std::ofstream rect_debug_log("rect_debug_log.txt", std::ios::app);

class CircleArea;

class RectArea: public Area
{
	public:
		ShapeType shape_type = ShapeType::RECT;


		std::optional<Vec> overlaps_with(std::shared_ptr<Area> other_area)
		{
			// Let's start by getting baseline normals
			std::vector<Vec> normals = other_area->get_normals();
			
			// Check if the other area is a circle, add the other vector if necessary
			if (other_area->shape_type == ShapeType::CIRCLE)
			{
				Position circle_center = other_area->origin; // figure out how tpo get this
				Position endpoint = get_normal_endpoint_from_center(circle_center);
				// Do we actually need to fnd the orthogonal vector here?
				normals.push_back(Vec{circle_center.x - endpoint.x, circle_center.y - endpoint.y});
			}

			double best_overlap_amount = 100000000.0;
			bool found = false;
			Vec best_norm = Vec{0.0, 0.0};
			for (Vec norm : normals)
			{
				Extent this_proj = get_projection(norm);
				Extent other_proj = other_area->get_projection(norm);

				// rect_debug_log << "Area 1 Addr: " << this << std::endl;
				// rect_debug_log << "Area 2 Addr: " << other_area.get() << std::endl;


				double overlap_amount = this_proj.get_overlap_amount(other_proj);
				if (overlap_amount <= 0.0)
				{
					return std::optional<Vec>();
				}
				else if (overlap_amount < best_overlap_amount)
				{
					found = true;
					best_overlap_amount = overlap_amount;
					best_norm = norm;
				}
			}
			return std::optional<Vec>(best_norm);
		}

		Position get_normal_endpoint_from_center(Position center) override
		{
			// Pick the closest corner to the origin.
			double shortest = std::numeric_limits<double>::infinity();
			Position best_corner;

			std::array<Position, 4> positions = {	Position{origin.x, origin.y},
													Position{origin.x + m_extent.x, origin.y},
													Position{origin.x, origin.y + m_extent.y},
													Position{origin.x + m_extent.x, origin.y + m_extent.y}};

			for (Position pos : positions)
			{
				double dist = sqrt(pow(pos.x - center.x, 2) + pow(pos.y - center.y, 2));
				if (dist < shortest)
				{
					shortest = dist;
					best_corner = pos;
				}
			}

			return best_corner;
		}

		void set_extent(Size new_extent) { m_extent = new_extent; }

	private:
		// Do I maybe want to make two simple structs called rect and circle, and then have each type of
		// area own theses structs? And maybe the area base class returns a union of rect and circle?
		// I feel like this avoids circular dependencies better, no pun intended
		Extent get_projection(Vec norm) override
		{
			// normalize vector
			// norm.x = norm.x / sqrt(norm.x * norm.x + norm.y * norm.y);
			// norm.y = norm.y / sqrt(norm.x * norm.x + norm.y * norm.y);

			std::array<Position, 4> positions = {	Position{origin.x, origin.y},
													Position{origin.x + m_extent.x, origin.y},
													Position{origin.x, origin.y + m_extent.y},
													Position{origin.x + m_extent.x, origin.y + m_extent.y}};


			double first_dot = norm.x * positions[0].x + norm.y * positions[0].y;
			double max_proj = first_dot;
			double min_proj = first_dot;
			// double max_proj, min_proj;
			for (int i = 1; i < positions.size(); i++)
			{
				double dot = norm.x * positions[i].x + norm.y * positions[i].y;
				if (dot > max_proj) max_proj = dot;
				if (dot < min_proj) min_proj = dot;
			}

			// Get extent
			return {min_proj, max_proj};
		}

		std::vector<Vec> get_normals() override
		{
			// Eventually, we'll want to factor rotation into this, but for now we can just return
			// the known normals.

			// Check the syntax here
			return std::vector<Vec>({{0, 1}, {1, 0}});
		}

		Size m_extent;


};