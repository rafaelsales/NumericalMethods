#ifndef POLINOMIO_H_
#define POLINOMIO_H_

class Polinomio {
public:
	Polinomio(double* coeficientes, int numCoeficientes);
	// Calcula o valor do polinomio no ponto x
	virtual double calcular(double x);
	// Calcula a derivada do polinomio no ponto x
	virtual double calcularDerivada(double x);
protected:
	double* coeficientes;
	int numCoeficientes;
};

#endif /* POLINOMIO_H_ */
