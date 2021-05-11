#include "main.h"
#include <algorithm>

// AUX functions
double smart_frac(double a, double b)
{
	if (b != 0)
		return a / b;
	else
		return 0.;
}

double pow2(double a)
{
	return a * a;
}

void print_statistics_at(int i, const std::vector<std::pair<input_vector, double>>& data, const parameter_vector& params)
{
	std::cout
		<< "N2 = " << data[i].first(ed::zN2) << std::endl
		<< "Ar = " << data[i].first(ed::zAr) << std::endl
		<< "O2 = " << data[i].first(ed::zO2) << std::endl
		<< "T1 = " << data[i].first(ed::T1) << std::endl
		<< "T2 = " << data[i].first(ed::T2) << std::endl
		<< "P1 = " << data[i].first(ed::P1) << std::endl
		<< "P2 = " << data[i].first(ed::P2) << std::endl
		<< "a1 = " << data[i].first(ed::alpha1_ref) << std::endl
		<< "a2 = " << data[i].first(ed::alpha2_ref) << std::endl
		<< "DH_ref   = " << data[i].first(ed::DH_ref) << std::endl
		<< "DH_rival = " << data[i].first(ed::DH_rival) << std::endl
		<< "DH_corr  = " << model(data[i].first, params) << std::endl
		<< std::endl
		<< "abs_error = " << abs(model(data[i].first, params) - data[i].second) << std::endl
		<< "rel_error = " << (abs(model(data[i].first, params) - data[i].second) / data[i].second) * 100. << " %"
		<< std::endl
		<< std::endl;
}


// PRIMARY FUNCTION
stats statistics(const std::vector<std::pair<input_vector, double>>& data, const parameter_vector& params)
{
	stats result;
	// --------- Brainstorming ---------
	// MIX TYPE
	// PHASE

	// Mean abs error
	// Mean squared error
	// Mean relative error

	// Std deviation abs error
	// Std deviation squared error
	// Std deviation relative error

	// Max relative error - with T, P, x

	// Max abs error - with T, P, x
	// ---------------------------------


	std::vector<double> abs_residue(n_data);
	std::vector<double> abs_rel_residue(n_data);

	for (auto i = 0; i < n_data; i++)
	{
		abs_residue[i] = abs(model(data[i].first, params) - data[i].second);
	}

	double sum_abs_error = 0.;
	double sum_sq_error = 0.;
	double sum_rel_error = 0.;
	double sum_rel_sq_error = 0.;

	//double mean_abs_error = 0.;
	//double mean_sq_error = 0.;
	//double mean_rel_error = 0.;

	for (auto i = 0; i < n_data; i++)
	{
		sum_abs_error += abs(abs_residue[i]);
		sum_sq_error += abs_residue[i] * abs_residue[i];
		abs_rel_residue[i] = smart_frac(abs_residue[i], data[i].second);
		sum_rel_error += abs_rel_residue[i];
		sum_rel_sq_error += pow2(abs_rel_residue[i]);
	}

	// MEAN
	result.mean_abs_error = sum_abs_error / n_data;
	result.mean_sq_error = sum_sq_error / n_data;
	result.mean_rel_error = sum_rel_error / n_data;

	// STD DEV
	result.std_dev_abs_error = sqrt((sum_sq_error / double(n_data - 1)));
	result.std_dev_rel_error = sqrt((sum_rel_sq_error / double(n_data - 1)));

	// MAX
	auto max_abs_residue = std::max_element(abs_residue.begin(), abs_residue.end());
	auto max_abs_rel_residue = std::max_element(abs_rel_residue.begin(), abs_rel_residue.end());

	result.i_max_abs_residue = std::distance(abs_residue.begin(), max_abs_residue);
	result.i_max_abs_rel_residue = std::distance(abs_rel_residue.begin(), max_abs_rel_residue);


	std::cout << "mean_abs_error\t\t= " << result.mean_abs_error << std::endl;
	std::cout << "mean_sq_error\t\t= " << result.mean_sq_error << std::endl;
	std::cout << "mean_rel_error\t\t= " << result.mean_rel_error * 100. << " %" << std::endl;
	std::cout << std::endl;
	std::cout << "std_dev_abs_error\t= " << result.std_dev_abs_error << std::endl;
	std::cout << "std_dev_rel_error\t= " << result.std_dev_rel_error * 100. << " %" << std::endl;
	std::cout << std::endl;

	std::cout << "-> max abs error:" << std::endl << "---------------" << std::endl;
	print_statistics_at(result.i_max_abs_residue, data, params);
	std::cout << "-> max rel error:" << std::endl << "---------------" << std::endl;
	print_statistics_at(result.i_max_abs_rel_residue, data, params);

	return result;
}