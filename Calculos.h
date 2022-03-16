//Calculos.h
#ifndef _MI_CAL
#define _MI_CAL
#include "Matriz.h"
class Calculos {
  private:
  Matriz* matrizFrecuencia;
  Matriz* matrizTranspuesta;
  Matriz* matrizProducto;
  Matriz* matrizPesos;
  int* vectorDeColores;
  int cantidadDeColores;  
    
  public:
  Calculos(Matriz*);  
  ~Calculos();
  int coloresDiferentes(Matriz*);
  bool colorEsta(int* ,int ,int);
  void obtenerFrecuencia(Matriz*);
  void rellenarMatrizFrecuencia(int, int, Matriz*, int*);
  void multiplicarMatrices(Matriz*, Matriz*);
  void obtenerTranspuesta(Matriz*);
  void calcularPesos(Matriz*);
  Matriz* getMatrizPesos();
};
#endif
