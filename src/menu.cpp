#include "menu.h"
#include "archivos.h"
#include "validaciones.h"
#include "asignaciones.h"
#include "deducciones.h"
#include "cola.h"
/*Funcion Menu*/
char menu(char *op){
	cout << setw(50) << "SISTEMA ADMINISTRATIVO UNEFA" << endl<<endl;
	cout << setw(10) << "1.- CREAR RECIBO" << endl<<endl;
	cout << setw(10) << "2.- MOSTRAR UN RECIBO" << endl<<endl;
	cout << setw(10) << "3.- ELIMINAR RECIBO" << endl<<endl;
	cout << setw(10) << "4.- MOSTRAR NOMINA" << endl<<endl;
	cout << setw(10) << "5.- MOSTRAR TOTAL COBRADO POR TRABAJADOR" << endl<<endl;
	cout << setw(10) << "6.- MOSTRAR TOTAL DEBITADO POR TRABAJADOR" << endl<<endl;
	cout << setw(10) << "7.- SALIR" << endl<<endl;
	cout << setw(10) << "Introduzca una opcion:";
	cin >> *op;
	return *op;
	CLS
}
/*Esta funcion se encarga de mostrar los recibos haciendo uso del archivo registro.txt 
 *lee este archivo y extrae todos los recibos que tenga el trabajador ya creado, en el caso contrario
 * muestra el mensaje de error, hace uso de las funciones archivos.
 * La funcion crea un submenu que muestra todos los recibos que estan contenidos en el archivo de registro de cada
 * trabajador luego con un ciclo for llena un arreglo que permite ir listando todos los nombres de los recibos que fueron creados
 * por la funcion crearRecibo */
void mostrarRecibo(){
	CLS
	string cedula;
	string linea, regs[300];
	int cant = 0, conseguido = -1;
	cin.ignore();
	if(existeArchivo("../txt/Registro.txt")){
		cout << "Introduzca la cedula del trabajador: ";
		getline(cin,cedula);
		CLS
		while(validarCadena(cedula) || !existeTrabajador("Registro",cedula)){
			cout << "Error cedula incorrecta" << endl;
			cout << "Introduzca la cedula del trabajador: ";
			getline(cin,cedula);
			CLS
		}
		string registro = "../txt/"+cedula+".txt";
		ifstream iRegistros;
		iRegistros.open(registro, ios::in);
		/*Este ciclo obtiene los recibos y los agrega al arreglo*/
		while(!iRegistros.eof()){
			getline(iRegistros,linea);
			conseguido = linea.find(cedula,0);
			if(conseguido >= 0){
				regs[cant] = linea;
				cant++;
			}
		}
		if(iRegistros.eof()){
			regs[cant] = "Salir";
		}
		CLS
		if(cant == 0){
			cout << "Este trabajador no tiene recibos guardados" << endl << endl << endl;
			return;
		}else{
			CLS
			/*Este ciclo muestra todos los registros que ya estan registrados*/
			cout << setw(30) << "RECIBOS DEL TRABAJADOR: " << cedula << endl;
			for(int i = 0; i <= cant; i++){
				cout << setw(10) << i+1 << "." << regs[i] << endl;
			}
			int iop;
			string op;
			cout << "Introduzca una opcion:";
			getline(cin,op);
			cin.ignore();
			
			while(validarOpcion(op, cant)){
				cout << "Opcion Incorrecta" << endl;
				cout << "Introduzca una opcion:";
				getline(cin,op);
				cin.ignore();

			}
			iop=atoi(op.c_str());
			if(iop-1 == cant)
				return;
			for(int i = 0; i < cant; i++){
				if(i == iop-1)
					break;
			}
			string resp;
			
			do{
			CLS
			LeeArchivo("../txt/"+regs[iop-1]+".txt");
			
			cout << "VOLVER (S/N): "<<endl;
			getline(cin,resp);
			resp=validarRespuesta(resp);
			while(resp!="S" && resp!="N"){
				cout <<"Error"<<endl;
				cout <<"VOLVER (S/N): "<<endl;
				getline(cin,resp);
			resp=validarRespuesta(resp);
			}
			}while(resp=="N");

	}CLS


	}else{
		cout << "Aun no ha registrado recibos!!!" << endl;
		cout<<endl<<endl;
	}
}
/*Esta funcion se encarga de buscar el recibo de cada trabajador pero en este caso se encarga de eliminarlo,
 * al igual que la funcion mostrarRecibo, busca en el archivo de registro de cada trabajador el nombre del recibo
 * y crea un submenu con todos los nombres de los recibos existentes*/
