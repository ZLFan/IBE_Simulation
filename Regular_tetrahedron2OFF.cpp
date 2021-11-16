//����һ���������壬��off��ʽ�������Ļ��д��off�ļ�
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
    /*--step 1. ������������--*/

    //�����������4�����㣬����ΪPoint_3(const)
    Point_3 p(0.0, 0.0, 0.0);//�㣨0.0��0.0��0.0��
    Point_3 q(1.0, 0.0, 0.0);//�㣨1.0��0.0��0.0��
    Point_3 r(0.0, 1.0, 0.0);//�㣨0.0��1.0��0.0��
    Point_3 s(0.0, 0.0, 1.0);//�㣨0.0��0.0��1.0��
    //�������������P
    Polyhedron P;
    //�ӵ�p,q,r,s����һ�������壬�������䶥���ʼ��Ϊp��������İ�ߡ�
    P.make_tetrahedron(p, q, r, s);

    /*--step 2. ׼�����--*/

    //��IO��std::cout�ĸ�ʽ����Ϊascii��
    CGAL::set_ascii_mode(std::cout);

    //step 2.1 �������Ļ
    //OFF�ļ���ʽ
    /*--------------------------------------------------------------------------------------------------
        OFF�ļ�ȫ����OFF�ؼ��ֿ�ʼ��ASCII�ļ���
        ��һ��˵���������������Ƭ���������ߵ��������ߵ��������԰�ȫ��ʡ�ԡ�
        ���㰴ÿ��һ���г�x��y��z���ꡣ
        �ڶ����б����Ƭ����ÿ��һ���б�����ÿ����Ƭ�������������ָ���ģ��������Ƕ��������б�

        ���磺
        OFF
        ������ ��Ƭ�� ����(����0)
        x y z
        x y z 
        ...
        n������ ����1������ ����2������ �� ����n������������������0��ʼ��
        ...
    ----------------------------------------------------------------------------------------------------*/
   //����ؼ���OFF����������������������0��
    std::cout << "OFF" << std::endl << P.size_of_vertices() << ' '
        << P.size_of_facets() << " 0" << std::endl;
    //��������P������p,q,r,s������iterator��д�루std::copy���������std::ostream���У�����ӡ����Ļ��
    std::copy(P.points_begin(), P.points_end(),
        std::ostream_iterator<Point_3>(std::cout, "\n"));
    //���ÿ����Ķ��������б�
    for (Facet_iterator i = P.facets_begin(); i != P.facets_end(); ++i) {//����������
        Halfedge_facet_circulator j = i->facet_begin();//Χ����İ��
        CGAL_assertion(CGAL::circulator_size(j) >= 3);//ʹ�ö��Լ��ÿ���������������Σ���������ߣ���û�ж���
        std::cout << CGAL::circulator_size(j) << ' ';//�����Ķ�����
        do {
            std::cout << ' ' << std::distance(P.vertices_begin(), j->vertex());//ͨ������������������ľ��루�м��ж��ٸ�Ԫ�أ������������
        } while (++j != i->facet_begin());//һ�����ѭ������
        std::cout << std::endl;
    }//������ѭ������

    //step 2.2 ������ļ�
    //�ļ�ָ��F
    std::ofstream F;
    //ʹ��д��ʽ���������ļ�regular_tetrahedron.off    
    F.open("data/regular_tetrahedron.off");
    //����ؼ���OFF����������������������0��
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
    //�ر��ļ�
    F.close();
    //�������
    return 0;
}