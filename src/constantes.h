#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <ctime>
#define CLS system("cls");
using namespace std;
//Estructuras
struct fecha{
	int dia;
	int mes;
	int anio;
};

struct trabajador{
	string nombre; //Nombre
	string apellido; //Apellido
	string CI; //Cedula de Identidad
	fecha pago; //Fecha de Pago
	int cargo; //Cargo
	int nInst; //Nivel de Instruccion
	int CantH; //Cantidad de Hijos
	int *edadH; //Edad de los Hijos
	char AfCajaH; //Afilacion Caja de Ahorro
	int anioIngreso; //Año de Ingreso
	double sueldoBase; //Sueldo Base
	double sueldoNeto; //Sueldo Neto
};

#define UT 850 //Unidades Tributarias
#define SLM 1000000 //Salario minimo
//Asignaciones
#define TSU 0.10 //TSU
#define ING 0.14 //Ingeniero
#define MAG 0.18 //Magister
#define DOC 0.20 //Doctor

#define PH (300*UT) //Prima Hogar
#define PHJ (15*UT) //Prima Hijos
#define PAD (15*UT) //Prima Apoyo Actividad Docente
#define PA 0.015 //Prima de Antiguedad

//Sueldo Base
#define OB (2*SLM)
#define ADMIN (6*SLM)
#define DOCENTES (7*SLM)

//Deducciones
#define CJA 0.10 //Caja de Ahorro
#define SSO 0.04 //Seguro Social
#define FAOV 0.01 //Fondo de Ahorro Obligatorio para la vivienda
#define PIE 0.01 //Perdida Involuntaria del Empleo

//Niveles De Instruccion
extern string NivelInst[5];
//Meses 
extern string Meses[12];
//Cargos
extern string Cargo[3];
