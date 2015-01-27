#include <iostream>
#include <limits>
#include <stdlib.h>
#include <math.h>
#include "Matriz.h"

using namespace std;


Matriz::Matriz()
{
    p = NULL;
    rows = 0;
    cols = 0;
}

Matriz::Matriz(const int row_count, const int column_count)
{
    try
    {
        p = NULL;

        if (row_count > 0 && column_count > 0)
        {
            rows = row_count;
            cols = column_count;

            p = new double*[rows];
            for (int r = 0; r < rows; r++)
            {
                p[r] = new double[cols];

                for (int c = 0; c < cols; c++)
                {
                    p[r][c] = 0;
                }
            }
        }
    }
    catch(std::bad_alloc&)
    {
        cout << "Error al crear una Matriz. No hay memoria suficiente" << endl;
        p = NULL;
        rows = 0;
        cols = 0;
    }
}

Matriz::Matriz(const Matriz& a)
{
    rows = a.rows;
    cols = a.cols;
    p = new double*[a.rows];
    for (int r = 0; r < a.rows; r++)
    {
        p[r] = new double[a.cols];

        for (int c = 0; c < a.cols; c++)
        {
            p[r][c] = a.p[r][c];
        }
    }
}

Matriz::~Matriz()
{
    for (int r = 0; r < rows; r++)
    {
        delete[] p[r];
    }
    delete[] p;
    p = NULL;
}

Matriz& Matriz::operator= (const Matriz& a)
{
    rows = a.rows;
    cols = a.cols;
    p = new double*[a.rows];
    for (int r = 0; r < a.rows; r++)
    {
        p[r] = new double[a.cols];

        // copia los valores de la matriz a
        for (int c = 0; c < a.cols; c++)
        {
            p[r][c] = a.p[r][c];
        }
    }
    return *this;
}

// le suma un valor double a la matriz a
Matriz& Matriz::sumar(const double v)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            p[r][c] += v;
        }
    }
    return *this;
}

// resta un double a la matriz a
Matriz& Matriz::restar(const double v)
{
    return sumar(-v);
}

// multiplica un double a la matriz a(elements wise)
Matriz& Matriz::multiplicar(const double v)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            p[r][c] *= v;
        }
    }
    return *this;
}

Matriz& Matriz::dividir(const double v)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            p[r][c] /= v;
        }
    }
    return *this;
}

Matriz& Matriz:: operator+(const Matriz& b)
{
    // me fijo si las dimensiones son las mismas
    if (this->rows == b.rows && this->cols == b.cols)
    {
        Matriz* res = new Matriz(this->rows, this->cols);

        for (int r = 0; r < this->rows; r++)
        {
            for (int c = 0; c < this->cols; c++)
            {
                res->p[r][c] = this->p[r][c] + b.p[r][c];
            }
        }
        return *res;
    }
    else
    {
        cout << "Error de dimensiones (+)";
    }
    Matriz* res = new Matriz();
    return *res;
}

Matriz& Matriz::multiplicar(const Matriz& b)
{
    if (this->cols == b.rows)
    {
      Matriz* res = new Matriz(this->rows, b.cols);

      for (int r = 0; r < this->rows; r++)
      {
        for (int c_res = 0; c_res < b.cols; c_res++)
        {
          for (int c = 0; c < this->cols; c++)
          {
            res->p[r][c_res] += this->p[r][c] * b.p[c][c_res];
          }
        }
      }
      return *res;
    }
    else
    {
      cout << "Error de dimensiones (multiplicar)" << endl << "n = " << this->rows << " m1 = " << this->cols << " m2 = " << b.rows << " k = " << b.cols;
      cout << "Error de dimensiones";
      Matriz* res = new Matriz(this->rows, this->cols);
      return *res;
    }
}

