#include "archivos.h"
/*Codigo de las funciones*/
/*Esta funcion se encarga de crear todo los recibos de los trabajadores 
 * el formato usado para el nombre de los archivos es cedula-diamesaño.txt */
void crearReciboT(struct trabajador Trabajador, double PrimaP, double PrimaH, double PrimaHJ, double PrimaAD, double PrimaA, double DescuentoCA, double DescuentoSSO, double DescuentoFAOV, double DescuentoPIE, double TotalAsignaciones, double TotalDeducciones){
	ofstream oTarch;//Archivo de Recibo del Trabajador Escritura
	string nombreArch = Trabajador.CI;
	/*Aqui hace uso de las funcion to_string() esta funcion permite cualquier tipo de variable no string 
	 * en un flujo de tipo string, solo se puede usar compilandolo con el estandar C++11 o C++ 2011*/
	string fechaP = to_string(Trabajador.pago.dia) + to_string(Trabajador.pago.mes) + to_string(Trabajador.pago.anio);
	string home = "../txt/"+ nombreArch + "-" + fechaP + ".txt";
	struct tm * timeInfo;
	time_t rawtime;
	time(&rawtime);
	timeInfo = localtime(&rawtime);
	char AnioActual[80];
	strftime(AnioActual,80,"%Y",timeInfo);
	if(existeArchivo(home)){
		cout << "El recibo ya existe!!!" << endl;
	}
	else{
		oTarch.open(home, ios::out);
		if(oTarch){
			oTarch << setw(20) << "Recibo del Trabajador: " << Trabajador.CI << " Fecha: " << Trabajador.pago.dia << "/" << Trabajador.pago.mes << "/" << Trabajador.pago.anio << endl << endl;
			oTarch << "Cedula: "  << Trabajador.CI << endl;
			oTarch << "Nombre: " << Trabajador.nombre <<  setw(30) << "Apellido: " << Trabajador.apellido << endl;
			oTarch << "Cargo: " << Cargo[Trabajador.cargo-1] << setw(28) << "Nivel de instruccion: "<< NivelInst[Trabajador.nInst-1] << endl;
			oTarch << "Afiliado a caja de ahorro: " << Trabajador.AfCajaH << setw(30) << "Año de Ingreso: " << Trabajador.anioIngreso << endl;
			oTarch << "Sueldo Base: " << fixed << setprecision(2) << Trabajador.sueldoBase << endl << endl;
			oTarch << setw(20) << "Asignaciones" << endl << endl;
			oTarch << "Prima Por Profesionalizacion: " << fixed << setprecision(2) << PrimaP << endl;
			oTarch << "Prima Por Hogar: " << setprecision(2) << PrimaH << endl;
			oTarch << "Prima Por Hijos: " << setprecision(2) << PrimaHJ << endl;
			oTarch << "Prima por apoyo a la Actividad docente: " << setprecision(2) << PrimaAD << endl;
			oTarch << "Prima De Antiguedad: " << setprecision(2) << PrimaA << endl << endl;
			oTarch << setw(20) << "Deducciones" << endl << endl;
			oTarch << "Descuento por Caja de Ahorro: " << DescuentoCA << endl;
			oTarch << "Descuento por SSO: " << DescuentoSSO << endl;
			oTarch << "Descuento por FAOV: " << DescuentoFAOV << endl;
			oTarch << "Descuento por PIE: " << DescuentoPIE << endl<< endl;
			oTarch << setw(20) << "Totales" << endl << endl;
			oTarch << "Total de Asignaciones: " << setprecision(2) << TotalAsignaciones << endl;
			oTarch << "Total de Deducciones: " << setprecision(2) << TotalDeducciones << endl;
			oTarch << "Sueldo Neto: " << setprecision(2) << Trabajador.sueldoNeto << endl;
			oTarch.close();
			/*Aqui se deben llamar todas las funciones que necesiten modificar los archivos de nomina,IVSS,registros en el caso de que se agregue un nuevo recibo*/
			creaActualizaNomina(Trabajador.sueldoNeto, TotalDeducciones, Trabajador.pago.mes-1);
			creaActualizaRegistro("Registro", Trabajador.CI);
			creaActualizaRegistro(Trabajador.CI,nombreArch+"-"+fechaP);
			creaActualizaTotalIVSS(Trabajador.CI, TotalDeducciones, Trabajador.pago.mes-1);
			creaActualizaRegistro(Trabajador.CI+"2", Trabajador.CI+Meses[Trabajador.pago.mes-1]+AnioActual);
		}
	}
	
}

