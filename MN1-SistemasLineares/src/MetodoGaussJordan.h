/*
 * MetodoGaussJordan.h
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#ifndef METODOGAUSSJORDAN_H_
#define METODOGAUSSJORDAN_H_

#include "MetodoSistema.h"

class MetodoGaussJordan: public MetodoSistema {
public:
	MetodoGaussJordan(SistemaLinear& sistema);
	virtual ~MetodoGaussJordan();
	virtual double* calcularRaizes();
};

#endif /* METODOGAUSSJORDAN_H_ */
