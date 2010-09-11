/*
 * NewtonCotes.cpp
 *
 *  Created on: 27/02/2010
 *      Author: Rafael Sales
 */

#include "NewtonCotes.h"
#include <math.h>
#include <iostream>

using namespace std;

NewtonCotes::NewtonCotes(double(*funcao)(double x)) :
	funcao(funcao) {
}

NewtonCotes::~NewtonCotes() {
}

double NewtonCotes::calcularTrapezoideFechadaSimples(double intervaloA, double intervaloB, double precisao) {
	cout << "\n=> Integração Numérica - Fórmula de Newton-Cotes - Regra dos Trapézios Fechada Simples" << endl;
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
		//I = [(b-a) / 2] * [(f(x0) + f(x1)]
		for (int i = 1; i <= numIntervalos; i++) {
			intervaloBi = intervaloAi + tamanhoSubintervalo;
			double x0 = calcularXi(intervaloAi, intervaloBi, 0, 1);
			double x1 = calcularXi(intervaloAi, intervaloBi, 1, 1);
			resultadoAtual += funcao(x0) + funcao(x1);
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

double NewtonCotes::calcularTrapezoideAbertaSimples(double intervaloA, double intervaloB, double precisao) {
	cout << "\n=> Integração Numérica - Fórmula de Newton-Cotes - Regra dos Trapézios Aberta Simples" << endl;
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
		//I = [(b-a) / 2] * [(f(x1) + f(x2)]
		for (int i = 1; i <= numIntervalos; i++) {
			intervaloBi = intervaloAi + tamanhoSubintervalo;
			double x1 = calcularXi(intervaloAi, intervaloBi, 1, 3);
			double x2 = calcularXi(intervaloAi, intervaloBi, 2, 3);
			resultadoAtual += funcao(x1) + funcao(x2);
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

double NewtonCotes::calcularTrapezoideFechadaEstendida(double intervaloA, double intervaloB, double precisao) {
	cout << "\n=> Integração Numérica - Fórmula de Newton-Cotes - Regra dos Trapézios Fechada Estendida" << endl;
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
		//I = [(b-a) / 2] * [(f(x0) + f(x1)]
		for (int i = 1; i <= numIntervalos; i++) {
			intervaloBi = intervaloAi + tamanhoSubintervalo;
			double x0 = calcularXi(intervaloAi, intervaloBi, 0, 1);
			double x1 = calcularXi(intervaloAi, intervaloBi, 1, 1);
			if (numIntervalos == 1) {
				resultadoAtual += funcao(x0) + funcao(x1);
			} else if (i == 1) {
				//Para a primeira partição calcula somente f(x0):
				resultadoAtual += funcao(x0);
			} else if (i <= numIntervalos) {
				//A partir da segunda partição calcula o f(x0):
				resultadoAtual += 2 * funcao(x0);
				if (i == numIntervalos) {
					resultadoAtual += funcao(x1);
				}
			}
			//Calcula a integral do subintervalo atual incluindo o valor funcao(x1) do subintervalo seguinte:
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

double NewtonCotes::calcularSimpsons13FechadaSimples(double intervaloA, double intervaloB, double precisao) {
	cout << "\n=> Integração Numérica - Fórmula de Newton-Cotes - Regra de Simpson's 1/3 Fechada Simples" << endl;
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
		//I = [(b-a) / 6] * [(f(x0) + 4 * f(x1) + f(x2)]
		for (int i = 1; i <= numIntervalos; i++) {
			intervaloBi = intervaloAi + tamanhoSubintervalo;
			double x0 = calcularXi(intervaloAi, intervaloBi, 0, 2);
			double x1 = calcularXi(intervaloAi, intervaloBi, 1, 2);
			double x2 = calcularXi(intervaloAi, intervaloBi, 2, 2);
			resultadoAtual += funcao(x0) + 4 * funcao(x1) + funcao(x2);
			intervaloAi = intervaloBi;
		}
		resultadoAtual = resultadoAtual * tamanhoSubintervalo / 6.0;
		if (numIntervalos >= 2) {
			erro = fabs(resultadoAnterior - resultadoAtual);
		}

		cout << numIntervalos << "  -  " << resultadoAtual << "  -  " << erro << endl;
		numIntervalos = numIntervalos * 2;
	} while (numIntervalos == 2 || erro > precisao);

	return resultadoAtual;
}

double NewtonCotes::calcularSimpsons13FechadaEstendida(double intervaloA, double intervaloB, double precisao) {
	cout << "\n=> Integração Numérica - Fórmula de Newton-Cotes - Regra de Simpson's 1/3 Fechada Estendida" << endl;
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
		//I = [(b-a) / 6] * [(f(x0) + 4 * f(x1) + f(x2)]
		for (int i = 1; i <= numIntervalos; i++) {
			intervaloBi = intervaloAi + tamanhoSubintervalo;
			double x0 = calcularXi(intervaloAi, intervaloBi, 0, 2);
			double x1 = calcularXi(intervaloAi, intervaloBi, 1, 2);
			double x2 = calcularXi(intervaloAi, intervaloBi, 2, 2);
			if (numIntervalos == 1) {
				resultadoAtual += funcao(x0) + 4 * funcao(x1) + funcao(x2);
			} else if (i == 1) {
				//Para a primeira partição calcula somente f(x0) + 4*f(x1):
				resultadoAtual += funcao(x0) + 4 * funcao(x1);
			} else if (i <= numIntervalos) {
				//A partir da segunda partição calcula o f(x2) da iteração i e da i+1 adicionado de 4*f(x1):
				resultadoAtual += 2 * funcao(x0) + 4 * funcao(x1);
				if (i == numIntervalos) {
					resultadoAtual += funcao(x2);
				}
			}
			intervaloAi = intervaloBi;
		}
		resultadoAtual = resultadoAtual * tamanhoSubintervalo / 6.0;
		if (numIntervalos >= 2) {
			erro = fabs(resultadoAnterior - resultadoAtual);
		}

		cout << numIntervalos << "  -  " << resultadoAtual << "  -  " << erro << endl;
		numIntervalos = numIntervalos * 2;
	} while (numIntervalos == 2 || erro > precisao);

	return resultadoAtual;
}

double NewtonCotes::calcularGrau2AbertaSimples(double intervaloA, double intervaloB, double precisao) {
	cout << "\n=> Integração Numérica - Fórmula de Newton-Cotes - Polinômio de Grau 2 Aberta Simples" << endl;
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
		//I = [(b-a) / 3] * [(2 * f(x1) - f(x2) + 2 * f(x3)]
		for (int i = 1; i <= numIntervalos; i++) {
			intervaloBi = intervaloAi + tamanhoSubintervalo;
			double x1 = calcularXi(intervaloAi, intervaloBi, 1, 4);
			double x2 = calcularXi(intervaloAi, intervaloBi, 2, 4);
			double x3 = calcularXi(intervaloAi, intervaloBi, 3, 4);
			resultadoAtual += 2 * funcao(x1) - funcao(x2) + 2 * funcao(x3);
			intervaloAi = intervaloBi;
		}
		resultadoAtual = resultadoAtual * tamanhoSubintervalo / 3.0;
		if (numIntervalos >= 2) {
			erro = fabs(resultadoAnterior - resultadoAtual);
		}

		cout << numIntervalos << "  -  " << resultadoAtual << "  -  " << erro << endl;
		numIntervalos = numIntervalos * 2;
	} while (numIntervalos == 2 || erro > precisao);

	return resultadoAtual;
}

double NewtonCotes::calcularXi(double intervaloA, double intervaloB, int i, int numIntervalos) {
	return intervaloA + i * (intervaloB - intervaloA) / numIntervalos;
}
