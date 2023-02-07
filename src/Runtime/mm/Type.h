#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/polygon_mesh_to_polygon_soup.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>
#include <CGAL/Polygon_mesh_processing/intersection.h>
#include <unordered_set>
#include <CGAL/draw_surface_mesh.h>
#include <CGAL/boost/graph/Euler_operations.h>
#include <CGAL/bounding_box.h>
#include <CGAL/Point_set_3.h>
#include <vector>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point_3;
typedef CGAL::Surface_mesh<Point_3> Surface_mesh;
typedef std::array<std::size_t, 3> Facet; // Èý½ÇÃæË÷Òý
typedef Kernel::Line_3 Line_3;
typedef std::array<Point_3, 2> Vector;
typedef Surface_mesh::Edge_index Edge_Descritor;

typedef Kernel::Triangle_3 Triangle_3;
typedef CGAL::Bbox_3 Bbox_3;
typedef CGAL::Timer Timer;

typedef Surface_mesh::Face_index Face_descriptor;
typedef Surface_mesh::Vertex_index Vertex_descriptor;
typedef Surface_mesh::Halfedge_index Halfedge_descriptor;

typedef CGAL::Point_set_3<Point_3> Point_set;

