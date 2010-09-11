/*
 * MetodoSecante.cpp
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#include <iostream>
#include <math.h>
#include "MetodoSecante.h"

using namespace std;

double MetodoSecante::encontrarRaiz(double intervaloA, double intervaloB) {
	double raizKAnt = 0;
	double raizK;
	double fRaiz;
	double fIntervaloRaizK;
	double fIntervaloRaizKAnt;
	int k = 0;

	//Exibe o cabeçalho da tabela dos dados das iterações do método:
	cout << "k \t Xk \t f(Xk)" << endl;

	do {
		if (k == 0) {
			raizK = intervaloA;
		} else if (k == 1) {
			raizK = intervaloB;
		} else {
			//Obtém f(raizK):
			fIntervaloRaizK = this->funcao.f(raizK);
			//Obtém f(raizKAnt):
			fIntervaloRaizKAnt = this->funcao.f(raizKAnt);
			//Calcula a raiz a aproximada:
			raizK = (raizKAnt * fIntervaloRaizK - raizK * fIntervaloRaizKAnt)
					/ (fIntervaloRaizK - fIntervaloRaizKAnt);
		}
		//Calcula f(raizK):
		fRaiz = this->funcao.f(raizK);

		//Exibe os dados da iteração:
		cout << k++ << " \t " << raizK << " \t " << fRaiz << endl;
	} while (fabs(fRaiz) > this->erro);
	return raizK;
}