//Esta funcion solo verifica si el archivo existe
bool existeArchivo(string direccion){
	ifstream iArch;
	iArch.open(direccion, ios::in);
	if(iArch){
		iArch.close();
		return true;
	}
	return false;
}
/* Esta funcion crear o actualiza la nomina */
void creaActualizaNomina(double sueldoNeto, double TotalDeducciones, int mes){
	ofstream oNomina;
	string linea;
	int x = 0;
	int y = 0;
	int z = 0, conseguido = -1;
	int ilinea = 0;
	double deduccion = 0.00, asignacion = 0.00; 
	bool bandera = true, modificado = false;
	char linea2[256], valores[2][256];
	if(existeArchivo("../txt/Nomina.txt")){
		ifstream iNomina("../txt/Nomina.txt", ios::in);
		while(!iNomina.eof()){
			/*Este While recorre linea por linea el archivo,
			 * va recorriendo el archivo hasta que con la condicion if(linea.find(Meses[mes], 0) != -1)
			 * localiza y verifica que si el nuevo recibo es del mismo mes entonces el if se va a encargar de asignarle
			 * haciendo uso de la funcion strcpy al arreglo linea2 el contenido de linea que es la linea que acaba de obtenerse
			 * con la funcion getline, luego entre en un segundo while este se dentendra cuando consiga que linea2 es igual a NULL
			 * o '\0', en lo que entra en este while se hace uso de la funcion isdigit que verifica de que lo que se este 
			 * recorriendo sea igual a un numero o digito, si esto es cierto el verifica de que x sea menor a 2, si esto tambien lo es,
			 * comienza a asignarle al arreglo valores[] caracter por caracter el contenido de linea2,
			 * el segundo if linea2[y] == 32 && bandera == true, se encarga de verficar de si linea2[y] es igual al caracter de espacio,
			 * y de si bandera es igual a true, si es cierto incrementa x en uno y reinicia la variable y a 0 y bandera la actualiza a false,
			 * una vez que se cumple con todo se detiene el bucle while principal */
			getline(iNomina, linea);
			conseguido = linea.find(Meses[mes], 0);
			if(conseguido >= 0){
				strcpy(linea2, linea.c_str());
				while(linea2[y] != '\0'){
					if(isdigit(linea2[y]) != 0 || linea2[y] == '.'){
						if(x < 2){
							valores[x][z] = linea2[y];
							z++;
						}
					}
					if(linea2[y] == 32 && bandera == true){
						x++;
						z = 0;
						bandera = false;
					}
					y++;
				}
				modificado = true;
				break;
			}
			else{
				ilinea++;
				continue;
			}
		}
		iNomina.close();
		/*Este if se encarga de verificar si se produjo alguna modificacion haciendo uso de la variable modificado
		 * se encarga de crear un archivo auxiliar que es usado para llenarlo con la informacion del archivo Nomina.txt
		 * una vez que crea el archivo se hacen uso de la funcione atof() esta funcion permite convertir un arreglo de caracteres
		 * en un dato de tipo double, esto es necesario ya que lo que cacturamos en el arreglo bidimensional llamado valores 
		 * lo vamos a usar para hacer operaciones con el, una vez que se hace esto se procede a llenar el archivo pero con la condicion,
		 * de que modifique solo la linea que a sido actualizada, esto se hace ya que si el recibo que se esta llenando es del mismo el programa
		 * tendra que modificar esa linea en especifico sin destruir todo el contenido del archivo orginal, una vez que pasamos la informacion a este
		 * archivo auxiliar, se vuelve a abrir el archivo de nomina pero este vez borrando todos su contenido, hecho esto se procede a su escritura
		 * con la nueva informacion*/
		if(modificado == true){
			ofstream oAuxArch;
			oAuxArch.open("../txt/Respaldo.txt", ios::out);
			asignacion = atof(valores[0]);
			deduccion = atof(valores[1]);
			sueldoNeto += asignacion;
			TotalDeducciones += deduccion;
			iNomina.open("../txt/Nomina.txt");
			while(!iNomina.eof()){
				getline(iNomina, linea);
				conseguido = linea.find(Meses[mes], 0);
				if(conseguido >= 0)
					oAuxArch << fixed << setprecision(2) << sueldoNeto << setprecision(2) << setw(20) << TotalDeducciones << setw(20) << Meses[mes] << endl;
				else
					oAuxArch << linea << endl;
			}
			oAuxArch.close();
			iNomina.close();
			ifstream iAuxArch;
			iAuxArch.open("../txt/Respaldo.txt", ios::in);
			oNomina.open("../txt/Nomina.txt", ios::out);
			while(!iAuxArch.eof()){
				getline(iAuxArch,linea);
				oNomina << linea << endl;
			}
			oNomina.close();
			iAuxArch.close();
			remove("../txt/Respaldo.txt");
		}else{
			/*En el caso de que no ocurra lo anterior solo se procede a escribir el archivo desde el final*/
			oNomina.open("../txt/Nomina.txt",ios::app);
			oNomina << fixed  << setprecision(2) << sueldoNeto << setprecision(2) << setw(20) << TotalDeducciones << setw(10) << Meses[mes] << endl;
			oNomina.close();
		}
		iNomina.close();
	}
	else{
		oNomina.open("../txt/Nomina.txt", ios::out);
		oNomina << setw(25) << "Nomina" << endl;
		oNomina << "Total Asignaciones" << setw(20) << "Total Deducciones" << setw(15) << "Mes" << endl;
		oNomina << fixed << setprecision(2) << sueldoNeto << setprecision(4) << setw(20) << TotalDeducciones << setw(20) << Meses[mes] << endl;
	}
}
/*Actualiza o crear el archivo registro.txt el cual va a contener todos los numeros de cedulas
 *que se van registrando a medida que se agrega un nuevo empleado */ 
