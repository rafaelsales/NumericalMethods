/*
 * MetodoSistemaIterativo.h
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#ifndef METODOSISTEMAITERATIVO_H_
#define METODOSISTEMAITERATIVO_H_

#include "MetodoSistema.h"
#include "SistemaLinear.h"

class MetodoSistemaIterativo: public MetodoSistema {
protected:
	double precisao;
	virtual bool isRaizesBoasSuficiente(double* raizesAnteriores, double* raizes);
public:
	MetodoSistemaIterativo(SistemaLinear& sistema, double precisao);
	virtual ~MetodoSistemaIterativo();
	virtual double* calcularRaizes() = 0;
};

#endif /* METODOSISTEMAITERATIVO_H_ */