Matriz& Matriz::operator* (const Matriz& b)
{
    if (this->cols == b.rows)
    {
      Matriz* res = new Matriz(this->rows, b.cols);

      for (int r = 0; r < this->rows; r++)
      {
        for (int c_res = 0; c_res < b.cols; c_res++)
        {
          for (int c = 0; c < this->cols; c++)
          {
            res->p[r][c_res] += this->p[r][c] * b.p[c][c_res];
          }
        }
        //cout << "r = " << r << " de " << this->rows << endl;
      }
      return *res;
    }
    else
    {
      cout << "Error de dimensiones (*)" << endl << "n = " << this->rows << " m1 = " << this->cols << " m2 = " << b.rows << " k = " << b.cols;
      cout << "Error de dimensiones";
      Matriz* res = new Matriz(this->rows, this->cols);
      return *res;
    }
}

Matriz& Matriz::operator-(const Matriz& b)
{
	Matriz* res = new Matriz(this->rows, this->cols);
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
        {
            res->p[i][j] = this->p[i][j] - b.p[i][j];
        }
    }
    return *res;
}

Matriz Matriz::traspuesta()
{
    Matriz res(this->cols, this->rows);
    for(int i=0; i<this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            res.p[j][i] = this->p[i][j];

    return res;
}

void Matriz::set(const int row, const int col, double valor)
{
    this->p[row][col] = valor;
}

double Matriz::get(const int fila, const int col)
{
    return this->p[fila][col];
}


/**     DCT(M):
M = floor((rango * Msombrero + 1) / 2)
Msombrero = C[i] * T[i][j]
C[i] = sqrt(1/n) si i==0; C[i] = sqrt(2/n) sino
T = cos(G * St)
G[i] = i
S[j] = PI/2 * (j + 1/2)

Siendo que G[0] = 0 => T[0][j] = cos(0*St) = cos(0) = 1
=> Msombrero[0][j] = sqrt(1/n) * 1
=> M[0][j] = floor( ( rango*sqrt(1/n)+1 ) /2 )
    y M[i][j] = floor( (rango*sqrt(2/n)*T[i][j] + 1) /2 )
*/

Matriz& Matriz::DCT(int rango, int n) //O(n^2)
{
    const double PI  =3.141592653589793238463;
    Matriz *res = new Matriz(n, n);

	//cout << "1/double(n): " << 1/double(n) << endl;
	cout << "sqrt(1/double(n)): " << sqrt(1/double(n)) << endl;

	double aux = sqrt(1/double(n));
	aux = rango * aux + 1;
        res->p[0][0] = floor(aux / 2);

	cout << "res->p[0][0]" << res->p[0][0];

    for (int j = 1; j < n; j++)
    {
        res->p[0][j] = res->p[0][0];
    }


    for(int i=1; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            aux = sqrt(2/ double(n));
            res->p[i][j] = floor((rango * aux * cos(i * PI/n *(j+1/2)) + 1) / 2);
        }

    return *res;
}

Matriz& Matriz::ruidoSuma()
{
	Matriz *res = new Matriz(this->rows, this->cols);
	srand (this->cols);
	for(int i=0; i<this->rows; i++)
	{
        for(int j = 0; j < this->cols; j++)
        {
            int ruido = rand() % 500;
            res->p[i][j] = this->p[i][j] + double(ruido)/100; //random entre 0 y 0.499
        }
	}
	return *res;
}

//void Matriz::normalizar_imagen()
//{

//}

double Matriz::PSNR(Matriz& conRuido, double Vmax)
{
    double ecm = 0;
    for(int i = 0; i < this->rows; i++)
	    for(int j = 0; j < this->cols; j++)
        {
            this->p[i][j] = round(this->p[i][j]);
            conRuido.p[i][j] = round(conRuido.p[i][j]);

            if(conRuido.p[i][j] < 0)
                conRuido.p[i][j] = 0;
            else
                if(conRuido.p[i][j] > 255)
                    conRuido.p[i][j] = 255;

            if(this->p[i][j] < 0)
                this->p[i][j] = 0;
            else
                if(this->p[i][j] > 255)
                    this->p[i][j] = 255;

			ecm+=pow(this->p[i][j] - conRuido.p[i][j],2);
			cout << "conRuido" << conRuido.p[i][j] << endl;
		}

	Vmax *=Vmax;
	if(ecm >= numeric_limits<double>::min( ))
        return 10 * log10((this->rows*Vmax)/ecm);
    else
	//cout << "ECM" << ecm << endl;
        return 987654321;
}


void Matriz::umbral(int umbral)
{
	for(int i = 0; i<this->rows; i++)
	{
		for(int j = 0; j<this->cols; j++)
        {
            if(abs(this->p[i][j]) < umbral)
            {
                this->p[i][j] = 0;
            }
        }
	}
}

void Matriz::menosUmbral(int umbral){
    for (int i = 0; i<this->rows; ++i) {
        for (int j = 0; j<this->cols; ++j) {
            if (this->p[i][j] > umbral) {
                this->p[i][j]-=umbral;
            }
        }
    }
}

/**
Lea A, b
Ab=[A b]
Para k= 1 hasta  n incrementando 1
    Para i= k + 1 hasta n
        Mik= Abik/Abkk
        Para j= k hasta n+1
            Abik= Abij - mik. Abkj
        Fin para
    Fin para
Fin para
X(n)=Ab(n,n+1)/Ab(n,n)
para i=n-1hasta 1 paso -1
    acum=0
    para j= i+1 hasta n
        acum = acum + Ab(i,j)*X(j)
    Fin para
    X(i)=(Ab(i,n+1)-acum)/Ab(i,i)
Fin para
Muestre A
Muestre X
*/
Matriz& Matriz::resolverGauss(Matriz& b) //Eliminacion Gaussiana con piboteo parcial
{
    Matriz *m = new Matriz(this->rows, this->cols);
    Matriz *x = new Matriz(b.rows, 1);
    int n = this->rows;
    for(int k = 0; k < n; k++)
    {
        this->piboteo(b,k);
        for(int i = k+1; i < n; i++)
        {
            m->p[i][k] = this->p[i][k] / this->p[k][k];
            for(int j = k; j < n; j++)
            {
                this->p[i][k] = this->p[i][j] - m->p[i][k] * this->p[k][j];
            }
            this->p[i][k] = b.p[i][0] - m->p[i][k] * b.p[k][0];
        }
    }
    x->p[n-1][0] = b.p[n-1][0] / this->p[n-1][n-1];
    for(int i = n-2; i >=0; i--)
    {
        double acum = 0;
        for(int j = i+1; j < n; j++)
        {
            acum += this->p[i][j] * x->p[j][0];
        }
        x->p[i][0] = (b.p[i][0] - acum) / this->p[i][i];
    }
    return *x;
}

void Matriz::piboteo(Matriz& b, int k)
{
    //coloco en la fila k-esima la que tiene en this->p[i][k] el mayor elemento (i >=k )
    int n = this->rows;
    double maximo = this->p[k][k];
    int maxPosicion = k;
    for (int i = k+1; i < n; i++)
    {
        if(this->p[i][k] > maximo)
            maxPosicion = i;
    }
    if(maxPosicion != k)
    {
        double aux;
        for(int j = k; j < n; j++) // solo intercambio desde k xq los anteriores elementos son 0 en ambos casos
        {
            aux = this->p[k][j];
            this->p[k][j] = this->p[maxPosicion][j];
            this->p[maxPosicion][j] = aux;
        }
    }
}

void Matriz::imprimir()
{
    for(int i = 0; i < this->rows; i++)
    {
        cout << "[ ";
        for(int j = 0; j < this->cols; j++)
        {
            cout << this->p[i][j];
            if(j != this->cols-1)
                cout << " ";
        }
        cout << "]" <<  endl;
    }
    cout << ";"<< endl << endl;
}
