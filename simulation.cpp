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

class Material
{
private:
	enum MKind { SCD };
	MKind kind = MKind(0);

	Point_set point_set;//是哈希表

	int point_set_density;
	double atomic_density = 0.293;
	double surface_banding_energy = 6.67;
public:
	Material();
	Material(Point_set point_set, MKind kind, int point_set_density)
	{
		this->point_set = point_set;
		this->kind = kind;
		switch (kind)
		{
		case 0:
		{
			this->atomic_density = 0.293;
			this->surface_banding_energy = 6.67;
		}
		default:
		{
			this->atomic_density = 0.293;
			this->surface_banding_energy = 6.67;
		}
		}
		this->point_set_density = point_set_density;

	}
	bool SetPoint_set(Point_set ps)
	{
		this->point_set = ps;
		return true;
	}
	bool SetKind(MKind kind)
	{
		this->kind = kind;

		switch (kind)
		{
		case 0:
		{
			this->atomic_density = 0.293;
			this->surface_banding_energy = 6.67;
		}
		default:
		{
			this->atomic_density = 0.293;
			this->surface_banding_energy = 6.67;
		}
		}

		return true;
	}
	bool SetPoint_set_density(int psd)
	{
		this->point_set_density = psd;
		return true;
	}

	bool GetPoint_set(Point_set& ps)
	{
		ps = this->point_set;
		return true;
	}
	bool GetKind(MKind&k, double &ad, double &sbe)
	{
		k = this->kind;
		ad = this->atomic_density;
		sbe = this->surface_banding_energy;
		return true;
	}
	bool Add_point(Point_set &point_set, Point point)
	{
		point_set.insert(Point(point));
		point_set.add_normal_map();
		return true;
	}
	bool Add_point_vector(Point_set& point_set, Point point, Vector vector)
	{
		point_set.insert(Point(point), Vector(vector));
		return true;
	}
	bool Delete_point(Point_set& point_set,int index)
	{
		Point_set::iterator it = point_set.begin();
		point_set.remove(it + index);
		return true;
	}
};
class Ion
{
private:
	enum IKind {Ar};
	IKind kind = IKind(0);
	double energy;
	double theta;//incidence angle
public:
	Ion();
	Ion(IKind kind, double energy, double theta)
	{
		this->kind = kind;
		this->energy = energy;
		this->theta = theta;
	}
	bool Getkind(IKind& kind)
	{
		kind = this->kind;
		return 0;
	}
	bool GetEnergy(double& energy)
	{
		energy = this->energy;
		return 0;
	}
	bool GetAngle(double& theta)
	{
		theta = this->theta;
		return ture;
	}
};
class IO
{
private:
	std::string ipath;
	std::string opath;
public:
	IO();
	bool SetIpath(std::string ipath)
	{
		this->ipath = ipath;
		return true;
	}
	bool SetOpath(std::string opath)
	{
		this->opath = opath;
		return true;
	}
	bool GetIpath(std::string &ipath)
	{
		ipath = this->ipath;
		return true;
	}
	bool GetOpath(std::string &opath)
	{
		opath = this->opath;
		return true;
	}
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
	void print_point_set(Point_set point_cloud)
	{
		std::cout << "Content of point set: " << std::endl;
		//使用迭代器遍历容器并打印点坐标
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
};
class Simulation :public Ion, public Material
{
private:
	double alpha;
	double beta;
public:
	Simulation();

	bool SetAlpha(double alpha)
	{
		this->alpha = alpha;
		return 0;
	}
	bool SetBeta(double beta)
	{
		this->beta = beta;
		return 0;
	}
	bool GetAlpha(double &alpha)
	{
		alpha = this->alpha;
		return 0;
	}
	bool GetBeta(double &beta)
	{
		beta = this->beta;
		return 0;
	}
	/* IBE Simulation Algorithm */
	double AngleDependency(
		double ion_E, //E
		double surface_banding_E, //U
		double atomic_E, //N
		double projected_E_range, //a
		double theta,
		double alpha,
		double beta
	)
	{
		double& E = ion_E;
		double& U = surface_banding_E;
		double& N = atomic_E;
		double& a = projected_E_range;
		double PI = 3.14159265;
		double cos_2_theta = cos(theta) * cos(theta);
		double sin_2_theta = sin(theta) * sin(theta);
		double A = (alpha * alpha * cos_2_theta) + (beta * beta * sin_2_theta);
		double yield = exp(0 - ((cos_2_theta * a * a) / (2 * A))) * ((E) / (U * N * sqrt(2 * PI * A)));
		return yield;
	}
	bool StepEtch()
	{}
	bool SurfaceReconstruction()
	{}
};


int main()
{
	return 0;
}