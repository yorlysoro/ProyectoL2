#include "deducciones.h"
#include "constantes.h"
/*Codigo de las funciones */
/*Calcula el descuento por Afilacion a la caja de ahorro y verifica
 * de que el trabajador posea afiliacion */
double Calcula_DescuentoCA(char AfCajaH, double sueldoBase){
	double Descuento = 0.00;
	if(toupper(AfCajaH) == 'S')
		Descuento = sueldoBase * CJA;
	return Descuento;
}
/*Calcula el descuento de el seguro social*/
double Calcula_SSO(double sueldoBase){
	double Descuento;
	Descuento = sueldoBase * SSO;
	return Descuento;
}
/*Calcula el Descuento de Fondo de Ahorro Obligatorio para la vivienda*/
double Calcula_FAOV(double sueldoBase){
	double Descuento;
	Descuento = sueldoBase * FAOV;
	return Descuento;
}
/*Calcula el Descuento de Perdida Involuntaria del Empleo*/
double Calcula_PIE(double sueldoBase){
	double Descuento;
	Descuento = sueldoBase * PIE;
	return Descuento;
}
