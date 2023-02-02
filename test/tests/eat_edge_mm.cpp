#include <mm/EatEdge.h>
int eat_edge_mm()
{
	Surface_mesh mesh0;
	Surface_mesh mesh1;

	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./mesh0.ply", mesh0);
	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./mesh1.ply", mesh1);

	Surface_mesh outmesh;
	mm::eatEdge(mesh0, mesh1, outmesh);
	CGAL::draw(outmesh);
}
