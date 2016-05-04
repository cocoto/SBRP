/**
 * \class Utils
 *
 * This class implements several utility functions that are helpful for all the
 * other classes.
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef SBRP_INCLUDE_UTILS_HPP_
#define SBRP_INCLUDE_UTILS_HPP_

#include "cmath"
#include <stdlib.h>
#include <sys/time.h>

/* Defines if the debugging code (that allows for extra checks) should be executed.
 * Delete or comment this line to disable the debugging code */
#define _DEBUG

class Utils {
private:
	static const double eps = 0.0000001;

public:

	/**
	 * Returns true if two doubles can be considered to be equal.
	 *
	 * \param d1 First double
	 * \param d2 Second double
	 * \return True if the doubles are equal, false otherwise.
	 */
	static bool are_equal(double d1, double d2);

	/**
	 * Initialize the random seed.
	 */
	static void ini_seed();
};



#endif /* SBRP_INCLUDE_UTILS_HPP_ */
