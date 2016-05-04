/*
 * NSwap.cpp
 *
 *  Created on: 26 avr. 2016
 *      Author: popoola
 */

#include <NSwap.h>
#include <iostream>

N_Swap::N_Swap(Instance* instance): ANeighborhood(instance) {

}

N_Swap::~N_Swap() {
	// TODO Auto-generated destructor stub
}

Solution* N_Swap::getNeighbor(Solution* old_solution,
		const bool& useMILP, const bool& strategy) const {
	Solution* solution  = old_solution->copy();
	std::cout<<"Starting NWAP"<<std::endl;
	std::vector<int> route_weights = solution->get_weights();
	int bestroute_i = -1;
	int bestroute_j = -1;
	int bestpos_i = -1;
	int bestpos_j = -1;
	int best_gain = 0;
	std::cout<<"Nb routes "<<solution->get_num_routes()<<std::endl;
	for (int routeI = 0; routeI < solution->get_num_routes(); ++routeI) {
		for (int routeJ = routeI; routeJ < solution->get_num_routes(); ++routeJ) {
			for (int positionI = 0; positionI < solution->get_size_route(routeI); ++positionI) {
				for (int positionJ = 0; positionJ < solution->get_size_route(routeJ); ++positionJ) {
					if (routeI == routeJ && positionI >= positionJ)
						continue;
					int stopI = solution->get_stop_route(routeI,positionI);
					int stopJ = solution->get_stop_route(routeJ,positionJ);
					double gain = 0;
					if(routeI == routeJ && positionJ == positionI+1){
						//TODO compute special case
						//take care about the school when stops are first or last
						continue;
					}else{
						gain =
							-	solution->calc_diff_dist_remove_stop_route(routeI,positionI)
							-	solution->calc_diff_dist_remove_stop_route(routeJ,positionJ)
							-	solution->calc_diff_dist_insert_stop_route(stopJ,routeI,positionI)
							-	solution->calc_diff_dist_insert_stop_route(stopI,routeJ,positionJ);
					}
					//std::cout<<solution->calc_diff_dist_remove_stop_route(routeI,positionI)<<std::endl;
					//std::cout<<"Testing "<<routeI<<" "<<routeJ<<" "<<positionI<<" "<<positionJ<<" gain : "<<gain<<std::endl;
					//check feasibility (tour weight)
					if(gain>best_gain){
						if(routeI != routeJ){
							int stopI = solution->get_stop_route(routeI,positionI);
							int stopJ = solution->get_stop_route(routeJ,positionJ);
							int weightI = solution->get_num_stu(stopI);
							int weightJ = solution->get_num_stu(stopJ);
							if(route_weights[routeI] - weightI + weightJ  <= _instance->get_cap_buses() )
								continue;
							if(route_weights[routeJ] - weightJ + weightI  <= _instance->get_cap_buses() )
								continue;
						}
						best_gain 	= gain;
						bestroute_i = routeI;
						bestroute_j = routeJ;
						bestpos_i	= positionI;
						bestpos_j 	= positionJ;
					}
				}
			}
		}
	}//for loops

	if(best_gain > 0){
		int stopI = solution->get_stop_route(bestroute_i,bestpos_i);
		int stopJ = solution->get_stop_route(bestroute_j,bestpos_j);
		solution->remove_stop_pos_route(bestroute_i,bestpos_i);
		solution->remove_stop_pos_route(bestroute_j,bestpos_j);
		solution->insert_stop_route(stopJ,bestroute_i,bestpos_i);
		solution->insert_stop_route(stopI,bestroute_j,bestpos_j);
	}
	return solution;
}

