/*
 * Main.cpp
 *
 *  Created on: 27/02/2010
 *      Author: Rafael Sales
 */

#include <iostream>
#include <math.h>
#include <stdio.h>
#include "NewtonCotes.h"
#include "QuadraturaGauss.h"
#include "Exponenciacao.h"

using namespace std;

double funcaoExemplo(double x) {
	return sin(x);
}

double funcaoExemploGaussHermite(double x) {
	return pow(x, 2);
}

double funcaoExemploGaussLaguerre(double x) {
	return 1;
}

double funcaoExemploGaussChebyshev(double x) {
	return x;
}

double funcaoExemploExponenciacao(double x) {
	return sqrt(1.0 + 1.0 / x);
}

void testeRegraTrapezio() {
	NewtonCotes newtonCotes(funcaoExemplo);
	double precisao = 0;
	cout << "Aplicação da Fórmula de Newton-Cotes de grau 1 - Regra do Trapézio" << endl;
	cout << "Integral de f(x) = sen(x) no intervalo [0, PI/2]" << endl;
	while (precisao <= 0) {
		cout << "Digite a precisão (Ex.: 0.0001): ";
		cin >> precisao;
	}
	newtonCotes.calcularTrapezoideFechadaSimples(0, M_PI / 2.0, precisao);
	newtonCotes.calcularTrapezoideFechadaEstendida(0, M_PI / 2.0, precisao);
	newtonCotes.calcularTrapezoideAbertaSimples(0, M_PI / 2.0, precisao);
}

void testeRegraSimpson() {
	NewtonCotes newtonCotes(funcaoExemplo);
	double precisao = 0;
	cout << "Aplicação das Fórmulas de Newton-Cotes de grau 2" << endl;
	cout << "Integral de f(x) = sen(x) no intervalo [0, PI/2]" << endl;
	while (precisao <= 0) {
		cout << "Digite a precisão (Ex.: 0.0001): ";
		cin >> precisao;
	}
	newtonCotes.calcularSimpsons13FechadaSimples(0, M_PI / 2.0, precisao);
	newtonCotes.calcularSimpsons13FechadaEstendida(0, M_PI / 2.0, precisao);
	newtonCotes.calcularGrau2AbertaSimples(0, M_PI / 2.0, precisao);
}

void testeGaussLegendre() {
	double precisao = 0;
	int numPontosLegendre = 0;
	cout << "Aplicação do método de integração Quadratura de Gauss-Legendre" << endl;
	cout << "Integral de f(x) = sen(x) no intervalo [0, PI/2]" << endl;
	while (precisao <= 0) {
		cout << "Digite a precisão (Ex.: 0.0001): ";
		cin >> precisao;
	}
	while (numPontosLegendre < 2 || numPontosLegendre > 4) {
		cout << "Digite o número de pontos de Legendre (Valores possíveis: 2, 3 e 4): ";
		cin >> numPontosLegendre;
	}
	QuadraturaGauss::calcularGaussLegendre(funcaoExemplo, 0, M_PI / 2.0, precisao, numPontosLegendre);
}

void testeGaussHermite() {
	int numPontosHermite = 0;
	cout << "Aplicação do método de integração Quadratura de Gauss-Hermite" << endl;
	cout << "Integral de f(x) = x² * e^(-x²) no intervalo (-INF, +INF)" << endl;
	while (numPontosHermite < 2 || numPontosHermite > 4) {
		cout << "Digite o número de pontos de Hermite (Valores possíveis: 2, 3 e 4): ";
		cin >> numPontosHermite;
	}
	QuadraturaGauss::calcularGaussHermite(funcaoExemploGaussHermite, numPontosHermite);
}

void testeGaussLaguerre() {
	int numPontosLaguerre = 0;
	cout << "Aplicação do método de integração Quadratura de Gauss-Laguerre" << endl;
	cout << "Integral de f(x) = e^(-x) no intervalo [0, +INF)" << endl;
	while (numPontosLaguerre < 2 || numPontosLaguerre > 4) {
		cout << "Digite o número de pontos de Laguerre (Valores possíveis: 2, 3 e 4): ";
		cin >> numPontosLaguerre;
	}
	QuadraturaGauss::calcularGaussLaguerre(funcaoExemploGaussLaguerre, numPontosLaguerre);
}

void testeGaussChebyshev() {
	int numPontosChebyshev = 0;
	double precisao = 0.0;
	cout << "Aplicação do método de integração Quadratura de Gauss-Chebyshev" << endl;
	cout << "Integral de f(x) = x / sqrt(1-x^2) no intervalo [0, 1]" << endl;
	while (precisao <= 0) {
		cout << "Digite a precisão (Ex.: 0.0001): ";
		cin >> precisao;
	}
	while (numPontosChebyshev < 2 || numPontosChebyshev > 4) {
		cout << "Digite o número de pontos de Chebyshev (Valores possíveis: 2, 3 e 4): ";
		cin >> numPontosChebyshev;
	}
	QuadraturaGauss::calcularGaussChebyshev(funcaoExemploGaussChebyshev, 0, 1, precisao, numPontosChebyshev);
}

void testeExponenciacao() {
	double precisao = 0.0;
	cout << "Aplicação do método de integração Exponenciação" << endl;
	cout << "Integral de f(x) = sqrt(1 - 1/x) no intervalo [0, 2]" << endl;
	while (precisao <= 0) {
		cout << "Digite a precisão (Ex.: 0.0001): ";
		cin >> precisao;
	}
	Exponenciacao::calcularExponenciacaoSimples(funcaoExemploExponenciacao, 0, 2, precisao);
	Exponenciacao::calcularExponenciacaoDupla(funcaoExemploExponenciacao, 0, 2, precisao);
}

int main() {
	int opcao;
	do {
		cout << "--- Integração Numérica ---" << endl;
		cout << " 1 - Teste da Regra do Trapezio" << endl;
		cout << " 2 - Teste da Regra de Simpson" << endl;
		cout << " 3 - Teste da Quadratura de Gauss-Legendre" << endl;
		cout << " 4 - Teste da Quadratura de Gauss-Hermite" << endl;
		cout << " 5 - Teste da Quadratura de Gauss-Laguerre" << endl;
		cout << " 6 - Teste da Quadratura de Gauss-Chebyshev" << endl;
		cout << " 7 - Teste da Regra de Exponenciação" << endl;
		cout << " 0 - Sair" << endl;
		cout << "Digite o número da opção: ";
		cin >> opcao;
		cout << endl;

		switch (opcao) {
		case 0:
			return 0;
		case 1:
			testeRegraTrapezio();
			break;
		case 2:
			testeRegraSimpson();
			break;
		case 3:
			testeGaussLegendre();
			break;
		case 4:
			testeGaussHermite();
			break;
		case 5:
			testeGaussLaguerre();
			break;
		case 6:
			testeGaussChebyshev();
			break;
		case 7:
			testeExponenciacao();
			break;
		default:
			cout << "Opção inválida!" << endl;
			continue;
		}
		cout << endl << "=> Cálculos finalizados" << endl;
		cout << "=> Pressione ENTER para continuar" << endl;
		cin.get();
		cin.get();
	} while (opcao != 0);
	return 0;
}
