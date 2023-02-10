#include <mm/Merge.h>
#include <mm/Move.h>
int merge()
{
	Surface_mesh mesh0;
	Surface_mesh mesh1;
	Surface_mesh mesh2;

	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./out0.ply", mesh0);
	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./out1.ply", mesh1);
	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./out_advancing_front.ply", mesh2);

	std::vector<Surface_mesh> meshs;
	meshs.push_back(mesh0);
	meshs.push_back(mesh1);
	meshs.push_back(mesh2);
	Surface_mesh outmeshs;
	mm::Merge(meshs, outmeshs);

	std::ofstream f("./mergeMesh.ply", std::ios_base::binary);
	CGAL::IO::set_binary_mode(f);
	CGAL::IO::write_PLY(f, outmeshs);
	f.close();
	return 0;
}


int merge_overlap()
{
	Surface_mesh mesh0;
	Surface_mesh mesh1;

	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./mesh0.ply", mesh0);
	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./mesh1.ply", mesh1);
	std::vector<Vertex_descriptor> vd0, vd1;
	mm::GetIntersectionBorderPoints(mesh0, mesh1, vd0, vd1);

	mm::MovePoint2Middle(mesh0, mesh1, vd0, vd1);

	Surface_mesh meshs;
	mm::Merge(mesh0, mesh1, vd0, vd1, meshs);
	//meshs.push_back(mesh0);
	//meshs.push_back(mesh1);
	////meshs.push_back(mesh2);
	//Surface_mesh outmeshs;
	//mm::Merge(meshs, outmeshs);

	/*std::ofstream f("./mergeOverlapMesh.ply", std::ios_base::binary);
	CGAL::IO::set_binary_mode(f);
	CGAL::IO::write_PLY(f, meshs);
	f.close();*/

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
