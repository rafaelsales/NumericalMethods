/*
 * QuadraturaGauss.h
 *
 *  Created on: Mar 20, 2010
 *      Author: root
 */

#ifndef QUADRATURAGAUSS_H_
#define QUADRATURAGAUSS_H_

class QuadraturaGauss {
private:
	QuadraturaGauss();
public:
	/**
	 * Método de Gauss-Legendre: integra funcao(x) no intervalo [a, b]
	 */
	static double calcularGaussLegendre(double(*funcao)(double x), double intervaloA, double intervaloB, double precisao, int numPontos);
	/**
	 * Método de Gauss-Hermite: integra e^(-x²) * funcao(x) no intervalo (-INF, +INF)
	 */
	static double calcularGaussHermite(double(*funcao)(double x), int numPontos);
	/**
	 * Método de Gauss-Laguerre: integra e^(-x) * funcao(x) no intervalo (0, +INF)
	 */
	static double calcularGaussLaguerre(double(*funcao)(double x), int numPontos);
	/**
	 * Método de Gauss-Chebyshev: integra funcao(x) no intervalo [a, b]
	 */
	static double calcularGaussChebyshev(double(*funcao)(double x), double intervaloA, double intervaloB, double precisao, int numPontos);
};

#endif /* QUADRATURAGAUSS_H_ */
