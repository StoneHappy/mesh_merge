#include <mm/Move.h>

int get_border_v()
{
	Surface_mesh mesh0;
	Surface_mesh mesh1;

	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./mesh0.ply", mesh0);
	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./mesh1.ply", mesh1);
	std::vector<Vertex_descriptor> vd0, vd1;
	mm::GetIntersectionBorderPoints(mesh0, mesh1, vd0, vd1);

	Point_set ps0, ps1;

	for (size_t i = 0; i < vd0.size(); i++)
	{
		ps0.insert(mesh0.point(vd0[i]));
	}

	for (size_t i = 0; i < vd1.size(); i++)
	{
		ps1.insert(mesh1.point(vd1[i]));
	}

	std::ofstream f0("./borderPoints0.ply", std::ios_base::binary);
	f0 << ps0;
	f0.close();

	std::ofstream f1("./borderPoints1.ply", std::ios_base::binary);
	f1 << ps1;
	f1.close();

	return 0;
}

int moveMeshBorder()
{
	Surface_mesh mesh0;
	Surface_mesh mesh1;

	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./mesh0.ply", mesh0);
	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./mesh1.ply", mesh1);
	std::vector<Vertex_descriptor> vd0, vd1;
	mm::GetIntersectionBorderPoints(mesh0, mesh1, vd0, vd1);

	mm::MovePoint2Middle(mesh0, mesh1, vd0, vd1);

	std::ofstream f0("./out_move_border_mesh0.ply", std::ios_base::binary);
	CGAL::IO::set_binary_mode(f0);
	CGAL::IO::write_PLY(f0, mesh0);
	f0.close();

	std::ofstream f1("./out_move_border_mesh1.ply", std::ios_base::binary);
	CGAL::IO::set_binary_mode(f1);
	CGAL::IO::write_PLY(f1, mesh1);
	f1.close();

	return 0;
}
