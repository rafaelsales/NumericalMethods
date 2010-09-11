/*
 * MetodoGaussPivotacao.cpp
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#include "MetodoGaussPivotacao.h"
#include "MetodoGauss.h"
#include "SistemaLinear.h"

MetodoGaussPivotacao::MetodoGaussPivotacao(SistemaLinear& sistema) :
	MetodoGauss(sistema) {
	for (int i = 0; i < sistema.numEquacoes; i++) {
		int iMelhorLinha = i;
		for (int k = i + 1; k < sistema.numEquacoes; k++) {
			if (sistema.coeficientes[k][i] > sistema.coeficientes[i][i]) {
				iMelhorLinha = k;
			}
		}
		if (iMelhorLinha != i) {
			sistema.trocarLinhas(i, iMelhorLinha);
		}
	}
}

MetodoGaussPivotacao::~MetodoGaussPivotacao() {
}
