#include <cmath>
#include <stdlib.h>
#include "tcd.h"

#define pi 3.14159265359

using namespace std;

double** vectorDeFrecuencias (unsigned int n){
	double** res = create_vector(n);
	for (unsigned int i = 0; i < n; i++)
		*res[i] = double(i);
	return res;
}

double** vectorDeMuestreo (unsigned int n){
	double** res = create_vector(n);
	for (unsigned int i = 0; i < n; i++){
		*res[i] = double(1 + (i/2));
		*res[i] = double(*res[i] * double(pi/n));
	}
	return res;
}

double** mSombrero (unsigned int n){
	double **g = vectorDeFrecuencias(n);
	double **s = vectorDeMuestreo(n);
	double **res = create_matrix(n, n);
	for (unsigned int i = 0; i < n; i++)
		for (unsigned int j = 0; j < n; j++)
		{
			double t = *g[i] * *s[j];
			if(i == 1)
				res[i][j] = sqrt(1/n) * cos(t);
			else
				res[i][j] = sqrt(2/n) * cos(t);
		}
	return res;
}

double** M (int q, unsigned int n)
{
	double **mS = mSombrero(n);

	double **res = create_matrix(n, n);
	for (unsigned int i = 0; i < n; i++)
		for (unsigned int j = 0; j < n; j++)
		{
			res[i][j] = floor((q * mS[i][j] + 1)/2);
		}
	return res;
}

double** multMatrices(double **a, double **b, unsigned int colsA, unsigned int rowsA, unsigned int colsB)
{
    //colsA = rowsB
	double **res = create_matrix(colsB, rowsA);
	for (unsigned int i = 0; i < colsB; i++)
		for (unsigned int j = 0; j < rowsA; j++)
		{
			res[i][j]= a[i][0] * b[0][j];
			for(unsigned int k = 1; k < colsA; k++)
			{
				res[i][j] += a[i][k] * b[k][j];
			}
		}
	return res;
}
double** multMatrizVector(double **a, double **b, unsigned int n)
{
	double **res = create_matrix(n, n);
	for (unsigned int i = 0; i < n; i++)
		for (unsigned int j = 0; j < n; j++)
		{
			res[i][j]= a[i][0] * *b[0];
			for(unsigned int k = 1; k < n; k++)
			{
				res[i][j] += a[k][j] * *b[k];
			}
		}
	return res;
}

double** traspuesta(double **m, unsigned int n)
{
	double **res = create_matrix(n, n);
	for (unsigned int i = 0; i < n; i++)
		for (unsigned int j = 0; j < n; j++)
		{
			res[j][i] = m[i][j];
		}
	return res;
}

double** resolverSistema(double **M, unsigned int n, double **vectord)
{
    int** pivot = create_vectorInt(n);
    double** result = create_vector(n);
    vueltaMatrizModificada(M, vectord, pivot, result, n);
    destroy_vectorInt(pivot, n);
    return result;
}

double** resolverSistema2D(double **M, unsigned int n, double **matriz)
{
    int** pivot = create_vectorInt(n);
    double** elemIesimo = create_vector(n);
    double** resultIesimo = create_vector(n);
    double** result = create_matrix(n, n);
    for(unsigned int j = 0; j < n; j++)
    {
        for(unsigned int i = 0; i < n; i++)
        {
            *elemIesimo[i] = matriz[i][j];
        }
        vueltaMatrizModificada(M, elemIesimo, pivot, resultIesimo, n);
        for(unsigned int i = 0; i < n; i++)
        {
            matriz[i][j] = *resultIesimo[i];
        }
    }
    destroy_vectorInt(pivot, n);
    destroy_vector(elemIesimo, n);
    destroy_vector(resultIesimo, n);
    return result;
}


double** ruidoSuma(double **signal, unsigned int n)
{
	double** res = create_vector(n);
	srand (n);
	for(unsigned int i=0; i<n; i++)
	{
		int ruido = rand() % 500;
		*res[i]= *signal[i] + double(ruido)/100; //random entre 0 y 0.499
	}
	return res;
}

double** ruidoSumaM(double **matriz, unsigned int cols, unsigned int rows)
{
	double** res = create_matrix(cols, rows);
	srand (cols);
	for(unsigned int i=0; i<cols; i++)
	{
        for(unsigned int j=0; i<rows; i++)
        {
            int ruido = rand() % 500;
            res[i][j]= matriz[i][j] + double(ruido)/100; //random entre 0 y 0.499
        }
	}

	return res;
}

double** ruidoMult(double **signal, unsigned int n)
{
	double** res = create_vector(n);
	srand (n);
	for(unsigned int i=0; i<n; i++)
	{
		int ruido = rand() % 500;
		*res[i]= *signal[i] * double(ruido)/100; //random entre 0 y 0.499
	}
	return res;
}

double** ruidoMultm(double **matriz, unsigned int cols, unsigned int rows)
{
	double** res = create_matrix(cols, rows);
	srand (cols);
	for(unsigned int i=0; i<cols; i++)
	{
	    for(unsigned int j=0; j<rows; j++)
        {
            int ruido = rand() % 500;
            res[i][j]= matriz[i][j] * double(ruido)/100; //random entre 0 y 0.499
        }
	}
	return res;
}

void fUmbral(double **signal, unsigned int n, int umbral)
{
	for(unsigned int i = 0; i<n; i++)
	{
		if(abs(*signal[i])<umbral)
		{
			*signal[i] = 0;
		}
	}
}

