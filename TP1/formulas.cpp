#include <cmath>
#include <iostream>
#include <list>
#include "formulas.h"
#include "TFloat.h"

using namespace std;

/*Cálculo de las funciones básicas (MdeS,MsombreroDeS,RdeS)*/

TFloat MdeS(TFloat s, int n, list<double>::iterator it){
	size_t _precision = s.precision();
	TFloat sum(0.0, _precision);
		
	for(int i = 0; i<n; i++)
	{
		sum=sum+((s*log(*it)).exponencial());
		it++;
	}
	return sum/n;
}

TFloat MsombreroDeS(TFloat s, int n, list<double>::iterator it){
	size_t _precision = s.precision();
	TFloat sum(0.0, _precision);
		
	for(int i = 0; i<n; i++)
	{
		sum=sum+(((s*log(*it)).exponencial())*log(*it));
		it++;
	}
	return sum/n;
}

TFloat RdeS(TFloat s, int n, list<double>::iterator it){
    return MsombreroDeS(s,n,it)/MdeS(s,n,it);
}

/*Cálculo de las derivadas de las funciones básicas(MsombreroPrimaDeS,RprimaDeS)
 * 
 * Aclaración: MPrimaDeS = MsombreroDeS*/

TFloat MPrimaDeS(TFloat s, int n, list<double>::iterator it){
	return MsombreroDeS(s, n, it);
}

TFloat MsombreroPrimaDeS(TFloat s, int n, list<double>::iterator it){
	size_t _precision = s.precision();
	TFloat sum(0.0, _precision);
		
	for(int i = 0; i<n; i++)
	{
		sum=sum+((s*log(*it)).exponencial()*pow(log(*it),2));
		it++;
	}
	return sum/n;
}

TFloat RprimaDeS(TFloat s, int n, list<double>::iterator it){
    TFloat numerador = MsombreroPrimaDeS(s, n, it)*MdeS(s, n, it) - MPrimaDeS(s, n, it)* MsombreroDeS(s, n, it);
    TFloat denominador = MdeS(s, n, it)*MdeS(s, n, it);
    return numerador/denominador;
}

/*Cálculo de f(s) y f'(s) (f(s) es la funcion (5) igualada a 0)*/

TFloat fDeS(TFloat s, int n, list<double>::iterator it){
    size_t _precision = s.precision();
    TFloat cero(0.0, _precision);
    return s*(RdeS(s, n, it) - RdeS(cero,n, it)) - (MdeS(s*2, n, it)/(MdeS(s, n, it)*MdeS(s, n, it))) + 1;
}

TFloat fPrimaDeS(TFloat s, int n, list<double>::iterator it){
    size_t _precision = s.precision();
    TFloat cero(0.0, _precision);
	TFloat _MdeS = MdeS(s, n, it);
    TFloat numerador = MPrimaDeS(s*2, n, it)*_MdeS*_MdeS*2 - MdeS(s*2, n, it)*MPrimaDeS(s, n, it)*_MdeS*2;
    TFloat denominador = _MdeS*_MdeS*_MdeS*_MdeS;
    return RdeS(s, n, it) + s*RprimaDeS(s, n, it) - RdeS(cero,n, it) - numerador/denominador;
}

/*Cálculo de Lambda*/

TFloat lambda(TFloat beta, int n, list<double>::iterator it){
    size_t _precision = beta.precision();
    TFloat res(0.0, _precision);
    TFloat cero(0.0, _precision);
    return (MdeS(beta, n, it)/((MsombreroDeS(beta,n,it)-MsombreroDeS(cero,n,it)*MdeS(beta, n, it))*beta));
}

/*Cálculo de sigma*/

TFloat sigma(TFloat beta, TFloat lambda, int n, list<double>::iterator it){
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
}
