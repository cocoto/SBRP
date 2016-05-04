/*
 * Implementation of the class Solution
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#include "Solution.hpp"

Solution::Solution() {
};

Solution::Solution(Instance* inst) {
	instance = inst;
	routes = new Set_routes(instance);
	assignment_maker = new Assignment_maker(instance, routes);
}

Solution::~Solution() {
	delete assignment_maker;
	delete routes;
}

Solution* Solution::copy() {
	/* Use the empty constructor and do everything by hand */
	Solution* copy = new Solution();
	copy->instance = instance;
	copy->routes = routes->copy();
	copy->assignment_maker = new Assignment_maker(copy->instance, copy->routes);
	return copy;
}

bool Solution::is_empty() {
	return routes->is_empty();
}

int Solution::get_num_routes() {
	return routes->get_num_routes();
}

int Solution::get_size_route(int r_i) {
	/* Check the input parameters */
	routes->assert_index_route(r_i);

	return routes->get_size_route(r_i);
}

double Solution::get_total_distance() {
	return routes->get_total_distance();
}

double Solution::get_total_time() {
	return routes->get_total_time();
}

int Solution::get_stop_route(int r_i, int p) {
	/* Check the input parameters */
	routes->assert_index_route(r_i);
	routes->assert_pos_route(r_i, p);

	return routes->get_stop_route(r_i, p);
}

bool Solution::is_stop_visited(int s_i) {
	/* Check the input parameters */
	instance->assert_index_stop(s_i);

	return routes->is_stop_visited(s_i);
}

void Solution::add_empty_route() {
	routes->add_empty_route();
}

void Solution::add_empty_route(int n) {
	routes->add_empty_route(n);
}

void Solution::remove_route(int r_i) {
	/* Check the input parameters */
	routes->assert_index_route(r_i);

	routes->remove_route(r_i);
}

void Solution::remove_empty_routes() {
	routes->remove_empty_routes();
}

void Solution::clear () {
	routes->clear();
}

bool Solution::can_route_pick_up_student(int r_i, int stu_i) {
	/* Check the input parameters */
	routes->assert_index_route(r_i);
	instance->assert_index_student(stu_i);

	return routes->can_route_pick_up_student(r_i, stu_i);
}

double Solution::calc_diff_dist_insert_stop_route(int s_i, int r_i, int p) {
	/* Check the input parameters */
	instance->assert_index_stop(s_i);
	routes->assert_index_route(r_i);
	routes->assert_pos_route_end(r_i, p);
	assert(!is_stop_visited(s_i));

	return routes->calc_diff_dist_insert_stop_route(s_i, r_i, p);
}

double Solution::calc_diff_time_insert_stop_route(int s_i, int r_i, int p) {
	/* Check the input parameters */
	instance->assert_index_stop(s_i);
	routes->assert_index_route(r_i);
	routes->assert_pos_route_end(r_i, p);
	assert(!is_stop_visited(s_i));

	return routes->calc_diff_time_insert_stop_route(s_i, r_i, p);
}

void Solution::insert_stop_route(int s_i, int r_i, int p) {
	/* Check the input parameters */
	instance->assert_index_stop(s_i);
	routes->assert_index_route(r_i);
	routes->assert_pos_route_end(r_i, p);
	assert(!is_stop_visited(s_i));

	routes->insert_stop_route(s_i, r_i, p);
}

double Solution::calc_diff_dist_remove_stop_route(int r_i, int p) {
	/* Check the input parameters */
	routes->assert_index_route(r_i);
	routes->assert_pos_route(r_i, p);

	return routes->calc_diff_dist_remove_stop_route(r_i, p);
}

double Solution::calc_diff_time_remove_stop_route(int r_i, int p) {
	/* Check the input parameters */
	routes->assert_index_route(r_i);
	routes->assert_pos_route(r_i, p);

	return routes->calc_diff_time_remove_stop_route(r_i, p);
}

