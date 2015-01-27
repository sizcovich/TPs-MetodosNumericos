#include <iostream>
#include <cmath>
#include <limits>
#include "Matriz.h"

#define N 60000
#define M 784
#define K 5

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

void Matriz::Cero()
{
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
        {
            this->p[i][j] = 0;
        }
    }
}

void Matriz::identidad()
{
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j< this->cols; j++)
        {
            if (i == j)
                this->p[i][j] = 1;
            else
                this->p[i][j] = 0;
        }
    }
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

void Matriz::operator+=(double b)
{
    this->sumar(b);
}

void Matriz::operator/=(double b)
{
    this->dividir(b);
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

void Matriz::operator-=(const double b)
{
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
        {
            this->p[i][j] = this->p[i][j] - b;
        }
    }
}

void Matriz::operator-=(const Matriz& b)
{
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
        {
            this->p[i][j] = this->p[i][j] - b.p[i][j];
        }
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

Matriz Matriz::traspuesta()
{
    Matriz res(this->cols, this->rows);
    for(int i=0; i<this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            res.p[j][i] = this->p[i][j];

    return res;
}

void Matriz::mediaCero()
{
    Matriz *media = new Matriz(1, this->cols);
    media->Cero();
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
        {
            media->p[0][j] += this->p[i][j];
        }
    }
    //tengo en el vector media la sumatoria de los vectores, me falta dividir cada uno de los elementos por n y restarle eso a la matriz original
    for(int j = 0; j < this->cols; j++)
    {
        media->p[0][j]/=this->rows;
        for(int i = 0; i < this->rows; i++)
        {
            this->p[i][j] -= (media->p[0][j]);
        }
    }
    delete media;
}

void Matriz::set(const int row, const int col, double valor)
{
    this->p[row][col] = valor;
}

double Matriz::get(const int fila, const int col)
{
    return this->p[fila][col];
}

const int Matriz::filas()
{
    return this->rows;
}

const int Matriz::columnas()
{
    return this->cols;
}

double Matriz::norma2()
{
    double res = 0;
    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
            res+= pow(this->p[i][j],2);
    res = sqrt(res);
    return res;
}

double Matriz::normaInf()
{
    double res;
    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
        {
            if(res < abs(this->p[i][j]))
                res = abs(this->p[i][j]);
        }

    return res;
}

double Matriz::prodInterno() //para vectores
{
    double sum = 0;
    for(int i = 0; i < this->rows; i++)
    {
        sum += pow(this->p[i][0], 2);
    }
    return sum;
}

double Matriz::potencia(Matriz* E, int Max, float epsilon, Matriz* X) //En X devuelvo el autovector, y la funcion devuelve el autovalor
{
    // X es m x 1
    Matriz res(E->rows, E->cols);
    *X/= X->norma2();
    double lambda = 100;
    double normaDeX;

    for(int i = 0; i < Max; i++)
    {
        normaDeX = X->normaInf();
        *X = *E * *X;
        lambda = X->normaInf() / normaDeX;
        *X/= X->norma2();

        if(abs(lambda) < epsilon)
            break;
    }
    return lambda;
}

Matriz* Matriz::potenciaYDeflacion(int cantAutovectores, double errorMax, int iterMax, Matriz* v)
{
    //v == Vi en el pseudocodigo
    // this = E
    /*
        N = 60000
        M = 784
        double Vt[K][M];
        double TC[K][M];
        double A[N][M];
    */
    Matriz *lambda = new Matriz();
    Matriz *Vt = new Matriz(cantAutovectores,M);
    Matriz *vt = new Matriz(); //esto es Vt[i], un vector
    for (int i = 0; i < cantAutovectores; i++)
    {
        potencia(this,iterMax,errorMax, v);
        for(int j = 0; j < M; j++)
        {
            Vt->p[i][j] = v->p[j][0]; //k x m, m x 1
        }
        cout << "Obtuve autovector Nro: " << i+1 << endl;
        *vt = v->traspuesta();
        *lambda = vt->multiplicar(*this);
        *lambda = *lambda * *v;
        *lambda/=v->prodInterno();
        double L = lambda->matrizAEscalar();
        *v = v->multiplicar(L);
        *v = *v * *vt;
        *this = *this - *v;
    }
    delete vt;
    return Vt;
}

double Matriz::matrizAEscalar()
{
    return this->p[0][0];
}

//esta funcion va a sumar en cada indice la transformada de cada matriz y despues las divide por la cantidad para quedarnos con el promedio de cada una
Matriz& Matriz::juntarMatrices(Matriz& X, Matriz& label){  //  X tendria q ser TC. De hecho, tendria q ser this.
    Matriz *res = new Matriz(M, 10);
    res->Cero();
	for(int j=0; j < label.cols; ++j){
    	if(label.p[0][j] == 0){
            for(int i = 0; i < res->rows; ++i){
				res->p[i][0] =  res->p[i][0] + X.p[i][0];
            }
        }else if(label.p[0][j] == 1){
        	for(int i = 0; i < res->rows; ++i){
				res->p[i][1] =  res->p[i][1] + X.p[i][1];
        	}
        }else if(label.p[0][j] == 2){
            for(int i = 0; i < res->rows; ++i){
				res->p[i][2] =  res->p[i][2] + X.p[i][2];
            }
        }else if(label.p[0][j] == 3){
            for(int i = 0; i < res->rows; ++i){
				res->p[i][3] =  res->p[i][3] + X.p[i][3];
            }
        }else if(label.p[0][j] == 4){
            for(int i = 0; i < res->rows; ++i){
				res->p[i][4] =  res->p[i][4] + X.p[i][4];
            }
        }else if(label.p[0][j] == 5){
            for(int i = 0; i < res->rows; ++i){
				res->p[i][5] =  res->p[i][5] + X.p[i][5];
            }
        }else if(label.p[0][j] == 6){
            for(int i = 0; i < res->rows; ++i){
				res->p[i][6] =  res->p[i][6] + X.p[i][6];
            }
        }else if(label.p[0][j] == 7){
            for(int i = 0; i < res->rows; ++i){
				res->p[i][7] =  res->p[i][7] + X.p[i][7];
            }
        }else if(label.p[0][j] == 8){
            for(int i = 0; i < res->rows; ++i){
				res->p[i][8] =  res->p[i][8] + X.p[i][8];
            }
        }else if(label.p[0][j] == 9){
            for(int i = 0; i < res->rows; ++i){
				res->p[i][9] =  res->p[i][9] + X.p[i][9];
            }
        }

    }
    for(int j=0; j < res->cols; ++j){
        if(j == 0){
   			for(int i=0; i < res->rows; ++i){
               res->p[i][j] = res->p[i][j]/5923;
            }
        }
        if(j == 1){
   			for(int i=0; i < res->rows; ++i){
                res->p[i][j] = res->p[i][j]/6742;
            }
        }
        if(j == 2){
   			for(int i=0; i < res->rows; ++i){
                res->p[i][j] = res->p[i][j]/5958;
            }
        }
        if(j == 3){
   			for(int i=0; i < res->rows; ++i){
                res->p[i][j] = res->p[i][j]/6131;
            }
        }
        if(j == 4){
   			for(int i=0; i < res->rows; ++i){
                res->p[i][j] = res->p[i][j]/5842;
            }
        }
        if(j == 5){
   			for(int i=0; i < res->rows; ++i){
                res->p[i][j] = res->p[i][j]/5421;
            }
        }
        if(j == 6){
   			for(int i=0; i < res->rows; ++i){
                res->p[i][j] = res->p[i][j]/5918;
            }
        }
        if(j == 7){
   			for(int i=0; i < res->rows; ++i){
                res->p[i][j] = res->p[i][j]/6265;
            }
        }
        if(j == 8){
   			for(int i=0; i < res->rows; ++i){
                res->p[i][j] = res->p[i][j]/5851;
            }
        }
        if(j == 9){
   			for(int i=0; i < res->rows; ++i){
                res->p[i][j] = res->p[i][j]/5949;
            }
        }
    }
    return *res;
}

int Matriz::averiguarDigito(Matriz& Vt, Matriz& Xi, Matriz& lab, int opcion) // this  =  TC
{
    int numero;
    int res;
	double menorDistancia = numeric_limits<double>::max( );
	Matriz *tcXi = new Matriz();
	Matriz *vectorTc = new Matriz(M,1);
	double distancia;
	// Xi es un vector columna. tc(Xi) = Vt * Xi
	*tcXi = Vt * Xi;

    if(opcion == 1)
    {
        for(int j=0; j < this->cols; ++j)
        {
            for(int i=0; i < this->rows; ++i)
            {
                //en la i-esima columna de TC estan los k valores que describen la i-esima imagen
                vectorTc->p[i][0] = this->p[i][j];
            }
            distancia = (*vectorTc-Xi).norma2();
            if(distancia < menorDistancia)
            {
                numero = j;
                menorDistancia = distancia;
            }
        }
        res = lab.p[numero][0];
    }
    else
    {
        //opcion 2
        Matriz *newTC = new Matriz();
        *newTC = this->juntarMatrices(*this, lab);

        for(int j=0; j < newTC->cols; ++j)
        {
            for(int i=0; i < newTC->rows; ++i)
            {
                //en la i-esima columna de TC estan los k valores que describen la i-esima imagen
                vectorTc->p[i][0] = newTC->p[i][j];
            }
            distancia = (*vectorTc-Xi).norma2();
            if(distancia < menorDistancia)
            {
                numero = j;
                menorDistancia = distancia;
            }
        }
        res = numero;
    }
    delete tcXi;
    delete vectorTc;
	return res;
}

void Matriz::compararTC(Matriz& tcMatlab)
{
    double mayorDirefencia = numeric_limits<double>::min( );
    int mDi, mDj;
    double normaVectorMasLejano = numeric_limits<double>::min( );
    double norma;
    int VML;
    Matriz *comparador1 = new Matriz(M, 1);
    Matriz *comparador2 = new Matriz(M, 1);

    for(int j = 0; j < this->cols; j++)
    {
        for(int i = 0; i < this->rows; i++)
        {
            if(abs(tcMatlab.p[i][j] - this->p[i][j]) > mayorDirefencia)
            {
                mayorDirefencia = tcMatlab.p[i][j];
                mDi = i;
                mDj = j;
            }

            comparador1->p[i][0] = tcMatlab.p[i][j];
            comparador2->p[i][0] = this->p[i][j];
        }
        norma = (*comparador1 - *comparador2).norma2();
        if(norma > normaVectorMasLejano)
        {
            normaVectorMasLejano = norma;
            VML = j;
        }
    }

    cout << endl << "Resultados del analisis:" << endl << endl;
    cout << "El elemento mas alejado del aportado es el TC[" << mDi << "][" << mDj <<"], por " << mayorDirefencia << " de diferencia" << endl;
    cout << "Por otro lado, el vector mas alejado del aportado es el " << VML << "-esimo vector, por una diferencia de " << normaVectorMasLejano << " en norma 2" << endl;
}

void  Matriz::rotacion(Matriz& Q, int i, int j)    //R = this
{
	double coseno = this->p[j][j]/sqrt(this->p[j][j]*this->p[j][j]+this->p[i][j]*this->p[i][j]);
	double seno = this->p[i][j]/sqrt(this->p[j][j]*this->p[j][j]+this->p[i][j]*this->p[i][j]);

	double aux;
	for(int w=j; w < this->rows; w ++){
		aux = this->p[j][w];
		this->p[j][w] = aux*coseno + seno * this->p[i][w];
		this->p[i][w] = aux*(-seno) +	coseno * this->p[i][w];
	}
	this->p[i][j]=0;

	for(int w=0; w < this->rows; w ++){
		aux = Q.p[j][w];
		Q.p[j][w] = aux*coseno + seno * Q.p[i][w];
		Q.p[i][w] = aux*(-seno) +	coseno * Q.p[i][w];
	}
}

void Matriz::factorizacionQR (Matriz Q, double toleranciaPorElemento) //return Q, R = this
{
    if(this->rows != this->cols)
    {
        cout << "Error de dimenciones. QR opera sobre matriz cuadrada." << endl;
    }
	Q.identidad();

	for (int j=0; j<this->rows -1;j++){
		for(int i=j+1;i<this->rows;i++){
			if(fabs(this->p[i][j])>=toleranciaPorElemento){
				this->rotacion(Q,i,j);
			}
		}
	}
}

void Matriz::algoritmoQR(Matriz Q, double tolMatrizA, double tolPorElemento)
{
    if(this->rows != this->cols)
    {
        cout << "Error de dimenciones. QR opera sobre matriz cuadrada." << endl;
    }
    while(! (this->paradaQR(tolMatrizA)))
    {
        this->factorizacionQR(Q, tolPorElemento);
        *this = *this * Q;
    }
}

bool Matriz::paradaQR(double tol)
{
    double aux = 0;
    for(int i = 1; i < this->rows; i++)
    {
        for(int j = 0; j < i-1; j++)
        {
            aux += abs(this->p[i][j]);
        }
    }
    return (tol > aux);
}

void Matriz::cortar(int nuevaCantFilas)
{
    for(int a = nuevaCantFilas; a < this->rows; a++)
    {
        delete[] p[a];
    }
}
