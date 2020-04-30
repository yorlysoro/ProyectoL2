#include "cola.h"
#include "archivos.h"
/*Intenta crear una lista fifo, esta funcion crea una lista fifo de todos los trabajadore almacenando el sueldo neto, su
 * cedula y mes de cobro. La funcion encolar se encarga de asignar la informacion a la cola, la funcion crearFifo se encarga
 * de guardar toda esa informacion en el archivo.txt mostrando en detalle el total cobrado el mes y la cedula del trabajador*/
void crearFifo(struct cola &c){
	struct nodo *aux;
	ofstream oFifo;
	string nArch = "../txt/FIFO.txt";
	if(existeArchivo(nArch)){
		oFifo.open(nArch, ios::app);
	}
	else{
		oFifo.open(nArch, ios::out);
		oFifo << setw(50) << "Total Cobrado" << endl << endl;
		oFifo << "Trabajador" << setw(20) << "Cobrado" << setw(15) << "Mes" << endl;
	}

	while(c.primero != NULL){
		aux = c.primero;
		oFifo << aux->cedula << fixed << setprecision(2) << setw(20) << aux->sueldoNeto  << setprecision(2) << setw(20) << Meses[aux->mes] << endl;
		c.primero = aux -> siguiente;
		delete(aux);
	}
}
void encolar(struct cola &c, string cedula, double sueldoNeto, int mes){
	struct nodo *aux = new(struct nodo);
	aux->cedula = cedula;
	aux->sueldoNeto = sueldoNeto;
	aux->mes = mes;
	aux->siguiente = NULL;
	if(c.primero == NULL)
		c.primero = aux;
	else
		(c.ultimo)->siguiente = aux;
	c.ultimo = aux;
}
