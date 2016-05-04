/*
 * StopAssignment.cpp
 *
 *  Created on: 26 avr. 2016
 *      Author: popoola
 */

#include <StopAssignment.h>
#include <cstdlib>
#include <iostream>

StopAssignment::StopAssignment(Instance* i, Stop** s) {
	instance = i;
	stops = s;

	/* Initialize the array that stores the route that each student is assigned to*/
	stop_student = new int[instance->get_num_students()];
	for (int i = 0; i < instance->get_num_students(); i++) {
		stop_student[i] = -1; /* It is assumed that -1 represent unassigned students*/
	}
}

StopAssignment::StopAssignment(StopAssignment& s):instance(s.instance),stops(s.stops),stop_student(s.stop_student) {
}

StopAssignment::~StopAssignment() {
	delete[] stop_student;
}

void StopAssignment::remove_all_assignments() {
	for (int i = 0; i < instance->get_num_students(); i++) {
		stop_student[i] = -1; /* It is assumed that -1 represent unassigned students*/
	}
}

bool StopAssignment::is_student_assigned(int s_i) {
	instance->assert_index_student(s_i);
	return stop_student[s_i] == -1;
}

void StopAssignment::assign_student_stop(int s_i, int r_i) {
	/* Check the input parameters */
	instance->assert_index_student(s_i);
	instance->assert_index_stop(r_i);

	stop_student[s_i] = r_i;
}

void StopAssignment::print() {
	int stop_stu; /* Stop that the student is assigned to*/
	double distance_stu; /* Distance that the student traverse to get to the stop*/
	double time_stu; /* Time that takes the student to get to the stop*/

	/* Check that the assignment is feasible*/
	//assert_assignment();

	printf(" Assignment of students to stops: \n");
	int nb_students = instance->get_num_students();
	printf("nb_students: %d\n", nb_students);
	for (int stu = 0; stu < nb_students; stu++) {
		stop_stu = stop_student[stu];

		printf("stop_stu: %d\n", stop_stu);
		distance_stu = instance->get_dist_student_stop(stu, stop_stu);
		time_stu = instance->get_time_student_stop(stu, stop_stu);

		printf("    Student %d to Stop %d [%6.2lf, %6.2lf]\n",
				stu, stop_stu, distance_stu, time_stu);
	}
}

void StopAssignment::print_file_format(FILE* file) {
	/* Check the input parameters */
	assert(file != NULL);

	int stop_stu; /* Stop that the student is assigned to*/

	for (int stu = 0; stu < instance->get_num_students(); stu++) {
		stop_stu = stop_student[stu];
		fprintf(file, "%d %d %d\n", 2, instance->get_student(stu)->get_id() + 1,
				instance->get_stop(stop_stu)->get_id() + 1);
	}
}

/**
	 * Get the stop to which a student is assigned
	 * @param student
	 * @return stop id assigned to student
	 */

int StopAssignment::get_stop_number(int student) {
	return stop_student[student];
}


/**
	 * Check if a stop is open or closed
	 * @return true if a stop is contained in any of the used routes
	 */
std::vector<bool> StopAssignment::stops_used() {
	int nb_stops = instance->get_num_stops();
	std::cout << nb_stops << std::endl;
	std::vector<bool> is_assigned(false, nb_stops);
	int n = instance->get_num_students();
	std::cout << n << std::endl;
	for (int i = 0; i < n; ++i) {
		is_assigned[stop_student[i]] = true;
	}
	return is_assigned;
}
