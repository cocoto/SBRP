/*
 * NConcatenate.cpp
 *
 *  Created on: 26 avr. 2016
 *      Author: popoola
 */


#include <NConcatenate.h>
#include <iostream>

N_Concatenate::N_Concatenate(Instance* instance): ANeighborhood(instance){
}


Solution* N_Concatenate::getNeighbor(Solution* old_solution,
		const bool& useMILP, const bool& strategy) const {
	Solution* solution  = old_solution->copy();
	int best_i = -1;
	int best_j = -1;
	int best_gain = 0;
	for (int i = 0; i < solution->get_num_routes(); ++i) {
		for (int j = 0; j < solution->get_num_routes(); ++j) {
			if(i != j){
				int routes_weight=0;
				for (int n = 0; n < _instance->get_num_students(); ++n) {
					int stop_number = solution->get_assignments()->get_stop_number(n);
					if(stop_number == i || stop_number == j){
						routes_weight += _instance->get_student(n)->getWeight();
					}
				}

				if(useMILP){
					//TODO use MILP to improve or check the feasibility
				}

				if (routes_weight <= _instance->get_cap_buses()) {
					int x = solution->get_stop_route(i,solution->get_size_route(i)-1);
					int y = solution->get_stop_route(j,0);
					double gain = _instance->get_dist_stop_school(x) + _instance->get_dist_school_stop(y) - _instance->get_dist_stops(x,y);
					if(gain > best_gain && strategy == 0){ //case of the best policy
						best_gain = gain;
						best_i = i;
						best_j = j;
					}else if(gain > 0 and strategy == 1){ //case of the first policy
						solution->merge_paths(i, j);
						return solution;
					}
				}
			}
		}//for each j
	}//for each i

	if(best_gain > 0){
		std::cout<<"Merging paths "<<best_i<<" and "<<best_j<<std::endl;
		solution->merge_paths(best_i, best_j);
		solution->print();
	}
	return solution;
}
