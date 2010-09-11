/*
 * IFuncao.h
 *
 *  Created on: 22/10/2009
 *      Author: Rafael Sales
 */

#ifndef IFUNCAO_H_
#define IFUNCAO_H_

/**
 * Define a interface de uma função f(x) tal que x é um número real e esta função retorna um numero real
 */
class IFuncao {
public:
	virtual double f(double x) = 0;
};

#endif /* IFUNCAO_H_ */
