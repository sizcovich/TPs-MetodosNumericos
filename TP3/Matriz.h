#include <iostream>
#include <cmath>

using namespace std;

class Matriz
{
public:
    Matriz();
    Matriz(const int row_count, const int column_count);
    Matriz(const Matriz& a);
    ~Matriz();

    void Cero();
    void identidad();
    Matriz& operator= (const Matriz& a);
    Matriz& sumar(const double v);
    Matriz& restar(const double v);
    Matriz& multiplicar(const double v);
    Matriz& multiplicar(const Matriz& b);
    Matriz& dividir(const double v);
    Matriz& operator+(const Matriz& b);
    void operator+= (const double b);
    void operator/= (const double b);
    void operator-=(const double b);
    void operator-=(const Matriz& b);
    Matriz& operator-(const Matriz& b);
    Matriz& operator*(const Matriz& b);
    void imprimir();

    Matriz traspuesta();
    void mediaCero();
    Matriz* potenciaYDeflacion(int cantAutovectores, double errorMax, int iterMax, Matriz* X0);
    void set(const int fila, const int col, double valor);
    double get(const int fila, const int col);
    const int columnas();
    const int filas();
    double norma2();
    double normaInf();
    double prodInterno();
	int averiguarDigito(Matriz& Vt, Matriz& Xi, Matriz& lab, int opcion);
    void compararTC(Matriz& tcMatlab);
    void algoritmoQR(Matriz Q, double tolMatrizA, double tolPorElemento);
    void cortar(int nuevaCantFilas);


private:
    double matrizAEscalar();
    double potencia(Matriz* E, int M, float epsilon, Matriz* X);
    Matriz& juntarMatrices(Matriz& TC, Matriz& label);
    void rotacion(Matriz& Q, int i, int j);
    void factorizacionQR (Matriz Q, double toleranciaPorElemento);
    bool paradaQR(double tol);

    int rows;
    int cols;
    double** p; //el puntero a la matriz
};
