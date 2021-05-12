#include "main.h"

double residual(const std::pair<input_vector, double>& data, const parameter_vector& params)
{
#if 0
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

	//double w1 = 100.;
	//double w2 = 50.;
	//double w3 = 1.;
	//double w4 = 0.5;

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

	return sqrt(weight) * (model(data.first, params) - data.second) / n_data;
#else
	//return (model(data.first, params) - data.second) / n_data;
	//return (model(data.first, params) - data.second) / n_data;
	return (model(data.first, params) - data.second);
#endif
}