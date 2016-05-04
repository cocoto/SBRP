/*
 * Implementation of the class Assignment
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#include "Assignment.hpp"

Assignment::Assignment(Instance* i, Set_routes* r) {
	instance = i;
	routes = r;

	/* Initialize the array that stores the route that each student is assigned to*/
	route_student = new int[instance->get_num_students()];
	for (int i = 0; i < instance->get_num_students(); i++) {
		route_student[i] = -1; /* It is assumed that -1 represent unassigned students*/
	}
}

Assignment::~Assignment() {
	delete [] route_student;
}

void Assignment::remove_all_assignments() {
	/* It is assumed that -1 represent unassigned students*/
	for (int i = 0; i < instance->get_num_students(); i++) {
		route_student[i] = -1;
	}
}

bool Assignment::is_student_assigned(int s_i) {
	/* Check the input parameters */
	instance->assert_index_student(s_i);

	/* It is assumed that -1 represent unassigned students*/
	return (route_student[s_i] == -1);
}

void Assignment::assign_student_route(int s_i, int r_i) {
	/* Check the input parameters */
	instance->assert_index_student(s_i);
	routes->assert_index_route(r_i);

	route_student[s_i] = r_i;
}

bool Assignment::is_feasible() {
	bool is_feas = true; /* States if the assignment is feasible or not*/
	int route; /* Route that a student is assigned to */

	/* Number of students assigned to each route*/
	int* num_stu_route = new int[routes->get_num_routes()];
	for (int i = 0; i < routes->get_num_routes(); i++) {
		num_stu_route[i] = 0;
	}

	/* Iterate over all the students*/
	for (int i = 0; i < instance->get_num_students() && is_feas; i++) {
		route = route_student[i];

		/* Check if the route contains a stop at which the student can be picked up*/
		is_feas = routes->can_route_pick_up_student(route, i);

		/* Increase the number of students assigned to that route*/
		num_stu_route[route]++;
	}

	/* Iterate over all the routes and check that they do not exceed the capacity*/
	for (int i = 0; i < routes->get_num_routes() && is_feas; i++) {
		is_feas = (num_stu_route[i] <= instance->get_cap_buses());
	}

	delete [] num_stu_route;

	return is_feas;
}

void Assignment::assert_assignment() {
	assert(is_feasible());
}

/************* Input/Output (reading and printing) functions *************/

void Assignment::print() {
	int stop_stu; /* Stop that the student is assigned to*/
	double distance_stu; /* Distance that the student traverse to get to the stop*/
	double time_stu; /* Time that takes the student to get to the stop*/

	/* Check that the assignment is feasible*/
	assert_assignment();

	printf(" Assignment of students to stops: \n");
	for (int stu = 0; stu < instance->get_num_students(); stu++) {
		stop_stu = routes->get_closest_stop_student_route(stu, route_student[stu]);
		distance_stu = instance->get_dist_student_stop(stu, stop_stu);
		time_stu = instance->get_time_student_stop(stu, stop_stu);

		printf("    Student %d to Stop %d [%6.2lf, %6.2lf]\n",
				stu, stop_stu, distance_stu, time_stu);
	}
}

void Assignment::print_file_format(FILE* file) {
	/* Check the input parameters */
	assert(file != NULL);

	int stop_stu; /* Stop that the student is assigned to*/

	for (int stu = 0; stu < instance->get_num_students(); stu++) {
		stop_stu = routes->get_closest_stop_student_route(stu, route_student[stu]);
		fprintf(file, "%d %d %d\n", 2, instance->get_student(stu)->get_id() + 1,
				instance->get_stop(stop_stu)->get_id() + 1);
	}
}



