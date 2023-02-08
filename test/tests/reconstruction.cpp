#include <mm/Reconstruction.h>

int reconstruction()
{
	//  ‰»Îµ„‘∆
	Point_set points;

	//std::string fname = CGAL::data_file_path("points_3//kitten.xyz");
	std::string fname = "D:\\codes\\mesh_merge\\out\\bin\\Debug\\outPoints.ply";

	std::ifstream stream(fname, std::ios::binary);

	if (!stream)
	{
		std::cerr << "Error: cannot read file " << fname << std::endl;
		return EXIT_FAILURE;
	}

	stream >> points;

	std::cout << "Read " << points.size() << " point(s)" << std::endl;
	if (points.empty())
		return EXIT_FAILURE;

	Surface_mesh output_mesh;

	mm::Reconstruction(points, output_mesh);

	std::ofstream f("./out_advancing_front.ply", std::ios_base::binary);
	CGAL::IO::set_binary_mode(f);
	CGAL::IO::write_PLY(f, output_mesh);
	f.close();
}
