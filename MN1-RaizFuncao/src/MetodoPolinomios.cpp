/*
 * MetodoPolinomios.cpp
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#include <iostream>
#include <math.h>
#include "MetodoPolinomios.h"

using namespace std;

double MetodoPolinomios::encontrarRaiz(double intervaloA, double intervaloB) {
	double raiz;
	double fRaiz;
	int k = 0;

	//Exibe o cabeçalho da tabela dos dados das iterações do método:
	cout << "k \t Xk \t f(Xk)" << endl;
	do {
		//Neste método o valor da raíz na primeira iteração é um chute:
		if (k == 0) {
			//O chute que escolhemos é meio do intervalo dado:
			raiz = (intervaloA + intervaloB) / 2;
		} else {
			//Calcula a raiz a aproximada:
			raiz = raiz - (this->funcao.f(raiz) / this->funcaoDerivada.f(raiz));
		}
		//Calcula f(raiz):
		fRaiz = this->funcao.f(raiz);

		//Exibe os dados da iteração:
		cout << k++ << " \t " << raiz << " \t " << fRaiz << " \t " << endl;
	} while (fabs(fRaiz) > this->erro);
	return raiz;
}
