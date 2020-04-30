#include "constantes.h"
#include "menu.h"

int main(){
	char op;
	do{
		menu(&op);CLS;
		switch(op){
			case '1':
				crearRecibo();
			break;
			case '2':
				mostrarRecibo();
			break;
			case '3':
				eliminarRecibo();
			break;
			case '4':
				mostrarNomina();
			break;
			case '5':
				totalCobrado();
			break;
			case '6':
				totalDeduccionesT();
			break;
			case '7':
				cout << "HASTA LUEGO..." << endl;
			break;
			default:
				cout << "OPCION INCORRECTA! " << endl;
		}
	}while(op != '7');
	return 0;
}
