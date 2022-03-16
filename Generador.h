// Generador.h
#ifndef _MI_GEN
#define _MI_GEN
#include "Matriz.h"

class Generador {
    private:
    Matriz* matrizOriginal;
    Matriz* matrizGrande;
	Matriz* matrizGrandeFinal;
	    
    public:
    Generador(Matriz*);
    ~Generador();
    void rellenar ();
	void completarMatriz(Matriz*);
	void asignarColor(int, int, Matriz*);
	int buscarVecinosDiferentes(int, int);
	int unicoColorVecino(int, int);
	bool colorExiste(int [], int);
	Matriz* crearTablaDePesos(Matriz*);
	double buscarValorEnPesosDeAsociacion(double, double, Matriz*);
	double buscarMayor(Matriz*);
	Matriz* getMatrizGrandeFinal();
};
#endif