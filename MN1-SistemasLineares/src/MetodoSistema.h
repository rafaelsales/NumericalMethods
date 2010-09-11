/*
 * MetodoSistema.h
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#ifndef METODOSISTEMA_H_
#define METODOSISTEMA_H_

#include "SistemaLinear.h"

class MetodoSistema {
protected:
	SistemaLinear& sistema;
public:
	MetodoSistema(SistemaLinear& sistema);
	virtual ~MetodoSistema();
	virtual double* calcularRaizes() = 0;
};

#endif /* METODOSISTEMA_H_ */
