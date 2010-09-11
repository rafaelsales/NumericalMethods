/*
 * SistemaLinear.cpp
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#include "SistemaLinear.h"

SistemaLinear::SistemaLinear(double** coeficientes, double* termosIndependentes, int numEquacoes) :
	coeficientes(coeficientes), termosIndependentes(termosIndependentes), numEquacoes(numEquacoes) {
}

SistemaLinear::~SistemaLinear() {
	for (int i = 0; i < numEquacoes; i++) {
		delete[] coeficientes[i];
	}
	delete[] coeficientes;
	delete[] termosIndependentes;
}

void SistemaLinear::trocarLinhas(int l1, int l2) {
	double* coeficientesL1 = coeficientes[l1];
	double termoIndependenteL1 = termosIndependentes[l1];
	coeficientes[l1] = coeficientes[l2];
	termosIndependentes[l1] = termosIndependentes[l2];
	coeficientes[l2] = coeficientesL1;
	termosIndependentes[l2] = termoIndependenteL1;
}
