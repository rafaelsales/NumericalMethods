/*
 * MetodoGaussPivotacao.h
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#ifndef METODOGAUSSPIVOTACAO_H_
#define METODOGAUSSPIVOTACAO_H_

#include "MetodoGauss.h"
#include "SistemaLinear.h"

class MetodoGaussPivotacao: public MetodoGauss {
public:
	MetodoGaussPivotacao(SistemaLinear& sistema);
	virtual ~MetodoGaussPivotacao();
};

#endif /* METODOGAUSSPIVOTACAO_H_ */
