#include "MC_VanillaOptions_Functions.h"
#include <cmath>

double genRandomNorm()
{
	double x, y;
	double sizeSquared;

	do
	{
		x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		sizeSquared = x * x + y * y;
	} while
		(sizeSquared >= 1.0);
	return x * sqrt(-2 * log(sizeSquared) / sizeSquared);
}