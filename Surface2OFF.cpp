#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <iostream>
#include <fstream>
typedef CGAL::Simple_cartesian<double>               Kernel;
typedef Kernel::Point_3                              Point_3;
typedef CGAL::Polyhedron_3<Kernel>                   Polyhedron;
typedef Polyhedron::Facet_iterator                   Facet_iterator;
typedef Polyhedron::Halfedge_handle                  Halfedge_handle;
typedef Polyhedron::Halfedge_around_facet_circulator Halfedge_facet_circulator;


template <class Poly>
typename Poly::Halfedge_handle make_cube_3(Poly& P) {
    // appends a cube of size [0,1]^3 to the polyhedron P.
    CGAL_precondition(P.is_valid());
    typedef typename Poly::Point_3         Point;
    typedef typename Poly::Halfedge_handle Halfedge_handle;
    
    Halfedge_handle h = P.make_tetrahedron(Point(1, 0, 0),
        Point(0, 0, 1),
        Point(0, 0, 0),
        Point(0, 1, 0));
    Halfedge_handle g = h->next()->opposite()->next();             // Fig. (a)
    P.split_edge(h->next());
    P.split_edge(g->next());
    P.split_edge(g);                                              // Fig. (b)
    h->next()->vertex()->point() = Point(1, 0, 1);
    g->next()->vertex()->point() = Point(0, 1, 1);
    g->opposite()->vertex()->point() = Point(1, 1, 0);            // Fig. (c)
    Halfedge_handle f = P.split_facet(g->next(),
        g->next()->next()->next()); // Fig. (d)
    Halfedge_handle e = P.split_edge(f);
    e->vertex()->point() = Point(1, 1, 1);                        // Fig. (e)
    P.split_facet(e, f->next()->next());                          // Fig. (f)
    CGAL_postcondition(P.is_valid());
    return h;
}

int main() {
    Polyhedron P;
    Halfedge_handle h = make_cube_3(P);
    if (P.is_tetrahedron(h))
    {
        std::cout << 1 << std::endl;
    }
    else
    {
        std::cout << 0 << std::endl;
    }
    //return (P.is_tetrahedron(h) ? 1 : 0);

    CGAL::set_ascii_mode(std::cout);
    std::ofstream F;
    //使用写方式创建并打开文件regular_tetrahedron.off    
    F.open("data/cube.off");
    //输出关键字OFF，顶点数，面数，边数（0）
    F << "OFF" << std::endl << P.size_of_vertices() << ' '
        << P.size_of_facets() << " 0" << std::endl;
    std::copy(P.points_begin(), P.points_end(),
        std::ostream_iterator<Point_3>(F, "\n"));
    for (Facet_iterator i = P.facets_begin(); i != P.facets_end(); ++i) {
        Halfedge_facet_circulator j = i->facet_begin();
        CGAL_assertion(CGAL::circulator_size(j) >= 3);
        F << CGAL::circulator_size(j) << ' ';
        do {
            F << ' ' << std::distance(P.vertices_begin(), j->vertex());
        } while (++j != i->facet_begin());
        F << std::endl;
    }
    //关闭文件
    F.close();

    return 0;
    
}