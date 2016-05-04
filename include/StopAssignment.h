/*
 * StopAssignment.h
 *
 *  Created on: 26 avr. 2016
 *      Author: popoola
 */

#ifndef STOPASSIGNMENT_H_
#define STOPASSIGNMENT_H_
#include "assert.h"
#include "Instance.hpp"

class StopAssignment {
private:
	/** Instance of the problem */
	Instance* instance;
	/** Set of routes considered for the assignment */
	Stop** stops;

	/** Route to which each student is assigned*/
	int* stop_student;

public:

	/**
	 * Constructor of the class.
	 *
	 * \param i instance of the problem
	 * \param r set of routes of the solution
	 */
	StopAssignment(Instance* i, Stop** s);

	StopAssignment(StopAssignment& s);
	/**
	 * Destructor of the class/
	 */
	~StopAssignment();

	/**
	 * Remove all the assignments made.
	 */
	void remove_all_assignments();

	/**
	 * Check if a student has been assigned to a route.
	 *
	 * \param s_i index of the student
	 * \return true if the student has been assigned, false otherwise.
	 */
	bool is_student_assigned(int s_i);

	/**
	 * Assign a student to a route.
	 *
	 * \param s_i index of the student
	 * \param r_i index of the route
	 */
	void assign_student_stop(int s_i, int r_i);

	/**
	 * Check if an assignment is feasible (taking into account the routes).
	 *
	 * \return true if the assignment is feasible, false otherwise.
	 */
	//bool is_feasible();

	/************* Assertion functions *************/

	/**
	 * Assert that an assignment is feasible.
	 */
	//void assert_assignment();

	/************* Input/Output (reading and printing) functions *************/

	/**
	 * Print the assignment on the console.
	 */
	void print();

	/**
	 * Print the assignment on a file with a format that can be read by the web service.
	 *
	 * \param file descriptor of the file on which the assignment will be printed
	 */
	void print_file_format(FILE *file);

	/**
	 * Get the stop to which a student is assigned
	 * @param student
	 * @return stop id assigned to student
	 */

	int get_stop_number(int student);

	/**
	 * Check if a stop is open or closed
	 * @return true if a stop is contained in any of the used routes
	 */
	std::vector<bool> stops_used();
};

#endif /* STOPASSIGNMENT_H_ */
