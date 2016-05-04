/*
 * Implementation of the class Assignment_maker
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#include "Assignment_maker.hpp"

Assignment_maker::Assignment_maker(Instance* i, Set_routes* r) {
	instance = i;
	routes = r;
	assignment = new Assignment(instance, routes);
}

Assignment_maker::~Assignment_maker() {
	delete assignment;
}

Assignment* Assignment_maker::calculate_assignment() {
	
	/* Insert your code here! And remove the "return NULL", of course :-) */

	return NULL;
}




