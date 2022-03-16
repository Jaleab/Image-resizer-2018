//Aplicacion.h
#ifndef _MI_APP
#define _MI_APP
#include "Matriz.h"
#include "Generador.h"
#include "Calculos.h"

class Aplicacion{  
private:
  
public:
  Aplicacion();
  Matriz* imagenGrande(int, char*);
  void generarArchivo(Matriz *);
  void run(int, char *);
  
};
#endif