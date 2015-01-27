#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include "Matriz.h"

#define N 60000
#define M 784
#define K 50

using namespace std;

int main(int argc, char **argv)
{
    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
    printf("\nBienvenido al programa del TP3 de MetNum, primer cuatrimestre 2013.\n");
    cout<<"Alumnos"<<endl;
    cout<<"		Izcovich, Sabrina. LU: 550/11"<<endl;
    cout<<"		Otero, Fernando. LU: 424/11"<<endl;
    cout<<"		Vita, Sebastian. LU: 149/11"<<endl;

    Matriz *Vt = new Matriz(K,M);
    Matriz *TC = new Matriz(K,N);

    /* 0) */
    ifstream archivoVt;
    archivoVt.open("Vt.txt");
    if(archivoVt.good() && archivoVt.is_open())
    {
        cout << "Existe la matriz Vt" << endl;
        cout << "Cargando..." << endl;
        int aux;
        for (int i = 0; i < K; i++)
        {
            for(int j = 0; j < M; j++)
            {
                if((i+1)%6001 == 0)
                    cout << "|"; // 10 barritas =  fila cargada

                archivoVt >> aux;
                Vt->set(i,j,aux);
            }
            cout << endl;
        }
        cout << "Matriz Vt cargada" << endl;

        ifstream archivoTC;
        archivoTC.open("TC.txt");
        if(archivoTC.good() && archivoTC.is_open())
        {
            cout << "Existe la matriz TC" << endl;
            cout << "Cargando..." << endl;
            int aux;
            for (int i = 0; i < K; i++)
            {
                for(int j = 0; j < N; j++)
                {
                    archivoTC >> aux;
                    TC->set(i,j,aux);
                }
                if((i+1)%6001 == 0)
                    cout << "|"; // 10 barritas =  matriz cargada
            }
            cout << "Matriz TC cargada" << endl;
        }
        else
        {
            cout << "Se produjo algun error. Existe Vt pero no existe TC" << endl;
            ifstream entradaDB;
            entradaDB.open("matriz.txt");
            if(entradaDB.good() && entradaDB.is_open())
            {
                Matriz *A = new Matriz(M,N);
                cout << "Existe la matriz de la base de datos" << endl;
                cout << "Cargando..." << endl;
                int aux;
                for (int i = 0; i < M; i++)
                {
                    for(int j = 0; j < N; j++)
                    {
                        entradaDB >> aux;
                        A->set(i,j,aux);
                    }
                    if((i+1)%6000 == 0)
                    cout << "| "; // 10 barritas =  matriz cargada
                }
                cout << " Matriz A cargada" << endl;

                //A->imprimir();
                /** 5) */
                *TC = *Vt * *A;
                cout << "Creada TC" << endl;
                delete A;

                ifstream matrizMatlab;
                matrizMatlab.open("matlab.txt");
                Matriz *matlab = new Matriz(N, 1);
                if(matrizMatlab.good() && matrizMatlab.is_open())
                {
                    cout << "Existe matriz externa TC para comparar." << endl << "Cargando...";

                    double elem;
                    for(int i = 0; i < K; i++)
                    {
                        for(int j = 0; j < N; j++)
                        matrizMatlab >> elem;
                        matlab->set(i, 0, elem);
                        if(i+1 % 6000 == 0)
                            cout << "|";
                    }
                    cout << "Matriz TC externa cargada" << endl;
                    TC->compararTC(*matlab);
                }
                else
                {
                    cout << "No hay matriz TC externa para comparar. El programa sigue su curso." <<  endl;
                }
                matrizMatlab.close();

                /* ME QUEDO CON TC Y CON Vt PARA TRABAJAR CON EL VECTOR QUE ME PASEN*/
                /** Y ACA ESCRIBO TC EN TC.txt*/

                ofstream escribirTC;
                escribirTC.open ("TC.txt", ofstream::trunc);
                if(escribirTC.good() && escribirTC.is_open())
                {
                    for(int i = 0; i < K; i++)
                    {
                        for(int j = 0; j < N; j++)
                        {
                            escribirTC << TC->get(i,j);
                        }
                    }
                }
                else
                {
                    cout << "Error al crear el archivo TC.txt";
                }
                escribirTC.close();
            }
            else
            {
                cout << "No existe el archivo de la base de datos." << endl << "El programa no puede continuar" << endl;
                entradaDB.close();
                archivoTC.close();
                int aux;
                cin >> aux;
                return 0;
            }
            entradaDB.close();
        }
        archivoTC.close();
    }
    else
    {
        cout << "No existe la matriz V" <<  endl << endl;
        ifstream entradaDB;
        entradaDB.open("matriz.txt");
        if(entradaDB.good() && entradaDB.is_open())
        {
            Matriz *A = new Matriz(M,N);
            Matriz *X = new Matriz(N,M);
            cout << "Existe la matriz de la base de datos" << endl;
            cout << "Cargando..." << endl;
            int aux;
            for (int i = 0; i < N; i++)
            {
                for(int j = 0; j < M; j++)
                {
                    entradaDB >> aux;
                    A->set(i,j,aux);
                }
                if((i+1)%6000 == 0)
                cout << "| "; // 10 barritas =  matriz cargada
            }
            cout << " Matriz A cargada" << endl;

            /** 2) y 3) */
            *X = A->traspuesta();
            X->mediaCero();
            Matriz *Xt = new Matriz();
        	*Xt = X->traspuesta();
        	cout << "Creada Xt" << endl;
        	Matriz *E = new Matriz();
        	*E = *Xt * *X;
        	*E/=(N-1);
        	delete X;
        	delete Xt;
        	cout << "Creada At * A" << endl;
        	/** 4a) Potencia y deflacion */
        	//double errorMax = 0.00001;
        	//int iterMax = 1000;
        	//Matriz *X0 = new Matriz(M, 1);
        	//X0->Cero();
            //X0->set(0,0, 1); //para q tenga norma 1, nada mas
        	//Vt = E->potenciaYDeflacion(K, errorMax, iterMax, X0);   //ya no vulevo a usar E
            //delete X0;
            /** 4b) Algoritmo QR*/
            Matriz *Q = new Matriz(E->columnas(), E->filas());
            E->algoritmoQR(*Q, 0.1, 0.00001);
            delete E;
            Vt->cortar(K); //deja la matriz de (K,M)
        	cout << "Creada Vt" << endl;
        	delete Q;
        	/** 5) */
        	*TC = *Vt * *A;
        	cout << "Creada TC" << endl;
        	delete A;

            ifstream matrizMatlab;
            matrizMatlab.open("matlab.txt");
            Matriz *matlab = new Matriz(N, 1);
            if(matrizMatlab.good() && matrizMatlab.is_open())
            {
                cout << "Existe matriz externa TC para comparar." << endl << "Cargando...";

                double elem;
                for(int i = 0; i < K; i++)
                {
                    for(int j = 0; j < N; j++)
                    matrizMatlab >> elem;
                    matlab->set(i, 0, elem);
                    if(i+1 % 6000 == 0)
                        cout << "|";
                }
                cout << "Matriz TC externa cargada" << endl;
                TC->compararTC(*matlab);
            }
            else
            {
                cout << "No hay matriz TC externa para comparar. El programa sigue su curso." <<  endl;
            }
            matrizMatlab.close();

        	/* ME QUEDO CON TC Y CON Vt PARA TRABAJAR CON EL VECTOR QUE ME PASEN*/
            /** Y ACA ESCRIBO VT EN Vt.txt Y TC EN TC.txt*/

            ofstream escribirVt;
            escribirVt.open ("Vt.txt", ofstream::trunc);
            if(escribirVt.good() && escribirVt.is_open())
            {
                // voy a escribir los 2 archivos al mismo tiempo porque Vt y TC tienen las mismas dimensiones NO NO TIENEN LAS MISMAS DIMECIONES PTM!
                // Vt ES DE K X M Y TC ES DE K X N
                ofstream escribirTC;
                escribirTC.open ("TC.txt", ofstream::trunc);
                if(escribirTC.good() && escribirTC.is_open())
                {
                    for(int i = 0; i < K; i++)
                    {
                        for(int j = 0; j < M; j++)
                        {
                            escribirVt << Vt->get(i,j);
                            if(j<N)
                                escribirTC << TC->get(i,j);
                        }
                    }
                }
                else
                {
                    cout << "Error al crear el archivo TC.txt";
                }
                escribirTC.close();
            }
            else
            {
                cout << "Error al crear el archivo Vt.txt";
            }
            escribirVt.close();
        }
        else
        {
            cout << "No existe el archivo de la base de datos." << endl << "El programa no puede continuar" << endl;
            entradaDB.close();
            archivoVt.close();
            int aux;
            cin >> aux;
            return 0;
        }
        entradaDB.close();
    }
    archivoVt.close();



    ifstream archivoLabel;
    archivoLabel.open("label.txt");
    Matriz *lab = new Matriz(N, 1);
    if(archivoLabel.good() && archivoLabel.is_open())
    {
        cout << "Existe el vector de etiquetas." << endl << "Cargando...";

        double elem;
        for(int i = 0; i < N; i++)
        {
            archivoLabel >> elem;
            lab->set(i, 0, elem);
            if(i+1 % 6000 == 0)
                cout << "|";
        }
        cout << "Matriz Label cargada" << endl;
    }
    else
    {
        cout << "No existe la etiqueta. El programa no puede continuar." <<  endl;
        int aux;
        cin >> aux;
        return 0;
    }
    archivoLabel.close();


    /** PARTE B
        1) Leo de un archivo el vector X ( Matriz *X = new Matriz(M,1); )
        2) tc(X) = *TC * *X
        3) Recorro lo que tenga que recorrer (sea TC, un TC alfa-podado, o un vector con los 10 promedios) viendo con quien se parece mas tc(X)
        Para ver con quien se parece mas miro (*X-algunVector).norma2()
    */

    ifstream archivoVectorX;
    archivoVectorX.open("digito.txt");
    if(archivoVectorX.good() && archivoVectorX.is_open())
    {
        cout << "Existe el vector a analizar." << endl << "Cargando...";
        Matriz *X = new Matriz(M, 1);
        double elem;
        for(int i = 0; i < M; i++)
        {
            archivoVectorX >> elem;
            X->set(i, 0, elem);
            if(i+1 % 78 == 0)
                cout << "|";
        }
        cout << "Matriz X cargada" << endl << endl;

        int opcion = -1;
        cout << "Listo! solo falta que elija la opcion con la que quiere que definamos que digito esta buscando" << endl;
        while (opcion < 1 || opcion > 2)
        {

            cout << "Opcion 1: Usar todas las imagenes de la base de datos" << endl << "Opcion 2: Usar el promedio de cada digito" << endl << endl;
            cout << "Ingrese el numero de la opcion que desea:" << endl;
            cin >> opcion;
            if (opcion < 1 || opcion > 2)
                cout << "Error. Ingrese 1 o 2" << endl << endl;
        }
        cout << "El digito que se cargo es el: " << endl;
        int resultado = TC->averiguarDigito(*Vt, *X, *lab, opcion);

        cout << resultado;

        delete lab;
        delete Vt;
        delete TC;
        delete X; // si quisiera, puedo dejar todos los archivos, hacer delete de X y volver a ingresarlo. Pero antes de cambiar su contenido tengo que hacerle delete y volverla a crear

    }
    else
    {
        cout << "Cree un archivo 'digito.txt' y vuelva a intentarlo." << endl;
    }
    archivoVectorX.close();
    return 0;
}
