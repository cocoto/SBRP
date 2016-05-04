/*
 * Implementation of the class Initial_solution
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#include "Initial_solution.hpp"

Solution* Initial_solution::random(Instance* inst) {
	Solution* sol = NULL; /* Solution*/
	int num_routes; /* Number of routes that will be used*/
	std::vector<int> stops_insert(inst->get_num_stops(), -1); /* Vector with the stops to be inserted in the solution*/
	int route; /* Route in which the stop will be inserted */

	while (sol == NULL) { /* Until a feasible solution is found*/

		sol = new Solution(inst);

		/* Select a random number of routes*/
		num_routes = (int) ((rand() % inst->get_num_stops())) + 1;
		sol->add_empty_route(num_routes);

		/*Fill the vector with the numbers of the stops*/
		for (int i = 0; i < inst->get_num_stops(); i++) {
			stops_insert[i] = i;
		}

		/* Shuffle the vector of stops randomly*/
		std::random_shuffle(stops_insert.begin(), stops_insert.end());

		/* Iterate over the vector of stops */
		for (int i = 0; i < inst->get_num_stops(); i++) {
			route = (int) (rand() % sol->get_num_routes());

			/* Insert the stop at the end of the route*/
			sol->insert_stop_route(stops_insert[i], route, sol->get_size_route(route));

		}

		/* Remove possible empty routes */
		sol->remove_empty_routes();

		/* If the assignment is not feasible, try again. Remove the commented part in
		 * order to generate a feasible solution. */
		//if (!sol->is_assignment_feasible()) {
		//	delete sol;
		//	sol = NULL;
		//}
	}

	return sol;
}



