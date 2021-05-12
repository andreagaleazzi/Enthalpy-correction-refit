#if 1
#include "main.h"

// GLOBAL VARS
std::vector<std::vector<double>> dataset;
unsigned int n_data;


int main(void)
{
	parse_dataset(dataset, DATASET_NAME);
	n_data = dataset.size();


	std::vector<std::pair<input_vector, double>> input_data(n_data);

	//#define BENCHMARK
#ifdef BENCHMARK
	for (int k = 0; k < 100; k++)
	{
		auto begin = std::chrono::high_resolution_clock::now();
#endif
		//#pragma omp parallel for
		for (int i = 0; i < n_data; i++)
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
#ifdef BENCHMARK
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << std::endl; //"ns" << std::endl;
	}
#endif

	parameter_vector initial_guess;
	//initial_guess = 0.;
	initial_guess = 1.;
	parameter_vector solution = initial_guess;

	for (int i = 0; i < POLY_FEATURES * 2; i++)
	{
		for (int j = 0; j < MIXTURE_MOLTIPLICATOR; j++)
		{
			double parameter = solution(i + j * 2 * POLY_FEATURES);
			if (parameter > 0)
				printf("+%.2e\t", parameter);
			else
				printf("%.2e\t", parameter);
		}
		printf("\n");
	}

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
		std::cout << model(input_data[i].first, solution) - 0 * input_data[i].second << std::endl;
	}
#else
#endif


#if 1
	dlib::solve_least_squares_lm(dlib::objective_delta_stop_strategy(1.e-20).be_verbose(),
	//dlib::solve_least_squares(dlib::gradient_norm_stop_strategy(1.e-20).be_verbose(),
		residual,
		derivative(residual),
		input_data,
		solution,
		100.);

	std::cout << std::endl << "-----------------------------" << std::endl;
	std::cout << "Solution:" << std::endl;
	for (int i = 0; i < POLY_FEATURES * 2; i++)
	{
		for (int j = 0; j < MIXTURE_MOLTIPLICATOR; j++)
		{
			double parameter = solution(i + j * 2 * POLY_FEATURES);
			if (parameter > 0)
				printf("+%.18e\t", parameter);
			else
				printf("%.18e\t", parameter);
		}
		printf("\n");
	}
	std::cout << "-----------------------------" << std::endl << std::endl;


	stats stats_results = statistics(input_data, solution);

	stats_results.data = input_data;

	print_results_to_file(DATASET_NAME, solution, stats_results);

#endif


	return 1;
}
#endif