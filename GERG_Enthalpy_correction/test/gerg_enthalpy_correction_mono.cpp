#include <iostream>
#include "dlib/optimization.h"
#include "dlib/global_optimization.h"

#include "../dat/data.h"
#include <chrono>

namespace ed = enthalpy_data;

std::vector<std::vector<double>> dataset = ed::dataset_12;

int n_data = dataset.size();
// ----------------------------------------------------------------------------------------

typedef dlib::matrix<double, ed::SIZE, 1> input_vector;
typedef dlib::matrix<double, 4 * 2 * 2, 1> parameter_vector;

// ----------------------------------------------------------------------------------------

const double temp_c[3] =
{
	126.192, 150.687, 154.58
};

const double dens_c[3] =
{
	11.18, 13.41, 13.624
};

double model_test(const input_vector& input, const parameter_vector& params)
{
	double DHr[2] = { 0., 0. };

	const double a[4] = { params(0), params(1), params(2), params(3) };
	const double c[4] = { params(4), params(5), params(6), params(7) };

	//std::cout << input << std::endl;
#if 1
	const double temp[2] = { input(ed::T1), input(ed::T2) };
	const double pres[2] = { input(ed::P1), input(ed::P2) };
	const double dens[2] = { input(ed::d1_rival), input(ed::d2_rival) };
	const double comp[3] = { input(ed::zN2), input(ed::zAr), input(ed::zO2) };
	const double DH = input(ed::DH_rival);


	const double temp_c_mix =
		+temp_c[0] * comp[0]
		+ temp_c[1] * comp[1]
		+ temp_c[2] * comp[2];

	const double dens_c_mix =
		+dens_c[0] * comp[0]
		+ dens_c[1] * comp[1]
		+ dens_c[2] * comp[2];

	double tau_print[2] = { 0., 0. };
	double delta_print[2] = { 0., 0. };

	for (int k = 0; k < 2; k++)
	{

		const double tau = temp_c_mix / temp[k];
		tau_print[k] = tau;

		const double delta = dens[k] / dens_c_mix;
		delta_print[k] = delta;

		const double tau2 = tau * tau;
		const double tau3 = tau * tau * tau;
		const double tau4 = tau * tau * tau * tau;

		const double delta2 = delta * delta;
		const double delta3 = delta * delta * delta;
		const double delta4 = delta * delta * delta * delta;

		{ // MONO CORRECTION
			for (int i = 0; i < 3; i++)
			{
				DHr[k] += (comp[i])
					*
					(a[0]
						+ tau * a[1]
						+ tau2 * a[2]
						+ tau3 * a[3])
					*
					(c[0]
						+ delta * c[1]
						+ delta2 * c[2]
						+ delta3 * c[3]);
			}
		}

		//{ // BINARY CORRECTION
		//	int i_[6] = { 0, 0, 1, 1, 2, 2 };
		//	int j_[6] = { 1, 2, 2, 0, 0, 1 };

		//	for (int n = 0; n < 6; n++)
		//	{
		//		r += (comp[i_[n]] * comp[i_[n]] * comp[j_[n]])
		//			*
		//			(a[0][n + 3]
		//				+ tau * a[1][n + 3]
		//				+ tau2 * a[2][n + 3]
		//				+ tau3 * a[3][n + 3])
		//			*
		//			(c[0][n + 3]
		//				+ delta * c[1][n + 3]
		//				+ delta2 * c[2][n + 3]
		//				+ delta3 * c[3][n + 3]);
		//	}
		//}

		//{ // TERNARY CORRECTION
		//	int i_[6] = { 0, 1, 2, 0, 1, 2 };
		//	int j_[6] = { 1, 0, 1, 2, 2, 0 };
		//	int k_[6] = { 2, 2, 0, 1, 0, 1 };

		//	for (int n = 0; n < 6; n++)
		//	{
		//		r += (comp[i_[n]] * comp[i_[n]] * comp[i_[n]] * comp[j_[n]] * comp[j_[n]] * comp[k_[n]])
		//			*
		//			(a[0][n + 3 + 6]
		//				+ tau * a[1][n + 3 + 6]
		//				+ tau2 * a[2][n + 3 + 6]
		//				+ tau3 * a[3][n + 3 + 6])
		//			*
		//			(c[0][n + 3 + 6]
		//				+ delta * c[1][n + 3 + 6]
		//				+ delta2 * c[2][n + 3 + 6]
		//				+ delta3 * c[3][n + 3 + 6]);
		//	}
		//}
	}

#if 0
	std::cout <<
		"tau1" << "\t" <<
		"tau2" << "\t" <<
		"delta1" << "\t" <<
		"delta2" << "\t" <<
		"DHr1" << "\t" <<
		"DHr2" <<
		std::endl;

	std::cout <<
		tau_print[0] << "\t" <<
		tau_print[1] << "\t" <<
		delta_print[0] << "\t" <<
		delta_print[1] << "\t" <<
		DHr[0] << "\t" <<
		DHr[1] <<
		std::endl;
#endif
	return DH + DHr[1] - DHr[0];
#else
	return 0;
#endif
}

