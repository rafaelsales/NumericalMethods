/*
 * Main.cpp
 *
 *  Created on: 10/04/2010
 *      Author: Rafael Sales
 */

#include <iostream>
#include <math.h>
#include "Diferenciacao.h"

using namespace std;

double funcaoSeno(double x) {
	return sin(x);
}

double funcaoDerivadaSeno(double x) {
	return cos(x);
}

void testeDiferenciacao() {
	double deltaX = 0;
	double x;
	cout << "Aplicação da Diferenciação Numérica (Filosofias: Forward, Central e Backward)" << endl;
	cout << "Derivada de f(x) = sen(x)  =>  f'(x) = cos(x)" << endl;

	cout << "Digite o valor do ponto x (Ex.: 0.5): ";
	cin >> x;

	while (deltaX <= 0) {
		cout << "Digite o valor do delta x (Ex.: 0.0001): ";
		cin >> deltaX;
	}

	cout << endl << "Derivada exata: " << funcaoDerivadaSeno(x) << endl;

	Diferenciacao::calcularDerivadaForward(funcaoSeno, x, deltaX);
	Diferenciacao::calcularDerivadaCentral(funcaoSeno, x, deltaX);
	Diferenciacao::calcularDerivadaBackward(funcaoSeno, x, deltaX);
}

int main() {
	testeDiferenciacao();
	cout << endl << "=> Cálculos finalizados" << endl;
	return 0;
}
