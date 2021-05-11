#include "main.h"

double model(const input_vector& input, const parameter_vector& params)
{
	double DHr[2] = { 0., 0. };


#if MIXTURE_COMPS == 1
	const double a[5][3] =
	{
		{params(0), params(0), params(0)},
		{params(1), params(1), params(1)},
		{params(2), params(2), params(2)},
		{params(3), params(3), params(3)},
		{params(4), params(4), params(4)}
	};
	const double c[5][3] =
	{
		{params(5), params(5), params(5)},
		{params(6), params(6), params(6)},
		{params(7), params(7), params(7)},
		{params(8), params(8), params(8)},
		{params(9), params(9), params(9)}
	};
#elif MIXTURE_COMPS == 2
#if PHASE == 0
	const double a[4][9] =
	{
		{ -2.287662830756571619e+00, -2.917655225508358541e+01, +2.600914739832605793e+00, params(0), params(0), params(0), params(+8), params(+8), params(+8) },
		{ -1.865307235105757755e+01, +5.964660375338181098e+01, -1.592582189291046468e+01, params(1), params(1), params(1), params(+9), params(+9), params(+9) },
		{ +3.259334469263008316e+01, -5.781719751720459044e+01, +2.537412074819967245e+01, params(2), params(2), params(2), params(10), params(10), params(10) },
		{ -1.042531845193346207e+01, +2.099336101248989550e+01, -9.914281176385982164e+00, params(3), params(3), params(3), params(11), params(11), params(11) }
	};
	const double c[4][9] =
	{
		{ -9.163306778761944882e-01, +5.899468318022441649e-01, -2.323432362461590461e+00, params(4), params(4), params(4), params(12), params(12), params(12) },
		{ -3.209031207309156741e+01, +7.109108829377028371e+01, +2.610268276683601485e+01, params(5), params(5), params(5), params(13), params(13), params(13) },
		{ +2.128694362043479060e+01, -4.106254525765723429e+01, -2.616025733450331003e+01, params(6), params(6), params(6), params(14), params(14), params(14) },
		{ -3.190132905926373219e+00, +5.137319620672425202e+00, +7.031600832700084069e+00, params(7), params(7), params(7), params(15), params(15), params(15) }
	};
#elif PHASE == 1
	const double a[4][9] =
	{
		{ +1.038837346959432750e+01, +2.577798755895314642e+01, +1.539691754953515357e+01, params(0), params(0), params(0), params(+8), params(+8), params(+8) },
		{ -2.712919266127455487e+01, -4.233189397507788954e+01, -9.430369449457735698e+01, params(1), params(1), params(1), params(+9), params(+9), params(+9) },
		{ +2.225308665848538325e+01, +2.516479973435729178e+01, +1.212385787388160026e+02, params(2), params(2), params(2), params(10), params(10), params(10) },
		{ -5.619762077624848473e+00, -5.175063182339798118e+00, -3.674191417593289088e+01, params(3), params(3), params(3), params(11), params(11), params(11) }
	};
	const double c[4][9] =
	{
		{ +3.160574832255711453e+00, +2.204306985296913624e+01, +1.508187386184534660e+02, params(4), params(4), params(4), params(12), params(12), params(12) },
		{ -3.629363394615641170e+01, -4.472747748490262154e+01, -8.290417043167140898e-01, params(5), params(5), params(5), params(13), params(13), params(13) },
		{ +1.734038264381736694e+00, +1.889379336707157908e-01, -5.121483172378324156e+01, params(6), params(6), params(6), params(14), params(14), params(14) },
		{ +7.890091647163401944e+00, +2.786303437248713877e+01, +1.249500695137454898e+01, params(7), params(7), params(7), params(15), params(15), params(15) }
	};
#endif
#elif MIXTURE_COMPS == 3
#if PHASE == 0
	const double a[4][15] =
	{
		{ -2.287662830756571619e+00, -2.917655225508358541e+01, +2.600914739832605793e+00, +2.023375344429418305e+02, -9.724457373587652498e+00, +2.258992266338437389e+02, +1.151246887964175301e+02, +1.975212429643667917e+02, -6.035234183848736222e+01, params(0), params(+8), params(16), params(24), params(32), params(40) },
		{ -1.865307235105757755e+01, +5.964660375338181098e+01, -1.592582189291046468e+01, -1.821972998534123462e+02, +3.670105002569225690e+02, -1.634812564099219117e+02, +3.804536199213036411e+02, -1.021100600172382428e+03, +4.468650654736296133e+02, params(1), params(+9), params(17), params(25), params(33), params(41) },
		{ +3.259334469263008316e+01, -5.781719751720459044e+01, +2.537412074819967245e+01, -4.985041565775981809e+01, -5.556498130652472582e+02, -2.638672691438570723e+02, -9.646075202034650147e+02, +1.377059036048933649e+03, -7.323952149342364919e+02, params(2), params(10), params(18), params(26), params(34), params(42) },
		{ -1.042531845193346207e+01, +2.099336101248989550e+01, -9.914281176385982164e+00, +6.338711520680066513e+01, +1.943453960339217303e+02, +2.100683993484429379e+02, +4.858461195751974060e+02, -5.367158464687856849e+02, +2.980055717773525430e+02, params(3), params(11), params(19), params(27), params(35), params(43) }
	};
	const double c[4][15] =
	{
		{ -9.163306778761944882e-01, +5.899468318022441649e-01, -2.323432362461590461e+00, +1.241833124538831712e-01, -6.855149047286019925e-01, -6.266062282462726840e-02, -1.408049625433240859e-01, +7.575729162032449060e-02, -7.027460328374451892e-01, params(4), params(12), params(20), params(28), params(36), params(44) },
		{ -3.209031207309156741e+01, +7.109108829377028371e+01, +2.610268276683601485e+01, +1.441079034853976992e+01, +4.098189854638872021e+01, -7.967496002977317637e+00, +4.247326553399885185e+00, +4.346895712815158852e+00, +5.710913344991640628e+01, params(5), params(13), params(21), params(29), params(37), params(45) },
		{ +2.128694362043479060e+01, -4.106254525765723429e+01, -2.616025733450331003e+01, -8.678731181259445648e+00, -4.170843352829085120e+02, +3.717632132055690022e+02, +7.636799014930893748e+01, -4.774228420723650288e+02, -4.140495565757174177e+02, params(6), params(14), params(22), params(30), params(38), params(46) },
		{ -3.190132905926373219e+00, +5.137319620672425202e+00, +7.031600832700084069e+00, +3.636366267913133470e+02, +9.955562493921718215e+02, +5.142955160285526972e+02, +1.262891601201916274e+03, +1.729289364752951542e+03, +9.010021785451707501e+02, params(7), params(15), params(23), params(31), params(39), params(47) }
	};
#elif PHASE == 1
	const double a[4][15] =
	{
		{ +1.038837346959432750e+01, +2.577798755895314642e+01, +1.539691754953515357e+01, +3.615683989625046024e+01, +7.492862541788818831e+00, -9.331041460438787283e+01, +5.116295387867545941e+01, -6.595833045118749283e+01, +1.365506277354415943e+02, params(0), params(+8), params(16), params(24), params(32), params(40) },
		{ -2.712919266127455487e+01, -4.233189397507788954e+01, -9.430369449457735698e+01, -5.944651073289499976e+01, +7.525900792832446484e+01, +1.101802272848049995e+02, +3.561923654036586839e+01, +8.672666700753671876e+01, +1.531397435877209112e+01, params(1), params(+9), params(17), params(25), params(33), params(41) },
		{ +2.225308665848538325e+01, +2.516479973435729178e+01, +1.212385787388160026e+02, +3.711206142494182103e+01, -9.344945555314954788e+01, -6.369324689122454686e+01, -3.811419104377760902e+01, -6.247174043534655397e+01, +8.012614096297835431e+01, params(2), params(10), params(18), params(26), params(34), params(42) },
		{ -5.619762077624848473e+00, -5.175063182339798118e+00, -3.674191417593289088e+01, -7.904756789572012998e+00, +3.885199713416388079e+01, +1.257301688935125128e+01, +3.649214697715805755e+01, +1.467886018917653423e+01, -1.943459779306192914e+01, params(3), params(11), params(19), params(27), params(35), params(43) }
	};
	const double c[4][15] =
	{
		{ +3.160574832255711453e+00, +2.204306985296913624e+01, +1.508187386184534660e+02, +3.839948591530574618e+01, +1.141050227316819559e+02, -9.700164245143962205e+01, +8.007309156349141688e+01, -1.082299611421554602e+02, +1.339606083500549403e+02, params(4), params(12), params(20), params(28), params(36), params(44) },
		{ -3.629363394615641170e+01, -4.472747748490262154e+01, -8.290417043167140898e-01, -1.458866551432055347e+00, -8.332140500697354568e+00, +1.115206812064812283e+02, +2.027055170352477731e+01, +2.973939116259901638e+01, -4.277809407489943538e+00, params(5), params(13), params(21), params(29), params(37), params(45) },
		{ +1.734038264381736694e+00, +1.889379336707157908e-01, -5.121483172378324156e+01, +7.878681614029096636e+01, +1.670104052599524991e+01, -6.549137911888125529e+01, -4.590665123424364680e+01, -2.756996920427734210e+01, +8.889481260314967415e+01, params(6), params(14), params(22), params(30), params(38), params(46) },
		{ +7.890091647163401944e+00, +2.786303437248713877e+01, +1.249500695137454898e+01, -3.030706474604291145e+01, -2.507024589336061204e+00, +1.276363621956404337e+01, +1.227341639622935077e+01, +7.558645699824420916e+00, -2.290381308826119167e+01, params(7), params(15), params(23), params(31), params(39), params(47) }
	};
#endif
#endif


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
		const double tau3 = tau * tau2;
		const double tau4 = tau * tau3;
		const double tau5 = tau * tau4;

		const double delta2 = delta * delta;
		const double delta3 = delta * delta2;
		const double delta4 = delta * delta3;
		const double delta5 = delta * delta4;

		{ // MONO CORRECTION
			for (int i = 0; i < 3; i++)
			{
				DHr[k] += (comp[i])
					*
					(a[0][i]
						+ tau * a[1][i]
						+ tau2 * a[2][i]
						+ tau3 * a[3][i]
						+ tau4 * a[4][i])
					*
					(c[0][i]
						+ delta * c[1][i]
						+ delta2 * c[2][i]
						+ delta3 * c[3][i]
						+ delta4 * c[4][i]);
			}
		}

#if MIXTURE_COMPS > 1
		{ // BINARY CORRECTION
			int i_[6] = { 0, 0, 1, 1, 2, 2 };
			int j_[6] = { 1, 2, 2, 0, 0, 1 };

			for (int n = 0; n < 6; n++)
			{
				DHr[k] += (comp[i_[n]] * comp[i_[n]] * comp[j_[n]])
					*
					(a[0][n + 3]
						+ tau * a[1][n + 3]
						+ tau2 * a[2][n + 3]
						+ tau3 * a[3][n + 3]
						)
					*
					(c[0][n + 3]
						+ delta * c[1][n + 3]
						+ delta2 * c[2][n + 3]
						+ delta3 * c[3][n + 3]
						);
			}
		}
#endif

#if MIXTURE_COMPS > 2
		{ // TERNARY CORRECTION
			int i_[6] = { 0, 0, 1, 1, 2, 2 };
			int j_[6] = { 1, 2, 0, 2, 0, 1 };
			int k_[6] = { 2, 1, 2, 0, 1, 0 };

			for (int n = 0; n < 6; n++)
			{
				DHr[k] += (comp[i_[n]] * comp[i_[n]] * comp[i_[n]] * comp[j_[n]] * comp[j_[n]] * comp[k_[n]])
					*
					(a[0][n + 3 + 6]
						+ tau * a[1][n + 3 + 6]
						+ tau2 * a[2][n + 3 + 6]
						+ tau3 * a[3][n + 3 + 6])
					*
					(c[0][n + 3 + 6]
						+ delta * c[1][n + 3 + 6]
						+ delta2 * c[2][n + 3 + 6]
						+ delta3 * c[3][n + 3 + 6]);
			}
		}
#endif
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
#if 0
	static long int iter_count = 0;
	if (iter_count % (dataset.size() * 48) == 0)
	{
		printf("\n--------------------------------------\n");
		printf("ITER: %d\n", iter_count);
		for (int k = 0; k < 2; k++)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < MIXTURE_MOLTIPLICATOR; j++)
				{
					double var = 0;
					if (k == 0)
						var = a[i][j + 3 + 6];
					else
						var = c[i][j + 3 + 6];


					if (var > 0)
						printf("+%.18e\t", var);
					else
						printf("%.18e\t", var);
				}
				printf("\n");
			}
		}
		printf("--------------------------------------\n");
	}
	iter_count++;
#endif

	return DH + DHr[1] - DHr[0];
#else
	return 0;
#endif
}
