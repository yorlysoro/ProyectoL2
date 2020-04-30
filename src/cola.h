/*cola para crear el archivo FIFO*/
#include <iostream>
using namespace std;
struct nodo {
	string cedula;
	double sueldoNeto;
	int mes;
	struct nodo *siguiente;
};
struct cola{
	nodo *primero;
	nodo *ultimo;
};

void encolar(struct cola &c, string cedula, double sueldoNeto, int mes);
void crearFifo(struct cola &c);
