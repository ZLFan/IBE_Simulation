#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/poisson_surface_reconstruction.h>
#include <vector>
#include <fstream>
#include<CGAL/Point_set_3.h>
#include<CGAL/IO/read_points.h>
// Types
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point;
typedef Kernel::Vector_3 Vector;
typedef std::pair<Point, Vector> Pwn;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef CGAL::Point_set_3<Point,Vector> Point_set;

bool point_set_read_ply(std::string ipath, Point_set& point_cloud)
{
    std::ifstream f(ipath, std::ios_base::binary);
    if (!CGAL::IO::read_PLY(f, point_cloud))
    {
        std::cerr << "Can not read input file " << std::endl;
        return false;
    }
    return true;
}

int main(void)
{
    Point_set point_set;
    std::string ipath = "data/cube.ply";
    /*point_set_read_ply(ipath, point_set);*/
    point_set.add_normal_map();
    if (!CGAL::IO::read_points(ipath, point_set.index_back_inserter(),
        CGAL::parameters::point_map(point_set.point_push_map())
        .normal_map(point_set.normal_push_map())))
    {
        std::cerr << "Can't read input file " << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "have read" << std::endl;

    Polyhedron output_mesh;
    double average_spacing = CGAL::compute_average_spacing<CGAL::Sequential_tag>
        (point_set, 6, CGAL::parameters::point_map(point_set.point_map()));
    std::cout << "have averaged" << std::endl;
    if (
        CGAL::poisson_surface_reconstruction_delaunay(
            point_set.begin(),
            point_set.end(),
            point_set.point_map(),
            point_set.normal_map(),
            output_mesh,
            average_spacing
        )
        )
    {
        std::cout << "done" << std::endl;
        std::ofstream out("data/Cube_surface.off");
        out << output_mesh;
    }
    else
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
    
    /*
    std::vector<Pwn> points;
    if (!CGAL::IO::read_points("data/Elephant.xyz", std::back_inserter(points),
        CGAL::parameters::point_map(CGAL::First_of_pair_property_map<Pwn>())
        .normal_map(CGAL::Second_of_pair_property_map<Pwn>())))
    {
        std::cerr << "Error: cannot read input file!" << std::endl;
        return EXIT_FAILURE;
    }
     Polyhedron output_mesh;
    double average_spacing = CGAL::compute_average_spacing<CGAL::Sequential_tag>
        (point_cloud, 6, CGAL::parameters::point_map(CGAL::First_of_pair_property_map<Point_set>()));

    if (CGAL::poisson_surface_reconstruction_delaunay
    (point_cloud.begin(), point_cloud.end(),
        CGAL::First_of_pair_property_map<Point_set>(),
        CGAL::Second_of_pair_property_map<Point_set>(),
        output_mesh, average_spacing))
    {
        std::ofstream out("data/Cube_surface.off");
        out << output_mesh;
    }
    else
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
    */


   
}