#ifndef FORMULAS_
#define FORMULAS_

#include <cmath>
#include <iostream>
#include "TFloat.h"
using namespace std;

/*Cálculo de f(s) y f'(s) (f(s) es la funcion (5) igualada a 0)*/

TFloat fDeS(TFloat s, int n, list<double>::iterator it);

TFloat fPrimaDeS(TFloat s, int n, list<double>::iterator it);

/*Cálculo de Lambda*/

TFloat lambda(TFloat beta, int n, list<double>::iterator it);

/*Cálculo de sigma*/

TFloat sigma(TFloat beta, TFloat lambda, int n, list<double>::iterator it);

#endif 
