#include <mm/Merge.h>
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
