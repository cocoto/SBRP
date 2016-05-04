/**
 * \class Stop
 *
 * This class models a bus stop in the SBRP
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef SBRP_INCLUDE_STOP_HPP_
#define SBRP_INCLUDE_STOP_HPP_

#include "Vertex.hpp"
#include "Utils.hpp"

class Stop:public Vertex {
public:
	/**
	 * Constructor of the class.
	 * \param i the identifier of the stop vertex
	 */
	Stop(int i);

};



#endif /* SBRP_INCLUDE_STOP_HPP_ */
