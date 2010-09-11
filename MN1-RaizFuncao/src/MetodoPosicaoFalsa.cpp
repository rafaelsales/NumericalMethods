/*
 * MetodoPosicaoFalsa.cpp
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#include <iostream>
#include <math.h>
#include "MetodoPosicaoFalsa.h"

using namespace std;

double MetodoPosicaoFalsa::encontrarRaiz(double intervaloA, double intervaloB) {
	double raiz;
	double fRaiz;
	double sinal;
	double absFIntervaloA;
	double absFIntervaloB;
	int k = 0;

	//Exibe o cabeçalho da tabela dos dados das iterações do método:
	cout << "k \t ak \t bk \t Xk \t f(Xk) \t |ak - bk|" << endl;

	do {
		//Obtém o módulo de f(intervaloA):
		absFIntervaloA = fabs(this->funcao.f(intervaloA));
		//Obtém o módulo de f(intervaloB):
		absFIntervaloB = fabs(this->funcao.f(intervaloB));
		//Calcula a raiz a aproximada:
		raiz = (intervaloA * absFIntervaloB + intervaloB * absFIntervaloA)
				/ (absFIntervaloA + absFIntervaloB);
		//Calcula f(raiz):
		fRaiz = this->funcao.f(raiz);

		//Exibe os dados da iteração:
		cout << k++ << " \t " << intervaloA << " \t " << intervaloB << " \t " << raiz
				<< " \t " << fRaiz << " \t " << fabs(intervaloA - intervaloB)
				<< endl;

		//Obtém o sinal de f(intervaloA)*f(raiz) para saber o novo intervalo onde está a raiz:
		sinal = this->funcao.f(intervaloA) * fRaiz;
		if (sinal < 0) {
			//Neste caso a raíz estará em [intervaloA, raiz]
			intervaloB = raiz;
		} else {
			//Neste caso a raíz estará em [raiz, intervaloB]
			intervaloA = raiz;
		}
	} while (fabs(fRaiz) > this->erro);
	return raiz;
}
