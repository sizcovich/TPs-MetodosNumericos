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

    Matriz& operator= (const Matriz& a);
    Matriz& sumar(const double v);
    Matriz& restar(const double v);
    Matriz& multiplicar(const double v);
    Matriz& multiplicar(const Matriz& b);
    Matriz& dividir(const double v);
    Matriz& operator+(const Matriz& b);
    Matriz& operator-(const Matriz& b);
    Matriz& operator*(const Matriz& b);

    Matriz traspuesta();
    void set(const int fila, const int col, double valor);
    double get(const int fila, const int col);

    Matriz& DCT(int rango, int dimencion);
    Matriz& ruidoSuma();
    double PSNR(Matriz& conRuido, double Vmax);
    void umbral(int umbral);
    void menosUmbral(int umbral);
    Matriz& resolverGauss(Matriz& b);

    void imprimir();

private:
    void piboteo(Matriz& b, int k);
    //void normalizar_imagen();

    int rows;
    int cols;
    double** p; //el puntero a la matriz
};
