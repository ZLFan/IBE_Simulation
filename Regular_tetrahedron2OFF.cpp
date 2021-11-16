//构建一个正四面体，以off格式输出到屏幕并写入off文件
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <iostream>
#include <fstream>
typedef CGAL::Simple_cartesian<double>               Kernel;
typedef Kernel::Point_3                              Point_3;
typedef CGAL::Polyhedron_3<Kernel>                   Polyhedron;
typedef Polyhedron::Facet_iterator                   Facet_iterator;
typedef Polyhedron::Halfedge_around_facet_circulator Halfedge_facet_circulator;
int main() {
    /*--step 1. 建立正四面体--*/

    //设置四面体的4个顶点，类型为Point_3(const)
    Point_3 p(0.0, 0.0, 0.0);//点（0.0，0.0，0.0）
    Point_3 q(1.0, 0.0, 0.0);//点（1.0，0.0，0.0）
    Point_3 r(0.0, 1.0, 0.0);//点（0.0，1.0，0.0）
    Point_3 s(0.0, 0.0, 1.0);//点（0.0，0.0，1.0）
    //建立多面体变量P
    Polyhedron P;
    //从点p,q,r,s构建一个四面体，返回入射顶点初始化为p的四面体的半边。
    P.make_tetrahedron(p, q, r, s);

    /*--step 2. 准备输出--*/

    //将IO流std::cout的格式设置为ascii码
    CGAL::set_ascii_mode(std::cout);

    //step 2.1 输出到屏幕
    //OFF文件格式
    /*--------------------------------------------------------------------------------------------------
        OFF文件全是以OFF关键字开始的ASCII文件。
        下一行说明顶点的数量、面片的数量、边的数量。边的数量可以安全地省略。
        顶点按每行一个列出x、y、z坐标。
        在顶点列表后，面片按照每行一个列表，对于每个面片，顶点的数量是指定的，接下来是顶点索引列表。

        例如：
        OFF
        顶点数 面片数 边数(总是0)
        x y z
        x y z 
        ...
        n个顶点 顶点1的索引 顶点2的索引 … 顶点n的索引（顶点索引从0开始）
        ...
    ----------------------------------------------------------------------------------------------------*/
   //输出关键字OFF，顶点数，面数，边数（0）
    std::cout << "OFF" << std::endl << P.size_of_vertices() << ' '
        << P.size_of_facets() << " 0" << std::endl;
    //将多面体P点序列p,q,r,s连续（iterator）写入（std::copy）输出流（std::ostream）中，并打印在屏幕上
    std::copy(P.points_begin(), P.points_end(),
        std::ostream_iterator<Point_3>(std::cout, "\n"));
    //输出每个面的顶点索引列表
    for (Facet_iterator i = P.facets_begin(); i != P.facets_end(); ++i) {//迭代所有面
        Halfedge_facet_circulator j = i->facet_begin();//围绕面的半边
        CGAL_assertion(CGAL::circulator_size(j) >= 3);//使用断言检查每个面至少是三角形（有三条半边）（没有洞）
        std::cout << CGAL::circulator_size(j) << ' ';//输出面的顶点数
        do {
            std::cout << ' ' << std::distance(P.vertices_begin(), j->vertex());//通过计算两个迭代器间的距离（中间有多少个元素）计算点索引号
        } while (++j != i->facet_begin());//一个面的循环结束
        std::cout << std::endl;
    }//多面体循环结束

    //step 2.2 输出到文件
    //文件指针F
    std::ofstream F;
    //使用写方式创建并打开文件regular_tetrahedron.off    
    F.open("data/regular_tetrahedron.off");
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
    //程序结束
    return 0;
}