/**
 * \class Solution
 *
 * This class models a solution to the SBRP
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef SBRP_INCLUDE_SOLUTION_HPP_
#define SBRP_INCLUDE_SOLUTION_HPP_

#include "Instance.hpp"
#include "Set_routes.hpp"
#include "StopAssignment.h"
#include "Utils.hpp"

class Solution {
private:
	/** Instance for which this is a solution */
	Instance* instance;
	/** Set of routes that the solution involves*/
	Set_routes* routes;
	/** Approach to calculate the assignment of students to stops */
	StopAssignment* assignments;

	/**
	 * Empty constructor of the class.
	 */
	Solution();

public:

	/**
	 * Constructor of the class.
	 *
	 * \param inst instance of the problem
	 */
	Solution(Instance* inst);

	/**
	 * Destructor of the class.
	 */
	~Solution();

	/**
	 * Create a new copy of the object.
	 *
	 * @return a pointer to the copy of the object
	 */
	Solution* copy();

	/**
	 * Check if a solution is empty or not. A solution is considered empty
	 * if there are no routes in it.
	 *
	 * \return true if the solution is empty, false otherwise.
	 */
	bool is_empty();

	/**
	 * Get the number of routes.
	 * \return the number of routes
	 */
	int get_num_routes();

	/**
	 * Get the size of a route in the solution.
	 *
	 * \param r_i index of the route
	 * \return the size of the route
	 */
	int get_size_route(int r_i);

	/**
	 * Get the total distance traversed by the routes in the solution.
	 *
	 * \return the total distance
	 */
	double get_total_distance();

	/**
	 * Get the total duration of the routes in the solution.
	 *
	 * \return the total duration
	 */
	double get_total_time();

	/**
	 * Get the (index of the) stop at a specific position in a route.
	 *
	 * \param r_i index of the route
	 * \param p position in the route
	 * \return the stop visited at the specified position at the specified route.
	 */
	int get_stop_route(int r_i, int p);

	/**
	 * Check if a stop is visited in one of the solutions in the route.
	 *
	 * \param s_i index of the stop
	 * \return true if the stop is visited, false otherwise
	 */
	bool is_stop_visited(int s_i);

	/**
	 * Add a new empty route.
	 */
	void add_empty_route();

	/**
	 * Add a specified number of empty routes.
	 * \param n number of routes to be added
	 */
	void add_empty_route(int n);

	/**
	 * Remove a route from the set of routes.
	 *
	 * \param r_i index of the route
	 */
	void remove_route(int r_i);

	/**
	 * Remove all the empty routes from the set.
	 */
	void remove_empty_routes();

	/**
	 * Remove all routes and therefore all the stops.
	 */
	void clear();

	/**
	 * Check if a student can be picked up in one of the stops visited
	 * in a route.
	 *
	 * \param r_i index of the route
	 * \param stu_i stu_i index of the student
	 * \return true if the student can be picked up in the route, false otherwise.
	 */
	bool can_route_pick_up_student(int r_i, int stu_i);

	/**
	 * Calculate the difference in the distance traversed by the route if a
	 * stop is inserted.
	 *
	 * \param s_i index of the stop
	 * \param r_i index of the route
	 * \param p position in the route to insert the stop at
	 * \return the difference in the distance
	 */
	double calc_diff_dist_insert_stop_route(int s_i, int r_i, int p);

	/**
	 * Calculate the difference in time required to traverse a route if a
	 * stop is inserted.
	 *
	 * \param s_i index of the stop
	 * \param r_i index of the route
	 * \param p position in the route to insert the stop at
	 * \return the difference in the time
	 */
	double calc_diff_time_insert_stop_route(int s_i, int r_i, int p);

	/**
	 * Insert a stop in a route at a specific position.
	 *
	 * \param s_i index of the stop
	 * \param r_i index of the route
	 * \param p position in the route to insert the stop at
	 */
	void insert_stop_route(int s_i, int r_i, int p);

	/**
	 * Calculate the difference in the distance traversed by a route if a
	 * stop is removed from it.
	 *
	 * \param r_i index of the route
	 * \param p position in the route of the stop to be removed
	 * \return the difference in the distance
	 */
	double calc_diff_dist_remove_stop_route(int r_i, int p);

	/**
	 * Calculate the difference in the time required to traverse a route if a
	 * stop is removed.
	 *
	 * \param r_i index of the route
	 * \param p position in the route of the stop to be removed
	 * \return the difference in the time
	 */
	double calc_diff_time_remove_stop_route(int r_i, int p);

	/**
	 * Remove a stop from a route in a specific position.
	 *
	 * \param r_i index of the route
	 * \param p position in the route of the stop to be removed
	 */
	void remove_stop_pos_route(int r_i, int p);

	/************* Functions related to the assignment of students *************/

	/**
	 * Check if the solution allows for a feasible assignment of students to stops.
	 *
	 * \return true if the solution allows for a feasible assignment, false otherwise
	 */
	bool is_assignment_feasible();

	/**
	 * Get the assignment of the students in the solution
	 *
	 * \return an object assignment if the assignment is feasible, NULL otherwise.
	 */
	StopAssignment* get_assignments();


	/************* Input/Output (reading and printing) functions *************/

	/**
	 * Print the solution on the console.
	 */
	void print();

	/**
	 * Print the solution on a file with a format that can be read by the web service.
	 * It prints both the routes traversed by the buses, and the paths of the students
	 * to their assigned stops.
	 *
	 * \param f_p path of the file on which the solution will be printed.
	 */
	void print_file_format(const char* f_p);

	/**
	 * Print the solution on a file with a format that can be read by the web service.
	 * It prints the routes traversed by the buses only.
	 *
	 * \param f_p path of the file on which the solution will be printed.
	 */
	void print_file_format_buses(const char* f_p);

	/**
	 * Print the solution on a file with a format that can be read by the web service.
	 * It prints the paths of the students to their assigned stops only.
	 *
	 * \param f_p path of the file on which the solution will be printed.
	 */
	void print_file_format_students(const char* f_p);

	void merge_paths(int i, int j);

	int get_num_stu(int route);

	int milp_assignment ();

	std::vector<int> get_weights();

};



#endif /* SBRP_INCLUDE_SOLUTION_HPP_ */
