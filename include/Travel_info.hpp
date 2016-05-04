/**
 * \class Travel_info
 *
 * Information for traveling between two pair of vertices
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef SBRP_INCLUDE_TRAVEL_INFO_HPP_
#define SBRP_INCLUDE_TRAVEL_INFO_HPP_

#include "assert.h"
#include <stdio.h>

#include "Utils.hpp"

class Travel_info {
private:
	/** Number of vertices*/
	int num_vert;

	/** Distance matrix*/
	double** distance;

	/** Travel time matrix*/
	double** travel_time;

public:

	/**
	 * Constructor of the class.
	 *
	 * \param n_v Number of vertices
	 */
	Travel_info(int n_v);

	/**
	 * Destructor of the class.
	 */
	~Travel_info();

	/**
	 * Get the distance of the path between a pair of vertices.
	 *
	 * \param v1 First vertex
	 * \param v2 Second vertex
	 * \return The distance between the two vertices
	 */
	double get_distance(int v1, int v2);

	/**
	 * Set the distance of the path between a pair of vertices.
	 *
	 * \param v1 First vertex
	 * \param v2 Second vertex
	 * \param d Distance between the two vertices
	 */
	void set_distance(int v1, int v2, double d);

	/**
	 * Get the travel time to traverse the path between a pair of vertices.
	 *
	 * \param v1 First vertex
	 * \param v2 Second vertex
	 * \return The travel time between the two vertices
	 */
	double get_time(int v1, int v2);

	/**
	 * Set the travel time to traverse the path between a pair of vertices.
	 *
	 * \param v1 First vertex
	 * \param v2 Second vertex
	 * \param t travel time between the two vertices
	 */
	void set_time(int v1, int v2, double t);

	/**
	 * Read the distance matrix from a file. It is assumed that the first number
	 * in the file determines the size of the matrix.
	 *
	 * \param f_p the path (relative or absolute) of the file
	 * \return True if the file was read successfully, false otherwise.
	 */
	bool read_distances_file(const char* f_p);

	/**
	 * Print the distance matrix in the console.
	 */
	void print_distances();

	/**
	 * Read the matrix with travel times from a file. It is assumed that the first number
	 * in the file determines the size of the matrix.
	 *
	 * \param f_p the path (relative or absolute) of the file
	 * \return True if the file was read successfully, false otherwise.
	 */
	bool read_times_file(const char* f_p);

	/**
	 * Print the matrix with the travel times in the console.
	 */
	void print_times();


	/************* Assertion functions *************/

	/**
	 * Assert that an index of a vertex is valid.
	 *
	 * \param v index of the vertex
	 */
	void assert_index_vertex(int v);

	/**
	 * Assert that a number is non-negative, useful to check the distance and
	 * the travel time.
	 *
	 * \param i number to be checked (distance or travel time)
	 */
	void assert_non_negative(double i);


};



#endif /* SBRP_INCLUDE_TRAVEL_INFO_HPP_ */
