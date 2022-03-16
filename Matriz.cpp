//Matriz.cpp
  
#include<iostream>
#include "Matriz.h"  
using namespace std; 

Matriz::Matriz(int filas, int columnas, int id){
  this->filas = filas;
  this->columnas = columnas;
  this->id = id;
  totalDeCeldas = filas * columnas; 
  matriz = new int * [filas];
  destructor = 0; //funciona como identificador para el destructor

  for(int f = 0; f < filas; ++f){
    matriz[f] = new int [columnas];
        for(int c = 0; c < columnas; ++c){
          setCelda(f, c, 0);
        }
    }

	
}//constructor de matriz de int

Matriz::Matriz(int filas, int columnas, double id){
  this->filas = filas;
  this->columnas = columnas;
  this->id = id;
  totalDeCeldas = filas * columnas;
  matrizDouble = new double * [filas];
  for(int f = 0; f < filas; ++f){
    matrizDouble[f] = new double [columnas];
        for(int c = 0; c < columnas; ++c){
          setCelda(f, c, 0.00);
        }
    }
destructor = 1;//funciona como identificador para el destructor
}//constructor de matriz de double

Matriz::~Matriz(){
  
  if ( destructor == 0) {
		for(int f=0; f < filas; ++f){
			delete [] matriz[f];
		}
		delete [] matriz;
		
	}
  
  if (destructor == 1) {
		for(int f=0; f < filas; ++f){
			delete [] matrizDouble[f];
		}
		delete [] matrizDouble;
		
	  
	}

}//el int destructor sirve para decir cual matriz eliminar



void Matriz::imprimir(){
  for(int f=0; f < filas; ++f){
        for(int c = 0; c < columnas; ++c){
          cout << matriz[f][c] << " ";
        }
    cout<< endl;
    }
	 cout << "-------------------" << endl;
}// imprime la matriz de int 

void Matriz::imprimirMatrizDouble(){
	for(int f=0; f < filas; ++f){
        for(int c = 0; c < columnas; ++c){
          cout << matrizDouble[f][c] << " ";
        }
    cout<< endl;
    }
	cout << "-------------------" << endl;
}// imprime la matriz de double

int Matriz::getFilas(){
  return filas;
 }

int Matriz::getColumnas(){
  return columnas;
  }

int ** Matriz::getMatriz(){
  return matriz;
}// devuelve un puntero a puntero de int 

void Matriz::setCelda(int x, int y, int valor){
  matriz[x][y] = valor;
}//guarda un valor (int)en una celda x,y

void Matriz::setCelda(int x, int y, double valor){
  matrizDouble[x][y] = valor;
} //guarda un valor (double)en una celda x,y

int Matriz::getValor(int f, int c){
  return matriz[f][c]; 
 }
 
double Matriz::getValorDouble(int f, int c){
  return matrizDouble[f][c]; 
} 

void Matriz::sumador(int f , int c, int valor){
  matriz[f][c] = matriz[f][c] + valor;
}// suma "valor" a la celda f,c más el número que ya contiene

void Matriz::sumador(int f, int c, double valor){
	matrizDouble[f][c] = matrizDouble[f][c] + valor;
}//análogo al método anterior, pero con una matriz de double

int Matriz::getTotalDeCeldas(){
  return totalDeCeldas;
}

void Matriz::sumarDiagonal(){
	for(int i = 0; i < filas && i < columnas; ++i){
		sumador(i, i, 1);
	}
}//Suma un uno a la diagonal (para hacer pruebas)

bool Matriz::celdaEsValida(int f, int c) { //sirve
  return (f >= 0 && c >= 0) && (c < columnas && f < filas);  
}//validar celdas

void Matriz::clonar(Matriz* matriz){
	for(int f = 0; f < filas & f < matriz->getFilas(); ++f){
		for(int c = 0; c < columnas & c < matriz->getColumnas(); ++c){
			this->matriz[f][c] = matriz->getValor(f, c);	
		} 
	}
}//crear una matriz identica a la que se ingresa en el puntero (parametro)

