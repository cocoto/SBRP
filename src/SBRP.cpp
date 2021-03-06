/*
 * Main function to be executed.
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#include <stdio.h>
#include <iostream>
#include <sys/time.h>

#include "Instance.hpp"
#include "Solution.hpp"
#include "Initial_solution.hpp"
#include "NSwap.h"
#include "Utils.hpp"
#include <ctime>


Solution* VND(std::vector<ANeighborhood*> neighborhoods, Solution* solution);

int main(int argc, char *argv[]) {

	/*Random seed initialization - DO NOT DELETE.*/
	Utils::ini_seed();


	/* Path of the file that contains the information about the instance */
	char const* file_instance = "files/info.txt";
	/* Path of the file that contains the distance matrix */
	char const* file_distances = "files/distances.txt";
	/* Path of the file that contains the travel time matrix */
	char const* file_times = "files/times.txt";
	/* Path of the file in which the resulting solution will be stored */
	char const* file_result = "files/result.txt";

	/* Read the instance */
	//long int before = GetTickCount();

	//std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	clock_t begin = clock();

	Instance* instance = Instance::read_from_files(file_instance, file_distances, file_times);

	/* Print the information about the instance on the console */
	instance->print();

	/* Create a solution */
	Solution* solution = Initial_solution::clark_and_wright(instance);

	std::cout << "AFTER C W" << std::endl;
	solution->print();


	std::vector<ANeighborhood*> neighborhoods;
	N_Swap* swapNeighborhood = new N_Swap(instance);
	N_Concatenate* concatNeighborhood = new N_Concatenate(instance);
	neighborhoods.push_back(swapNeighborhood);
	neighborhoods.push_back(concatNeighborhood);
	solution = VND(neighborhoods,solution);

	clock_t end = clock();

	/* Print the solution on the console */
	std::cout << "FINAL SOLUTION" << std::endl;
	solution->print();

	/* Generating the output files for the web-service platform. Be careful, these functions
	 * check that the solution is feasible (there is a feasible assignment of students). */

	/* Print the solution on the output file */
	solution->print_file_format(file_result);

	/* Print the solution (only the routes) on the output file */
	//solution->print_file_format_buses(file_result);

	/* Print the solution (only the paths of the students to the stops) on the output file */
	//solution->print_file_format_students(file_result);

	printf("Time taken: %d\n",(end-begin));
	printf("***END***\n");

	delete solution;
	delete instance;
}

Solution* VND(std::vector<ANeighborhood*> neighborhoods, Solution* solution){
	unsigned int k = 0;
	while(k<neighborhoods.size()){
		std::cout<<"Neighborhood "<<k<<std::endl;
		Solution* newSol = neighborhoods[k]->getNeighbor(solution,false);
		if(newSol->get_total_distance() < solution->get_total_distance()){
			k = 0;
			solution = newSol;
		}else{
			++k;
		}
	}
	return solution;
}
