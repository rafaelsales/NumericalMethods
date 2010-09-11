/*
 * MetodoRaizFuncaoAbstrato.h
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#ifndef METODORAIZFUNCAOABSTRATO_H_
#define METODORAIZFUNCAOABSTRATO_H_
#include "IFuncao.h"

class MetodoRaizFuncaoAbstrato {
protected:
	IFuncao& funcao;
	double erro;
public:
	/**
	 * @param funcao
	 * @param erro - Erro para condição de parada
	 */
	MetodoRaizFuncaoAbstrato(IFuncao& funcao, double erro) :
		funcao(funcao), erro(erro) {
	}

	/**
	 * Aplica o método sobre a função para encontrar uma raiz no intervalo fechado [intervaloA, intervaloB]
	 * @param intervaloA
	 * @param intervaloB
	 * @return raiz encontrada
	 */
	virtual double encontrarRaiz(double intervaloA, double intervaloB) = 0;
};

#endif /* METODORAIZFUNCAOABSTRATO_H_ */
