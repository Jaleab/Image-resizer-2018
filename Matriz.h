//Matriz.h
#ifndef _MI_MAT
#define _MI_MAT
class Matriz {
    private:
    int** matriz;
	double** matrizDouble;
    int filas;
    int columnas;
    int id;
	double idDouble;
    int totalDeCeldas;
	int destructor;

    public:
	Matriz(int, int, double);
    Matriz(int, int, int);
    ~Matriz();
    void imprimir();
	void imprimirMatrizDouble();
    int getFilas();
    int getColumnas();
    int** getMatriz();
    void setCelda(int, int, int);
	void setCelda(int, int, double);
    int getValor(int, int);
	double getValorDouble(int, int);
    void sumador (int, int, int); 
	void sumador (int, int, double);
    int getTotalDeCeldas();
	void sumarDiagonal();
	bool celdaEsValida(int, int);
	void clonar(Matriz*);
};
#endif    
 