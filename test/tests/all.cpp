#include <mm/EatEdge.h>
#include <mm/Reconstruction.h>
#include <mm/Merge.h>
int all()
{
	Surface_mesh mesh0;
	Surface_mesh mesh1;

	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./polygon_mesh0.ply", mesh0);
	CGAL::Polygon_mesh_processing::IO::read_polygon_mesh("./polygon_mesh1.ply", mesh1);

	Surface_mesh newMesh0, newMesh1;
	mm::eatEdge(mesh0, mesh1, newMesh0);
	mm::eatEdge(mesh1, mesh0, newMesh1);

	Point_set overlapPoints;
	mm::eatEdgeVertices(mesh0, mesh1, overlapPoints);

	Surface_mesh overlapMesh;

	mm::Reconstruction(overlapPoints, overlapMesh);

	std::vector<Surface_mesh> meshs = { newMesh0, newMesh1, overlapMesh };
	
	Surface_mesh allMesh;
	mm::Merge(meshs, allMesh);

	std::ofstream f("./allMesh.ply", std::ios_base::binary);
	CGAL::IO::set_binary_mode(f);
	CGAL::IO::write_PLY(f, allMesh);
	f.close();
}
