/*
 * ANeighborhood.h
 *
 *  Created on: 26 avr. 2016
 *      Author: popoola
 */

#ifndef ANEIGHBORHOOD_H_
#define ANEIGHBORHOOD_H_
#include "Solution.hpp"
#include "Instance.hpp"
class ANeighborhood {
public:
	ANeighborhood(Instance* instance);
	virtual ~ANeighborhood();
	virtual Solution* getNeighbor(Solution* solution, const bool &useMILP, const bool &strategy=false) const = 0;
protected:
	Instance* _instance;
};

#endif /* ANEIGHBORHOOD_H_ */
