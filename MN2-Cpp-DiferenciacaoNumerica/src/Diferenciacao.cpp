/*
 * Diferenciacao.cpp
 *
 *  Created on: Apr 10, 2010
 *      Author: Rafael Sales
 */

#include <iostream>
#include <math.h>
#include "Diferenciacao.h"

using namespace std;

Diferenciacao::Diferenciacao() {
}

bool Diferenciacao::validarPontoFuncaoDefinido(double(*funcao)(double x), double x) {
	static const string MSG_PONTO_NAO_DEFINIDO = "Erro: f(x) não está definido no ponto x = ";
	if (isnan(funcao(x)) || isinf(funcao(x))) {
		cout << MSG_PONTO_NAO_DEFINIDO << x << endl;
		return false;
	}
	return true;
}

double Diferenciacao::calcularDerivada(double(*funcao)(double x), double x, double deltaX, EFilosofia filosofia) {
	double derivadaFxi = 0.0;

	switch (filosofia) {
	case FILOSOFIA_FORWARD:
		if (!validarPontoFuncaoDefinido(funcao, x) || !validarPontoFuncaoDefinido(funcao, x + deltaX)) {
			return 0.0;
		}
		derivadaFxi = (funcao(x + deltaX) - funcao(x)) / (deltaX);
		break;
	case FILOSOFIA_CENTRAL:
		if (!validarPontoFuncaoDefinido(funcao, x - deltaX) || !validarPontoFuncaoDefinido(funcao, x + deltaX)) {
			return 0.0;
		}
		derivadaFxi = (funcao(x + deltaX) - funcao(x - deltaX)) / (2 * deltaX);
		break;
	case FILOSOFIA_BACKWARD:
		if (!validarPontoFuncaoDefinido(funcao, x - deltaX) || !validarPontoFuncaoDefinido(funcao, x)) {
			return 0.0;
		}
		derivadaFxi = (funcao(x) - funcao(x - deltaX)) / (deltaX);
		break;
	}
	cout << "Derivada: " << derivadaFxi << endl;
	return derivadaFxi;
}

double Diferenciacao::calcularDerivadaForward(double(*funcao)(double x), double x, double deltaX) {
	cout << "\n=> Diferenciação Numérica - Filosofia Forward" << endl;
	return calcularDerivada(funcao, x, deltaX, FILOSOFIA_FORWARD);
}

double Diferenciacao::calcularDerivadaCentral(double(*funcao)(double x), double x, double deltaX) {
	cout << "\n=> Diferenciação Numérica - Filosofia Central" << endl;
	return calcularDerivada(funcao, x, deltaX, FILOSOFIA_CENTRAL);
}

double Diferenciacao::calcularDerivadaBackward(double(*funcao)(double x), double x, double deltaX) {
	cout << "\n=> Diferenciação Numérica - Filosofia Backward" << endl;
	return calcularDerivada(funcao, x, deltaX, FILOSOFIA_BACKWARD);
}
