#ifndef TCD_
#define TCD_

#include <iostream>
#include <cmath>
using namespace std;

double** M (int q,unsigned int n);
double** mult(double **a, double **b);
double** traspuesta(double **m, unsigned int n);
//void traspuesta(double **m, unsigned int n);
double** multMatrices(double **a, double **b, unsigned int colsA, unsigned int rowsA, unsigned int colsB);
double** multMatrizVector(double **a, double **b, unsigned int n);
double** resolverSistema(double **M, unsigned int n, double **vectord); // en vector devuelve el resultado
double** resolverSistema2D(double **M, unsigned int n, double **matriz); // en matriz devuelve el resultado
double** factorizar(double **L, double **U, double **A, unsigned int n); //devuelve la matriz P
double** ruidoSuma(double **signal, unsigned int n);
double** ruidoSumaM(double **signal, unsigned int cols, unsigned int rows);
double** ruidoMult(double **signal, unsigned int n);
void fUmbral(double **signal, unsigned int n, int umbral);
void fMenosUmbral(double **signal, unsigned int n, int umbral);
void fUmbralm(double **signal, unsigned int cols, unsigned int rows, int umbral);
void fMenosUmbralm(double **signal, unsigned int cols, unsigned int rows, int umbral);
double PSNR(double **signal, double **conRuido, unsigned int n, double max);
double PSNRm(double **signal, double **conRuido, unsigned int cols, unsigned int rows, double max);
double ECM(double **signal, double **conRuido, unsigned int n);
double ECMm(double **signal, double **conRuido, unsigned int cols, unsigned int rows);

double** create_matrix(unsigned int cols, unsigned int rows);
void destroy_matrix(double **matrix, unsigned int rows);
double** create_vector(unsigned int n);
void destroy_vector(double **vectord, unsigned int rows);

int** create_vectorInt(unsigned int n);
void destroy_vectorInt(int **vectord, unsigned int rows);


int vueltaMatrizModificada(double **A, double** B, int** pivot, double** x, int n);
int LU_conpivote(double **A, int **pivot, int n);

#endif
