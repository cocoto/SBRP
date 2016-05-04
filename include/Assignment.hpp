/**
 * \class Assignment
 *
 * This class represents an assignment of students to stops in a SBRP solution.
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef ASSIGNMENT_HPP_
#define ASSIGNMENT_HPP_

#include "assert.h"

#include "Instance.hpp"
#include "Set_routes.hpp"

class Assignment {
private:
	/** Instance of the problem */
	Instance* instance;
	/** Set of routes considered for the assignment */
	Set_routes* routes;

	/** Route to which each student is assigned*/
	int* route_student;

public:

	/**
	 * Constructor of the class.
	 *
	 * \param i instance of the problem
	 * \param r set of routes of the solution
	 */
	Assignment(Instance* i, Set_routes* r);

	/**
	 * Destructor of the class/
	 */
	~Assignment();

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
	void assign_student_route(int s_i, int r_i);

	/**
	 * Check if an assignment is feasible (taking into account the routes).
	 *
	 * \return true if the assignment is feasible, false otherwise.
	 */
	bool is_feasible();

	/************* Assertion functions *************/

	/**
	 * Assert that an assignment is feasible.
	 */
	void assert_assignment();

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
};



#endif /* ASSIGNMENT_HPP_ */
