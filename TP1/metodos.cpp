#include <cmath>
#include <iostream>
#include <list>
#include <time.h>
#include "metodos.h"
#include "formulas.h"
#include "TFloat.h"

using namespace std;

TFloat newton(int n, list<double>::iterator m, size_t precision, double error, TFloat p0, int tipoError, int maxIteraciones, int *iteracionesQRealiza, double *errorFinal, float *tiempo){
    TFloat xn = p0;
  TFloat xnMas1(0.0, precision);
  bool _error = 0;
  int i=1;

    clock_t t_ini, t_fin;        

    t_ini = clock();
  while(i <= maxIteraciones && _error == 0){

    xnMas1 = xn - (fDeS(xn, n, m)/(fPrimaDeS(xn, n, m)));

    switch (tipoError) { //calculo _error
      case 1:
        if(fabs(fDeS(xnMas1, n, m).dbl()) < error){
          *errorFinal = fabs(fDeS(xnMas1, n, m).dbl());
          _error=1;
        }
        break;
      case 2:
        if(fabs((xnMas1-xn).dbl()) < error){
          *errorFinal = fabs((xnMas1-xn).dbl());
          _error=1;
        }
        break;
      case 3:
        if(fabs(((xnMas1-xn)/ xn).dbl()) < error){
          *errorFinal = fabs(((xnMas1-xn)/ xn).dbl());
          _error=1;
        }
        break;
      case 4:
        if(fabs((fDeS(xnMas1, n, m)-fDeS(xn, n, m)).dbl())< error){
          *errorFinal = fabs((fDeS(xnMas1, n, m)-fDeS(xn, n, m)).dbl());
          _error=1;
        }
        break;
      case 5:
        if(fabs(((fDeS(xnMas1, n, m)-fDeS(xn, n, m))/fDeS(xn, n, m)).dbl())< error){
          *errorFinal = fabs(((fDeS(xnMas1, n, m)-fDeS(xn, n, m))/fDeS(xn, n, m)).dbl());
          _error=1;
        }
        break;       

    }
    xn = xnMas1;
    i++;
  }
  
  *iteracionesQRealiza = --i;

    t_fin = clock();
    
    *tiempo = (((float)t_fin-(float)t_ini) * 1000)/CLOCKS_PER_SEC;

  
  switch (tipoError) { //calculo _error
    case 1:
      if(_error==0){
        *errorFinal = fabs(fDeS(xnMas1, n, m).dbl());
      }
      break;
    case 2:
      if(_error==0){
        *errorFinal = fabs((xnMas1-xn).dbl());
      }
      break;
    case 3:
      if(_error==0){
        *errorFinal = fabs(((xnMas1-xn)/ xn).dbl());
      }
      break;
    case 4:
      if(_error==0){
        *errorFinal = fabs((fDeS(xnMas1, n, m)-fDeS(xn, n, m)).dbl());
      }
      break;
    case 5:
      if(_error==0){
        *errorFinal = fabs(((fDeS(xnMas1, n, m)-fDeS(xn, n, m))/fDeS(xn, n, m)).dbl());
      }
      break;       
    }
    
  return xn;
}

TFloat secante(int n, list<double>::iterator m, size_t precision, double error, TFloat p0, TFloat p1, int tipoError, int maxIteraciones, int *iteracionesQRealiza, double *errorFinal, float *tiempo){
    TFloat xnMenos1 = p0;
    TFloat xn = p1;
  TFloat xnMas1(0, precision);
  bool _error = 0;
  int i=1;
  
  clock_t t_ini, t_fin;  
    t_ini = clock();

  while(i <= maxIteraciones && _error == 0){
    xnMas1 = xn - ((xn - xnMenos1 )/(fDeS(xn, n, m)-fDeS(xnMenos1, n, m))) * fDeS(xn, n, m);
    
    switch (tipoError) { //calculo _error
      case 1:
        if(fabs(fDeS(xnMas1, n, m).dbl()) < error){
          *errorFinal = fabs(fDeS(xnMas1, n, m).dbl());
          _error=1;
        }
        break;
      case 2:
        if(fabs((xnMas1-xn).dbl()) < error){
          *errorFinal = fabs((xnMas1-xn).dbl());
          _error=1;
        }
        break;
      case 3:
        if(fabs(((xnMas1-xn)/ xn).dbl()) < error){
          *errorFinal = fabs(((xnMas1-xn)/ xn).dbl());
          _error=1;
        }
        break;
      case 4:
        if(fabs((fDeS(xnMas1, n, m)-fDeS(xn, n, m)).dbl())< error){
          *errorFinal = fabs((fDeS(xnMas1, n, m)-fDeS(xn, n, m)).dbl());
          _error=1;
        }
        break;
      case 5:
        if(fabs(((fDeS(xnMas1, n, m)-fDeS(xn, n, m))/fDeS(xn, n, m)).dbl())< error){
          *errorFinal = fabs(((fDeS(xnMas1, n, m)-fDeS(xn, n, m))/fDeS(xn, n, m)).dbl());
          _error=1;
        }
        break;       

    }
    xn = xnMas1;
    i++;
  }
  
  *iteracionesQRealiza = --i;
    t_fin = clock();
    *tiempo = (((float)t_fin-(float)t_ini) * 1000)/CLOCKS_PER_SEC;
    
    switch (tipoError) { //calculo _error
    case 1:
      if(_error==0){
        *errorFinal = fabs(fDeS(xnMas1, n, m).dbl());
      }
      break;
    case 2:
      if(_error==0){
        *errorFinal = fabs((xnMas1-xn).dbl());
      }
      break;
    case 3:
      if(_error==0){
        *errorFinal = fabs(((xnMas1-xn)/ xn).dbl());
      }
      break;
    case 4:
      if(_error==0){
        *errorFinal = fabs((fDeS(xnMas1, n, m)-fDeS(xn, n, m)).dbl());
      }
      break;
    case 5:
      if(_error==0){
        *errorFinal = fabs(((fDeS(xnMas1, n, m)-fDeS(xn, n, m))/fDeS(xn, n, m)).dbl());
      }
      break;       
    }
    
  return xn;
}

