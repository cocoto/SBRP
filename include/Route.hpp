/**
 * \class Route
 *
 * This class models a route in a solution to the SBRP
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef ROUTE_HPP_
#define ROUTE_HPP_

#include <vector>
#include "assert.h"
#include <limits>
#include <stdio.h>

#include "Instance.hpp"
#include "Utils.hpp"

class Route {
private:
	/** Instance for which the route is generated */
	Instance* instance;
	/** Distance of the route */
	double distance;
	/** Duration of the route */
	double time;

	/** Vector containing the index of the stops visited*/
	std::vector<int> route;

public:
	/**
	 * Constructor of the class.
	 *
	 * \param inst instance of the problem
	 *
	 */
	Route(Instance* inst);

	/**
	 * Create a new copy of the object.
	 *
	 * @return a pointer to the copy of the object
	 */
	Route* copy();

	/**
	 * Get the size of the route. In other words, the number of stops that it
	 * visits.
	 *
	 * \return the size of the route
	 */
	int get_size();

	/**
	 * Get the distance traversed by the route.
	 *
	 * \return the distance of the route
	 */
	double get_distance();

	/**
	 * Get the duration of the route.
	 *
	 * \return the duration of the route
	 */
	double get_time();

	/**
	 * Get the (index of the) stop at a specific position in the route.
	 *
	 * \param p position in the route
	 * \return the stop visited at the specified position
	 */
	int get_stop(int p);

	/**
	 * Check if a student can be picked up in one of the stops visited
	 * in the route.
	 *
	 * \param stu_i index of the student
	 * \return true if the student can be picked up, false otherwise.
	 */
	bool can_pick_up_student(int stu_i);

	/**
	 * Calculate the difference in the distance traversed by the route if a
	 * stop is inserted.
	 *
	 * \param s_i index of the stop
	 * \param p position in the route to insert the stop at
	 * \return the difference in the distance
	 */
	double calc_diff_dist_insert_stop(int s_i, int p);

	/**
	 * Calculate the difference in the time required to traverse a route if a
	 * stop is inserted.
	 *
	 * \param s_i index of the stop
	 * \param p position in the route to insert the stop at
	 * \return the difference in the time required
	 */
	double calc_diff_time_insert_stop(int s_i, int p);

	/**
	 * Insert a stop in the route at a specific position.
	 *
	 * \param s_i index of the stop
	 * \param p position in the route to insert the stop at
	 */
	void insert_stop(int s_i, int p);

	/**
	 * Calculate the difference in the distance traversed by the route if a
	 * stop is removed from it.
	 *
	 * \param p position in the route of the stop to be removed
	 * \return the difference in the distance
	 */
	double calc_diff_dist_remove_stop(int p);

	/**
	 * Calculate the difference in the time required to traverse a route if a
	 * stop is removed.
	 *
	 * \param p position in the route of the stop to be removed
	 * \return the difference in the time
	 */
	double calc_diff_time_remove_stop(int p);

	/**
	 * Remove a stop from the route in a specific position.
	 *
	 * \param p position in the route of the stop to be removed
	 */
	void remove_stop_pos(int p);

	/**
	 * Calculate the closest stop in the route to which a student can be
	 * assigned.
	 *
	 * \param stu_i index of the student
	 * \return the index of the closest stop
	 */
	int get_closest_stop_student(int stu_i);

	/************* Assertion functions *************/

	/**
	 * Assert that a position in the route is valid.
	 *
	 * \param p position in the route
	 */
	void assert_pos_route(int p);

	/**
	 * Assert that a position in the route is valid (considering the last position as valid).
	 *
	 * \param p position in the route
	 */
	void assert_pos_route_end(int p);

	/**
	 * Assert that the distance and the travel time of a route are correct.
	 */
	void assert_route_distance_time();

	/************* Input/Output (reading and printing) functions *************/

	/**
	 * Print the route on the console.
	 */
	void print();

	/**
	 * Print the route on a file with a format that can be read by the web service.
	 *
	 * \param file descriptor of the file on which the route will be printed
	 */
	void print_file_format(FILE *file);

};



#endif /* ROUTE_HPP_ */
