/**

1) Decido si leo un sonido o una imagen
2) Leo el archivo ( z = señal )
3) Agrego ruido ( R(z) = x )
4) Transformo con la DCT ( y = M * x ó y = M * x * Mt )
5) Modifico ( f(y) = y' )
6) Reconstruyo ( Mx' = y' )
7) Comparo (PSNR(z, x'))
8) Liberar memoria

*/

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
#include <list>
#include <ctype.h>
#include "Matriz.h"

using namespace std;

int main()
{
    Matriz *signal;
    double Vmax = -200;
    int sonido = 0;

    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
    printf("\nBienvenido al programa revisado del TP2 de MetNum, primer cuatrimestre 2013.\n");
    cout<<"Alumnos"<<endl;
    cout<<"		Izcovich, Sabrina. LU: 550/11"<<endl;
    cout<<"		Otero, Fernando. LU: 424/11"<<endl;
    cout<<"		Vita, Sebastian. LU: 149/11"<<endl;
    string archivo;
    char respuesta = 'n';

    int cantMuestra = 0;
    ifstream entrada;
/** 1 */
    while(sonido >2 || sonido < 1)
    {
		cout << "Ingrese si quiere trabajar sobre una imagen o sonido"<<endl;
		cout << "1 = sonido" << endl;
		cout << "2 = imagen" << endl;
		cin >> sonido;
	}

/** 2 */
    while (tolower(respuesta) == 'n')
    {
        cout << "\n Ingrese el archivo donde este la muestra (sin olvidar su extension)\n este debe encontrarse en la misma carpeta que el ejecutable.\n" << endl;
        cin >> archivo;
        char * cArchivo = new char [archivo.length()+1];
        strcpy(cArchivo, archivo.c_str());

        entrada.open(cArchivo);
        if(entrada.good())
        {
            respuesta = 's';
            entrada >> cantMuestra;
            if(sonido == 1)
            {
                signal = new Matriz(cantMuestra,1);
            }
            else
            {
                signal = new Matriz(cantMuestra,cantMuestra);
            }

            int j = 0;
            double aux;
            for(int i = 0; i < cantMuestra; i++)
            {
                if(sonido == 2) //IMAGEN
                {
                    for(j = 0; j < cantMuestra; j++)
                    {
                        entrada >> aux;
                        signal->set(i, j, aux);
                        if(aux > Vmax)
                            Vmax = aux;
                    }
                }
                else    //SONIDO
                {
                    entrada >> aux;
                    signal->set(i, j, aux);
                    if(aux > Vmax)
                        Vmax = aux;
                }
            }
        }
        else
        {
            printf("\nNo se cargo el archivo. Salir? (s/n)\n");
            cin >> respuesta;
            if(tolower(respuesta) == 's')
            {
                entrada.close();
                return 0;
            }
        }
    }
    //TENGO LA SEÑAL (SONIDO O IMAGEN)
    Matriz *M = new Matriz();
    *M = M->DCT(Vmax,cantMuestra);

/** 3 */
    Matriz *R = new Matriz();
    *R = signal->ruidoSuma();

/** Testeo */
    cout << "PSNR de la señal con ruido sin filtrar: ";
    cout << signal->PSNR(*R,Vmax) << endl;

/** 4 */
    *R = *M * *R;
    if(sonido == 2)
        *R = *R * M->traspuesta();

    respuesta = 's';
    while(tolower(respuesta) == 's')
    {
    /** 5 */
        int efe = 0;
        while(efe <1 || efe >2)
        {
            cout << "Ingrese cual de las 2 funciones quiere aplicar para sacar el ruido:" << endl;
            cout << "1 = Aplanar" << endl;
            cout << "2 = Restar umbral" << endl;
            cin >> efe;
        }
        int umbral = -1;
        while(umbral < 0)
        {
            cout << "Ingrese el valor borde para la funcion elegida: " << endl;
            cin >> umbral;
        }
        if(efe == 1)
            R->umbral(umbral);
        else
            R->menosUmbral(umbral);

            R->imprimir();

    /** 6 */
    *R = M->resolverGauss(*R);
    if(sonido == 2)
    {
        R->traspuesta();
        *R = M->resolverGauss(*R);
        R->traspuesta();
    }


    /** 7 */
        cout << "PSNR de la señal con ruido luego de tratarla: ";
        cout << signal->PSNR(*R,Vmax) << endl << endl;

        respuesta = 't';
        while(tolower(respuesta) != 'n' && tolower(respuesta) != 's')
        {
            cout << "Quiere volver a ingresar la funcion? (s/n)" << endl;
            cin >> respuesta;
        }
    }
/** 8 */
    delete M;
    delete R;
    delete signal;

	return 0;
}
