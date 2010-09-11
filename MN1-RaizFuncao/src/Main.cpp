//============================================================================
// Name        : Main.cpp
// Author      : Rafael Sales
//============================================================================

#include <iostream>
#include <math.h>
#include "IFuncao.h"
#include "MetodoBissecao.h"
#include "MetodoPosicaoFalsa.h"
#include "MetodoPontoFixo.h"
#include "MetodoNewtonRaphson.h"
#include "MetodoSecante.h"
#include "MetodoPolinomios.h"

using namespace std;

/**
 * Define a função dada na questão:
 */
class FuncaoExemplo: public IFuncao {
public:
	virtual double f(double x) {
		return pow(x, 3) - 9 * x + 3;
	}
};

/**
 * Define a derivada da função dada na questão:
 */
class FuncaoDerivadaExemplo: public IFuncao {
public:
	virtual double f(double x) {
		return 3 * pow(x, 2) - 9;
	}
};

/**
 * Define a função fi (utilizada no método do Ponto Fixo) para a função dada na questão:
 */
class FuncaoFiExemplo: public IFuncao {
public:
	virtual double f(double x) {
		return (pow(x, 3) + 3) / 9;
	}
};

int main() {
	double erro = 0.00001;
	//Instancia a função de exemplo, sua derivada e a função fi para o método do Ponto Fixo:
	FuncaoExemplo funcao;
	FuncaoDerivadaExemplo funcaoDerivada;
	FuncaoFiExemplo funcaoFi;

	cout << "--- Método da Bisseção ---" << endl;
	MetodoBissecao metodoBissecao(funcao, erro);
	cout << "Raíz aproximada: " << metodoBissecao.encontrarRaiz(0, 1) << endl;

	cout << " --- Método da Posição Falsa --- " << endl;
	MetodoPosicaoFalsa metodoPosicaoFalsa(funcao, erro);
	cout << "Raíz aproximada: " << metodoPosicaoFalsa.encontrarRaiz(0, 1) << endl;

	cout << " --- Método do Ponto Fixo --- " << endl;
	MetodoPontoFixo metodoPontoFixo(funcao, funcaoFi, erro);
	cout << "Raíz aproximada: " << metodoPontoFixo.encontrarRaiz(0, 1) << endl;

	cout << " --- Método de Newton-Raphson --- " << endl;
	MetodoNewtonRaphson metodoNewtonRaphson(funcao, funcaoDerivada, erro);
	cout << "Raíz aproximada: " << metodoNewtonRaphson.encontrarRaiz(0, 1) << endl;

	cout << " --- Método da Secante --- " << endl;
	MetodoSecante metodoSecante(funcao, erro);
	cout << "Raíz aproximada: " << metodoSecante.encontrarRaiz(0, 1) << endl;

	cout << " --- Método dos Polinomios --- " << endl;
	MetodoPolinomios metodoPolinomios(funcao, funcaoDerivada, erro);
	cout << "Raíz aproximada: " << metodoPolinomios.encontrarRaiz(0, 1) << endl;

	return 0;
}
