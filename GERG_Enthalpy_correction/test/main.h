#pragma once

#include <iostream>
#include "dlib/optimization.h"
#include "dlib/global_optimization.h"

#include "data/data.h"
#include <chrono>

// MIXTURE CORRECTION SELECTOR
//#define DATASET_NAME "dat/extended/vap/dataset_vap_123.csv"
#define DATASET_NAME "dat/extended/liq/dataset_liq_123.csv"
#define PHASE 1	// [0, 1] = [Vapour, Liquid]
#define MIXTURE_COMPS 3
#define POLY_FEATURES 5

#define MIXTURE_MOLTIPLICATOR MIXTURE_COMPS
#if MIXTURE_COMPS == 3
#define MIXTURE_MOLTIPLICATOR 6
#endif
// ---------------------------

namespace ed = enthalpy_data;

// GLOBAL VARS
extern std::vector<std::vector<double>> dataset;
extern unsigned int n_data;

// ----------------------------------------------------------------------------------------

typedef dlib::matrix<double, ed::SIZE, 1> input_vector;
typedef dlib::matrix<double, POLY_FEATURES * 2 * MIXTURE_MOLTIPLICATOR, 1> parameter_vector;

// ----------------------------------------------------------------------------------------

const double temp_c[3] =
{
	126.192, 150.687, 154.58
};

const double dens_c[3] =
{
	11.18, 13.41, 13.624
};

struct stats
{
	double mean_abs_error;
	double mean_sq_error;
	double mean_rel_error;
	double std_dev_abs_error;
	double std_dev_rel_error;
	unsigned int i_max_abs_residue;
	unsigned int i_max_abs_rel_residue;
	std::vector<std::pair<input_vector, double>> data;
};

// FUNCTONS DECLARATIONS
double model(const input_vector& input, const parameter_vector& params);
double residual(const std::pair<input_vector, double>& data, const parameter_vector& params);
stats statistics(const std::vector<std::pair<input_vector, double>>& data, const parameter_vector& params);
void print_results_to_file(std::string dataset_name, const parameter_vector& params, stats stats_results);


