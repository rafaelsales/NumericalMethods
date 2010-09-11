/*
 * MetodoNewtonRaphson.cpp
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#include <iostream>
#include <math.h>
#include "MetodoNewtonRaphson.h"

using namespace std;

double MetodoNewtonRaphson::encontrarRaiz(double(*funcao)(double x), double(*funcaoDerivada)(double x), double intervaloA, double intervaloB, double erro) {
	cout << "\n=> Raiz de função - Método Newton-Raphson" << endl;
	double raiz = 0;
	double fRaiz;
	int k = 0;

	//Exibe o cabeçalho da tabela dos dados das iterações do método:
	cout << "k  |  Xk  |  f(Xk)" << endl;
	do {
		//Neste método o valor da raíz na primeira iteração é um chute:
		if (k == 0) {
			//O chute que escolhemos é meio do intervalo dado:
			raiz = (intervaloA + intervaloB) / 2;
		} else {
			//Calcula a raiz a aproximada:
			raiz = raiz - (funcao(raiz) / funcaoDerivada(raiz));
		}
		//Calcula f(raiz):
		fRaiz = funcao(raiz);

		//Exibe os dados da iteração:
		cout << k++ << "  |  " << raiz << "  |  " << fRaiz << endl;
	} while (fabs(fRaiz) > erro);
	return raiz;
}
