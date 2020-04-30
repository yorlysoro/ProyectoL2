#include "constantes.h"
#include "asignaciones.h"
#include "validaciones.h"
/*Codigo de las funciones*/
/*Calcula la prima de profesionalizacion en base al nivel de instruccion */
double Calcula_PrimaProf(int nInst,double sueldoBase){
	double Prima = 0.00;
	if(nInst == 1)
		Prima = 0.00;
	else if(nInst == 2)
		Prima = sueldoBase * TSU;
	else{
		if(nInst == 3)
			Prima = sueldoBase * ING;
		else{
			if(nInst == 4)
			 Prima = sueldoBase * MAG;
			else
				Prima = sueldoBase * DOC;
		}
	}
	return Prima;
}
/*Calcula la prima de Hogar*/
double Calcula_PrimaHog(void){
	return PH;
}
/*Calcula la prima de Hijo en base a la cantidad de hijos y de que estos sea menores de edad*/
double Calcula_PrimaHij(int cantHijos, int *edades){
	double Prima = 0.00;
	for(int i = 0;i < cantHijos; i++){
		if(edades[i] < 18){
			Prima += PHJ;
		}
	}
	return Prima;
}
/*Calcula la prima de actividad docente */
double Calcula_ActiDocen(){
	return PAD;
}
/*Calcula la prima de antiguedad en base a la cantidad de años*/
double Calcula_PrimaAnti(int anioIngreso, double sueldoBase){
	double Prima = 0.00;
	int cantAnios, ianioActual;
	struct tm * timeInfo;
	time_t rawtime;
	time(&rawtime);
	timeInfo = localtime(&rawtime);
	char AnioActual[80];
	strftime(AnioActual,80,"%Y",timeInfo);
	ianioActual = atoi(AnioActual);
	cantAnios = ianioActual - anioIngreso;
	if(cantAnios > 0){
		Prima = sueldoBase * PA;
		Prima = Prima * cantAnios;
	}
	return Prima;
}

