#include <iostream>
#include "dlib/optimization.h"
#include "dlib/global_optimization.h"

// ----------------------------------------------------------------------------------------

typedef dlib::matrix<double, 3, 1> input_vector;
typedef dlib::matrix<double, 3, 1> parameter_vector;

// ----------------------------------------------------------------------------------------


double model_test(const input_vector & input, const parameter_vector & params)
{
	double x = input(0);
	double y = input(1);
	double z = input(2);

	double a = params(0);
	double b = params(1);
	double c = params(2);

	return (a * x*x + b * y*y + c * z*z + 1.);
}

double residual_test(const std::pair<input_vector, double>& data, const parameter_vector& params)
{
	return model_test(data.first, params) - data.second;
}



int main(void)
{
	std::vector<std::pair<input_vector, double>> data(6);

	//-------------------
	data[0].first(0) = 1;
	data[1].first(0) = 1;
	data[2].first(0) = 2;
	data[3].first(0) = 2;
	data[4].first(0) = 3;
	data[5].first(0) = 3;

	data[0].first(1) = 2;
	data[1].first(1) = 3;
	data[2].first(1) = 1;
	data[3].first(1) = 3;
	data[4].first(1) = 1;
	data[5].first(1) = 2;

	data[0].first(2) = 3;
	data[1].first(2) = 2;
	data[2].first(2) = 3;
	data[3].first(2) = 1;
	data[4].first(2) = 2;
	data[5].first(2) = 1;

	data[0].second = 35.9882;
	data[1].second = 41.0358;
	data[2].second = 41.9193;
	data[3].second = 50.3769;
	data[4].second = 56.9147;
	data[5].second = 60.0747;
	//-------------------


	parameter_vector x;
	x = 6.;

#ifdef MANUAL_BACKUP
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << data[i].first(j) << "\t";
		}
			std::cout << data[i].second << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < data.size(); i++)
	{
		std::cout << model_test(data[i].first, x) - data[i].second << std::endl;
	}
#endif

#ifndef MAUAL_DEBUG
	dlib::solve_least_squares_lm(dlib::objective_delta_stop_strategy(1e-7).be_verbose(),
		residual_test,
		derivative(residual_test),
		data,
		x);


	std::cout << x << std::endl;
#endif


	return 1;
}