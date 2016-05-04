/*
 * Implementation of the class Set_routes
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#include "Set_routes.hpp"

Set_routes::Set_routes(Instance* inst) {
	instance = inst;
	total_distance = 0.0;
	total_time = 0.0;

	/* Initialize the array that stores the route in which a stop is visited*/
	route_stop = new int[instance->get_num_stops()];
	for (int i = 0; i < instance->get_num_stops(); i++) {
		/*It is assumed that if the route is equal to -1, the stop is not visited*/
		route_stop[i] = -1;
	}
}

Set_routes::~Set_routes() {
	delete [] route_stop;
	/* Delete the routes*/
	for (int i = 0; i < get_num_routes(); i++) {
		delete route[i];
	}
}

Set_routes* Set_routes::copy() {
	Set_routes* copy = new Set_routes(instance);

	copy->total_distance = total_distance;
	copy->total_time = total_time;

	/* Copy the array that stores the route in which a stop is visited */
	for (int i = 0; i < instance->get_num_stops(); i++) {
		copy->route_stop[i] = route_stop[i];
	}

	/* Copy the actual routes */
	for (int i = 0; i < get_num_routes(); i++) {
		copy->route.push_back(route[i]->copy());
	}

	return copy;
}

bool Set_routes::is_empty() {
	return(get_num_routes() == 0);
}

int Set_routes::get_num_routes() {
	return route.size();
}

int Set_routes::get_size_route(int r_i) {
	/* Check the input parameters */
	assert_index_route(r_i);

	return route[r_i]->get_size();
}

double Set_routes::get_total_distance() {
	return total_distance;
}

double Set_routes::get_total_time() {
	return total_time;
}

bool Set_routes::is_stop_visited(int s_i) {
	/* Check the input parameters */
	instance->assert_index_stop(s_i);

	/* It is assumed that if the route is equal to -1, the stop is not visited*/
	return (route_stop[s_i] != -1);
}

int Set_routes::get_stop_route(int r_i, int p) {
	/* Check the input parameters */
	assert_index_route(r_i);
	assert_pos_route(r_i, p);

	return route[r_i]->get_stop(p);
}

void Set_routes::add_empty_route() {
	route.push_back(new Route(instance));
}

void Set_routes::add_empty_route(int n) {
	for (int i = 0; i < n; i++) {
		add_empty_route();
	}
}

void Set_routes::remove_route(int r_i) {
	/* Check the input parameters */
	assert_index_route(r_i);

	int size_route = get_size_route(r_i); /* Size of the route to be removed*/

	/* Remove all the customers in the route, if there are any*/
	for (int i = 0; i < size_route; i++) {
		remove_stop_pos_route(r_i, 0);
	}

	/* Delete the route object*/
	delete route[r_i];

	/* Remove the route from the array of routes*/
	route.erase(route.begin() + r_i);

	/* Decrease the number of the route that each stop is assigned to
	 * (for those routes whose index is larger than r_i) */
	for (int s_i = 0; s_i < instance->get_num_stops(); s_i++) {
		if (route_stop[s_i] > r_i) { /* If the route has larger index than r_i*/
			route_stop[s_i]--;
		}
	}

	/* Code to be executed only if the flag _DEBUG is set*/
	#ifdef _DEBUG
	/* Check the structure of the routes*/
	assert_routes_structure();
	#endif
}

void Set_routes::remove_empty_routes() {
	for (int i = get_num_routes() - 1; i >= 0; i--) {
		if (get_size_route(i) == 0) {
			remove_route(i);
		}
	}
}

void Set_routes::clear() {
	int num_routes = get_num_routes(); /* Number of routes*/
	for (int i = 0; i < num_routes; i++) {
		remove_route(0);
	}
}

bool Set_routes::can_route_pick_up_student(int r_i, int stu_i) {
	/* Check the input parameters */
	assert_index_route(r_i);
	instance->assert_index_student(stu_i);

	return route[r_i]->can_pick_up_student(stu_i);
}

double Set_routes::calc_diff_dist_insert_stop_route(int s_i, int r_i, int p) {
	/* Check the input parameters */
	instance->assert_index_stop(s_i);
	assert_index_route(r_i);
	assert_pos_route_end(r_i, p);

	/* Check that the stop has not been assigned yet*/
	assert(!is_stop_visited(s_i));

	return route[r_i]->calc_diff_dist_insert_stop(s_i, p);
}

