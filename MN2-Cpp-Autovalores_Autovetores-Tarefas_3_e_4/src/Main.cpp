/*
 * Main.cpp
 *
 *  Created on: Apr 12, 2010
 *      Author: Rafael de Castro Dantas Sales - rafaelcds@gmail.com
 */

#include <iostream>
#include <math.h>
#include "MetodoNewtonRaphson.h"
#include "Polinomio.h"
using namespace std;

//Cria o polinomio da equacao característica (x^3 - 12 * x ^ 2 + 38 * x - 29 = 0):
double coeficientesEqCaracteristica[4] = { -29, 38, -12, 1 }; //Em ordem crescente da potencia de x
Polinomio polinomio(coeficientesEqCaracteristica, 4);

double calcularPx(double x) {
	return polinomio.calcular(x);
}

double derivadaEquacaoCaracteristica(double x) {
	return polinomio.calcularDerivada(x);
}

int main() {
	cout << "Calculo de uma raíz da função f(x) = x^3 -12 * x^2 + 38 * x -29" << endl;
	double raiz = MetodoNewtonRaphson::encontrarRaiz(calcularPx, derivadaEquacaoCaracteristica, 0, 10, 0.0001);
	cout << "Raíz encontrada: " << raiz << endl;
	return 0;
}
