#ifndef METODOS_
#define METODOS_

#include <cmath>
#include <iostream>
#include <list>
#include "formulas.h"
#include "TFloat.h"
using namespace std;


/*tipoError
 * 1 => |f(c)|< error
 * 2 => |an - an-1|< error
 * 3 => |an - an-1|/|an-1| < error
 * 4 => |f(an) - f(an-1)| < error
 * 5 => |f(an) - f(an-1)|/|f(an-1)|< error
 */

TFloat newton(int n, list<double>::iterator m, size_t precision, double error, TFloat p0, int tipoError, int maxIteraciones, int *iteracionesQRealiza, double *errorFinal, float *tiempo);
TFloat secante(int n, list<double>::iterator m, size_t precision, double error, TFloat p0, TFloat p1, int tipoError, int maxIteraciones, int *iteracionesQRealiza, double *errorFinal, float *tiempo);
TFloat biseccion(int n, list<double>::iterator m, size_t precision, double error, TFloat a, TFloat b, int tipoError, int maxIteraciones, int *iteracionesQRealiza, double *errorFinal, float *tiempo, TFloat *c2, bool sacarC2);

#endif