void fMenosUmbral(double **signal, unsigned int n, int umbral){
    for (unsigned int i = 0; i<n; ++i) {
        if (*signal[i] > umbral) {
            *signal[i]-=umbral;
        }
    }
}

void fUmbralm(double **matriz, unsigned int cols, unsigned int rows, int umbral)
{
	for(unsigned int i = 0; i<cols; i++)
	{
		for(unsigned int j = 0; j<rows; j++)
        {
            if(abs(matriz[i][j])<umbral)
            {
                matriz[i][j] = 0;
            }
        }
	}
}

void fMenosUmbralm(double **matriz, unsigned int cols, unsigned int rows, int umbral){
    for (unsigned int i = 0; i<cols; ++i) {
        for (unsigned int j = 0; j<rows; ++j) {
            if (matriz[i][j] > umbral) {
                matriz[i][j]-=umbral;
            }
        }
    }
}


double PSNR(double **signal, double **conRuido, unsigned int n, double Vmax)
{
	double ecm = ECM(signal, conRuido, n);
	Vmax *=Vmax;
	if(ecm != 0)
        return 10 * log10(Vmax/ecm);
    else
        return 9999999999999;
}

double ECM(double **signal, double **conRuido, unsigned int n)
{
	double sum = 0;
	for(unsigned int i = 0; i < n; i++)
	{
		sum+=pow(*signal[i] - *conRuido[i],2);
	}

	return sum/n;
}

double PSNRm(double **matriz, double **conRuido, unsigned int cols, unsigned int rows, double Vmax)
{
	double ecm = ECMm(matriz, conRuido, cols, rows);
	Vmax *=Vmax;
	if(ecm != 0)
        return 10 * log10(Vmax/ecm);
    else
        return 9999999999999;
}

double ECMm(double **matriz, double **conRuido, unsigned int cols, unsigned int rows)
{
	double sum = 0;
	for(unsigned int i = 0; i < cols; i++)
	{
	    for(unsigned int j = 0; j < rows; j++)
        {
            sum+=pow(matriz[i] - conRuido[i],2);
        }
	}
	return sum/(cols*rows);
}

double** create_matrix(unsigned int cols, unsigned int rows) {
	double **bar = (double**)malloc(rows * sizeof(double*));
    for (size_t i = 0; i < rows; ++i)
    {
        bar[i] = (double*)malloc(cols * sizeof(double));
    }
    return bar;
}

void destroy_matrix(double **matrix, unsigned int rows) {
    for (size_t i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

double** create_vector(unsigned int n) {
	unsigned int rows = n, cols = 1;
	double **bar = (double**)malloc(rows * sizeof(double*));
    for (size_t i = 0; i < rows; ++i)
    {
        bar[i] = (double*)malloc(cols * sizeof(double));
    }
    return bar;
}

void destroy_vector(double **vector, unsigned int rows) {
    free(vector);
}

int** create_vectorInt(unsigned int n) {
	unsigned int rows = n, cols = 1;
	int **bar = (int**)malloc(rows * sizeof(int*));
    for (size_t i = 0; i < rows; ++i)
    {
        bar[i] = (int*)malloc(cols * sizeof(int));
    }
    return bar;
}

void destroy_vectorInt(int **vector, unsigned int rows) {
    free(vector);
}

int LU_conpivote(double **A, int **pivot, int n)
{
   int i, j, k;
   double *p_k, *p_row, *p_col;
   double max;

   for (k = 0, p_k = *A; k < n; p_k += n, k++) {

      *pivot[k] = k;
      max = fabs( *(p_k + k) );
      for (j = k + 1, p_row = p_k + n; j < n; j++, p_row += n) {
         if ( max < fabs(*(p_row + k)) ) {
            max = fabs(*(p_row + k));
            *pivot[k] = j;
            p_col = p_row;
         }
      }

      if (*pivot[k] != k)
         for (j = 0; j < n; j++) {
            max = *(p_k + j);
            *(p_k + j) = *(p_col + j);
            *(p_col + j) = max;
         }

      if ( *(p_k + k) == 0.0 ) return -1;

      for (i = k+1, p_row = p_k + n; i < n; p_row += n, i++) {
         *(p_row + k) /= *(p_k + k);
      }

      for (i = k+1, p_row = p_k + n; i < n; p_row += n, i++)
         for (j = k+1; j < n; j++)
            *(p_row + j) -= *(p_row + k) * *(p_k + j);

   }

   return 0;
}

int vueltaMatrizModificada(double **A, double** B, int** pivot, double** x, int n)
{
   int i, k;
   double *p_k;
   double dum;
    LU_conpivote(A, pivot, n);

   for (k = 0, p_k = *A; k < n; p_k += n, k++) {
      if (*pivot[k] != k) {dum = *B[k]; *B[k] = *B[*pivot[k]]; *B[*pivot[k]] = dum; }
      *x[k] = *B[k];
      for (i = 0; i < k; i++) *x[k] -= *x[i] * *(p_k + i);
   }

   for (k = n-1, p_k = *A + n*(n-1); k >= 0; k--, p_k -= n) {
      if (*pivot[k] != k) {dum = *B[k]; *B[k] = *B[*pivot[k]]; *B[*pivot[k]] = dum; }
      for (i = k + 1; i < n; i++) *x[k] -= *x[i] * *(p_k + i);
      if (*(p_k + k) == 0.0) return -1;
      *x[k] /= *(p_k + k);
   }

   return 0;
}

