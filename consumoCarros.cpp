#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int ingresarCarros(){
	int carros;
	do {
		cout << "Ingrese el numero de carros de 0 a 25: ";
		cin >> carros;
		
		if (carros < 0 || carros > 25) {
			cout << "Valor invalido. Intente nuevamente."<<endl;
		}
		
	} while (carros < 0 || carros > 25);
	
	return carros;
}

void registrarPlacas(string* placas, int carros){

	for (int i = 0; i < carros; i++) {
		cout<<"Dijite las placas: "<<endl;
		cin>>*(placas + i);
	}
}

void registrarkm(int* km, int carros){
	
	for(int i=0; i < carros; i++){
		cout<<"Dijite la cantidad de kilometros: "<<endl;
		cin>>*(km + i);
	}
}
	

void registarCombustibleCarros(vector<vector<int>> &tabla, int carros){
	
	int dias =7;
	
	string semana[7] = {
		"Lunes",
		"Martes",
		"Miercoles",
		"Jueves",
		"Viernes",
		"Sabado",
		"Domingo"
	};
	
	for (int i=0; i<carros; i++){
		cout<<"\nCarro #:"<<i+1<<endl;
		for(int j=0; j<dias; j++){
			cout<< "Dijite el consumo de combustible "<<semana[j]<<" : "<<endl;
			cin>> tabla[i][j];
		}
	}
}
	
void menu(){
	cout << "\n------ MENU ------\n";
	cout << "1. Mostrar informacion tabular\n";
	cout << "2. Consumo total por vehiculo\n";
	cout << "3. Sumatoria de kilometros\n";
	cout << "4. Consumo promedio semanal\n";
	cout << "5. Vehiculo con mayor consumo\n";
	cout << "0. Salir\n";
	cout << "Seleccione una opcion: ";
}
	
void imprimirTabla(string *placas, int *km, vector<vector<int>> &tabla, int carros, int dias){
	
	string semana[7] = {
		"Lunes",
		"Martes",
		"Miercoles",
		"Jueves",
		"Viernes",
		"Sabado",
		"Domingo"
	};
	
	cout << "\n====================== Informacion de vehiculos ======================\n\n";
	
	cout << left << setw(10) << "PLACAS"
		<< setw(18) << "Km Inicial";
	for(int i = 0; i < dias; i++)
		cout << setw(12) << semana[i];
	
	cout << endl;
	cout << string(10 + 18 + (dias * 12), '-') << endl;
	
	
	for(int i = 0; i < carros; i++) {
		cout << left << setw(10) << *(placas + i)
			<< setw(18) << *(km + i);
		for(int j = 0; j < dias; j++)
			cout << setw(12) << tabla[i][j];
			cout << endl;
	}
	cout << endl;
}
		
int consumoVehiculo(int *fila, int dias){
	
	int suma =0;
	for (int i = 0; i < dias; i++) {
		suma += *(fila +i); 
		
	}
	
	return suma;
	
}
	
int totalKm(int *km, int carros){
	int sumakm =0;
	for(int i=0; i<carros; i++){
		sumakm += *(km +i);
	}
	
	return sumakm;
}
	
float promedioTabla(vector<vector<int>> &tabla, int carros, int dias){
	float suma =0;
	float promedio;
	
	for (int i=0; i<carros; i++){
		for(int j=0; j<dias; j++){
			suma += tabla[i][j];
		}
	}
	
	promedio= suma/(carros*dias);
	
	return promedio;
}

int carroMayorConsumo( vector<vector<int>> &tabla, int carros, int dias){
		
	int maximo=0;
	int suma=0;
	int *sumatoria = new int[carros];
	
	for(int i=0; i<carros;i++){
		for(int j=0; j<dias; j++){
			suma += tabla[i][j];
		}
		sumatoria[i] = suma;
		suma=0;
	}
	
	for(int i=0; i<carros;i++){
		if(sumatoria[i] > maximo){
			maximo=sumatoria[i];
		}
	}
	delete[] sumatoria; 
	sumatoria = nullptr;
	
	return maximo;
	
}
		
int main(int argc, char *argv[]) {

	int carros=0;
	int dias=7;
	int opcion =0;
	int selecionarCarro =0;
	int consumoTotalVehiculo =0;
	int sumaTotalKm =0;
	float promedioGeneral=0;
	int mayorConsumo=0;

	carros=ingresarCarros();
	
	
	//arreglos dinamicos
	string* placas = new string[carros]; 
	int* km = new int[carros];
	vector<vector<int>> tablaCombustible(carros, vector<int>(dias));
	
	//Datos
	registrarPlacas(placas, carros);
	registrarkm(km, carros);	
	registarCombustibleCarros(tablaCombustible,carros);

	do{

		menu();
		cout<<"Dijite la opcion de su preferencia:"<<endl;
		cin>>opcion;
		
		switch(opcion){
			case 1:
				imprimirTabla(placas, km, tablaCombustible, carros, dias);

				break;
			case 2:
	
				cout<<"Dijite el carro en numero de fila para su consumo total"<<endl;
				cin>>selecionarCarro;
				consumoTotalVehiculo = consumoVehiculo(tablaCombustible[selecionarCarro -1].data(), dias);
				
				cout<<"El total del consumo por vehiculo"<<*(placas + (selecionarCarro - 1 ))<<" es: "<< consumoTotalVehiculo<<endl;

				break;
			case 3:
				
				sumaTotalKm=totalKm(km, carros);
				
				cout<<"La suma total de km es: "<<sumaTotalKm;
				
				break;
			case 4:
		
				promedioGeneral=promedioTabla(tablaCombustible,carros,dias);
		
				cout<<"El promedio general es de: "<<promedioGeneral; 
			
				break;
			case 5:
				mayorConsumo=carroMayorConsumo(tablaCombustible, carros, dias);
				
				cout<<"El mayor consumo es: "<<mayorConsumo;
				break;
				
			case 0:
				cout<<"Hasta luego :)";
				
				break;
			default:
				cout<<"Error debe dijitar las opciones que se encuentran en el menu";
				
				break;
			}
		
	} while(opcion != 0);
	
	
	delete[] placas; 
	delete[] km;
	placas = nullptr;
	km = nullptr;
	
	return 0;
}

