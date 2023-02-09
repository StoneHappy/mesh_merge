#include "Move.h"
#include <CGAL/compute_average_spacing.h>
namespace mm
{
	int GetIntersectionBorderPoints(const Surface_mesh& mesh0, const Surface_mesh& mesh1, std::vector<Vertex_descriptor>& vd0, std::vector<Vertex_descriptor>& vd1)
	{
		Kernel::Iso_cuboid_3 bbox1 = CGAL::bounding_box(mesh1.points().begin(), mesh1.points().end());
		Kernel::Iso_cuboid_3 bbox0 = CGAL::bounding_box(mesh0.points().begin(), mesh0.points().end());

		auto bbox_p = CGAL::intersection(bbox0, bbox1);
		Kernel::Iso_cuboid_3 bbox = boost::get<Kernel::Iso_cuboid_3>(bbox_p.value());


		for (auto e : mesh0.edges())
		{
			if (!mesh0.is_border(e)) continue;


			auto v0 = mesh0.vertex(e, 0);
			auto v1 = mesh0.vertex(e, 0);

			if (mesh0.is_border(v0) && !bbox.has_on_unbounded_side(mesh0.point(v0))) vd0.push_back(v0);
			if (mesh0.is_border(v1) && !bbox.has_on_unbounded_side(mesh0.point(v1))) vd0.push_back(v1);
		}

		for (auto e : mesh1.edges())
		{
			if (!mesh1.is_border(e)) continue;

			auto v0 = mesh1.vertex(e, 0);
			auto v1 = mesh1.vertex(e, 0);

			if (mesh1.is_border(v0) && !bbox.has_on_unbounded_side(mesh1.point(v0))) vd1.push_back(v0);
			if (mesh1.is_border(v1) && !bbox.has_on_unbounded_side(mesh1.point(v1))) vd1.push_back(v1);
		}

		return 0;
	}

	

	static void moveBorderVertices(Surface_mesh& mesh, const std::vector<Vertex_descriptor>& vds, int direction, double step)
	{
		Point_3 aaa;
		for (size_t i = 0; i < vds.size(); i++)
		{
			auto&& p = mesh.point(vds[i]);
			switch (abs(direction))
			{
			case 1:
				p += {direction/abs(direction) * step, 0, 0};
			case 2:
				p += {0, direction / abs(direction) * step, 0};
			case 3:
				p += {0, 0, direction / abs(direction) * step};
			default:
				break;
			}
		}
	}

	/*void moveBorderVerticesDir(Surface_mesh& mesh, const std::vector<Vertex_descriptor>& vds, Kernel::Vector_3 direction, double step)
	{
		
		for (size_t i = 0; i < vds.size(); i++)
		{
			auto&& p = mesh.point(vds[i]);
				p += direction * step;
			}
		}
	}*/

	Kernel::Vector_3 getMovedir(const Surface_mesh& mesh0, const Surface_mesh& mesh1, const std::vector<Vertex_descriptor>& vd0, const std::vector<Vertex_descriptor>& vd1)
	{
		Kernel::Vector_3 direction;
		double minlength = 0;
		for (size_t i = 0; i < vd0.size(); i++)
		{
			for (size_t j = 0; j < vd1.size(); j++)
			{
				auto delta = mesh0.point(vd0[i]) - mesh1.point(vd1[j]);
				auto length = delta.squared_length();
				if (length < minlength)
				{
					minlength = length;
					direction = delta;
				}
			}
		}

		return { 0, 1, 0 };

		if (direction.x() >= direction.y() && direction.x() >= direction.z()) return { 1, 0, 0 };
		if (direction.y() >= direction.x() && direction.y() >= direction.z()) return { 0, 1, 0 };
		if (direction.z() >= direction.x() && direction.z() >= direction.y()) return { 0, 0, 1 };
		return direction;
	}

	double getIntersectionVolume(const Surface_mesh& mesh0, const Surface_mesh& mesh1)
	{
		Kernel::Iso_cuboid_3 bbox1 = CGAL::bounding_box(mesh1.points().begin(), mesh1.points().end());
		Kernel::Iso_cuboid_3 bbox0 = CGAL::bounding_box(mesh0.points().begin(), mesh0.points().end());

		auto bbox_p = CGAL::intersection(bbox0, bbox1);
		Kernel::Iso_cuboid_3 bbox = boost::get<Kernel::Iso_cuboid_3>(bbox_p.value());
		return bbox.volume();
	}

	int MovePoint2Middle(Surface_mesh& mesh0, Surface_mesh& mesh1, const std::vector<Vertex_descriptor>& vd0, const std::vector<Vertex_descriptor>& vd1)
	{
		// 计算点的平均距离
		Point_set points0, points1;

		for (auto&& p : mesh0.points())
		{
			points0.insert(p);
		}

		for (auto&& p : mesh1.points())
		{
			points1.insert(p);
		}
		double spacing0 = CGAL::compute_average_spacing<CGAL::Sequential_tag>(
			points0, 2
			);

		double spacing1 = CGAL::compute_average_spacing<CGAL::Sequential_tag>(
			points0, 2
			);

		double spacemin = (spacing0 + spacing1) / 100.0;

		auto volume = getIntersectionVolume(mesh0, mesh1);
		auto dir = getMovedir(mesh0, mesh1, vd0, vd1);
		
		while (volume != 0)
		{
			for (size_t i = 0; i < vd0.size(); i++)
			{
				auto&& p = mesh0.point(vd0[i]);
				p += dir * spacemin;
			}

			for (size_t i = 0; i < vd1.size(); i++)
			{
				auto&& p = mesh1.point(vd1[i]);
				p -= dir * spacemin;
			}
			auto delta = getIntersectionVolume(mesh0, mesh1) - volume;

			if (delta >= 0) break;

			volume = getIntersectionVolume(mesh0, mesh1);
		}

		return 0;
	}
}
