/*
 * MetodoGaussSeidel.cpp
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#include "MetodoGaussSeidel.h"
#include "MetodoGaussJacobi.h"
#include "SistemaLinear.h"

MetodoGaussSeidel::MetodoGaussSeidel(SistemaLinear& sistema, double precisao) :
	MetodoGaussJacobi(sistema, precisao) {
}

MetodoGaussSeidel::~MetodoGaussSeidel() {
}

void MetodoGaussSeidel::melhorarRaizes(double* raizesAnteriores, double* raizes, int i) {
	raizes[i] = 0;
	for (int j = 0; j < sistema.numEquacoes; j++) {
		if (i != j) {
			if (j < i) {
				raizes[i] = raizes[i] - sistema.coeficientes[i][j] * raizes[j];
			} else {
				raizes[i] = raizes[i] - sistema.coeficientes[i][j] * raizesAnteriores[j];
			}
		}
	}

	raizes[i] = (raizes[i] + sistema.termosIndependentes[i]) / sistema.coeficientes[i][i];
}
