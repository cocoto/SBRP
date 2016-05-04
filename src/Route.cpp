/*
 * Implementation of the class Route
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#include "Route.hpp"

Route::Route(Instance* inst) {
	instance = inst;
	distance = 0.0;
	time = 0.0;
}

Route* Route::copy() {
	Route* copy = new Route(instance);

	for (int i = 0; i < get_size(); i++) {
		copy->insert_stop(get_stop(i), i);
	}

	return copy;
}

int Route::get_size() {
	return route.size();
}

double Route::get_distance() {
	return distance;
}

double Route::get_time() {
	return time;
}

int Route::get_stop(int p) {
	/* Check the input parameters */
	assert_pos_route(p);

	return route[p];
}

bool Route::can_pick_up_student(int stu_i) {
	/* Check the input parameters */
	instance->assert_index_student(stu_i);

	for (int i = 0; i < get_size(); i++) {
		if (instance->can_student_assigned_stop(stu_i, get_stop(i))) {
			return true;
		}
	}
	return false;
}

double Route::calc_diff_dist_insert_stop(int s_i, int p) {
	/* Check the input parameters */
	instance->assert_index_stop(s_i);
	assert_pos_route_end(p);

	double diff_dist = 0;

	if (get_size() == 0) { /* If the route is empty */

		diff_dist =  instance->get_dist_school_stop(s_i)
				   + instance->get_dist_stop_school(s_i);

	} else { /* If the route is not empty */

		if (p == 0) { /* If the stop is inserted at the beginning of the route */

			diff_dist = - instance->get_dist_school_stop(get_stop(p))
		    			+ instance->get_dist_school_stop(s_i)
						+ instance->get_dist_stops(s_i, get_stop(p));

		} else if (p == get_size()) { /* If the stop is inserted at the end of the route */

			diff_dist = - instance->get_dist_stop_school(get_stop(p - 1))
					    + instance->get_dist_stop_school(s_i)
				        + instance->get_dist_stops(get_stop(p - 1), s_i);

		} else { /* If the stop is inserted at somewhere in the middle */

			diff_dist = - instance->get_dist_stops(get_stop(p - 1), get_stop(p))
						+ instance->get_dist_stops(get_stop(p - 1), s_i)
					    + instance->get_dist_stops(s_i, get_stop(p));
		}
	}
	return diff_dist;
}

double Route::calc_diff_time_insert_stop(int s_i, int p) {
	/* Check the input parameters */
	instance->assert_index_stop(s_i);
	assert_pos_route_end(p);

	double diff_time = 0;

	if (get_size() == 0) { /* If the route is empty */

		diff_time =  instance->get_time_school_stop(s_i)
				   + instance->get_time_stop_school(s_i);

	} else { /* If the route is not empty */

		if (p == 0) { /* If the stop is inserted at the beginning of the route */

			diff_time = - instance->get_time_school_stop(get_stop(p))
					    + instance->get_time_school_stop(s_i)
					    + instance->get_time_stops(s_i, get_stop(p));

		} else if (p == get_size()) { /* If the stop is inserted at the end of the route */

			diff_time = - instance->get_time_stop_school(get_stop(p - 1))
			     		+ instance->get_time_stop_school(s_i)
			    		+ instance->get_time_stops(get_stop(p - 1), s_i);

		} else { /* If the stop is inserted at somewhere in the middle */

			diff_time = - instance->get_time_stops(get_stop(p - 1), get_stop(p))
			     		+ instance->get_time_stops(get_stop(p - 1), s_i)
			    		+ instance->get_time_stops(s_i, get_stop(p));
		}
	}
	return diff_time;
}

void Route::insert_stop(int s_i, int p) {
	/* Check the input parameters */
	instance->assert_index_stop(s_i);
	assert_pos_route_end(p);

	/* Update the distance and the travel time */
	distance += calc_diff_dist_insert_stop(s_i, p);
	time += calc_diff_time_insert_stop(s_i, p);

	/* Make the actual insertion */
	route.insert(route.begin() + p, s_i);

	/* Code to be executed only if the flag _DEBUG is set*/
	#ifdef _DEBUG
	/* Check the integrity of the route (distance and travel time)*/
	assert_route_distance_time();
	#endif
}

double Route::calc_diff_dist_remove_stop(int p) {
	/* Check the input parameters */
	assert_pos_route(p);

	/* Check that the route is not empty*/
	assert(get_size() != 0);

	double diff_dist = 0;

	if (get_size() == 1 && p == 0) { /* If there is only one stop in the route */

		diff_dist = -instance->get_dist_school_stop(get_stop(p))
				    - instance->get_dist_stop_school(get_stop(p));

	} else { /* If the route has more than one stop */

		if (p == 0) { /* If the stop is removed from the beginning of the route */

			diff_dist = + instance->get_dist_school_stop(get_stop(p + 1))
		    			- instance->get_dist_school_stop(get_stop(p))
						- instance->get_dist_stops(get_stop(p), get_stop(p + 1));

		} else if (p == get_size() - 1) { /* If the stop is removed from the end of the route */

			diff_dist = + instance->get_dist_stop_school(get_stop(p - 1))
					    - instance->get_dist_stop_school(get_stop(p))
				        - instance->get_dist_stops(get_stop(p - 1), get_stop(p));

		} else { /* If the stop is removed from somewhere in the middle */

			diff_dist = + instance->get_dist_stops(get_stop(p - 1), get_stop(p + 1))
						- instance->get_dist_stops(get_stop(p - 1), get_stop(p))
					    - instance->get_dist_stops(get_stop(p), get_stop(p + 1));
		}
	}

	return diff_dist;
}

