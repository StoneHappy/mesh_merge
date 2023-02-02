#include "EatEdge.h"

#include <vector>
namespace mm {

	/// small helper to extract a triangle from a face
	Triangle_3 triangle(const Surface_mesh& sm, Face_descriptor f)
	{
		Halfedge_descriptor hf = sm.halfedge(f);
		Point_3 a = sm.point(sm.target(hf));
		hf = sm.next(hf);
		Point_3 b = sm.point(sm.target(hf));
		hf = sm.next(hf);
		Point_3 c = sm.point(sm.target(hf));
		hf = sm.next(hf);
		return Triangle_3(a, b, c);
	}

	class Box
		: public CGAL::Box_intersection_d::Box_d<double, 3, CGAL::Box_intersection_d::ID_NONE> {
	private:
		typedef CGAL::Box_intersection_d::Box_d<
			double, 3, CGAL::Box_intersection_d::ID_NONE> Base;
		Face_descriptor fd;
	public:
		typedef double                                   NT;
		typedef std::size_t                              ID;

		Box(Face_descriptor f, const Surface_mesh& sm) : Base(triangle(sm, f).bbox()), fd(f) {}
		Box(const Bbox_3& b, Face_descriptor fd) : Base(b), fd(fd) {}
		Face_descriptor f() const { return fd; }
		ID  id() const { return static_cast<ID>(fd); }
	};

	struct Callback {
		Callback(const Surface_mesh& P, const Surface_mesh& Q, unsigned int& i, std::vector<Face_descriptor>& p_Pf,
		std::vector<Face_descriptor>& p_Qf)
			: P(P), Q(Q), count(i), Pf(p_Pf), Qf(p_Qf)
		{}

		void operator()(const Box* bp, const Box* bq) {
			Face_descriptor fp = bp->f();
			Triangle_3 tp = triangle(P, fp);

			Face_descriptor fq = bq->f();
			Triangle_3 tq = triangle(Q, fq);
			if (do_intersect(tp, tq)) {
				++(count);
				Qf.push_back(fq);
				Pf.push_back(fp);
			}
		}

		const Surface_mesh& P;
		const Surface_mesh& Q;
		unsigned int& count;
		std::vector<Face_descriptor>& Qf;
		std::vector<Face_descriptor>& Pf;
	};

	const Box*
	address_of_box(const Box& b)
	{
		return &b;
	}

	std::pair<std::vector<Face_descriptor>, std::vector<Face_descriptor>> intersect(const Surface_mesh& P, const Surface_mesh& Q) {
		std::vector<Box> P_boxes, Q_boxes;
		std::vector<const Box*> P_box_ptr, Q_box_ptr;
		P_boxes.reserve(P.number_of_faces());
		P_box_ptr.reserve(P.number_of_faces());
		Q_boxes.reserve(Q.number_of_faces());
		Q_box_ptr.reserve(Q.number_of_faces());

		// build boxes and pointers to boxes
		for (auto f : P.faces())
			P_boxes.push_back(Box(f, P));
		std::transform(P_boxes.begin(), P_boxes.end(), std::back_inserter(P_box_ptr),
			&address_of_box);
		for (auto f : Q.faces())
			Q_boxes.push_back(Box(f, Q));
		std::transform(Q_boxes.begin(), Q_boxes.end(), std::back_inserter(Q_box_ptr),
			&address_of_box);

		unsigned int i = 0;
		std::vector<Face_descriptor> Qf;
		std::vector<Face_descriptor> Pf;
		Callback c(P, Q, i, Pf, Qf);
		CGAL::box_intersection_d(P_box_ptr.begin(), P_box_ptr.end(),
			Q_box_ptr.begin(), Q_box_ptr.end(),
			c);
		return { Pf, Qf };
	}

	bool isFaceAroundDelete(Face_descriptor f, Surface_mesh m, std::vector<Face_descriptor>& Pf)
	{
		auto halfedge = m.halfedge(f);
		//mesh0.halfedges_around_face(f);
		auto facesaround = m.faces_around_face(halfedge);

		for (auto f : facesaround)
		{
			if (std::find(Pf.begin(), Pf.end(), f) != Pf.end())
			{
				return false;
			}
		}
		return true;
	}
	int eatEdge(const Surface_mesh& mesh0, const Surface_mesh& mesh1, Surface_mesh& outMesh)
	{
		outMesh = mesh0;
		auto [Pf, Qf] = intersect(mesh0, mesh1);
		for (auto f : Pf)
		{
			CGAL::remove_face(f, outMesh);
		}
		outMesh.collect_garbage();
		std::vector<Point_3> vertices;
		std::vector<Facet> facets;
		CGAL::Polygon_mesh_processing::polygon_mesh_to_polygon_soup(mesh0, vertices, facets);
		std::cout << "origin: " << vertices.size() << " " << facets.size() << std::endl;
		CGAL::Polygon_mesh_processing::remove_isolated_points_in_polygon_soup(vertices, facets);
		std::cout << "new: " << vertices.size() << " " << facets.size() << std::endl;
		//Surface_mesh meshtmp;
		//// 更新面索引的多边形汤
		//CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(vertices, facets, meshtmp);
	
		/*CGAL::draw(meshtmp);
		std::ofstream f("./out.ply", std::ios_base::binary);
		CGAL::IO::set_binary_mode(f);
		CGAL::IO::write_PLY(f, meshtmp);
		f.close();*/
		return 0;
	}
}
