#pragma once

#include <array>
#include <vector>
#include "csv_parser.h"


//std::array<std::array<double, 15>, 651> input_data;
//std::vector<std::vector<double>> enthalpy_dataset;

void parse_dataset(std::vector<std::vector<double>> & dataset, std::string filename);

namespace enthalpy_data
{
	enum input_data_enum
	{
		P1,         // [kPa]
		P2,         // [kPa]
		T1,         // [K]
		T2,         // [K]
		zN2,
		zAr,
		zO2,
		alpha1_ref,
		alpha2_ref,
		alpha1_rival,
		alpha2_rival,
		d1_ref,     // [mol/L]
		d2_ref,     // [mol/L]
		d1_rival,   // [mol/L]
		d2_rival,   // [mol/L]
		DH_ref,     // [kJ/kmol]
		DH_rival,   // [kJ/kmol]
		SIZE
	};


	//extern std::vector<std::vector<double>> dataset_1;
	//extern std::vector<std::vector<double>> dataset_2;
	//extern std::vector<std::vector<double>> dataset_3;
	//extern std::vector<std::vector<double>> dataset_12;
	//extern std::vector<std::vector<double>> dataset_13;
	//extern std::vector<std::vector<double>> dataset_23;
	//extern std::vector<std::vector<double>> dataset_123;
}