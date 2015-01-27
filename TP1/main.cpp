#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
#include <list>
#include "metodos.h"
#include "TFloat.h"


using namespace std;

size_t precision(const size_t maxT)
{
	size_t res = -1;
    while(res > maxT || res < 1)
    {
        cout << "\nIngrese los dígitos de precisión en la mantisa (número entero) entre 1 y ";
        cout << maxT  << endl;
        cin >> res;
    }
    return res;
} 

int tipoError(int maxElem)
{
	int res = -1;
    while (res <1 || res >maxElem)
    {
    	/*tipoError
    	 * 1 => |f(c)|< error
    	 * 2 => |an - an-1|< error
    	 * 3 => |an - an-1|/|an-1| < error
    	 * 4 => |f(an) - f(an-1)| < error
    	 * 5 => |f(an) - f(an-1)|/|f(an-1)|< error
    	 */
    	cout << "\n Ingrese el tipo de error (entre 1 y ";
    	cout << maxElem;
    	cout << ")\n 	1 implica |f(c)|< error\n	2 implica |an - an-1|< error \n	3 implica |an - an-1|/|an| < error\n	4 implica |f(an) - f(an-1)| < error\n	5 implica |f(an) - f(an-1)|/|f(an-1)|< error" << endl;
    	cin >> res;
    }

    return res;
} //tipoError es el tipo de tolencia que se acepta, sacado de una lista. Entonces es entero.

double error()
{
	double res = -1;
    while(res >=1 || res <= 0)
    {
        printf("\nIngrese el error máximo aceptado entre 0 y 1 (float).\n");
        cin >> res;
    }

    return res;
} // Es el Epsilon (error) que ponemos como cota. Es un punto flotante

int maxIteraciones()
{
	int res = 0;
    while (res <1)
    {

    	printf("\nIngrese la cantidad máxima de iteraciones para el método de estimación que elija\n");
    	cin >> res;
    }

    return res;
} // Es la máxima cantidad de iteraciones que harán los métodos. Es entero


void pedirExtremosParaBiseccion(TFloat *a, TFloat *b, bool *fin, int n, list<double>::iterator it)
{
	double aD,bD;
	do
	{
		cout << "\nIngrese el extremo negativo a" << endl;
		cin >> aD;
		*a = aD;
	}while(fDeS(*a, n, it).dbl()>0);

	if(fDeS(*a, n, it) == 0)
	{
		cout << "\n¡Encontraste el cero!\n El cero es ";
		cout <<aD;
		cout << "\n Pulse una tecla para salir." << endl;
		cin >> aD;
		*fin = true;
	}
	if(!(*fin))
	{
		do
		{
			cout << "\nIngrese el extremo positivo b" << endl;
			cin >> bD;
			*b = bD;
		}while(fDeS(*b, n, it).dbl()<0);

		if(fDeS(*b, n, it) == 0)
		{
			cout << "\n¡Encontraste el cero!\n El cero es ";
			cout <<bD;
			cout << "\n Pulse una tecla para salir." << endl;
			cin >> bD;
			*fin = true;
		}
	}
} // Pide a y b. Verifica que f(a) sea negativo y f(b) positivo y mayor que a. Luego devuelve a y b por referencia


TFloat sacoP0(int cantMuestra, list<double>::iterator muestra, bool *fin, TFloat *p1, int metodo, size_t precision, double error, int tipoError, int maxIteraciones)
{
	//Acá consigo p0 con bisección o por pantalla
	TFloat p0(0.0,precision);
	double p0Double, p1Double;

	int iteracionesQRealiza = 0;
	double errorFinal = 0;
	float tiempo = 0;

	int p0PorUsuario;

	printf("Ingrese '1' para que el programa busque p0. Ingrese '2' para ingresarlo por consola \n");
	cin >> p0PorUsuario;

	if(p0PorUsuario == 1)
	{
		TFloat a = TFloat(precision);
		TFloat b = TFloat(precision);
		pedirExtremosParaBiseccion(&a, &b, fin, cantMuestra, muestra);
		if (metodo == 1)
			p0 = biseccion(cantMuestra, muestra, precision, error, a, b, tipoError, maxIteraciones, &iteracionesQRealiza, &errorFinal, &tiempo, p1, true);

		else
			p0 = biseccion(cantMuestra, muestra, precision, error, a, b, tipoError, maxIteraciones, &iteracionesQRealiza, &errorFinal, &tiempo, p1, false);

	}
	else
	{
		printf("\nIngrese la estimación de Beta, p0 \n");
		cin >> p0Double;
		if (metodo == 1)
		{
			printf("\nIngrese la segunda estimación de Beta, p1 \n");
			cin >> p1Double;
		}
		TFloat p0b(p0Double, precision);
		TFloat p1b(p1Double, precision);
		*p1 = p1b;
		p0 = p0b;
	}

	return p0;
} //Saco p0 (y p1 si usa secante). Para eso discrimino entre pedirlo por consola y obtenerlos haciendo biseccion.

