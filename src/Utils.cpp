/*
 * Implementation of the class Utils
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#include "Utils.hpp"


bool Utils::are_equal(double d1, double d2) {
	return (std::abs(d1 - d2) < eps);
}

void Utils::ini_seed() {
	timeval t1;
	gettimeofday(&t1, NULL);
	srand(t1.tv_usec * t1.tv_sec);
}
