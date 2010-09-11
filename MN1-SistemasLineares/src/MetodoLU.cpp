/*
 * MetodoLU.cpp
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#include "MetodoLU.h"
#include "MetodoSistema.h"
#include "SistemaLinear.h"
#include <iostream>

MetodoLU::MetodoLU(SistemaLinear& sistema) :
	MetodoSistema(sistema) {
}

MetodoLU::~MetodoLU() {
}

double* MetodoLU::calcularRaizes() {
	//Cria a matriz de multiplicadores, que inicialmente é uma matriz identidade:
	double** multiplicadores = new double*[sistema.numEquacoes];
	for (int i = 0; i < sistema.numEquacoes; i++) {
		multiplicadores[i] = new double[sistema.numEquacoes];
		for (int j = 0; j < sistema.numEquacoes; j++) {
			multiplicadores[i][j] = 0;
		}
		multiplicadores[i][i] = 1;
	}

	//Deixa a matriz do sistema na forma de matriz triangular:
	for (int k = 0; k < sistema.numEquacoes; k++) {
		double pivo = sistema.coeficientes[k][k];

		//Zera os elementos da coluna k das linhas k + 1 até a última linha:
		for (int i = k + 1; i < sistema.numEquacoes; i++) {
			//Calcula o multiplicador M(i,k) para zerar o elemento [i][k]:
			multiplicadores[k][i] = sistema.coeficientes[i][k] / pivo;

			//Calcula os novos valores das colunas da linha i:
			sistema.coeficientes[i][k] = 0;
			for (int j = k + 1; j < sistema.numEquacoes; j++) {
				//Calcula Li = Li - Lk * M(i,k):
				sistema.coeficientes[i][j] -= multiplicadores[k][i] * sistema.coeficientes[k][j];
			}

			//Cacula o novo valor do termo indepentente da linha i:
			sistema.termosIndependentes[i] -= multiplicadores[k][i] * sistema.termosIndependentes[k];
		}
	}

	//Calcula os termos independentes do sistema baseado somente na matriz de multiplicadores:
	double* termosIndependentesLU = new double[sistema.numEquacoes];

	for (int i = 0; i < sistema.numEquacoes; i++) {
		termosIndependentesLU[i] = sistema.termosIndependentes[i];
		for (int j = 0; j < i; j++) {
			termosIndependentesLU[i] = termosIndependentesLU[i] - multiplicadores[i][j] * termosIndependentesLU[j];
		}
		termosIndependentesLU[i] = termosIndependentesLU[i] / multiplicadores[i][i];
		std::cout << "m " << multiplicadores[0][i] << " t " << termosIndependentesLU[i] << std::endl;
	}

	//Efetua retro-substituição para calcular as raízes:
	double* raizes = new double[sistema.numEquacoes];

	for (int i = sistema.numEquacoes - 1; i >= 0; i--) {
		raizes[i] = termosIndependentesLU[i];
		for (int j = sistema.numEquacoes - 1; j > i; j--) {
			raizes[i] = raizes[i] - sistema.coeficientes[i][j] * raizes[j];
		}
		raizes[i] = raizes[i] / sistema.coeficientes[i][i];
	}

	delete[] multiplicadores;
	return raizes;
}