void creaActualizaRegistro(string Direccion, string nombReg){
	ofstream oRegistro;
	Direccion = "../txt/"+Direccion+".txt";
	if(existeArchivo(Direccion))
		oRegistro.open(Direccion, ios::app);
	else
		oRegistro.open(Direccion, ios::out);
	if(oRegistro){
		oRegistro << nombReg << endl;
		oRegistro.close();
	}
	else
		cout << "Error al abrir el archivo" << endl;
}
/*Verifica si para ese numero de cedula existe un archivo con el mismo numero de cedula*/
bool existeTrabajador(string Registro, string cedula){
	ifstream iRegistro;
	string linea;
	Registro = "../txt/"+Registro+".txt";
	bool existe = false;
	if(existeArchivo(Registro)){
		iRegistro.open(Registro, ios::in);
		while(!iRegistro.eof()){
			getline(iRegistro, linea);
			if(linea == cedula){
				existe = true;
				break;
			}
		}
	}
	return existe;
}
/*Esta funcion permite extraer el numero de cedula que se encuentra registrado en el archivo registro.txt,
 * devuelve el numero de cedula una vez que verifica de que existe en el archivo registro*/
string extraeCedula(string Registro, string cedula){
	string Archivo = "../txt/"+Registro+".txt";
	ifstream iArch;
	string linea;
	if(existeArchivo(Archivo)){
		iArch.open(Archivo);
		if(existeTrabajador("Registro", cedula)){
			while(!iArch.eof()){
				getline(iArch, linea);
				if(linea == cedula)
					break;
				else
					linea = "";
			}
		}
		iArch.close();
	}
	return linea;
}
/*Extrae el nombre de un recibo*/
string extraeRecibo(string cedula, string nRecibo){
	string linea,Recibo;
	linea = " ";
	Recibo = "../txt/"+cedula+".txt";
	int conseguido = -1;
	if(existeArchivo(Recibo)){
		ifstream Recibos(Recibo, ios::in);
		while(!Recibos.eof()){
			getline(Recibos,linea);
			conseguido = linea.find(nRecibo,0);
			if(conseguido >= 0)
				break;
			else
				linea = " ";
		}

	}
	return linea;
}
/*Crea el archivo que indica el total pagado al IVSS por trabajador*/
void creaActualizaTotalIVSS(string cedula, double totalDeducciones, int mes){
	ofstream IVSS;
	string nombreArch = "../txt/IVSS.txt";
	if(existeArchivo(nombreArch)){
		IVSS.open(nombreArch, ios::app);
		IVSS << cedula << setw(20) << fixed  << setprecision(2) << totalDeducciones << setw(20) << Meses[mes] << endl;
		IVSS.close();
	}
	else{
		IVSS.open(nombreArch, ios::out);
		IVSS << setw(30) << "Total Pagado al IVSS" << endl << endl;
		IVSS << "Trabajador" << setw(20) << "Total Pagado" << setw(15) << "MES" << endl;
		IVSS << cedula << setw(20) << fixed << setprecision(2) <<  totalDeducciones << setw(20) << Meses[mes] << endl; 
		IVSS.close();
	}
}
/*Funcion que lee los archivos*/
void LeeArchivo(string Direccion){
	ifstream iArch;
	iArch.open(Direccion, ios::in);
	string linea;
	if(iArch){
		while(!iArch.eof()){
			getline(iArch, linea);
			if(!linea.empty())
				cout << linea << endl;
		}
	}else
		cout << "Error al abrir el archivo" << endl;
}
/*Elimina un archivo*/
void eliminarArchivo(string Direccion){
	if(existeArchivo(Direccion)){
		remove(Direccion.c_str());
	}else{
		cout << "El registro no existe!!!" << endl;
	}
}
/*Elimina un registro ya almacenado en el archivo de registro que posee cada trabajador, la funcion
 * se encarga de localizar el registro a borrar y actualiza el archivo del trabajador creando un archivo temporal
 * y borrando el archivo original, luego escribe en el archivo original ya borrado todo su contenido excepto el registro ya eliminado
 * esta funcion es llamada por la funcion eliminarRecibo de menu*/
void borraRegistro(string archivo, string nRecibo){
	ifstream iArchivo;
	ofstream oAuxArch;
	string linea;
	iArchivo.open(archivo, ios::in);
	oAuxArch.open("../txt/Respaldo.txt", ios::out);
	int conseguido = -1;
	while(!iArchivo.eof()){
		getline(iArchivo, linea);
		conseguido = linea.find(nRecibo, 0);
		if(conseguido >= 0){
			continue;
		}else{
			oAuxArch << linea << endl;
		}
	}
	iArchivo.close();
	oAuxArch.close();
	ifstream Respaldo;
	Respaldo.open("../txt/Respaldo.txt", ios::in);
	ofstream oArchivo;
	oArchivo.open(archivo, ios::out);
	while(!Respaldo.eof()){
		getline(Respaldo, linea);
		oArchivo << linea << endl;
	}
	Respaldo.close();
	oArchivo.close();
	remove("../txt/Respaldo.txt");
}
