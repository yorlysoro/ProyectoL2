#include "constantes.h"
#include "validaciones.h"
/*Valida la cadena de caracteres que se le pasa por parametro, verifica de que no contenga caracteres alfabeticos,espacios en blanco o signos de puntuacion
 * haciendo uso de las funciones isalpha, ispunct e issapce*/
bool validarCadena(string cadena){
	int tamanio = cadena.length();
	if(cadena.empty()){
		return true;
	}
	for(int y = 0; y < tamanio; y++){
		if(isalpha(cadena[y]) !=0 || ispunct(cadena[y]) != 0 || isspace(cadena[y]) != 0)
			return true;
	}
	return false;
}
/*Validad el Nombre y Apellido, verifica de que no contenga numeros y signos de puntuacion, haciendo uso de las funciones 
 * isdigit e ispunct*/
bool validarNombreApellido(string nombreApellido){
	int tamanio = nombreApellido.length();
	if(nombreApellido.empty()){
		return true;
	}
	for(int y = 0; y < tamanio; y++){
		if(isdigit(nombreApellido[y]) != 0 || ispunct(nombreApellido[y]) != 0 )
			return true;
	}
	return false;
}
/*Convierte en mayuscula la primera letra de cada palabra contenida en cadena de texto*/
string convertirPM(string cadena){
	cadena[0] = toupper(cadena[0]);
	for(int i = 1; i < cadena.length(); i++){
		if(cadena[i] != ' ')
			cadena[i] = tolower(cadena[i]);
		else{
			i++;
			cadena[i] = toupper(cadena[i]);
		}
	}
	return cadena;
}
/*Validad la fecha*/
bool validarFecha(string dia, string mes, string anio){
	struct tm * timeInfo;
	time_t rawtime;
	time(&rawtime);
	timeInfo = localtime(&rawtime);
	char AnioActual[80];
	strftime(AnioActual,80,"%Y",timeInfo);
	int imes, idia, ianio, tdia, tmes, tanio;
	tdia = dia.length();
	tmes = mes.length();
	tanio = anio.length();
	if(dia.empty() || mes.empty() || anio.empty()){
		return true;
	}
	if(tdia > 2 || tmes > 2){
		return true;
	}else if(tanio > 4){
		return true;
	}
	for(int y = 0; y < tdia; y++){
		if(isalpha(dia[y]) != 0 || ispunct(dia[y]) != 0 || isspace(dia[y]) != 0) {
			return true;
			break;
		}
	}
	for(int y = 0; y < tmes; y++){
		if(isalpha(mes[y]) != 0 || ispunct(mes[y]) != 0 || isspace(mes[y]) != 0){
			return true;
			break;
		}
	}
	for(int y = 0; y < tanio; y++){
		if(isalpha(anio[y]) != 0 || ispunct(anio[y]) != 0 || isspace(anio[y]) != 0){
			return true;
			break;
		}
	}
	imes = atoi(mes.c_str());
	idia = atoi(dia.c_str());
	ianio = atoi(anio.c_str());
	if(imes > 12 || imes < 1)
		return true;
	else if(idia < 1 || idia > 31)
		return true;
	else if(idia > 29 && imes == 2)
		return true;
	else{
		if(strcmp(AnioActual,anio.c_str()) != 0)
			return true;
	}
	return false;
}

bool validarAnio(string anio){
	struct tm * timeInfo;
	time_t rawtime;
	time(&rawtime);
	timeInfo = localtime(&rawtime);
	char AnioActual[80];
	strftime(AnioActual,80,"%Y",timeInfo);
	int tanio = anio.length();
	if(anio.empty()){
		return true;
	}
	if(tanio > 4){
		return true;
	}
	for(int y = 0; y < tanio; y++){
		if(isalpha(anio[y]) != 0 || ispunct(anio[y]) != 0 || isspace(anio[y])){
			return true;
			break;
		}
	}
	int ianio, anioA;
	ianio = atoi(anio.c_str());
	anioA = atoi(AnioActual);
	if(ianio < 1999 || ianio > anioA){
		return true;
	}
	return false;

}

double validarSueldo(string sueldo){
	int cantP = 0;
	if(sueldo.empty()){
		return 0.00;
	}
	for(int y; y < sueldo.length(); y++){
		if(sueldo[y] == '.')
			cantP += 1;
		if(isalpha(sueldo[y]) != 0 || isspace(sueldo[y]) != 0 ){
			return 0.00;
			break;
		}
		if(sueldo[y] == ';' || sueldo[y]== ',' || sueldo[y]==':')
		{
			return 0.00;
		}
		
	}
	double fsueldo = atof(sueldo.c_str());
	return fsueldo;
}

bool validarNumero(string numero){
	int tamanio=numero.length();
	if(numero.empty()){
		return true;
	}
	if(tamanio>2){
		return true;
	}

	for(int i = 0; i<tamanio; i++){
		if(isalpha(numero[i])!= 0 || isspace(numero[i]) != 0 || ispunct(numero[i]) != 0 ){
			return true;
			break;
		}
	}
	int inumero = atoi(numero.c_str());
	if(inumero<=0){
		return true;
	}
return false;
}
bool validarEdad(string edad){
	int tamanio=edad.length();
	if(edad.empty()){
		return true;
	}
	if(tamanio>2){
		return true;
	}

	for(int i = 0; i<tamanio; i++){
		if(isalpha(edad[i])!= 0 || isspace(edad[i]) != 0 || ispunct(edad[i]) != 0){
			return true;
			break;
		}
	}
	int iedad = atoi(edad.c_str());
	if(iedad<=0 || iedad > 100){
		return true;
	}

return false;
}

bool validarOpcion(string nivel, string tipo){

	int tamanio=nivel.length();
	if(nivel.empty()){
		return true;
	}
	if(tamanio > 1){
		return true;
	}
		for(int i = 0; i<tamanio; i++){
		if(isalpha(nivel[i])!= 0 || isspace(nivel[i]) != 0 || ispunct(nivel[i]) != 0){
			return true;
			break;
		}
	}
	int inivel = atoi(nivel.c_str());
	if(tipo=="cargo"){
		if (inivel<1 || inivel > 3)
	{
		return true;
	}

	}else{
	if (inivel<1 || inivel > 5)
	{
		return true;
	}
	}
return false;
}

bool validarOpcion(string op, int cant){

	int tamanio=op.length();
	if(op.empty()){
		return true;
	}
	if(tamanio>2){
		return true;
	}

	for(int i = 0; i<tamanio; i++){
		if(isalpha(op[i])!= 0 || isspace(op[i]) != 0 || ispunct(op[i]) != 0){
			return true;
			break;
		}
	}
	int iop = atoi(op.c_str());
	
	if (iop-1<0 || iop-1> cant)
	{
		return true;
	}

return false;	
}

string validarRespuesta(string resp){

	int tamanio=resp.length();
	if(resp.empty()){
		return (" ");
	}
	if(tamanio>2){
		return (" ");
	}


	for(int i = 0; i<tamanio; i++){
		if(isdigit(resp[i])!= 0 || isspace(resp[i]) != 0 || ispunct(resp[i]) != 0){
			return (" ");
			break;
		}
	}

	for(int i=0;i<tamanio;i++){
	resp[i] = toupper(resp[i]);
	}

	if(resp=="S" || resp=="SI"){
		return ("S");
	}else if(resp == "N" || resp == "NO"){

		return("N");
	}
	return(" ");
}