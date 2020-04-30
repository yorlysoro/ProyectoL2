#include "constantes.h"

void crearReciboT(struct trabajador, double, double, double , double, double, double, double, double, double, double, double);
bool existeArchivo(string);
void crearFifo(struct trabajador);
void creaActualizaNomina(double TotalAsignaciones, double TotalDeducciones, int mes);
void creaActualizaRegistro(string Direccion, string cedula);
bool existeTrabajador(string Registro, string cedula);
string extraeCedula(string Registro, string cedula);
void LeeArchivo(string Direccion);
string extraeRecibo(string cedula, string nRecibo);
void creaActualizaTotalIVSS(string cedula, double totalDeducciones, int mes);
void eliminarArchivo(string);
void borraRegistro(string archivo, string nRecibo);
