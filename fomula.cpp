#include<iostream>
#include<cmath>

double Angle_dependency(
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