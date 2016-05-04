/**
 * \class Vertex
 *
 * This class models a vertex in the graph. A vertex can be either a school,
 * a student (or a group of students) or a potential bus stop.
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef SBRP_INCLUDE_VERTEX_HPP_
#define SBRP_INCLUDE_VERTEX_HPP_

#include "Utils.hpp"

class Vertex {

protected:
	/** Identifier */
	int id;

public:
	/**
	 * Constructor of the class.
	 * \param i the identifier of the vertex
	 */
	Vertex(int i);

	/**
	 * Get the identifier of the vertex.
	 */
	int get_id();
};

#endif /* SBRP_INCLUDE_VERTEX_HPP_ */
