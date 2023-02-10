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
		std::vector<Kernel::Vector_3> directions;
		directions.resize(vd0.size());

		double minlength = 10000000000.0;
		
		for (size_t i = 0; i < vd0.size(); i++)
		{
			minlength = 10000000000.0;
			Kernel::Vector_3 mindir;
			for (size_t j = 0; j < vd1.size(); j++)
			{
				auto delta = mesh0.point(vd0[i]) - mesh1.point(vd1[j]);
				auto length = delta.squared_length();
				if (length < minlength)
				{
					minlength = length;
					mindir = delta;
				}
			}
			directions[i] = mindir;
		}
		int x = 0, y = 0, z = 0;
		for (auto&& dir : directions)
		{
			if (abs(dir.x()) >= abs(dir.y()) && abs(dir.x()) >= abs(dir.z()))
			{
				x++;
			}
			else if(abs(dir.y()) >= abs(dir.z()))
			{
				y++;
			}
			else
			{
				z++;
			}
		}

		if (x >= y && x >= z)
		{
			x = 1;
			y = 0;
			z = 0;
		}
		else if( y >= z )
		{
			x = 0;
			y = 1;
			z = 0;
		}
		else
		{
			x = 0;
			y = 0;
			z = 1;
		}
		return  { x,  y, z };
	}

	double getIntersectionVolume(const Surface_mesh& mesh0, const Surface_mesh& mesh1)
	{
		Kernel::Iso_cuboid_3 bbox1 = CGAL::bounding_box(mesh1.points().begin(), mesh1.points().end());
		Kernel::Iso_cuboid_3 bbox0 = CGAL::bounding_box(mesh0.points().begin(), mesh0.points().end());

		auto bbox_p = CGAL::intersection(bbox0, bbox1);
		Kernel::Iso_cuboid_3 bbox = boost::get<Kernel::Iso_cuboid_3>(bbox_p.value());
		return bbox.volume();
	}

	static Triangle_3 triangle(const Surface_mesh& sm, Face_descriptor f)
	{
		Halfedge_descriptor hf = sm.halfedge(f);
		Point_3 a = sm.point(sm.target(hf));
		hf = sm.next(hf);
		Point_3 b = sm.point(sm.target(hf));
		hf = sm.next(hf);
		Point_3 c = sm.point(sm.target(hf));
		hf = sm.next(hf);
		return Triangle_3(a, b, c);
	}

	bool isInterV2Mesh(const Surface_mesh& mesh0, const Surface_mesh& mesh1, const Vertex_descriptor& currentvd, const std::vector<Vertex_descriptor>& vd1)
	{
		auto point =mesh0.point(currentvd);
		
		for (auto&& f1 : mesh1.faces())
		{
			auto tr1 = triangle(mesh1, f1);
			Kernel::Iso_cuboid_3 bbox = tr1.bbox();
			if (!bbox.has_on_unbounded_side(point)) return true;
		}
	
		return false;
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

		double spacemin = (spacing0 + spacing1) / 50.0;

		auto volume = getIntersectionVolume(mesh0, mesh1);
		auto dir0 = getMovedir(mesh0, mesh1, vd0, vd1);
		//auto dir1 = getMovedir(mesh1, mesh0, vd1, vd0);
		
		bool isbreak = false;
		int maxtime = 0;

		while (!isbreak != 0 && maxtime < 100)
		{
			isbreak = true;
			for (size_t i = 0; i < vd0.size(); i++)
			{
				
				if (isInterV2Mesh(mesh0, mesh1, vd0[i], vd1))
				{
					isbreak = false;
					auto&& p = mesh0.point(vd0[i]);
					p += dir0 * spacemin;
				}
			}

			for (size_t i = 0; i < vd1.size(); i++)
			{
				if (isInterV2Mesh(mesh1, mesh0, vd1[i], vd0))
				{
					isbreak = false;
					auto&& p = mesh1.point(vd1[i]);
					p -= dir0* spacemin;
				}
			}
			maxtime++;
		}
		std::cout << "maxtime: " << maxtime << std::endl;
		return 0;
	}
}