double residual_test(const std::pair<input_vector, double>& data, const parameter_vector& params)
{
#if 1
	double weight = 1.;

	double temp = data.first(ed::T1);
	double pres = data.first(ed::P1);

	//double w1 = 3.;
	//double w2 = 1.5;
	//double w3 = 0.6;

	double w1 = 10.;
	double w2 = 5.;
	double w3 = 0.25;
	double w4 = 0.6;

	if (pres < 1000 && temp < 120) {
		if (pres > 100 && temp > 77) {

			if (pres < 600 && temp < 100) {
				weight = w1;
			}
			else {
				weight = w2;
			}
		}
		else {
			weight = w4;
		}
	}
	else {
		weight = w3;

	}


	//static int counter = 1;
	//std::cout << "count" << '\t' << "temp" << '\t' << "pres" << '\t' << "weight" << std::endl;
	//std::cout << counter << '\t' << temp << '\t' << pres << '\t' << weight << std::endl;
	//counter++;

	//if (counter > 100)
	//getchar();

	return sqrt(weight) * (model_test(data.first, params) - data.second) / n_data;
#else
	return (model_test(data.first, params) - data.second) / n_data;
#endif
}



int main(void)
{

	std::vector<std::pair<input_vector, double>> input_data(dataset.size());


	auto begin = std::chrono::high_resolution_clock::now();

	//#pragma omp parallel for
	for (int i = 0; i < dataset.size(); i++)
	{
		input_data[i].first(ed::P1) = dataset[i][ed::P1];
		input_data[i].first(ed::P2) = dataset[i][ed::P2];
		input_data[i].first(ed::T1) = dataset[i][ed::T1];
		input_data[i].first(ed::T2) = dataset[i][ed::T2];
		input_data[i].first(ed::zN2) = dataset[i][ed::zN2];
		input_data[i].first(ed::zAr) = dataset[i][ed::zAr];
		input_data[i].first(ed::zO2) = dataset[i][ed::zO2];
		input_data[i].first(ed::alpha2_ref) = dataset[i][ed::alpha2_ref];
		input_data[i].first(ed::alpha2_rival) = dataset[i][ed::alpha2_rival];
		input_data[i].first(ed::d1_ref) = dataset[i][ed::d1_ref];
		input_data[i].first(ed::d2_ref) = dataset[i][ed::d2_ref];
		input_data[i].first(ed::d1_rival) = dataset[i][ed::d1_rival];
		input_data[i].first(ed::d2_rival) = dataset[i][ed::d2_rival];
		input_data[i].first(ed::DH_ref) = dataset[i][ed::DH_ref];
		input_data[i].first(ed::DH_rival) = dataset[i][ed::DH_rival];

		input_data[i].second = dataset[i][ed::DH_ref];
	}

	auto end = std::chrono::high_resolution_clock::now();
	//std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;

	//x = { -2.554880759, 1.471228167, 1.34775077, -0.596306379, -6.079246061, -4.126438287, -0.892860118, 3.861231704 };
	parameter_vector initial_guess;
	initial_guess = { 1., 0., 0., 0., 1., 0., 0., 0. };
	parameter_vector solution = initial_guess;



#if 0
	for (int i = 0; i < input_data.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << input_data[i].first(j) << "\t";
		}
		std::cout << input_data[i].second << std::endl;
	}

	std::cout << std::endl;
	for (int i = 200; i < 220; i++)
	{
		for (int j = 0; j < ed::SIZE; j++)
		{
			std::cout << dataset[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < input_data.size(); i++)
	{
		std::cout << model_test(input_data[i].first, x) - 0 * input_data[i].second << std::endl;
	}
#else
#endif



#if 1
	dlib::solve_least_squares_lm(dlib::objective_delta_stop_strategy(1.e-10).be_verbose(),
		residual_test,
		derivative(residual_test),
		input_data,
		solution);

	std::cout << std::endl << "-----------------------------" << std::endl;
	std::cout << "Solution:" << std::endl;
	for (int i = 0; i < initial_guess.size(); i++)
	{
		printf("%.18e\n", solution(i));
	}
	std::cout << "-----------------------------" << std::endl;
#endif


	return 1;
}