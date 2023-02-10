#include "Merge.h"
#include <CGAL/Polygon_mesh_processing/polygon_mesh_to_polygon_soup.h>
#include "Reconstruction.h"
namespace mm
{
	int Merge(std::vector<Surface_mesh>& meshs, Surface_mesh& outMesh)
	{
		typedef std::array<std::size_t, 3> Facet; // Èý½ÇÃæË÷Òý
		std::vector<Facet> facets;
		std::vector<Point_3> vertices;
		
		for (size_t i = 0; i < meshs.size(); i++)
		{
			std::vector<Facet> fs;
			std::vector<Point_3> vs;
			CGAL::Polygon_mesh_processing::polygon_mesh_to_polygon_soup(meshs[i], vs, fs);

			for (auto& f : fs)
			{
				for (auto& v : f)
				{
					v += vertices.size();
				}
			}

			vertices.insert(vertices.end(), vs.begin(), vs.end());
			facets.insert(facets.end(), fs.begin(), fs.end());
		}
		CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(vertices, facets, outMesh);
		return 0;
	}

	static int getIndex()
	{

	}
	int Merge(const Surface_mesh& mesh0, const Surface_mesh& mesh1, const std::vector<Vertex_descriptor>& vd0, const std::vector<Vertex_descriptor>& vd1, Surface_mesh& outMesh)
	{
		Point_set ps0, ps1;

		for (size_t i = 0; i < vd0.size(); i++)
		{
			ps0.insert(mesh0.point(vd0[i]));
		}

		for (size_t i = 0; i < vd1.size(); i++)
		{
			ps1.insert(mesh1.point(vd1[i]));
		}

		Surface_mesh middleMesh;

		Point_set points;

		points.join(ps0);
		points.join(ps1);

		int middleIndex = ps0.size();

		if (points.empty())
			return EXIT_FAILURE;

		::mm::Reconstruction(points, middleMesh);

		std::vector<Facet> facets;
		std::vector<Point_3> vertices;
		std::vector<Facet> fs0, fs1;
		std::vector<Point_3> vs0, vs1;
		CGAL::Polygon_mesh_processing::polygon_mesh_to_polygon_soup(mesh0, vs0, fs0);
		vertices.insert(vertices.end(), vs0.begin(), vs0.end());
		facets.insert(facets.end(), fs0.begin(), fs0.end());

		CGAL::Polygon_mesh_processing::polygon_mesh_to_polygon_soup(mesh1, vs1, fs1);
		vertices.insert(vertices.end(), vs1.begin(), vs1.end());
		facets.insert(facets.end(), fs1.begin(), fs1.end());

		CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(vertices, facets, outMesh);

		Vertex_descriptor v0, v1, v2;

		outMesh.add_face(v0, v0, v0);
		for (auto&& f : middleMesh.faces())
		{

		}

		return 0;
	}
}

