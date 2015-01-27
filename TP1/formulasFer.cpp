#include <cmath>
#include <iostream>
#include <list>
#include "formulas.h"
#include "TFloat.h"

using namespace std;

/*FÓRMULAS BY FERNANDO*/
TFloat A (TFloat s, int n, list<double>::iterator it){
	int _precision = s.precision();
	TFloat sum = TFloat(0, _precision);
	double s1 = s.dbl();

	for(int i = 0; i<n; i++)
	{
		sum=sum+(s * log(*it)).exponencial();
		it++;
	}
	return sum;
}

TFloat B (TFloat s, int n, list<double>::iterator it){
	int _precision = s.precision();
	TFloat sum = TFloat(0, _precision);
	double s1 = s.dbl();

	for(int i = 0; i<n; i++)
	{
		sum=sum+((s * log(*it)).exponencial() * log(*it));
		it++;
	}
	return sum;
}

TFloat C (TFloat s, int n, list<double>::iterator it){
	int _precision = s.precision();
	TFloat sum = TFloat(0, _precision);

	for(int i = 0; i<n; i++)
	{
		sum=sum+((s * log(*it)).exponencial() * pow(log(*it),2));
		it++;
	}
	return sum;
}

TFloat D (TFloat s, int n, list<double>::iterator it){
	int _precision = s.precision();
	TFloat sum = TFloat(0, _precision);

	for(int i = 0; i<n; i++)
	{
		sum=sum+(log(*it));
		it++;
	}
	return sum/n;
}

TFloat P (TFloat s, int n, list<double>::iterator it){
	TFloat res = B(s,n,it)/A(s,n,it) - D(s,n,it);

	return res;
}

TFloat PPrima (TFloat s, int n, list<double>::iterator it){
	TFloat res = C(s,n,it)/A(s,n,it) - (B(s,n,it) * B(s,n,it)) / (A(s,n,it) * A(s,n,it));
	return res;
}

TFloat Q (TFloat s, int n, list<double>::iterator it){
	TFloat res = A(s*2,n,it) / (A(s,n,it) * A(s,n,it)) * n; // a(2s) / a(s)²
	return res;
}

TFloat QPrima (TFloat s, int n, list<double>::iterator it){
	TFloat res = ((B(s * 2,n,it) / pow(A(s,n,it).dbl(),2)) * 2 - (A(s*2,n,it) * A(s,n,it) * B(s,n,it) * 2) / pow(A(s,n,it).dbl(),4)) * n;
	return res;
}
/* FIN DE MIS FORMULAS*/

/*Cálculo de las funciones básicas (MdeS,MsombreroDeS,RdeS)*/

TFloat MdeS(TFloat s, int n, list<double>::iterator it){
	return A(s,n,it)/n;
}

TFloat MsombreroDeS(TFloat s, int n, list<double>::iterator it){
	return B(s,n,it)/n;
}

TFloat RdeS(TFloat s, int n, list<double>::iterator it){
    return B(s,n,it)/A(s,n,it);
}

/*Cálculo de las derivadas de las funciones básicas(MsombreroPrimaDeS,RprimaDeS)
 *
 * Aclaración: MPrimaDeS = MsombreroDeS*/

TFloat MPrimaDeS(TFloat s, int n, list<double>::iterator it){
	return MsombreroDeS(s, n, it);
}

TFloat MsombreroPrimaDeS(TFloat s, int n, list<double>::iterator it){
	return C(s,n,it)/n;
}

TFloat RprimaDeS(TFloat s, int n, list<double>::iterator it){
    TFloat numerador = C(s, n, it)*A(s, n, it) - B(s, n, it)* B(s, n, it);
    TFloat denominador = A(s, n, it)*A(s, n, it);
    return numerador/denominador;
}

/*Cálculo de f(s) y f'(s) (f(s) es la funcion (5) igualada a 0)*/

TFloat fDeS(TFloat s, int n, list<double>::iterator it){

    return s * P(s,n,it) - Q(s,n,it) + 1;
}

TFloat fPrimaDeS(TFloat s, int n, list<double>::iterator it){
	return P(s,n,it) + s * PPrima(s,n,it) - QPrima(s,n,it);
}

/*Cálculo de Lambda*/

TFloat lambda(TFloat beta, int n, list<double>::iterator it){
    /*
	size_t _precision = beta.precision();
    TFloat base(0.0, _precision);

	base = beta*(RdeS(beta, n, it)-MsombreroDeS(0, n, it));

    double base1 = base.dbl();
    double resultD = pow(base1,-1);
    TFloat resultTF = TFloat(resultD, _precision);
    return resultTF;
    */
	size_t _precision = beta.precision();
	double res1 = pow( (beta * (B(beta,n,it)/A(beta,n,it)) - D(beta,n,it)).dbl() , -1);
	TFloat res = TFloat(res1, _precision);
	return res;

}

/*Cálculo de sigma*/

TFloat sigma(TFloat beta, TFloat lambda, int n, list<double>::iterator it){
    /*
	size_t _precision = beta.precision();
    TFloat base(0.0, _precision);
	double exponente = 1;
	double beta1 = beta.dbl();

	base = MdeS(beta, n, it)/lambda;
    exponente = 1/beta1;
    double base1 = base.dbl();
    double resultD = pow(base1, exponente);
    TFloat resultTF = TFloat(resultD, _precision);
    return resultTF;
    */
	return A(beta,n,it)/ (lambda * n);
}
