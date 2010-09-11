/*
 * MetodoGauss.cpp
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#include "MetodoGauss.h"
#include "MetodoSistema.h"
#include "SistemaLinear.h"

MetodoGauss::MetodoGauss(SistemaLinear& sistema) :
	MetodoSistema(sistema) {
}

MetodoGauss::~MetodoGauss() {
}

double* MetodoGauss::calcularRaizes() {
	//Deixa a matriz do sistema na forma de matriz triangular:
	for (int k = 0; k < sistema.numEquacoes; k++) {
		double pivo = sistema.coeficientes[k][k];
		/* O numero de multiplicadores é o numero de linhas que tem que
		 * ter seu elemento da coluna k com valor 0:
		 */
		int numMultiplicadores = sistema.numEquacoes - k + 1;
		double* multiplicadores = new double[numMultiplicadores];

		//Zera os elementos da coluna k das linhas k + 1 até a última linha:
		for (int i = k + 1, iMultiplicador = 0; i < sistema.numEquacoes; i++, iMultiplicador++) {
			//Calcula o multiplicador M(i,k) para zerar o elemento [i][k]:
			multiplicadores[iMultiplicador] = sistema.coeficientes[i][k] / pivo;

			//Calcula os novos valores das colunas da linha i:
			sistema.coeficientes[i][k] = 0;
			for (int j = k + 1; j < sistema.numEquacoes; j++) {
				//Calcula Li = Li - Lk * M(i,k):
				sistema.coeficientes[i][j] -= multiplicadores[iMultiplicador] * sistema.coeficientes[k][j];
			}

			//Cacula o novo valor do termo indepentente da linha i:
			sistema.termosIndependentes[i] -= multiplicadores[iMultiplicador] * sistema.termosIndependentes[k];
		}

		delete[] multiplicadores;
	}

	//Efetua retro-substituição para calcular as raízes:
	double* raizes = new double[sistema.numEquacoes];

	for (int i = sistema.numEquacoes - 1; i >= 0; i--) {
		raizes[i] = sistema.termosIndependentes[i];
		for (int j = sistema.numEquacoes - 1; j > i; j--) {
			raizes[i] = raizes[i] - sistema.coeficientes[i][j] * raizes[j];
		}
		raizes[i] = raizes[i] / sistema.coeficientes[i][i];
	}

	return raizes;
}
