/*
 * Exponenciacao.cpp
 *
 *  Created on: Apr 8, 2010
 *      Author: Rafael Sales
 */

#include <iostream>
#include <math.h>
#include "Exponenciacao.h"

using namespace std;

Exponenciacao::Exponenciacao() {
}

double Exponenciacao::funcaoTransformacaoExponenciacaoSimples(struct Integral& integral, double s) {
	double x = (integral.intervaloA + integral.intervaloB + (integral.intervaloA - integral.intervaloB) * tanh(s)) / 2.0;
	double dxds = (integral.intervaloA - integral.intervaloB) / 2.0 * (1 / pow(cosh(s), 2));
	//Se houver singularidade em x, despreza o valor:
	if (isinf(integral.funcaoOriginal(x)) || isnan(integral.funcaoOriginal(x))) {
		return 0.0;
	}
	return integral.funcaoOriginal(x) * dxds;
}

double Exponenciacao::funcaoTransformacaoExponenciacaoDupla(struct Integral& integral, double s) {
	double x = (integral.intervaloA + integral.intervaloB + (integral.intervaloB - integral.intervaloA) * tanh(M_PI / 2 * sinh(s))) / 2.0;
	double dxds = ((integral.intervaloB - integral.intervaloA) / 2.0) * (M_PI / 2 * cosh(s)) / pow(cosh(M_PI / 2 * sinh(s)), 2);
	//Se houver singularidade em x, despreza o valor:
	if (isinf(integral.funcaoOriginal(x)) || isnan(integral.funcaoOriginal(x))) {
		return 0.0;
	}
	return integral.funcaoOriginal(x) * dxds;
}

double Exponenciacao::calcularExponenciacaoSimples(double(*funcao)(double x), double intervaloA, double intervaloB, double precisao) {
	cout << "\n=> Integração Numérica - Exponenciação simples" << endl;
	struct Integral integral;
	integral.funcaoOriginal = funcao;
	integral.intervaloA = intervaloA;
	integral.intervaloB = intervaloB;
	integral.funcaoTransformacao = funcaoTransformacaoExponenciacaoSimples;
	return calcularExponenciacao(integral, precisao);
}

double Exponenciacao::calcularExponenciacaoDupla(double(*funcao)(double x), double intervaloA, double intervaloB, double precisao) {
	cout << "\n=> Integração Numérica - Exponenciação dupla" << endl;
	struct Integral integral;
	integral.funcaoOriginal = funcao;
	integral.intervaloA = intervaloA;
	integral.intervaloB = intervaloB;
	integral.funcaoTransformacao = funcaoTransformacaoExponenciacaoDupla;
	return calcularExponenciacao(integral, precisao);
}

double Exponenciacao::calcularExponenciacao(struct Integral& integral, double precisao) {
	cout << "Intervalo  -  Num. Interavalos  -  Integral  -  Erro" << endl;
	int numIntervalos = 10;
	double resultadoAtual = 0.0;
	double resultadoAnterior;
	double erro = NAN;
	do {
		resultadoAnterior = resultadoAtual;
		resultadoAtual = 0.0;
		double s1 = -numIntervalos / 2;
		double s2 = numIntervalos / 2;
		resultadoAtual = calcularTrapezoideExponenciacao(integral, s1, s2, precisao);
		if (numIntervalos >= 2) {
			erro = fabs(resultadoAnterior - resultadoAtual);
		}
		numIntervalos = numIntervalos * 2;
	} while (numIntervalos == 2 || erro > precisao);

	return resultadoAtual;
}

double Exponenciacao::calcularTrapezoideExponenciacao(struct Integral& integral, double intervaloA, double intervaloB, double precisao) {
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
			resultadoAtual += integral.funcaoTransformacao(integral, intervaloAi) + integral.funcaoTransformacao(integral, intervaloBi);
			intervaloAi = intervaloBi;
		}
		resultadoAtual = resultadoAtual * tamanhoSubintervalo / 2.0;
		if (numIntervalos >= 2) {
			erro = fabs(resultadoAnterior - resultadoAtual);
		}

		cout << "[" << intervaloA << ", " << intervaloB << "]  -  " << numIntervalos << "  -  " << resultadoAtual << "  -  " << erro << endl;
		numIntervalos = numIntervalos * 2;
	} while (numIntervalos == 2 || erro > precisao);

	return resultadoAtual;
}
