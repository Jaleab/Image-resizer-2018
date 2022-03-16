//Aplicacion.cpp
#include "Aplicacion.h"
#include "Matriz.h"
#include "Generador.h"
#include "Calculos.h"
#include<fstream>
#include<iostream> 
using namespace std;  

Aplicacion::Aplicacion(){
    
}

void Aplicacion::run(int repeticiones, char* archivo){
   generarArchivo(imagenGrande(repeticiones, archivo));
}//Método que hace funcionar la generacion de un archivo, a partir de una matriz que es aumentada "repeticiones" veces 

Matriz* Aplicacion:: imagenGrande(int repeticiones, char* archivo){
  int filas;
  int columnas;
  int valor; 
  fstream entrada (archivo);
  entrada >> filas;
  entrada >> columnas;
  Matriz* matrizOriginal = new Matriz(filas, columnas, 1);
  
  for(int f=0; f < filas; ++f){
      for(int c = 0; c < columnas; ++c){
      entrada >> valor;
            matrizOriginal->setCelda(f, c, valor);
          }
  }    
	
  cout << "Matriz Original: " << endl << endl;
  matrizOriginal->imprimir();
  
  if (repeticiones >= 1) {
    
    for (int i = 0; i <= repeticiones-1 ; ++i) {
        Generador* generador = new Generador(matrizOriginal); 
        Calculos* calculos = new Calculos(matrizOriginal);
        generador->completarMatriz(calculos->getMatrizPesos());
		delete matrizOriginal;
        matrizOriginal = generador->getMatrizGrandeFinal();       
		cout << "Matriz Numero " << i+1 << ":" << endl << endl;
		matrizOriginal->imprimir();
		delete calculos;
        delete generador;  
    }  
		
  } 

  
  return matrizOriginal;

 }//Método que recibe el archivo y aumento deseado, al final devuelve la matriz aumentada correspondiente al archivo

void Aplicacion:: generarArchivo(Matriz * matriz){
	ofstream salida("FabricioPresidente.txt");
	
	salida<< matriz->getFilas() << " ";
	salida<< matriz->getColumnas()<< " ";
	salida<<endl;
	for(int f=0; f < matriz->getFilas(); ++f){
        for(int c = 0; c < matriz->getColumnas(); ++c){
			
			salida<<matriz->getValor(f,c)<<" ";
        }
		salida<<endl;
    }
cout << "La matriz generada fue guardada en el archivo FabricioPresidente.txt dentro de la carpeta" << endl;
}//Método que recibe la matriz final (aumentada xN) y genera un archivo FabricioPresidente.txt 

 
  
