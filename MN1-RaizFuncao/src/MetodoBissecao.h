/*
 * MetodoBissecao.h
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#ifndef METODOBISSECAO_H_
#define METODOBISSECAO_H_

#include "MetodoRaizFuncaoAbstrato.h"
#include "IFuncao.h"

class MetodoBissecao: public MetodoRaizFuncaoAbstrato {
public:
	MetodoBissecao(IFuncao& funcao, double erro) :
		MetodoRaizFuncaoAbstrato(funcao, erro) {
	}

	virtual double encontrarRaiz(double intervaloA, double intervaloB);
};

#endif /* METODOBISSECAO_H_ */
