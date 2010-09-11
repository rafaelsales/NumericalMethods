/*
 * MetodoSecante.h
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#ifndef METODOSECANTE_H_
#define METODOSECANTE_H_

#include "MetodoRaizFuncaoAbstrato.h"
#include "IFuncao.h"

class MetodoSecante: public MetodoRaizFuncaoAbstrato {
public:
	MetodoSecante(IFuncao& funcao, double erro) :
		MetodoRaizFuncaoAbstrato(funcao, erro) {
	}

	virtual double encontrarRaiz(double intervaloA, double intervaloB);
};

#endif /* METODOSECANTE_H_ */
