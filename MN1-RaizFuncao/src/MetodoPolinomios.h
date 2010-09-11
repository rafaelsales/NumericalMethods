/*
 * MetodoPolinomios.h
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#ifndef METODOPOLINOMIOS_H_
#define METODOPOLINOMIOS_H_

#include "MetodoRaizFuncaoAbstrato.h"
#include "IFuncao.h"

class MetodoPolinomios: public MetodoRaizFuncaoAbstrato {
protected:
	IFuncao& funcaoDerivada;
public:
	MetodoPolinomios(IFuncao& funcao, IFuncao& funcaoDerivada, double erro) :
		MetodoRaizFuncaoAbstrato(funcao, erro), funcaoDerivada(funcaoDerivada) {
	}

	virtual double encontrarRaiz(double intervaloA, double intervaloB);
};

#endif /* METODOPOLINOMIOS_H_ */
