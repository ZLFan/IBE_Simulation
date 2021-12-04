#include<iostream>
#include<string>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Point_set_3.h>
#include<fstream>
#include<limits>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::FT FT;
typedef Kernel::Point_3 Point;
typedef Kernel::Vector_3 Vector;
typedef CGAL::Point_set_3<Point> Point_set;

bool point_set_read_ply(std::string ipath, Point_set &point_cloud)
{
	std::ifstream f(ipath, std::ios_base::binary);
	if (!CGAL::IO::read_PLY(f, point_cloud))
	{
		std::cerr << "Can not read input file " << std::endl;
		return false;
	}
	return true;
}
void print_point_set(Point_set point_cloud)
{
	std::cout << "Content of point set: " << std::endl;
	//ʹ�õ�����������������ӡ������
	for (Point_set::const_iterator it = point_cloud.begin(); it != point_cloud.end(); it++)
	{
		std::cout << "* Point " << *it << ":" << point_cloud.point(*it) << std::endl;
	}
}
bool point_set_write_ply(std::string opath, Point_set point_cloud)
{
	std::ofstream f(opath, std::ios_base::binary);
	if (!CGAL::IO::write_PLY(f, point_cloud))
	{
		std::cerr << "Can not write input file " << std::endl;
		return false;
	}
	return true;
}
int main()
{
	Point_set point_cloud;
	std::string ipath = "data/cube.ply";
	point_set_read_ply(ipath, point_cloud);
	//���㲻��������ı�����ʱ��ɾȥ
	for (Point_set::const_iterator it = point_cloud.begin(); it != point_cloud.end(); it++)
	{
		Point p = point_cloud.point(*it);
		if (p.x() == 1 || p.x() == 0 || p.y() == 1 || p.y() == 0 || p.z() == 1 || p.z() == 0)
		{
			std::cout<<"retain" << std::endl;
		}
		else
		{
			point_cloud.remove(*it);//�ڵ㼯��ȥ��it��ָ��ĵ㣬ɾ��ֻ�ǽ��������ɾ��
			std::cout << "remove!" << std::endl;
		}
	}
	//��ӡ�ѹ��˵ĵ���
	print_point_set(point_cloud);
	//����ָ���ļ�
	std::string opath = "data/clear_cube.ply";
	point_set_write_ply(opath, point_cloud);
	return 0;
}
