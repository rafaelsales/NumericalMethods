/*
 * NewtonCotes.h
 *
 *  Created on: 27/02/2010
 *      Author: Rafael Sales
 */

#ifndef NEWTONCOTES_H_
#define NEWTONCOTES_H_

class NewtonCotes {
private:
	//Função a ser integrada:
	double (*funcao)(double x);
public:
	NewtonCotes(double(*funcao)(double x));
	virtual ~NewtonCotes();

	virtual double calcularTrapezoideFechadaSimples(double intervaloA, double intervaloB, double precisao);
	virtual double calcularTrapezoideAbertaSimples(double intervaloA, double intervaloB, double precisao);
	virtual double calcularTrapezoideFechadaEstendida(double intervaloA, double intervaloB, double precisao);

	virtual double calcularSimpsons13FechadaSimples(double intervaloA, double intervaloB, double precisao);
	virtual double calcularSimpsons13FechadaEstendida(double intervaloA, double intervaloB, double precisao);
	virtual double calcularGrau2AbertaSimples(double intervaloA, double intervaloB, double precisao);

	//Calcula a abscissa Xi do intervalo [intervaloA, intervaloB] particionado equidistantemente
	virtual double calcularXi(double intervaloA, double intervaloB, int i, int numIntervalos);

};

#endif /* NEWTONCOTES_H_ */
