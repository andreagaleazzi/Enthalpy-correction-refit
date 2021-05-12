#include "main.h"
#include <ostream>


void print_statistics_to_file_at(std::ofstream & file, int i, const parameter_vector& params, stats stats_results)
{
	file
		<< "N2 = " << stats_results.data[i].first(ed::zN2) << std::endl
		<< "Ar = " << stats_results.data[i].first(ed::zAr) << std::endl
		<< "O2 = " << stats_results.data[i].first(ed::zO2) << std::endl
		<< "T1 = " << stats_results.data[i].first(ed::T1) << std::endl
		<< "T2 = " << stats_results.data[i].first(ed::T2) << std::endl
		<< "P1 = " << stats_results.data[i].first(ed::P1) << std::endl
		<< "P2 = " << stats_results.data[i].first(ed::P2) << std::endl
		<< "a1 = " << stats_results.data[i].first(ed::alpha1_ref) << std::endl
		<< "a2 = " << stats_results.data[i].first(ed::alpha2_ref) << std::endl
		<< "DH_ref   = " << stats_results.data[i].first(ed::DH_ref) << std::endl
		<< "DH_rival = " << stats_results.data[i].first(ed::DH_rival) << std::endl
		<< "DH_corr  = " << model(stats_results.data[i].first, params) << std::endl
		<< std::endl
		<< "abs_error = " << abs(model(stats_results.data[i].first, params) - stats_results.data[i].second) << std::endl
		<< "rel_error = " << (abs(model(stats_results.data[i].first, params) - stats_results.data[i].second) / stats_results.data[i].second) * 100. << " %"
		<< std::endl
		<< std::endl;
}

void print_results_to_file(std::string dataset_name, const parameter_vector& solution, stats stats_results)
{
	std::ofstream file;
	file.open(dataset_name + "_res.dat");

	file << "Solution matrix" << std::endl;
	for (int i = 0; i < POLY_FEATURES * 2; i++)
		{
			for (int j = 0; j < MIXTURE_MOLTIPLICATOR; j++)
			{
				double parameter = solution(i + j * POLY_FEATURES * 2);
				if (parameter > 0)
					file << "+" << std::scientific << std::setprecision(18) << parameter << "\t";	// "+%.18e\t"
				else
					file << std::scientific << std::setprecision(18) << parameter << "\t";			// "-%.18e\t"
			}
			file << std::endl;
		}


	file << std::endl << std::endl << std::endl;
	file << "Solution benchmark" << std::endl;
	file << std::fixed << std::setprecision(6);
	file << "mean_abs_error\t" << stats_results.mean_abs_error << std::endl;
	file << "mean_sq_error\t" << stats_results.mean_sq_error << std::endl;
	file << "mean_rel_error\t" << stats_results.mean_rel_error * 100. << " %" << std::endl;
	file << std::endl;
	file << "std_dev_abs_error\t" << stats_results.std_dev_abs_error << std::endl;
	file << "std_dev_rel_error\t" << stats_results.std_dev_rel_error * 100. << " %" << std::endl;
	file << std::endl;

	file << "-> Max abs error" << std::endl;
	print_statistics_to_file_at(file, stats_results.i_max_abs_residue, solution, stats_results);
	file << "-> Max rel error" << std::endl;
	print_statistics_to_file_at(file, stats_results.i_max_abs_rel_residue, solution, stats_results);

	file.close();
}


