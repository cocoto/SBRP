/*
 * NSwap.h
 *
 *  Created on: 26 avr. 2016
 *      Author: popoola
 */

#ifndef NSWAP_H_
#define NSWAP_H_

#include <ANeighborhood.h>

class N_Swap: public ANeighborhood {
public:
	N_Swap(Instance* instance);
	virtual ~N_Swap();
	Solution* getNeighbor(Solution* solution,
			const bool& useMILP, const bool& strategy) const;
};

#endif /* NSWAP_H_ */