int main(void)
{
    
    list<double> muestra;

    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
    printf("\nBienvenido al programa del TP1 de MetNum, primer cuatrimestre 2013.\n");

    size_t _precision = precision(52);

    int _tipoError = tipoError(5);

    double _error = error();

    int _maxIteraciones = maxIteraciones();
	
	TFloat Beta(0.0,_precision);
    
    string archivo;
    char respuesta = 'n';
    int cantMuestra = -1;

    while (respuesta == 'n')
    {
        cout << "\n Ingrese el archivo donde está la muestra (sin olvidar su extensión)\nÉste debe encontrarse en la misma carpeta que el ejecutable.\n" << endl;
        cin >> archivo;
        //tengo q pasar de string a char* para poder abrir un archivo con el nombre que me pasan por pantalla.
            char * cArchivo = new char [archivo.length()+1];
            strcpy(cArchivo, archivo.c_str());

        ifstream entrada(cArchivo);
        if(entrada.good())
        {
            entrada >> cantMuestra;
            while(!entrada.eof())
            {
                float nuevoElemento;
                entrada >> nuevoElemento;
                if(nuevoElemento != EOF)
                    muestra.push_back(nuevoElemento);
            }
            respuesta = 's';
        }
        else
        {
            printf("\nNo se cargó el archivo. Salir? (s/n)\n");
            cin >> respuesta;
            if(respuesta == 's')
            {
                return 0;
            }
        }
        entrada.close();
    }

    int metodo = 8;
    while (metodo < 0 || metodo > 2)
    {
        printf("\nIngrese el método numérico que desee utilizar para aproximar Beta\n    0 = Newton\n    1 = Secante \n    2 = Bisección\n");
        cin >> metodo;
    }
    bool fin = false;
    TFloat p0(0.0,_precision);
    TFloat p1(0.0,_precision);
    if (metodo == 0 || metodo == 1)
    {
    	p0 = sacoP0(cantMuestra, muestra.begin(), &fin, &p1, metodo, _precision, _error, _tipoError, _maxIteraciones);

    	if(fin)
    		return 0;
    }
    TFloat a(0.0,_precision);
    TFloat b(0.0,_precision);
    //ésto me lo devuelven las funciones.
    /**/int iteracionesQrealiza;
    /**/float tiempo;
    /**/double errorFinal;

    if(metodo == 1)
        Beta = secante(cantMuestra, muestra.begin(), _precision, _error, p0, p1, _tipoError, _maxIteraciones, &iteracionesQrealiza, &errorFinal, &tiempo);
    else
    	if(metodo == 2)
    		{
    			pedirExtremosParaBiseccion(&a, &b, &fin, cantMuestra, muestra.begin());
    	    	if(fin)
    	    		return 0;
    			Beta = biseccion(cantMuestra, muestra.begin(), _precision, _error, a, b, _tipoError, _maxIteraciones, &iteracionesQrealiza, &errorFinal, &tiempo, &p1, false);
    		}
    	else
    		Beta = newton(cantMuestra, muestra.begin(), _precision, _error, p0, _tipoError, _maxIteraciones, &iteracionesQrealiza, &errorFinal, &tiempo);


    TFloat l(0.0,_precision);
    TFloat s(0.0,_precision);
    l = lambda(Beta, cantMuestra, muestra.begin());
    s = sigma(Beta, l, cantMuestra, muestra.begin());

    cout << "\n\n**********************************" << endl;
    cout << "**Resumen:\n*-Precisión (t, cantidad de dígitos de mantisa): ";
    cout << _precision << endl;
    cout << "*-Error: ";
    cout << _error << endl;
    cout << "*-Tipo de error: ";
    switch(_tipoError)
    {
    	case 1:
    		cout << "|f(c)|< error" << endl;
    		break;
    	case 2:
    	    cout << "|an - an-1|< error" << endl;
    	    break;
    	case 3:
    	    cout << "(|an - an-1| / |an-1|)< error" << endl;
    	    break;
    	case 4:
    	    cout << "|f(an( - (an-1)|< error" << endl;
    	    break;
    	case 5:
    	    cout << "(|f(an) - f(an-1)| / |f(an-1)|)< error" << endl;
    	    break;
    }
    cout << "*-Máxima cantidad de iteraciones: ";
    cout << _maxIteraciones << endl;
    cout << "*-Método: ";
    switch(metodo)
    {
    	case 0:
    		cout << "Newton" << endl;
    		break;
    	case 1:
    	    cout << "Secante" << endl;
    	    break;
    	case 2:
    	    cout << "Biseccion" << endl;
    	    break;
    }
    if(metodo == 2)
    {
    	cout << "	a: ";
    	cout << a.dbl() << endl;
    	cout << "	b: ";
    	cout << b.dbl() << endl;
    }
    else
    {
    	cout << "	p0: ";
    	cout << p0.dbl() << endl;
    	if(metodo == 1)
    	{
        	cout << "	p1: ";
        	cout << p1.dbl() << endl;
    	}
    }


    	cout << "\nSigma = ";
    	cout << s.dbl();
        cout << " ; Beta = ";
        cout << Beta.dbl();
        cout << " ; Lambda = ";
        cout << l.dbl();
        cout << "\nTardó ";
        cout << tiempo;
        cout << " milisegundos, realizó ";
        cout << iteracionesQrealiza;
        cout << " iteraciones y terminó con un error de ";
        cout << errorFinal << endl;
    return 0;
}
