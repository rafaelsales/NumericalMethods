//============================================================================
// Name        : Metodos-Tarefa3.cpp
// Author      : Rafael Sales
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "SistemaLinear.h"
#include "MetodoGauss.h"
#include "MetodoGaussPivotacao.h"
#include "MetodoGaussJordan.h"
#include "MetodoLU.h"
#include "MetodoGaussSeidel.h"

using namespace std;

void executarQuestao01();
void executarQuestao02();
SistemaLinear criarSistemaLinearQuestao01();
SistemaLinear criarSistemaLinearQuestao02();
void imprimirSistema(SistemaLinear& sistema);
void imprimirRaizesCalculadas(double* raizes, int numRaizes);

int main() {
	cout << "### Questão 1 ###" << endl << endl;
	executarQuestao01();

	cout << endl << "### Questão 2 ###" << endl << endl;
	executarQuestao02();

	return 0;
}

void executarQuestao01() {
	SistemaLinear sistemaGauss = criarSistemaLinearQuestao01();
	SistemaLinear sistemaGaussPivotacao = criarSistemaLinearQuestao01();
	SistemaLinear sistemaGaussJordan = criarSistemaLinearQuestao01();
	SistemaLinear sistemaLU = criarSistemaLinearQuestao01();
	double* raizes;

	cout << "Sistema Linear dado: " << endl;
	imprimirSistema(sistemaGauss);

	//Procura as raizes pelo Método de Gauss:
	cout << "\n => Método de Gauss" << endl;
	MetodoGauss metodoGauss(sistemaGauss);
	raizes = metodoGauss.calcularRaizes();
	cout << "Sistema Linear alterado pelo método: " << endl;
	imprimirSistema(sistemaGauss);
	imprimirRaizesCalculadas(raizes, sistemaGauss.numEquacoes);

	cout << "\n => Método de Gauss com pivotação parcial" << endl;
	MetodoGaussPivotacao metodoGaussPivotacao(sistemaGaussPivotacao);
	raizes = metodoGaussPivotacao.calcularRaizes();
	cout << "Sistema Linear alterado pelo método: " << endl;
	imprimirSistema(sistemaGaussPivotacao);
	imprimirRaizesCalculadas(raizes, sistemaGaussPivotacao.numEquacoes);

	cout << "\n => Método de Gauss-Jordan" << endl;
	MetodoGaussJordan metodoGaussJordan(sistemaGaussJordan);
	raizes = metodoGaussJordan.calcularRaizes();
	cout << "Sistema Linear alterado pelo método: " << endl;
	imprimirSistema(sistemaGaussJordan);
	imprimirRaizesCalculadas(raizes, sistemaGaussJordan.numEquacoes);

	cout << "\n => Método LU" << endl;
	MetodoLU metodoLU(sistemaLU);
	raizes = metodoLU.calcularRaizes();
	cout << "Sistema Linear alterado pelo método: " << endl;
	imprimirSistema(sistemaLU);
	imprimirRaizesCalculadas(raizes, sistemaLU.numEquacoes);
}

void executarQuestao02() {
	SistemaLinear sistemaGaussJacobi = criarSistemaLinearQuestao02();
	SistemaLinear sistemaGaussSeidel = criarSistemaLinearQuestao02();
	double* raizes;
	double precisao = 0.0001;

	cout << "Sistema Linear dado: " << endl;
	imprimirSistema(sistemaGaussJacobi);

	//Procura as raizes pelo Método de Gauss:
	cout << "\n => Método de Gauss-Jacobi" << endl;
	MetodoGaussJacobi metodoGaussJacobi(sistemaGaussJacobi, precisao);
	raizes = metodoGaussJacobi.calcularRaizes();
	if (raizes == 0) {
		cout << "O limite de 1000 iterações foi alcançado e as raízes não foram encontradas." << endl;
	} else {
		imprimirRaizesCalculadas(raizes, sistemaGaussJacobi.numEquacoes);
	}

	cout << "\n => Método de Gauss-Seidel" << endl;
	MetodoGaussSeidel metodoGaussSeidel(sistemaGaussSeidel, precisao);
	raizes = metodoGaussSeidel.calcularRaizes();
	if (raizes == 0) {
		cout << "O limite de 1000 iterações foi alcançado e as raízes não foram encontradas." << endl;
	} else {
		imprimirRaizesCalculadas(raizes, sistemaGaussSeidel.numEquacoes);
	}
}

SistemaLinear criarSistemaLinearQuestao01() {
	int numEquacoes = 3;
	double** coeficientes = new double*[numEquacoes];
	for (int i = 0; i < numEquacoes; i++) {
		coeficientes[i] = new double[numEquacoes];
	}
	double* termosIndependentes = new double[numEquacoes];

	coeficientes[0][0] = 20;
	coeficientes[0][1] = 7;
	coeficientes[0][2] = 9;
	coeficientes[1][0] = 7;
	coeficientes[1][1] = 30;
	coeficientes[1][2] = 8;
	coeficientes[2][0] = 9;
	coeficientes[2][1] = 8;
	coeficientes[2][2] = 30;
	termosIndependentes[0] = 16;
	termosIndependentes[1] = 38;
	termosIndependentes[2] = 38;

	SistemaLinear sistemaLinear(coeficientes, termosIndependentes, numEquacoes);
	return sistemaLinear;
}

SistemaLinear criarSistemaLinearQuestao02() {
	int numEquacoes = 3;
	double** coeficientes = new double*[numEquacoes];
	for (int i = 0; i < numEquacoes; i++) {
		coeficientes[i] = new double[numEquacoes];
	}
	double* termosIndependentes = new double[numEquacoes];

	coeficientes[0][0] = 10;
	coeficientes[0][1] = 2;
	coeficientes[0][2] = 2;
	coeficientes[1][0] = 1;
	coeficientes[1][1] = 10;
	coeficientes[1][2] = 2;
	coeficientes[2][0] = 2;
	coeficientes[2][1] = -7;
	coeficientes[2][2] = -10;
	termosIndependentes[0] = 28;
	termosIndependentes[1] = 7;
	termosIndependentes[2] = -17;

	SistemaLinear sistemaLinear(coeficientes, termosIndependentes, numEquacoes);
	return sistemaLinear;
}

void imprimirSistema(SistemaLinear& sistema) {
	for (int i = 0; i < sistema.numEquacoes; i++) {
		cout << "\t";
		for (int j = 0; j < sistema.numEquacoes; j++) {
			cout << sistema.coeficientes[i][j] << "*x" << j + 1;
			if (j != sistema.numEquacoes - 1) {
				cout << " + ";
			}
		}
		cout << " = " << sistema.termosIndependentes[i] << endl;
	}
}

void imprimirRaizesCalculadas(double* raizes, int numRaizes) {
	cout << "Raizes:" << endl;
	for (int i = 0; i < numRaizes; i++) {
		cout << "x" << i + 1 << " = " << raizes[i];
		if (i != numRaizes - 1) {
			cout << "\t";
		}
	}
	cout << endl;
}
