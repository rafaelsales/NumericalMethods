/*
 * MetodoSistema.cpp
 *
 *  Created on: 09/12/2009
 *      Author: Rafael Sales
 */

#include "MetodoSistema.h"
#include "SistemaLinear.h"

MetodoSistema::MetodoSistema(SistemaLinear& sistema) :
	sistema(sistema) {
}

MetodoSistema::~MetodoSistema() {
}
