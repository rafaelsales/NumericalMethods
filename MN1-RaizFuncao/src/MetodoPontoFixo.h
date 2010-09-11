/*
 * MetodoPontoFixo.h
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#ifndef METODOPONTOFIXO_H_
#define METODOPONTOFIXO_H_

#include "MetodoRaizFuncaoAbstrato.h"
#include "IFuncao.h"

class MetodoPontoFixo: public MetodoRaizFuncaoAbstrato {
protected:
	IFuncao& funcaoFi;
public:
	MetodoPontoFixo(IFuncao& funcao, IFuncao& funcaoFi, double erro) :
		MetodoRaizFuncaoAbstrato(funcao, erro), funcaoFi(funcaoFi) {
	}

	virtual double encontrarRaiz(double intervaloA, double intervaloB);
};

#endif /* METODOPONTOFIXO_H_ */
