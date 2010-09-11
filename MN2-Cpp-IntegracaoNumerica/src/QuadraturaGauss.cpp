/*
 * QuadraturaGauss.cpp
 *
 *  Created on: Mar 20, 2010
 *      Author: root
 */

#include <iostream>
#include <math.h>
#include "QuadraturaGauss.h"

using namespace std;

QuadraturaGauss::QuadraturaGauss() {
}

double QuadraturaGauss::calcularGaussLegendre(double(*funcao)(double x), double intervaloA, double intervaloB, double precisao, int numPontos) {
	if (numPontos < 2 || numPontos > 4) {
		cout << "Número de pontos inválido. Valores possíveis: 2, 3 e 4" << endl;
		return 0.0;
	}
	cout << "\n=> Integração Numérica - Gauss-Legendre utilizando " << numPontos << " pontos de Legendre" << endl;
	/* Tabelas com os pontos de Legendre.
	 * A primeira coluna é o ponto de Legendre e a segunda é o peso correspondente.
	 */
	double tabelaLegendreN2[2][2] = {
			{ -0.577350269, 1.0 },
			{ 0.577350269, 1.0 }
	};
	double tabelaLegendreN3[3][2] = {
			{ -0.774596669, 0.555555556 },
			{ 0, 0.888888889 },
			{ 0.774596669, 0.555555556 }
	};
	double tabelaLegendreN4[4][2] = {
			{ -0.861136312, 0.347854845 },
			{ -0.339981043, 0.652145155 },
			{ 0.339981043, 0.652145155 },
			{ 0.861136312, 0.347854845 }
	};
	cout << "Num. Interavalos  -  Integral  -  Erro" << endl;
	int numIntervalos = 1;
	double resultadoAtual = 0.0;
	double resultadoAnterior;
	double erro = NAN;
	double intervaloAi, intervaloBi;
	double tamanhoSubintervalo;
	do {
		resultadoAnterior = resultadoAtual;
		resultadoAtual = 0.0;
		intervaloAi = intervaloA;
		intervaloBi = intervaloB;
		tamanhoSubintervalo = (intervaloB - intervaloA) / numIntervalos;
		//I = [(b - a) / 2] * [Somatorio dos pesos multiplicados pelos f((pl * (b - a) + a + b) / 2)] onde pl é um ponto de Legendre
		for (int i = 1; i <= numIntervalos; i++) {
			intervaloBi = intervaloAi + tamanhoSubintervalo;
			double resultadoSubintervalo = 0.0;
			for (int iPL = 0; iPL < numPontos; iPL++) {
				double pl = 0.0; //Ponto de Legendre atual
				double peso = 0.0; //Peso correspondente ao peso de Legendre atual
				//Decide qual ponto de Lengendre e peso sera usado:
				switch (numPontos) {
				case 2:
					pl = tabelaLegendreN2[iPL][0];
					peso = tabelaLegendreN2[iPL][1];
					break;
				case 3:
					pl = tabelaLegendreN3[iPL][0];
					peso = tabelaLegendreN3[iPL][1];
					break;
				case 4:
					pl = tabelaLegendreN4[iPL][0];
					peso = tabelaLegendreN4[iPL][1];
					break;
				}
				//Calcula x(pl) - devido a mudança de variável para calcular no intervalo [a, b]
				double xi = (pl * (intervaloBi - intervaloAi) + intervaloAi + intervaloBi) / 2.0;
				//Acrescenta em resultadoSubintervalo o valor: peso * f(x(pl))
				resultadoSubintervalo += peso * funcao(xi);
			}
			resultadoAtual += resultadoSubintervalo;
			intervaloAi = intervaloBi;
		}
		resultadoAtual = resultadoAtual * tamanhoSubintervalo / 2.0;
		if (numIntervalos >= 2) {
			erro = fabs(resultadoAnterior - resultadoAtual);
		}

		cout << numIntervalos << "  -  " << resultadoAtual << "  -  " << erro << endl;
		numIntervalos = numIntervalos * 2;
	} while (numIntervalos == 2 || erro > precisao);

	return resultadoAtual;
}

double QuadraturaGauss::calcularGaussHermite(double(*funcao)(double x), int numPontos) {
	if (numPontos < 2 || numPontos > 4) {
		cout << "Número de pontos inválido. Valores possíveis: 2, 3 e 4" << endl;
		return 0.0;
	}
	cout << "\n=> Integração Numérica - Gauss-Hermite utilizando " << numPontos << " pontos de Hermite" << endl;
	/* Tabelas com os pontos de Hermite.
	 * A primeira coluna é o ponto de Hermite e a segunda é o peso correspondente.
	 */
	double tabelaHermiteN2[2][2] = {
			{ -0.70710678, 0.88622692 },
			{ 0.70710678, 0.88622692 }
	};
	double tabelaHermiteN3[3][2] = {
			{ -1.22474487, 0.29540897 },
			{ 0, 1.18163590 },
			{ 1.22474487, 0.29540897 }
	};
	double tabelaHermiteN4[4][2] = {
			{ -1.65068012, 0.08131283 },
			{ -0.52464762, 0.80491409 },
			{ 0.52464762, 0.80491409 },
			{ 1.65068012, 0.08131283 }
	};
	double resultado = 0.0;
	//I = [Somatorio dos pesos multiplicados pelos f(ph)] onde ph é um ponto de Hermite
	for (int iPH = 0; iPH < numPontos; iPH++) {
		double ph = 0.0; //Ponto de Hermite atual
		double peso = 0.0; //Peso correspondente ao peso de Hermite atual
		//Decide qual ponto de Hermite e peso sera usado:
		switch (numPontos) {
		case 2:
			ph = tabelaHermiteN2[iPH][0];
			peso = tabelaHermiteN2[iPH][1];
			break;
		case 3:
			ph = tabelaHermiteN3[iPH][0];
			peso = tabelaHermiteN3[iPH][1];
			break;
		case 4:
			ph = tabelaHermiteN4[iPH][0];
			peso = tabelaHermiteN4[iPH][1];
			break;
		}
		//Acrescenta em resultadoSubintervalo o valor: peso * f(ph)
		resultado += peso * funcao(ph);
	}
	cout << "Integral: " << resultado << endl;
	return resultado;
}

