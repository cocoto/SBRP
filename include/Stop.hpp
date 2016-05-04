/**
 * \class Stop
 *
 * This class models a bus stop in the SBRP
 *
 * \author EPS2016
 *
 * \date April, 2016
 */

#ifndef STOP_HPP_
#define STOP_HPP_

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



#endif /* STOP_HPP_ */
