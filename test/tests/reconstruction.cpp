#include <mm/Reconstruction.h>

int reconstruction()
{
	// 输入点云
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


int reconstruction_border()
{
	// 输入点云
	Point_set points0, points1;

	//std::string fname = CGAL::data_file_path("points_3//kitten.xyz");
	std::string fname0 = "./borderPoints0.ply";
	std::string fname1 = "./borderPoints1.ply";

	std::ifstream stream0(fname0, std::ios::binary);
	std::ifstream stream1(fname1, std::ios::binary);

	if (!stream0)
	{
		std::cerr << "Error: cannot read file " << fname0 << std::endl;
		return EXIT_FAILURE;
	}

	if (!stream1)
	{
		std::cerr << "Error: cannot read file " << fname1 << std::endl;
		return EXIT_FAILURE;
	}

	stream0 >> points0;
	stream1 >> points1;
	Point_set points;

	points.join(points0);
	points.join(points1);
	if (points.empty())
		return EXIT_FAILURE;

	Surface_mesh output_mesh;

	mm::Reconstruction(points, output_mesh);

	std::ofstream f("./out_advancing_front_border.ply", std::ios_base::binary);
	CGAL::IO::set_binary_mode(f);
	CGAL::IO::write_PLY(f, output_mesh);
	f.close();
}