double QuadraturaGauss::calcularGaussLaguerre(double(*funcao)(double x), int numPontos) {
	if (numPontos < 2 || numPontos > 4) {
		cout << "Número de pontos inválido. Valores possíveis: 2, 3 e 4" << endl;
		return 0.0;
	}
	cout << "\n=> Integração Numérica - Gauss-Laguerre utilizando " << numPontos << " pontos de Laguerre" << endl;
	/* Tabelas com os pontos de Laguerre.
	 * A primeira coluna é o ponto de Laguerre e a segunda é o peso correspondente.
	 */
	double tabelaLaguerreN2[2][2] = {
			{ 0.58578643, 0.85355339 },
			{ 3.41421356, 0.14644660 }
	};
	double tabelaLaguerreN3[3][2] = {
			{ 0.41577455, 0.71109300 },
			{ 2.29428036, 0.27851773 },
			{ 6.28994508, 0.010389256 }
	};
	double tabelaLaguerreN4[4][2] = {
			{ 0.32254768, 0.60315410 },
			{ 1.74576110, 0.35741869 },
			{ 4.53662029, 0.038887908 },
			{ 9.39507091, 0.00053929470 }
	};
	double resultado = 0.0;
	//I = [Somatorio dos pesos multiplicados pelos f(PL)] onde pl é um ponto de Laguerre
	for (int iPL = 0; iPL < numPontos; iPL++) {
		double pl = 0.0; //Ponto de Laguerre atual
		double peso = 0.0; //Peso correspondente ao peso de Laguerre atual
		//Decide qual ponto de Laguerre e peso sera usado:
		switch (numPontos) {
		case 2:
			pl = tabelaLaguerreN2[iPL][0];
			peso = tabelaLaguerreN2[iPL][1];
			break;
		case 3:
			pl = tabelaLaguerreN3[iPL][0];
			peso = tabelaLaguerreN3[iPL][1];
			break;
		case 4:
			pl = tabelaLaguerreN4[iPL][0];
			peso = tabelaLaguerreN4[iPL][1];
			break;
		}
		//Acrescenta em resultadoSubintervalo o valor: peso * f(pl)
		resultado += peso * funcao(pl);
	}
	cout << "Integral: " << resultado << endl;
	return resultado;
}

double QuadraturaGauss::calcularGaussChebyshev(double(*funcao)(double x), double intervaloA, double intervaloB, double precisao, int numPontos) {
	if (numPontos < 2 || numPontos > 4) {
		cout << "Número de pontos inválido. Valores possíveis: 2, 3 e 4" << endl;
		return 0.0;
	}
	cout << "\n=> Integração Numérica - Gauss-Chebyshev utilizando " << numPontos << " pontos de Chebyshev" << endl;
	cout << "Num. Interavalos  -  Integral  -  Erro" << endl;
	int numIntervalos = 1;
	double resultadoAtual = 0.0;
	double resultadoAnterior;
	double erro = NAN;
	double intervaloAi, intervaloBi;
	double tamanhoSubintervalo;
	do {
		resultadoAnterior = resultadoAtual;
		resultadoAtual = 0.0;
		intervaloAi = intervaloA;
		intervaloBi = intervaloB;
		tamanhoSubintervalo = (intervaloB - intervaloA) / numIntervalos;
		//I = [(b - a) / 2] * [Somatorio dos pesos multiplicados pelos f((pc * (b - a) + a + b) / 2)] onde pc é um ponto de Chebyshev
		for (int i = 1; i <= numIntervalos; i++) {
			intervaloBi = intervaloAi + tamanhoSubintervalo;
			double resultadoSubintervalo = 0.0;
			for (int iPC = 1; iPC <= numPontos; iPC++) {
				double pc = cos((iPC - 0.5) * M_PI / numPontos); //Ponto de Chebyshev atual
				//Calcula x(pc) - devido a mudança de variável para calcular no intervalo [a, b]
				double xi = (pc * (intervaloBi - intervaloAi) + intervaloAi + intervaloBi) / 2.0;
				//Acrescenta em resultadoSubintervalo o valor: f(x(pc))
				resultadoSubintervalo += funcao(xi);
			}
			resultadoAtual += resultadoSubintervalo;
			intervaloAi = intervaloBi;
		}
		resultadoAtual = (tamanhoSubintervalo / 2.0) * (M_PI / numPontos) * resultadoAtual;
		if (numIntervalos >= 2) {
			erro = fabs(resultadoAnterior - resultadoAtual);
		}

		cout << numIntervalos << "  -  " << resultadoAtual << "  -  " << erro << endl;
		numIntervalos = numIntervalos * 2;
	} while (numIntervalos == 2 || erro > precisao);

	return resultadoAtual;
}