double Set_routes::calc_diff_time_insert_stop_route(int s_i, int r_i, int p) {
	/* Check the input parameters */
	instance->assert_index_stop(s_i);
	assert_index_route(r_i);
	assert_pos_route_end(r_i, p);

	/* Check that the stop has not been assigned yet*/
	assert(!is_stop_visited(s_i));

	return route[r_i]->calc_diff_time_insert_stop(s_i, p);
}

void Set_routes::insert_stop_route(int s_i, int r_i, int p) {
	/* Check the input parameters */
	instance->assert_index_stop(s_i);
	assert_index_route(r_i);
	assert_pos_route_end(r_i, p);

	/* Check that the stop has not been assigned yet*/
	assert(!is_stop_visited(s_i));

	/* Update the total distance and the total travel time */
	total_distance += calc_diff_dist_insert_stop_route(s_i, r_i, p);
	total_time += calc_diff_time_insert_stop_route(s_i, r_i, p);

	/* Mark the stop as visited */
	route_stop[s_i] = r_i;

	/* Make the actual insertion */
	route[r_i]->insert_stop(s_i, p);

	/* Code to be executed only if the flag _DEBUG is set*/
	#ifdef _DEBUG
	/* Check the structure of the routes*/
	assert_routes_structure();
	#endif
}

double Set_routes::calc_diff_dist_remove_stop_route(int r_i, int p) {
	/* Check the input parameters */
	assert_index_route(r_i);
	assert_pos_route(r_i, p);

	return route[r_i]->calc_diff_dist_remove_stop(p);
}

double Set_routes::calc_diff_time_remove_stop_route(int r_i, int p) {
	/* Check the input parameters */
	assert_index_route(r_i);
	assert_pos_route(r_i, p);

	return route[r_i]->calc_diff_time_remove_stop(p);
}

void Set_routes::remove_stop_pos_route(int r_i, int p) {
	/* Check the input parameters */
	assert_index_route(r_i);
	assert_pos_route(r_i, p);

	/* Update the total distance and the total travel time */
	total_distance += calc_diff_dist_remove_stop_route(r_i, p);
	total_time += calc_diff_time_remove_stop_route(r_i, p);

	/* Mark the stop as not visited */
	route_stop[get_stop_route(r_i, p)] = -1;

	/* Make the actual removal */
	route[r_i]->remove_stop_pos(p);

	/* Code to be executed only if the flag _DEBUG is set*/
	#ifdef _DEBUG
	/* Check the structure of the routes*/
	assert_routes_structure();
	#endif
}

int Set_routes::get_closest_stop_student_route(int stu_i, int r_i) {
	/* Check the input parameters */
	instance->assert_index_student(stu_i);
	assert_index_route(r_i);

	return route[r_i]->get_closest_stop_student(stu_i);
}

/************* Assertion functions *************/

void Set_routes::assert_index_route(int r_i) {
	assert(r_i >= 0 && r_i < get_num_routes());
}

void Set_routes::assert_pos_route(int r_i, int p) {
	assert_index_route(r_i);
	route[r_i]->assert_pos_route(p);
}

void Set_routes::assert_pos_route_end(int r_i, int p) {
	assert_index_route(r_i);
	route[r_i]->assert_pos_route_end(p);
}

void Set_routes::assert_routes_structure() {

	double distance_check = 0;
	double time_check = 0;

	/* Iterate over the routes*/
	for (int i = 0; i < get_num_routes(); i++) {

		/* Check the route itself*/
		route[i]->assert_route_distance_time();

		distance_check += route[i]->get_distance();
		time_check += route[i]->get_time();

		for (int p = 0; p < get_size_route(i); p++) {
			assert(route_stop[get_stop_route(i, p)] == i);
		}
	}

	/* Check that the values calculated are equal to those stored */
	assert(Utils::are_equal(distance_check, total_distance));
	assert(Utils::are_equal(time_check, total_time));

}


/************* Input/Output (reading and printing) functions *************/

void Set_routes::print() {

	/* Code to be executed only if the flag _DEBUG is set*/
	#ifdef _DEBUG
	/* Check the integrity of the route (distance and travel time)*/
	assert_routes_structure();
	#endif

	printf("  - Total distance traversed: %.2lf\n", get_total_distance());
	printf("  - Total time: %.2lf\n", get_total_time());

	printf("  - Set of routes traversed by the buses: \n");
	for (int i = 0; i < get_num_routes(); i++) {
		route[i]->print();
	}
}

void Set_routes::print_file_format(FILE* file) {
	/* Check the input parameters */
	assert(file != NULL);

	for (int i = 0; i < get_num_routes(); i++) {
		route[i]->print_file_format(file);
	}
}



