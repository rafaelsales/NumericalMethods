/*
 * MetodoGaussSeidel.h
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#ifndef METODOGAUSSSEIDEL_H_
#define METODOGAUSSSEIDEL_H_

#include "MetodoGaussJacobi.h"
#include "SistemaLinear.h"

class MetodoGaussSeidel: public MetodoGaussJacobi {
	virtual void melhorarRaizes(double* raizesAnteriores, double* raizes, int i);
public:
	MetodoGaussSeidel(SistemaLinear& sistema, double precisao);
	virtual ~MetodoGaussSeidel();
};

#endif /* METODOGAUSSSEIDEL_H_ */
