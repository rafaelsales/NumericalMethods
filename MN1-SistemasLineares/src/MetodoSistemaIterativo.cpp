/*
 * MetodoSistemaIterativo.cpp
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#include "MetodoSistemaIterativo.h"
#include "MetodoSistema.h"
#include "SistemaLinear.h"
#include <math.h>

MetodoSistemaIterativo::MetodoSistemaIterativo(SistemaLinear& sistema, double precisao) :
	MetodoSistema(sistema), precisao(precisao) {
}

MetodoSistemaIterativo::~MetodoSistemaIterativo() {
}

bool MetodoSistemaIterativo::isRaizesBoasSuficiente(double* raizesAnteriores, double* raizes) {
	double maiorErroAbsoluto = 0;
	//Calcula o maior erro absoluto: d(k) = max(|Xi(k) - Xi(k-1)|)
	for (int i = 0; i < sistema.numEquacoes; i++) {
		maiorErroAbsoluto = fmax(maiorErroAbsoluto, fabs(raizes[i] - raizesAnteriores[i]));
	}
	double maiorRaiz = raizes[0];
	for (int i = 1; i < sistema.numEquacoes; i++) {
		maiorRaiz = fmax(maiorRaiz, fabs(raizes[i]));
	}
	//Calcula o erro relativo: dr(k) = d(k)/max(Xi(k))
	double erroRelativo = maiorErroAbsoluto / maiorRaiz;
	return erroRelativo < precisao;
}
