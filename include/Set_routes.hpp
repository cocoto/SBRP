/**
 * \class Set_routes
 *
 * This class models the set of routes that compose a solution to the SBRP
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef SET_ROUTES_HPP_
#define SET_ROUTES_HPP_

#include "assert.h"
#include <vector>
#include <stdio.h>

#include "Route.hpp"
#include "Utils.hpp"

class Set_routes {
	/** Instance for which the set of routes is built */
private:
	Instance* instance;
	/** Total distance traversed by the routes */
	double total_distance;
	/** Total duration of the routes */
	double total_time;

	/** Routes */
	std::vector<Route*> route;

	/** (Index of the) Route that visits a stop.*/
	int* route_stop;

public:

	/**
	 * Constructor of the class.
	 *
	 * \param inst instance of the problem
	 */
	Set_routes(Instance* inst);

	/**
	 * Destructor of the class.
	 */
	~Set_routes();

	/**
	 * Create a new copy of the object.
	 *
	 * @return a pointer to the copy of the object
	 */
	Set_routes* copy();

	/**
	 * Check if a set of routes is empty or not. A set of routes is considered empty
	 * if there are no routes in it.
	 *
	 * \return true if the set of routes is empty, false otherwise.
	 */
	bool is_empty();

	/**
	 * Get the number of routes.
	 *
	 * \return the number of routes
	 */
	int get_num_routes();

	/**
	 * Get the size of a route.
	 *
	 * \param r_i index of the route
	 * \return the size of the route
	 */
	int get_size_route(int r_i);

	/**
	 * Get the total distance traversed by the routes.
	 *
	 * \return the total distance
	 */
	double get_total_distance();

	/**
	 * Get the total duration of the routes.
	 *
	 * \return the total duration
	 */
	double get_total_time();

	/**
	 * Check if a stop is visited in one of the routes.
	 *
	 * \param s_i index of the stop
	 * \return true if the stop is visited, false otherwise
	 */
	bool is_stop_visited(int s_i);

	/**
	 * Get the (index of the) stop at a specific position in a route.
	 *
	 * \param r_i index of the route
	 * \param p position in the route
	 * \return the stop visited at the specified position at the specified route.
	 */
	int get_stop_route(int r_i, int p);

	/**
	 * Add a new empty route.
	 */
	void add_empty_route();

	/**
	 * Add a specified number of empty routes.
	 *
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

	/**
	 * Calculate the closest stop in a route to which a student can be
	 * assigned.
	 *
	 * \param stu_i index of the student
	 * \param r_i index of the route
	 * \return the index of the closest stop
	 */
	int get_closest_stop_student_route(int stu_i, int r_i);


	/************* Assertion functions *************/

	/**
	 * Assert that an index of a route is valid.
	 *
	 * \param r_i index of the route
	 */
	void assert_index_route(int r_i);

	/**
	 * Assert that a position in a route is valid.
	 *
	 * \param r_i index of the route
	 * \param p position in the route
	 */
	void assert_pos_route(int r_i, int p);

	/**
	 * Assert that a position in a route is valid (considering the position at the end as valid).
	 *
	 * \param r_i index of the route
	 * \param p position in the route
	 */
	void assert_pos_route_end(int r_i, int p);

	/**
	 * Assert that the routes are correct. In other words, that the travelled distance and the
	 * time are correct, and that each stop is assigned to the correct route.
	 */
	void assert_routes_structure();

	/************* Input/Output (reading and printing) functions *************/

	/**
	 * Print the routes on the console.
	 */
	void print();

	/**
	 * Print the routes on a file with a format that can be read by the web service.
	 *
	 * \param file descriptor of the file on which the routes will be printed
	 */
	void print_file_format(FILE *file);


};



#endif /* SET_ROUTES_HPP_ */