void eliminarRecibo(){
	CLS
	string cedula;
	string linea, regs[300];
	cin.ignore();
	int cant = 0, conseguido = -1;
	if(existeArchivo("../txt/Registro.txt")){
		cout << "Introduzca la cedula del trabajador: "<<endl;
		getline(cin,cedula);
		while(validarCadena(cedula) || !existeTrabajador("Registro",cedula)){
			cout << "Error cedula incorrecta" << endl;
			cout << "Introduzca la cedula del trabajador: ";
			getline(cin,cedula);
		}
		string registro = "../txt/"+cedula+".txt";
		ifstream iRegistros;
		iRegistros.open(registro, ios::in);
		while(!iRegistros.eof()){
			getline(iRegistros,linea);
			conseguido = linea.find(cedula,0);
			if(conseguido >= 0){
				regs[cant] = linea;
				cant++;
			}
		}
		if(iRegistros.eof()){
			regs[cant] = "Eliminar Todos";
			cant++;
			regs[cant] = "Salir";
		}
		CLS
		if(cant == 1){
			cout << "Este trabajador no tiene recibos guardados" << endl << endl << endl;
			return;
		}
		else{
			/*Este ciclo muestra los recibos*/
			cout << setw(30) << "RECIBOS DEL TRABAJADOR " << cedula << endl;
			for(int i = 0; i <= cant; i++){
				cout << setw(10) << i+1 << ".- " << regs[i] << endl;
			}
			string op;
			int iop;
			cout<<endl;
			cout << "Introduzca una opcion:";
			getline(cin, op);
			cin.ignore();
			while(validarOpcion(op, cant)){
				cout << "Opcion Incorrecta" << endl;
				cout << "Introduzca una opcion:";
				getline(cin, op);
				cin.ignore();
			}
			iop = atoi(op.c_str());
			CLS
			/*Verifica que opcion fue elegida y en el caso de destruir uno o todos los registros 
			 * advierte */
			if(iop-1 == cant)
				return;
			else if(iop-1 == cant-1){
				string resp;
				cout << "Desea realizar esta accion? (S/N)";
				getline(cin,resp);
				resp = validarRespuesta(resp);
				while(resp != "S" && resp != "N"){
					cout << "Opcion Incorrecta !! " << endl;
					cout << "Desea realizar esta accion? (S/N)";
					getline(cin,resp);
					resp = validarRespuesta(resp);
				}
				if(resp == "S"){
					cout << "Eliminado todos los Recibos!!!"<< endl;
					for(int y = 0; y < cant-1; y++){
						if(y != cant){
							eliminarArchivo("../txt/"+regs[y]+".txt");
							borraRegistro("../txt/"+cedula+".txt", regs[y]);
						}
					}
					eliminarArchivo("../txt/"+cedula+"2"+".txt");
					cout << "Registros eliminados!!!" << endl << endl << endl;
					return;
				}else{
					cout << "Accion Cancelada..." << endl << endl << endl;
					return;
				}
			}else{
				string resp;
				for(int i = 0; i < cant; i++){
						if(i == iop-1){
						cout << "Desea realizar esta accion? (S/N): ";
						getline(cin,resp);
						resp = validarRespuesta(resp);
						while(resp != "S" && resp != "N"){
							cout << "Opcion Incorrecta !! " << endl;
							cout << "Desea realizar esta accion? (S/N)";
							getline(cin,resp);
							resp = validarRespuesta(resp);
						}
						if(resp == "S"){
							eliminarArchivo("../txt/"+regs[iop-1]+".txt");
							borraRegistro("../txt/"+cedula+".txt", regs[iop-1]); 
							cout << "Registro eliminado!!!" << endl << endl << endl;
							return;
						}else{
							cout << "Accion Cancelada..." << endl << endl << endl;
							return;
						}
					}
				}
			}
		}
	}else{
		cout << "Aun no ha registrados recibos!!" << endl;
	}
cout<<endl<<endl<<endl;
}
/*Esta funcion solo muestra la nomina */
void mostrarNomina(){
	CLS
	string resp3;
			
	if(existeArchivo("../txt/Nomina.txt")){
		cin.ignore();
		do{
		CLS

			LeeArchivo("../txt/Nomina.txt");
			cout<<endl<<endl;
			cout << "VOLVER (S/N): "<<endl;
			getline(cin,resp3);
			resp3=validarRespuesta(resp3);
			while(resp3!="S" && resp3!="N"){
				cout <<"Error!"<<endl;
				cout <<"VOLVER (S/N): "<<endl;
				getline(cin,resp3);
			    resp3=validarRespuesta(resp3);
			}cin.ignore();
			}while(resp3=="N");
	CLS
	}else{
		cout << "Aun no ha registrado un trabajador" << endl;
	}
}
/*Esta funcion muestra el total de deducciones que ha tenido cada trabajador por mes*/
void totalDeduccionesT(){
	CLS
	string resp3;
	if(existeArchivo("../txt/IVSS.txt")){
		cin.ignore();
		do{
		CLS

			LeeArchivo("../txt/IVSS.txt");
			cout<<endl<<endl;
			cout << "VOLVER (S/N): "<<endl;
			getline(cin,resp3);
			resp3=validarRespuesta(resp3);
			while(resp3!="S" && resp3!="N"){
				cout <<"Error!"<<endl;
				cout <<"VOLVER (S/N): "<<endl;
				getline(cin,resp3);
			    resp3=validarRespuesta(resp3);
			}cin.ignore();
			}while(resp3=="N");
	CLS
	}else{
		cout << "*Aun no ha registrado un trabajador*" << endl;
	}
}
/*Crea y registra un recibo nuevo de cada trabajador verifica de que este recibo exista  y de que no se genere mas de un recibo por trabajador en un mismo mes*/
void crearRecibo(){
	CLS
	string nRecibo, nRegistro;
	double PrimaHiJ, DescuentoCA, TotalDeducciones = 0.00, TotalAsignaciones = 0.00, PrimaPAD, PrimaH, PrimaA, PrimaProF,DescuentoSSO, DescuentoFAOV,DescuentoPIE;
	string resp;
	struct trabajador Trabajador;
	struct cola c;
	c.primero = NULL;
	c.ultimo = NULL;
	struct tm * timeInfo;
	time_t rawtime;
	time(&rawtime);
	timeInfo = localtime(&rawtime);
	char AnioActual[80];
	strftime(AnioActual,80,"%Y",timeInfo);
	do{
		do{
			/*Verifca de que la cedula exista y de que se introdujo correctamente, tambien se encarga de verficar la fecha*/
			cin.ignore();
			cout << "Introduzca la cedula del Trabajador: ";
			getline(cin,Trabajador.CI);
			cin.ignore();
			while(validarCadena(Trabajador.CI)){
				cout << "Error Cedula Incorrecta" << endl;
				cout << "Introduzca la cedula del Trabajador: ";
				getline(cin,Trabajador.CI);
				cin.ignore();

			}
			string cauxDia, cauxMes, cauxAnio;
			cout<<endl<<endl;
			cout << "Intrduzca la fecha de Pago" << endl;
			cout << "Intrdoduzca el dia:";
			getline(cin,cauxDia);
			cin.ignore();
			cout<<endl;
			cout << "Introduzca el mes:";
			getline(cin,cauxMes);
			cin.ignore();
			cout<<endl;
			cout << "Introduzca el año:";
			getline(cin,cauxAnio);
			cin.ignore();
			cout<<endl<<endl;
			while(validarFecha(cauxDia, cauxMes, cauxAnio)){
				cout<<endl<<endl;
				cout << "Fecha Incorrecta!!!" << endl;
				cout << "Intrdoduzca el dia:";
				getline(cin,cauxDia);
				cin.ignore();
				cout<<endl;
				cout << "Introduzca el mes:";
				getline(cin,cauxMes);
				cin.ignore();
				cout<<endl;
				cout << "Introduzca el año:";
				getline(cin,cauxAnio);
				cout<<endl;
				cin.ignore();
			}
			Trabajador.pago.dia = atoi(cauxDia.c_str());
			Trabajador.pago.mes = atoi(cauxMes.c_str());
			Trabajador.pago.anio = atoi(cauxAnio.c_str());
			nRecibo = "../txt/"+Trabajador.CI+"-"+to_string(Trabajador.pago.dia)+to_string(Trabajador.pago.mes)+to_string(Trabajador.pago.anio)+".txt";
			nRegistro = extraeRecibo(Trabajador.CI+"2", Trabajador.CI+Meses[Trabajador.pago.mes-1]+AnioActual);
			if(existeArchivo(nRecibo))
				cout << "Error Ya existe un recibo con ese numero de cedula y mes!!" << endl;
			else if(nRegistro == Trabajador.CI+Meses[Trabajador.pago.mes-1]+AnioActual)
				cout << "Error Ya el trabajador tiene un recibo de pago en el mes de " << Meses[Trabajador.pago.mes-1] << endl;
				cout<<endl;
		}while(existeArchivo(nRecibo) || nRegistro != " ");
		cout << "Intrdoduzca su nombre: ";
		getline(cin, Trabajador.nombre);
		cout<<endl;
		while(validarNombreApellido(Trabajador.nombre)){
			cout << "Nombre Incorrecto!!!" << endl;
			cout << "Intrdoduzca su nombre:";
			getline(cin,Trabajador.nombre);
			cout<<endl;
		}
		cin.ignore();
		Trabajador.nombre = convertirPM(Trabajador.nombre);
		cout << "Introduzca su apellido: ";
		getline(cin, Trabajador.apellido);
		cout<<endl;
		while(validarNombreApellido(Trabajador.apellido)){
			cout << "Apellido Incorrecto!!!" << endl;
			cout << "Intrdoduzca su apellido:";
			getline(cin,Trabajador.apellido);
			cout<<endl;
		}
		cin.ignore();
		string cargo;
		CLS
		Trabajador.apellido = convertirPM(Trabajador.apellido);
		cout << "INTRODUZCA SU CARGO" << endl;
		cout<<endl;
		cout << "1.- PERSONAL ADMINISTRATIVO" << endl<<endl;
		cout << "2.- PERSONAL DOCENTE" << endl<<endl;
		cout << "3.- PERSONAL OBRERO" << endl<<endl;
		cout << "Introduzca una de las opciones:";
		getline(cin,cargo);

		while(validarOpcion(cargo, "cargo")){
			cout << "Error!!" << endl;
			cout << "Introduzca una de las opciones:";
			getline(cin,cargo);
		}
		CLS
		Trabajador.cargo = atoi(cargo.c_str());
		string nivel;
		cout << "INTRODUZCA SU NIVEL DE INSRUCCION" << endl<<endl;
		cout << "1.- BACHILLER" << endl<<endl;
		cout << "2.- TSU" << endl<<endl;
		cout << "3.- INGENIERO" << endl<<endl;
		cout << "4.- MAGISTER" << endl<<endl;
		cout << "5.- DOCTOR" << endl<<endl;
		cout << "Introduzca una de las opciones:";
		getline(cin,nivel);
		while(validarOpcion(nivel, "nivel")){
			cout << "Error!!" << endl;
			cout << "Introduzca una de las opciones:";
			getline(cin,nivel);
		}
		Trabajador.nInst = atoi(nivel.c_str());
		cin.ignore();
		CLS
		string resp2;
		string canth;
		int aux;
		cout<<endl<<endl;
		cout << "POSEE HIJOS? (S/N): ";
		getline(cin,resp2);

		resp2 = validarRespuesta(resp2);
		while(resp2 != "S" && resp2 != "N"){
			cout << "Opcion Incorrecta!!" << endl;
			cout << "POSEE HIJOS? (S/N): ";
			getline(cin,resp2);

			resp2 = validarRespuesta(resp2);
			cin.ignore();
		}
		if(resp2 == "S"){
			cout<<endl<<endl;
			cout << "Introduzca la cantidad de hijos que posee: ";
			getline(cin,canth);
			cin.ignore();
			
			while(validarNumero(canth)){
				cout << "Debe introducir un numero!!" << endl;
				cout << "Introduzca la cantidad de hijos que posee: ";
				getline(cin,canth);
				cin.ignore();
			}
			Trabajador.CantH = atoi(canth.c_str());
			aux = 0;
			string edad;
			Trabajador.edadH = new int(Trabajador.CantH);
			for(int i = 0; i < Trabajador.CantH; i++){
				cout << "Introduzca la edad de su hijo n° "  << i+1 << " :";
				getline(cin,edad);
				cin.ignore();
				while(validarEdad(edad)){
					cout << "Error la edad no puede ser menor o igual a cero" << endl;
					cout << "Introduzca la edad de su hijo n° "  << i+1 << " :";
					getline(cin,edad);
					cin.ignore();
					}

				Trabajador.edadH[i] = atoi(edad.c_str());

			}
			PrimaHiJ = Calcula_PrimaHij(Trabajador.CantH, Trabajador.edadH);
		}else{
			Trabajador.CantH = 0;
			PrimaHiJ = 0;
		}
		cin.ignore();
		string auxcaja;
		cout<<endl;
		cout << "Posee Afifiliacion en caja de ahorro(S/N): ";
		getline(cin,auxcaja);

		auxcaja = validarRespuesta(auxcaja);
		while(auxcaja != "S" && auxcaja != "N"){
			cout << "Error! Introduzca (S/N):";
			getline(cin,auxcaja);

			auxcaja = validarRespuesta(auxcaja);
		}
		Trabajador.AfCajaH =  auxcaja[0];
		string auxAnio;
		cin.ignore();
		cout<<endl;
		cout << "Introduzca el año de ingreso a la institucion: ";
		getline(cin,auxAnio);
		cin.ignore();
		while( validarAnio(auxAnio)){
			cout << "Error en la fecha de ingreso!!" << endl;
			cout << "Introduzca el año de ingreso a la institucion:";
			getline(cin,auxAnio);
			cin.ignore();
		}
		Trabajador.anioIngreso = atoi(auxAnio.c_str());
		string auxSueldo;
		cin.ignore();
		cout<<endl;
		cout << "Introduzca el sueldo base: ";
		getline(cin,auxSueldo);
		cin.ignore();
		if(Trabajador.cargo == 1 && validarSueldo(auxSueldo) < ADMIN){
			while(validarSueldo(auxSueldo) == 0.00 || validarSueldo(auxSueldo) < ADMIN){
				cout << "Error!" << endl;
				cout << "Introduzca el sueldo base: ";
				getline(cin,auxSueldo);
				cin.ignore();
			}
		}else if(Trabajador.cargo == 2 && validarSueldo(auxSueldo) < DOCENTES){
			while(validarSueldo(auxSueldo) == 0.00 || validarSueldo(auxSueldo) < DOCENTES){
				cout << "Error!" << endl;
				cout << "Introduzca el sueldo base: ";
				getline(cin,auxSueldo);
				cin.ignore();	
			}
		}else{
			if(Trabajador.cargo == 3 && validarSueldo(auxSueldo) < OB){
					while(validarSueldo(auxSueldo) == 0.00 || validarSueldo(auxSueldo) < OB){
					cout << "Error!" << endl;
					cout << "Introduzca el sueldo base: ";
					getline(cin,auxSueldo);
					cin.ignore();
				}
			}
		}

		Trabajador.sueldoBase = validarSueldo(auxSueldo);
		PrimaH = Calcula_PrimaHog();
		if(Trabajador.cargo == 2)
			PrimaPAD = Calcula_ActiDocen();
		else
			PrimaPAD = 0;
		/*Calcula las asignaciones y deducciones, encola y crea los archivos correspondientes de cada trabajador*/
		PrimaProF = Calcula_PrimaProf(Trabajador.nInst, Trabajador.sueldoBase);
		PrimaA = Calcula_PrimaAnti(Trabajador.anioIngreso, Trabajador.sueldoBase);
		DescuentoCA = Calcula_DescuentoCA(Trabajador.AfCajaH,Trabajador.sueldoBase);
		DescuentoFAOV = Calcula_FAOV(Trabajador.sueldoBase);
		DescuentoSSO = Calcula_SSO(Trabajador.sueldoBase);
		DescuentoPIE = Calcula_PIE(Trabajador.sueldoBase);
		TotalAsignaciones = PrimaA + PrimaProF + PrimaPAD + PrimaH + PrimaHiJ;
		TotalDeducciones = DescuentoCA + DescuentoFAOV + DescuentoPIE + DescuentoSSO;
		Trabajador.sueldoNeto = Trabajador.sueldoBase + TotalAsignaciones - TotalDeducciones;
		crearReciboT(Trabajador,PrimaProF, PrimaH, PrimaHiJ, PrimaPAD, PrimaA, DescuentoCA, DescuentoSSO, DescuentoFAOV, DescuentoPIE, TotalAsignaciones, TotalDeducciones);
		encolar(c,Trabajador.CI, Trabajador.sueldoNeto, Trabajador.pago.mes-1);
		cin.ignore();
		cout << "Desea Crear Otro recibo?(S/N):";
		getline(cin,resp);
		resp = validarRespuesta(resp);
		while(resp != "S" && resp != "N"){
			cout << "Error! Solo (S/N):";
			getline(cin,resp);
			resp = validarRespuesta(resp);
		}
		cin.ignore();
	}while(resp != "N");
	crearFifo(c);
}
/*Muestra el total cobrado por cada trabajador por mes*/
void totalCobrado(){
	CLS
	string resp3;
	if(existeArchivo("../txt/FIFO.txt")){
		cin.ignore();
		do{
		CLS

			LeeArchivo("../txt/FIFO.txt");
			cout<<endl<<endl;
			cout << "VOLVER (S/N): "<<endl;
			getline(cin,resp3);
			resp3=validarRespuesta(resp3);
			while(resp3!="S" && resp3!="N"){
				cout <<"Error!"<<endl;
				cout <<"VOLVER (S/N): "<<endl;
				getline(cin,resp3);
			    resp3=validarRespuesta(resp3);
			}cin.ignore();
			}while(resp3=="N");
	CLS
	}else{
		cout << "NO SE ENCUENTRA NINGUN TRABAJADOR REGISTRADO..." << endl;
	}
}
