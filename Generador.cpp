// Generador.cpp
#include<iostream>
#include "Generador.h" 
#include "Matriz.h"  
using namespace std; 

Generador::Generador (Matriz* matrizOriginal){
  this->matrizOriginal = matrizOriginal; //matriz que se desea ampliar
  matrizGrande = new Matriz((matrizOriginal->getFilas()*2) + 1, (matrizOriginal->getColumnas()*2) + 1, 2); // la matriz ampliada, pero en esta solo se hacen iteraciones (no se guardan resultados)
  matrizGrandeFinal = new Matriz((matrizOriginal->getFilas()*2) + 1, (matrizOriginal->getColumnas()*2) + 1, 2); // la matriz ampliada final 
  rellenar();//rellenar matriz como primer resultado (solo con los colores de la matriz original)
  matrizGrandeFinal->clonar(matrizGrande);// inicialización de matrizGrandeFinal (para que también quede rellena previamente)

  
}

Generador::~Generador(){
  delete matrizGrande;
}

void Generador::rellenar(){
	for(int f=0; f < matrizGrande->getFilas(); ++f){
      for(int c = 0; c < matrizGrande->getColumnas(); ++c){
			matrizGrande->setCelda(f,c,-1);
	  }
	}//llena la matriz de "-1"

  for(int f=0; f < matrizOriginal->getFilas(); ++f){
      for(int c = 0; c < matrizOriginal->getColumnas(); ++c){
          matrizGrande->setCelda((2*f)+1, (2*c)+1, matrizOriginal->getValor(f, c));
      }   
  } //coloca los colores de la matriz original en su lugar correspondiente después de cada aumento
}
void Generador::completarMatriz(Matriz* pesosDeAsociacion){
    for ( int f = 0; f < matrizGrande->getFilas(); ++f){
		
        for ( int c = 0; c < matrizGrande->getColumnas(); ++c){          
            if (matrizGrande->getValor(f,c) == -1) {                
                asignarColor(f ,c ,pesosDeAsociacion);                	
            }          
        }      
    }  


}// hace los cálculos correspondientes para después llenar completamente la matrizGrandeFinal



void Generador::asignarColor(int f, int c, Matriz* pesosDeAsociacion) {
    Matriz* tablaDePesos = crearTablaDePesos(pesosDeAsociacion);
    double color1 = 0.00;
    double color2 = 0.00;
    for(int i = 0; i < tablaDePesos->getColumnas(); ++i){
     color1 =  tablaDePesos->getValorDouble(0,i);
      for(int x = f-1; x <= f + 1; ++x) {
          for(int y =  c -1 ; y <= c+1; ++y) {
			  if( !(c == y && f == x) && matrizGrande->celdaEsValida(x, y)){
                  if(matrizGrande->getValor(x,y) != -1){
					  color2= (double) matrizGrande->getValor(x,y);
                      
					  tablaDePesos->sumador(1,i, buscarValorEnPesosDeAsociacion(color1, color2, pesosDeAsociacion));
					 
                  }
              }
          }
      }
	}
	if(buscarVecinosDiferentes(f,c) > 2){
		matrizGrandeFinal->setCelda(f, c, (int)buscarMayor(tablaDePesos)); 
	}
	else{
		matrizGrandeFinal->setCelda(f, c, unicoColorVecino(f,c)); 
	}
    delete tablaDePesos;
}//método que permite asignar los colores según la matriz de pesos de asociación (parametro)

int Generador::buscarVecinosDiferentes(int f, int c){
	int v[8];
	int contador = 0;
	
	for(int i = 0; i < 8; ++i){
		v[i] = 0;
	}
	for(int x = f-1; x <= f + 1; ++x) {
          for(int y =  c -1 ; y <= c+1; ++y) {
			  if( !(c == y && f == x) && matrizGrande->celdaEsValida(x, y)){
				int color = matrizGrande->getValor(x,y);
				if(!colorExiste(v, color) && color != -1){
					v[contador] = color;
					++contador;
				}
				
			  }
		  }
	}
	return ++contador;
}

int Generador::unicoColorVecino(int f, int c){
	int color = -1;
	for(int x = f-1; x <= f + 1 && color == -1; ++x) {
          for(int y =  c -1 ; y <= c+1 && color == -1; ++y) {
			  if( !(c == y && f == x) && matrizGrande->celdaEsValida(x, y)){
				color = matrizGrande->getValor(x,y);
				}
		  }
	}
	return color;
}

bool Generador::colorExiste(int v[], int color){
	bool existe = false;
	for(int i = 0; i < 8; ++i){
		if(v[i] == color){
			existe = true;
		}
	}
	return existe;
}
                  

Matriz* Generador::crearTablaDePesos(Matriz* matriz){   
  Matriz* tablaDePesos = new Matriz (2, matriz->getColumnas()- 1, 6.0);  
  for(int i = 0; i < tablaDePesos->getColumnas(); ++i){
      tablaDePesos->setCelda(0,i,matriz->getValorDouble(i+1, 0));    // Revisar 
   }     
      
  
   return tablaDePesos;
  
}//Hace las sumas en la tabla de pesos de asociación (el parametro que recibe es la matriz de pesos de asociación)

 
double Generador::buscarValorEnPesosDeAsociacion(double valorF ,double valorC ,Matriz* pesos) {
  int pivoteF = 1;
  int pivoteC = 1; 
  double resultado = 0; 

  while (valorF != pesos->getValorDouble(pivoteF,0)&& (pivoteF < pesos->getFilas()) ){
    ++pivoteF;
  }  
  while (valorC != pesos->getValorDouble(0,pivoteC)&& (pivoteC < pesos->getColumnas()) ){
    ++pivoteC;
  } 
  resultado = pesos->getValorDouble(pivoteF,pivoteC);
  if(resultado == 1){
	  resultado = 0;	  
  }
 
  return resultado;
} //Busca el peso de asociación (parametro)de un par de colores(valorF y valorC) ejemplo: el peso de asociación 1 con 2 o 3 con 2            
	 
double Generador::buscarMayor(Matriz* matriz) {

  double mayor = matriz->getValorDouble(1,0);
  double colorMayor = matriz->getValorDouble(0,0);
  for (int i = 1 ; i < matriz->getColumnas();++i){
      if(matriz->getValorDouble(1,i) > mayor) {          
        mayor = matriz->getValorDouble(1,i);
		colorMayor= matriz->getValorDouble(0,i);
		
	  } 
  }
  return colorMayor;
}//Busca el mayor de la suma en la table de pesos de asociación (parametro)

Matriz* Generador::getMatrizGrandeFinal(){
	return matrizGrandeFinal;
}