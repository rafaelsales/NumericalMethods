/*
 * MetodoNewtonRaphson.h
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#ifndef METODONEWTONRAPHSON_H_
#define METODONEWTONRAPHSON_H_

#include "MetodoRaizFuncaoAbstrato.h"
#include "IFuncao.h"

class MetodoNewtonRaphson: public MetodoRaizFuncaoAbstrato {
protected:
	IFuncao& funcaoDerivada;
public:
	MetodoNewtonRaphson(IFuncao& funcao, IFuncao& funcaoDerivada, double erro) :
		MetodoRaizFuncaoAbstrato(funcao, erro), funcaoDerivada(funcaoDerivada) {
	}

	virtual double encontrarRaiz(double intervaloA, double intervaloB);
};

#endif /* METODONEWTONRAPHSON_H_ */
