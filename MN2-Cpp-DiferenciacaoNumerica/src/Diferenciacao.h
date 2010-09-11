/*
 * Diferenciacao.h
 *
 *  Created on: Apr 10, 2010
 *      Author: Rafael Sales
 */

#ifndef DIFERENCIACAO_H_
#define DIFERENCIACAO_H_

#include <iostream>

using namespace std;

class Diferenciacao {
private:
	enum EFilosofia {
		FILOSOFIA_FORWARD, FILOSOFIA_CENTRAL, FILOSOFIA_BACKWARD
	};
	Diferenciacao();
	static double calcularDerivada(double(*funcao)(double x), double x, double deltaX, EFilosofia filosofia);
	//Verifica se funcao(x) é NaN ou INF:
public:
	static bool validarPontoFuncaoDefinido(double(*funcao)(double x), double x);
	static double calcularDerivadaForward(double(*funcao)(double x), double x, double deltaX);
	static double calcularDerivadaCentral(double(*funcao)(double x), double x, double deltaX);
	static double calcularDerivadaBackward(double(*funcao)(double x), double x, double deltaX);
};

#endif /* DIFERENCIACAO_H_ */
