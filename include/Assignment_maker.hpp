/**
 * \class Assignment_maker
 *
 * This class models the algorithmic approach to generate the assignment of
 * students to stops.
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

//#include "localsolver.h"
//#include "gurobi_c++.h"

#include "Instance.hpp"
#include "Set_routes.hpp"
#include "Assignment.hpp"

//using namespace localsolver;
//using namespace std;

#ifndef ASSIGNMENT_MAKER_HPP_
#define ASSIGNMENT_MAKER_HPP_

class Assignment_maker {
private:
	/** Instance of the problem */
	Instance* instance;
	/** Set of routes in the solution */
	Set_routes* routes;
	/** Assignment */
	Assignment* assignment;

public:

	/**
	 * Constructor of the class.
	 *
	 * \param i instance of the problem
	 * \param r set of routes in the solution
	 */
	Assignment_maker(Instance* i, Set_routes* r);

	/**
	 * Destructor of the class.
	 */
	~Assignment_maker();

	/**
	 * Calculate an assignment of the students in the current routes.
	 *
	 * \return an object assignment if the assignment is feasible, NULL otherwise.
	 */
	Assignment* calculate_assignment();

};



#endif /* ASSIGNMENT_MAKER_HPP_ */
