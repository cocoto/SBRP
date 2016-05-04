/**
 * \class School
 *
 * This class models a school in the SBRP
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef SCHOOL_HPP_
#define SCHOOL_HPP_

#include "Vertex.hpp"
#include "Utils.hpp"

class School:public Vertex {
public:
	/**
	 * Constructor of the class.
	 * \param i the identifier of the school vertex
	 */
	School(int i);

};


#endif /* SCHOOL_HPP_ */
