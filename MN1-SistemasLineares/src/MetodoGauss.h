/*
 * MetodoGauss.h
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#ifndef METODOGAUSS_H_
#define METODOGAUSS_H_

#include "MetodoSistema.h"
#include "SistemaLinear.h"

class MetodoGauss: public MetodoSistema {
public:
	MetodoGauss(SistemaLinear& sistema);
	virtual ~MetodoGauss();
	virtual double* calcularRaizes();
};

#endif /* METODOGAUSS_H_ */
