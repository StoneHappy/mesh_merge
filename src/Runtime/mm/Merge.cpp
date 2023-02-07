#include "Merge.h"
#include <CGAL/Polygon_mesh_processing/polygon_mesh_to_polygon_soup.h>
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
	}
}

