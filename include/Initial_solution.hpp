/**
 * \class Initial_solution
 *
 * This class implement the algorithms to create an initial solution to the SBRP
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#include <vector>
#include <algorithm>

#include "Instance.hpp"
#include "Solution.hpp"
#include "NConcatenate.h"

#ifndef INITIAL_SOLUTION_HPP_
#define INITIAL_SOLUTION_HPP_

class Initial_solution {
public:

	/**
	 * Create a a random solution to an instance of the SBRP. It inserts all the
	 * potential stops in the solution (in a randomly chosen route) in a random order.
	 *
	 * \param inst instance of the problem
	 * \return a solution to the problem
	 */
	static Solution* random(Instance* inst);
	static Solution* clark_and_wright(Instance* inst);

};





#endif /* INITIAL_SOLUTION_HPP_ */
