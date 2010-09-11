#include "Polinomio.h"
#include <iostream>

Polinomio::Polinomio(double* coeficientes, int numCoeficientes) {
	this->coeficientes = coeficientes;
	this->numCoeficientes = numCoeficientes;
}

double Polinomio::calcular(double x) {
	int i, grau;
	grau = this->numCoeficientes - 1;
	double resultado = coeficientes[grau];
	//Calcula o b[0] de b[i] = b[i+1] * x + a[i], onde a é coeficiente, de forma iterativa:
	for (i = grau - 1; i >= 0; i--) {
		resultado = resultado * x + coeficientes[i];
	}
	return resultado;
}

double Polinomio::calcularDerivada(double x) {
	int i, grau;
	grau = this->numCoeficientes - 1;
	double resultado = coeficientes[grau] * grau;
	int grauAtual = grau - 1;
	//Calcula o c[1] de c[i] = c[i+1] * x + a[i] * (grau de a), onde a é coeficiente, de forma iterativa:
	for (i = grau - 1; i >= 1; i--) {
		resultado = resultado * x + coeficientes[i] * grauAtual;
		grauAtual--;
	}
	return resultado;
}