void Solution::remove_stop_pos_route(int r_i, int p) {
	/* Check the input parameters */
	routes->assert_index_route(r_i);
	routes->assert_pos_route(r_i, p);

	routes->remove_stop_pos_route(r_i, p);
}

/************* Functions related to the assignment of students *************/

bool Solution::is_assignment_feasible() {
	Assignment* assignment = get_assignment();

	if (assignment == NULL) {
		return false;
	} else {
		return true;
	}
}

Assignment* Solution::get_assignment() {
	/* If the solution is empty, return NULL right away */
	if (is_empty()) {
		return NULL;
	}

	return assignment_maker->calculate_assignment();
}

/************* Input/Output (reading and printing) functions *************/

void Solution::print() {
	/* Assignment calculated by the assignment maker */
	Assignment* assignment;

	printf(" Information about the solution: \n");
	routes->print();

	if (is_assignment_feasible()) {
		assignment = get_assignment();
		assignment->print();
	} else {
		printf("WARNING!!! Infeasible solution! There is no feasible assignment of students to stops. \n");
	}
}

void Solution::print_file_format(const char* f_p) {
	FILE *file; /*File*/
	/* Assignment calculated by the assignment maker */
	Assignment* assignment;

	/* Check that it was possible to make an assignment */
	assert(is_assignment_feasible());

	/* Get the assignment*/
	assignment = get_assignment();

	/* Open the file to store the solution*/
	file = fopen(f_p, "w");

	/* Check if the file could be opened or not.*/
	if (file == NULL) {
		printf("   ERROR! The file in which a solution is going to be stored"
				"could not be opened (Class Solution).\n");
		return;
	}

	/* Print the total number of paths that need to be drawn*/
	fprintf(file, "%d\n", routes->get_num_routes() + instance->get_num_students());
	/* Print the total distance*/
	fprintf(file, "%lf\n", get_total_distance());
	/* Print the total time*/
	fprintf(file, "%lf\n", get_total_time());

	/* Print paths of the students to the stops they are assigned to*/
	assignment->print_file_format(file);

	/* Print the routes traversed by the buses*/
	routes->print_file_format(file);

	fclose(file);
}

void Solution::print_file_format_buses(const char* f_p) {
	FILE *file; /*File*/

	/* Check that it was possible to make an assignment */
	assert(is_assignment_feasible());

	/* Open the file to store the solution*/
	file = fopen(f_p, "w");

	/* Check if the file could be opened or not.*/
	if (file == NULL) {
		printf("   ERROR! The file in which a solution is going to be stored"
				"could not be opened (Class Solution).\n");
		return;
	}

	/* Print the total number of paths that need to be drawn*/
	fprintf(file, "%d\n", routes->get_num_routes());
	/* Print the total distance*/
	fprintf(file, "%lf\n", get_total_distance());
	/* Print the total time*/
	fprintf(file, "%lf\n", get_total_time());

	/* Print the routes traversed by the buses*/
	routes->print_file_format(file);

	fclose(file);
}

void Solution::print_file_format_students(const char* f_p) {
	FILE *file; /*File*/
	/* Assignment calculated by the assignment maker */
	Assignment* assignment = assignment_maker->calculate_assignment();

	/* Check that it was possible to make an assignment */
	assert(assignment != NULL);

	/* Open the file to store the solution*/
	file = fopen(f_p, "w");

	/* Check if the file could be opened or not*/
	if (file == NULL) {
		printf("   ERROR! The file in which a solution is going to be stored"
				" could not be opened (Class Solution).\n");
		return;
	}

	/* Print the total number of paths that need to be drawn*/
	fprintf(file, "%d\n", instance->get_num_students());
	/* Print the total distance*/
	fprintf(file, "%lf\n", get_total_distance());
	/* Print the total time*/
	fprintf(file, "%lf\n", get_total_time());

	/* Print paths of the students to the stops they are assigned to*/
	assignment->print_file_format(file);

	fclose(file);
}



