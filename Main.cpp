//Main.cpp
#include "Aplicacion.h"
#include <cstdlib>
using namespace std;
int main (int argc, char ** argv) {
	char* entrada; // archivo 
	int aumento; // aumento
  	if(argc>=1){
		entrada = argv[1];
		aumento = atoi(argv[2]); //de ascci a int
	}
	else {
	   	entrada = (char *) "datos.txt"; //default
		aumento=1; //default
		
	}
    Aplicacion* aplicacion = new Aplicacion();
    aplicacion->run(aumento, entrada);
	
	delete aplicacion;
    return 0;
}
