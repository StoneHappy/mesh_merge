#include <mm/EatEdge.h>
int eat_edge_mm()
{
	Surface_mesh mesh0;
	Surface_mesh mesh1;

	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./polygon_mesh0.ply", mesh0);
	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./polygon_mesh1.ply", mesh1);

	Surface_mesh outmesh;
	mm::eatEdge(mesh0, mesh1, outmesh);
	CGAL::draw(outmesh);

	std::ofstream f("./out.ply", std::ios_base::binary);
	CGAL::IO::set_binary_mode(f);
	CGAL::IO::write_PLY(f, outmesh);
	f.close();
	return 0;
}

int eat_edge_v_mm()
{
	Surface_mesh mesh0;
	Surface_mesh mesh1;

	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./polygon_mesh0.ply", mesh0);
	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./polygon_mesh1.ply", mesh1);

	//Surface_mesh outmesh;
	Point_set outPoints;
	mm::eatEdgeVertices(mesh0, mesh1, outPoints);

	std::ofstream f("./outPoints.ply", std::ios_base::binary);
	f << outPoints;
	f.close();
	return 0;
}
