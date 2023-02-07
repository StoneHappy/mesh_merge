#include <mm/EatEdge.h>
int eat_edge_mm()
{
	Surface_mesh mesh0;
	Surface_mesh mesh1;

	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./polygon_mesh0.ply", mesh0);
	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./polygon_mesh1.ply", mesh1);

	Surface_mesh outmesh0, outmesh1;
	mm::eatEdge(mesh0, mesh1, outmesh0);
	mm::eatEdge(mesh1, mesh0, outmesh1);
	//CGAL::draw(outmesh0);

	std::ofstream f0("./out0.ply", std::ios_base::binary);
	CGAL::IO::set_binary_mode(f0);
	CGAL::IO::write_PLY(f0, outmesh0);
	f0.close();


	std::ofstream f1("./out1.ply", std::ios_base::binary);
	CGAL::IO::set_binary_mode(f1);
	CGAL::IO::write_PLY(f1, outmesh1);
	f1.close();
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
