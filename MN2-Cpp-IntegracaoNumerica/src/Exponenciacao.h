/*
 * Exponenciacao.h
 *
 *  Created on: Apr 8, 2010
 *      Author: Rafael Sales
 */

#ifndef EXPONENCIACAO_H_
#define EXPONENCIACAO_H_

class Exponenciacao {
private:
	struct Integral {
		double(*funcaoOriginal)(double x);
		double intervaloA;
		double intervaloB;
		double(*funcaoTransformacao)(struct Integral& integral, double s);
	};
	Exponenciacao();
	static double funcaoTransformacaoExponenciacaoSimples(struct Integral& integral, double s);
	static double funcaoTransformacaoExponenciacaoDupla(struct Integral& integral, double s);
	static double calcularTrapezoideExponenciacao(struct Integral& integral, double intervaloA, double intervaloB, double precisao);
	static double calcularExponenciacao(struct Integral& integral, double precisao);
public:
	static double calcularExponenciacaoSimples(double(*funcao)(double x), double intervaloA, double intervaloB, double precisao);
	static double calcularExponenciacaoDupla(double(*funcao)(double x), double intervaloA, double intervaloB, double precisao);
};

#endif /* EXPONENCIACAO_H_ */
