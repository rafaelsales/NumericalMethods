/*
 * SistemaLinear.h
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#ifndef SISTEMALINEAR_H_
#define SISTEMALINEAR_H_

class SistemaLinear {
public:
	double** coeficientes;
	double* termosIndependentes;
	int numEquacoes;
	SistemaLinear(double** coeficientes, double* termosIndependentes, int numEquacoes);
	virtual ~SistemaLinear();
	virtual void trocarLinhas(int l1, int l2);
};

#endif /* SISTEMALINEAR_H_ */
