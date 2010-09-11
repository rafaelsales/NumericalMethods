/*
 * MetodoPosicaoFalsa.h
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#ifndef METODOPOSICAOFALSA_H_
#define METODOPOSICAOFALSA_H_

#include "MetodoRaizFuncaoAbstrato.h"
#include "IFuncao.h"

class MetodoPosicaoFalsa: public MetodoRaizFuncaoAbstrato {
public:
	MetodoPosicaoFalsa(IFuncao& funcao, double erro) :
		MetodoRaizFuncaoAbstrato(funcao, erro) {
	}

	virtual double encontrarRaiz(double intervaloA, double intervaloB);
};

#endif /* METODOPOSICAOFALSA_H_ */