TFloat biseccion(int n, list<double>::iterator m, size_t precision, double error, TFloat a, TFloat b, int tipoError, int maxIteraciones, int *iteracionesQRealiza, double *errorFinal, float *tiempo, TFloat *c2, bool sacarC2){
  TFloat c(0.0, precision);
    TFloat anMenos1(0.0, precision);
  bool _error = 0;
  int i=1;
  
    clock_t t_ini, t_fin; 
    t_ini = clock();
  do
  {
    *c2 = c;
    while(i <= maxIteraciones && _error == 0){
      
      c = (a+b)/2;
      
      if((fDeS(a, n, m)*fDeS(c, n, m)).dbl() < 0){
                anMenos1 = a;        
                b = c;
            }
      else{
                anMenos1 = b;        
                a = c;
      }
      
      switch (tipoError) { //calculo _error
        case 1:
          if(fabs(fDeS(c, n, m).dbl()) < error){
            *errorFinal = fabs(fDeS(c, n, m).dbl());
            _error=1;
          }
          break;
        case 2:
          if(fabs((c-anMenos1).dbl()) < error){
            *errorFinal = fabs((c-anMenos1).dbl());
            _error=1;
          }
          break;
        case 3:
          if(fabs(((c-anMenos1)/ anMenos1).dbl())< error){
            *errorFinal = fabs(((c-anMenos1)/ anMenos1).dbl());
            _error=1;
          }
          break;
        case 4:
          if(fabs((fDeS(c, n, m)-fDeS(anMenos1, n, m)).dbl())< error){
            *errorFinal = fabs((fDeS(c, n, m)-fDeS(anMenos1, n, m)).dbl());
            _error=1;
          }
          break;
        case 5:
          if(fabs(((fDeS(c, n, m)-fDeS(anMenos1, n, m))/fDeS(anMenos1, n, m)).dbl()) < error){
            *errorFinal = fabs(((fDeS(c, n, m)-fDeS(anMenos1, n, m))/fDeS(anMenos1, n, m)).dbl());
            _error=1;
          }
          break;       
      }
      i++;
    }

  sacarC2 = !sacarC2;
  if (sacarC2 == true)
    i--;
  else
  {
    i = maxIteraciones -2;
    _error = 0;
  }
  }while(sacarC2 == false);
  
  *iteracionesQRealiza = i;

    t_fin = clock();
    *tiempo = (((float)t_fin-(float)t_ini) * 1000)/CLOCKS_PER_SEC;
    
    switch (tipoError) { //calculo _error
      case 1:
        if(_error==0){
          *errorFinal = fabs(fDeS(c, n, m).dbl());
        }
        break;
      case 2:
        if(_error==0){
          *errorFinal = fabs((c-anMenos1).dbl());
        }
        break;
      case 3:
        if(_error==0){
          *errorFinal = fabs(((c-anMenos1)/ anMenos1).dbl());
        }
        break;
      case 4:
        if(_error==0){
          *errorFinal = fabs((fDeS(c, n, m)-fDeS(anMenos1, n, m)).dbl());
        }
        break;
      case 5:
        if(_error==0){
          *errorFinal = fabs(((fDeS(c, n, m)-fDeS(anMenos1, n, m))/fDeS(anMenos1, n, m)).dbl());
        }
      break;       
      }
      
  return c;  
}