double Route::calc_diff_time_remove_stop(int p) {
	/* Check the input parameters */
	assert_pos_route(p);

	/* Check that the route is not empty*/
	assert(get_size() != 0);

	double diff_time = 0;

	if (get_size() == 1 && p == 0) { /* If there is only one stop in the route */

		diff_time = -instance->get_time_school_stop(get_stop(p))
				    - instance->get_time_stop_school(get_stop(p));

	} else { /* If the route has more than one stop */

		if (p == 0) { /* If the stop is removed from the beginning of the route */

			diff_time = + instance->get_time_school_stop(get_stop(p + 1))
		    			- instance->get_time_school_stop(get_stop(p))
						- instance->get_time_stops(get_stop(p), get_stop(p + 1));

		} else if (p == get_size() - 1) { /* If the stop is removed from the end of the route */

			diff_time = + instance->get_time_stop_school(get_stop(p - 1))
					    - instance->get_time_stop_school(get_stop(p))
				        - instance->get_time_stops(get_stop(p - 1), get_stop(p));

		} else { /* If the stop is removed from somewhere in the middle */

			diff_time = + instance->get_time_stops(get_stop(p - 1), get_stop(p + 1))
						- instance->get_time_stops(get_stop(p - 1), get_stop(p))
					    - instance->get_time_stops(get_stop(p), get_stop(p + 1));
		}
	}

	return diff_time;
}

void Route::remove_stop_pos(int p) {
	/* Check the input parameters */
	assert_pos_route(p);

	/* Check that the route is not empty*/
	assert(get_size() != 0);

	/* Update the distance and the travel time */
	distance += calc_diff_dist_remove_stop(p);
	time += calc_diff_time_remove_stop(p);

	/* Make the actual removal */
	route.erase(route.begin() + p);

	/* Code to be executed only if the flag _DEBUG is set*/
	#ifdef _DEBUG
	/* Check the integrity of the route (distance and travel time)*/
	assert_route_distance_time();
	#endif
}

int Route::get_closest_stop_student(int stu_i) {
	/* Check the input parameters */
	instance->assert_index_student(stu_i);

	/* Stop to which the student is assigned*/
	int stop = -1;
	/* Distance between the student and the stop*/
	double distance_stop = std::numeric_limits<double>::max();

	for (int i = 0; i < get_size(); i++) {
		/* If the student can be assigned to the stop and
		 * the distance between the student and the stop is smaller */
		if (instance->can_student_assigned_stop(stu_i, get_stop(i))
				&& instance->get_dist_student_stop(stu_i, get_stop(i)) < distance_stop) {
			stop = get_stop(i);
			distance_stop = instance->get_dist_student_stop(stu_i, get_stop(i));
		}
	}

	/* Check that a stop has been found*/
	assert(stop != -1);

	return stop;
}

/************* Assertion functions *************/

void Route::assert_pos_route(int p) {
	assert(p >= 0 && p < get_size());
}

void Route::assert_pos_route_end(int p) {
	assert(p >= 0 && p <= get_size());
}

void Route::assert_route_distance_time() {
	double distance_check = 0;
	double time_check = 0;

	if (get_size() == 0) { /* If the route is empty */

		assert(Utils::are_equal(distance, 0) && Utils::are_equal(time, 0));

	} else if (get_size() == 1) { /* If the route contains only one stop*/

		assert(Utils::are_equal(distance,
				instance->get_dist_school_stop(get_stop(0))
				+ instance->get_dist_stop_school(get_stop(0)))
		);

		assert(Utils::are_equal(time,
				instance->get_time_school_stop(get_stop(0))
				+ instance->get_time_stop_school(get_stop(0)))
		);

	} else { /* If the route contains more than one stop*/

		distance_check = instance->get_dist_school_stop(get_stop(0));
		time_check = instance->get_time_school_stop(get_stop(0));

		for (int i = 0; i < get_size() - 1; i++) { /* Iterate over all the stops in the route*/
			distance_check += instance->get_dist_stops(get_stop(i), get_stop(i + 1));
			time_check += instance->get_time_stops(get_stop(i), get_stop(i + 1));
		}

		distance_check += instance->get_dist_stop_school(get_stop(get_size() - 1));
		time_check += instance->get_time_stop_school(get_stop(get_size() - 1));

		assert(Utils::are_equal(distance, distance_check)
			&& Utils::are_equal(time, time_check));
	}
}

/************* Input/Output (reading and printing) functions *************/
void Route::print() {
	/* Code to be executed only if the flag _DEBUG is set*/
	#ifdef _DEBUG
	/* Check the integrity of the route (distance and travel time)*/
	assert_route_distance_time();
	#endif

	printf("    [%8.2lf, %8.2lf] ", get_distance(), get_time());
	printf("< S, ");
	for (int i = 0; i < get_size(); i++) {
		printf("%d, ", get_stop(i));
	}
	printf("S > \n");
}

void Route::print_file_format(FILE *file) {
	/* Check the input parameters */
	assert(file != NULL);

	/* Print the size of the path (+2 due to including the school)*/
	fprintf(file, "%d ", get_size() + 2);

	/* Print the school*/
	fprintf(file, "%d ", instance->get_school()->get_id() + 1);

	for (int i = 0; i < get_size(); i++) {
		fprintf(file, "%d ", instance->get_stop(get_stop(i))->get_id() + 1);
	}
	/* Print the school*/
	fprintf(file, "%d\n", instance->get_school()->get_id() + 1);
}


