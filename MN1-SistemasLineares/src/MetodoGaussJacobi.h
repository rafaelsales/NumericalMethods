/*
 * MetodoGaussJacobi.h
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#ifndef METODOGAUSSJACOBI_H_
#define METODOGAUSSJACOBI_H_

#include "MetodoSistemaIterativo.h"

class MetodoGaussJacobi: public MetodoSistemaIterativo {
protected:
	virtual double* primeirosChutes();
	virtual void melhorarRaizes(double* raizesAnteriores, double* raizes, int i);
public:
	MetodoGaussJacobi(SistemaLinear& sistema, double precisao);
	virtual ~MetodoGaussJacobi();
	virtual double* calcularRaizes();
};

#endif /* METODOGAUSSJACOBI_H_ */
