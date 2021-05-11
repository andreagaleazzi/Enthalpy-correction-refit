#include "data.h"

#include <iostream>

namespace csv = aria::csv;
typedef aria::csv::CsvParser csv_parser;


void parse_dataset(std::vector<std::vector<double>>& dataset, std::string filename)
{
	std::ifstream f(filename);
	csv_parser parser(f);

	for (auto& row : parser)
	{
		std::vector<double> temp_vec;
		for (auto& field : row)
		{
			temp_vec.push_back(std::stod(field));
		}
		dataset.push_back(temp_vec);
	}
}