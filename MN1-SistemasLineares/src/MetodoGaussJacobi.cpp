/*
 * MetodoGaussJacobi.cpp
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#include "MetodoGaussJacobi.h"
#include "MetodoSistemaIterativo.h"
#include "SistemaLinear.h"

MetodoGaussJacobi::MetodoGaussJacobi(SistemaLinear& sistema, double precisao) :
	MetodoSistemaIterativo(sistema, precisao) {
}

MetodoGaussJacobi::~MetodoGaussJacobi() {
}

double* MetodoGaussJacobi::primeirosChutes() {
	double* chutes = new double[sistema.numEquacoes];
	for (int i = 0; i < sistema.numEquacoes; i++) {
		chutes[i] = 0.0;
	}
	return chutes;
}

void MetodoGaussJacobi::melhorarRaizes(double* raizesAnteriores, double* raizes, int i) {
	raizes[i] = 0;
	for (int j = 0; j < sistema.numEquacoes; j++) {
		if (i != j) {
			raizes[i] = raizes[i] - sistema.coeficientes[i][j] * raizesAnteriores[j];
		}
	}

	raizes[i] = (raizes[i] + sistema.termosIndependentes[i]) / sistema.coeficientes[i][i];
}

double* MetodoGaussJacobi::calcularRaizes() {
	double* raizesAnteriores = new double[sistema.numEquacoes]; //Raízes da iteração anterior: k
	double* raizes = primeirosChutes(); //Raízes da iteração atual: k+1

	int contIteracoes = 0;
	do {
		int i;
		//Copia as raízes da iteração k+1 para a iteração k:
		for (i = 0; i < sistema.numEquacoes; i++) {
			raizesAnteriores[i] = raizes[i];
		}
		//Calcula as novas raízes:
		for (i = 0; i < sistema.numEquacoes; i++) {
			melhorarRaizes(raizesAnteriores, raizes, i);
		}
		contIteracoes++;
	} while (!isRaizesBoasSuficiente(raizesAnteriores, raizes) && contIteracoes <= 1000);

	if (contIteracoes == 1000) {
		return 0;
	}
	return raizes;
}
