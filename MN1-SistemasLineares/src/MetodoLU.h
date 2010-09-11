/*
 * MetodoLU.h
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#ifndef METODOLU_H_
#define METODOLU_H_

#include "MetodoSistema.h"
#include "SistemaLinear.h"

class MetodoLU: public MetodoSistema {
public:
	MetodoLU(SistemaLinear& sistema);
	virtual ~MetodoLU();
	virtual double* calcularRaizes();
};

#endif /* METODOLU_H_ */
