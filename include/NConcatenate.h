/*
 * NConcatenate.h
 *
 *  Created on: 26 avr. 2016
 *      Author: popoola
 */

#ifndef NCONCATENATE_H_
#define NCONCATENATE_H_

#include <ANeighborhood.h>

class N_Concatenate: public ANeighborhood {
public:
	N_Concatenate(Instance* instance);
	Solution* getNeighbor(Solution* solution, const bool &useMILP, const bool &strategy=false) const;

};

#endif /* NCONCATENATE_H_ */
