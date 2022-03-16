//Calculos.cpp
#include<iostream>
#include "Calculos.h" 
#include "Matriz.h"
using namespace std; 

Calculos::Calculos(Matriz* matrizOriginal) {  
  vectorDeColores = new int [matrizOriginal->getTotalDeCeldas()];
  for (int i = 0; i < matrizOriginal->getTotalDeCeldas(); ++i){
        vectorDeColores[i] = -1;	    
  }// crea un vector lleno de "-1" del tamaño "cantidad de celdas" de la matriz original.
  obtenerFrecuencia(matrizOriginal); 
  obtenerTranspuesta(matrizFrecuencia); 
  multiplicarMatrices(matrizFrecuencia, matrizTranspuesta); 
  calcularPesos(matrizProducto); 
}

Calculos::~Calculos() {
  delete matrizProducto;
  delete matrizTranspuesta;
  delete matrizFrecuencia; 
  delete [] vectorDeColores;
}

int Calculos::coloresDiferentes(Matriz* matrizOriginal) {   //Sirve
    int contador = 0;
	int totalDeCeldas = matrizOriginal->getTotalDeCeldas();
	for(int f = 0; f < matrizOriginal->getFilas(); ++f) {
        for( int c = 0; c < matrizOriginal->getColumnas(); ++c) {                      
           if(!colorEsta(vectorDeColores, matrizOriginal->getValor(f,c),totalDeCeldas ) && contador<totalDeCeldas){
                          vectorDeColores[contador]=matrizOriginal->getValor(f,c);
                          ++contador;						  
            }
        }
    }
		

	return contador;
}//crea un vector con todos los colores diferentes que hay en la matriz original y además devuelve el total de colores DIFERENTES que hay en la matriz original 

bool Calculos::colorEsta(int* vector, int elemento, int limite){  //sirve
  bool existe = false;
  for(int i = 0; i < limite; ++i){
    if(vector[i] == elemento){
      existe = true;
    }     
  }
  return existe;
}//saber si un color ya fue agregado en el vector de colores diferentes
                    


void Calculos::obtenerFrecuencia(Matriz* matrizOriginal) { 
    cantidadDeColores = coloresDiferentes(matrizOriginal);                                  
	matrizFrecuencia = new Matriz (cantidadDeColores, cantidadDeColores, 3); 	
    //matrizFrecuencia->sumarDiagonal();

	for(int f = 0; f < matrizOriginal->getFilas(); ++f){		
        for(int c = 0; c < matrizOriginal->getColumnas(); ++c){			
            rellenarMatrizFrecuencia(f, c, matrizOriginal, vectorDeColores);		    
        }
    } 	
}//obtener la frecuencia con la cual aparece un color acompañado de otro en la matriz original y el mismo (parametro)


void Calculos::rellenarMatrizFrecuencia(int f, int c, Matriz* matrizOriginal, int* vectorDeColores){ //sirve con las cuadradas
    int pivoteY = 0;
    int pivoteX = 0;  
    
	while (matrizOriginal->getValor(f,c) != vectorDeColores [pivoteX]) { // hay que ver si hay que añadir un && extra para que no se desborde del vector de vectorDeColores
        ++pivoteX;      
    }
    matrizFrecuencia->sumador(pivoteX, pivoteX, 1);
	for(int x = f -1 ; x <= f + 1; ++x){
            for(int y = c - 1; y <= c + 1; ++y){                
                 if (matrizOriginal->celdaEsValida(x, y) && !(c == y && f == x)){                    
                   pivoteY = 0;                   
                   while (matrizOriginal->getValor(x,y) != vectorDeColores [pivoteY]) { // hay que ver si hay que añadir un && extra para que no se desborde del vector de vectorDeColores
                        ++pivoteY;        
                    }                    
                   
				   if (matrizOriginal->getValor(x,y) == matrizOriginal->getValor(f,c)) {
					   if((f<x) || (f==x && c<y)) {
						   matrizFrecuencia->sumador(pivoteX, pivoteY, 1); 
					   }
				   }
				   
				   else {
						matrizFrecuencia->sumador(pivoteX, pivoteY, 1);  					
				   }
				}                
            }
     }  
}//llenar una matriz según corresponde basado en el método obtenerFrecuencia(Matriz*)


  void Calculos::multiplicarMatrices(Matriz* matriz1, Matriz* matriz2){ //sirve
  int filas1 = matriz1->getFilas();
  int columnas1 = matriz1->getColumnas();
  int filas2 = matriz2->getFilas();
  int columnas2 = matriz2->getFilas();
  matrizProducto = new Matriz(filas1, columnas2, 5);
  for(int c = 0; c < columnas2; ++c){
	for(int f = 0; f < filas1; ++f){               
        for(int i = 0; i < filas1 && i < columnas2; ++i){            
		  matrizProducto->sumador(f, c, (matriz1->getValor(f,i) * matriz2->getValor(i,c)));            
          }          
        }    
    } 
}//multiplicar dos matrices

void Calculos::obtenerTranspuesta(Matriz* matriz){ //sirve
  matrizTranspuesta = new Matriz(matriz->getColumnas(), matriz->getFilas(), 4);  
  for(int f = 0; f < matrizTranspuesta->getFilas(); ++f){
    for(int c = 0; c < matrizTranspuesta->getColumnas(); ++c){
      matrizTranspuesta->setCelda(f, c, matriz->getValor(c, f));
      }
  }

}//transponer una matriz 

void Calculos::calcularPesos(Matriz* matriz){ //sirve
 
  int filas = matriz->getFilas();
  int columnas = matriz->getColumnas();
  matrizPesos = new Matriz(filas+1,columnas+1, 5.00);
  int i = 0;
 
  while(vectorDeColores[i] != -1 && i < cantidadDeColores){
	  matrizPesos->setCelda(i+1, 0, (double)vectorDeColores[i]);
	  matrizPesos->setCelda(0, i+1, (double)vectorDeColores[i]);
	  ++i;
  }	

  for(int f = 0; f < filas; ++f){
	for(int c = 0; c < columnas; ++c){		
     matrizPesos->setCelda(f+1, c+1, (double)((double)(2 * matriz->getValor(f,c)) / (double)(matriz->getValor(f,f)+matriz->getValor(c,c)))); 
    }
  }
 
}//Calcular los pesos de asociación basado en la matriz producto (parametro)
  
Matriz* Calculos::getMatrizPesos(){
	return matrizPesos;
}
  

      
                  

