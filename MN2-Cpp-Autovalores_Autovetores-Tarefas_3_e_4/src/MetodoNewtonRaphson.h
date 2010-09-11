/*
 * MetodoNewtonRaphson.h
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#ifndef METODONEWTONRAPHSON_H_
#define METODONEWTONRAPHSON_H_

class MetodoNewtonRaphson{
private:
	MetodoNewtonRaphson();
public:
	static double encontrarRaiz(double(*funcao)(double x), double(*funcaoDerivada)(double x), double intervaloA, double intervaloB, double erro);
};

#endif /* METODONEWTONRAPHSON_H_ */
