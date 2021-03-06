/*LABORAT�RIO DE SISTEMAS OPERATIVOS - PARTE 2 DO PROJETO DE PROG 2016/2017 */
//Gon�alo Nuno Bernardo e Joana Sofia Ramos


#include <iostream> // I/O reasoning
#include <vector> //For use of vectors
#include <string> //For use of strings
#include <fstream> //Manipulation of files
#include <limits> //Invalid inputs
#include <iomanip> //setfill, setw, ...

//ADTs and their matching headers
#include "Bus.h" 
#include "Shift.h"
#include "Company.h"
#include "Driver.h"
#include "Line.h"

using namespace std;

//PROTOTYPING
void MenuPrincipal();
void InvalidInputMenu();
void InvalidInputFile();
void ErrorErrorError(int &i);
void ErrorErrorError(unsigned int &i); //overloading of the function ErrorErrorError
void SaveFileMenu();
void ScheduleStops();
void ScheduleLines();
void LineManagment();
void DriverManagment();
void AddDriver();
void RemoveDriver();
void ChangeDriverMenu();
void SeeExistingLines();
void SeeExistingStops();
void SeeExistingDrivers();
void LinesStops();
void ROUTES();
void DriversShifts();
void BusMenu();
void nrBusCalculation();
//void BusesDistribution();
//void BusWithNoDriver();
void streamsLinesDrivers();
void SaveFileLines();
void SaveFileDrivers();
int RetIDDrivers(unsigned int id);
int RetIDLines(unsigned int id);
int CheckIDLines(unsigned int id);
int CheckIDDrivers(unsigned int id);
int Commas(string stringe);
unsigned int hrs2min(unsigned int &mins);

//VECTORS
vector <Driver> Drivers;
vector <Line> Lines;

//FILES
void SaveFileDrivers() {
	string FicheiroCondutor;
	"========================================================================================================\n";
	cout << "Insira o nome do ficheiro de condutores que pretende gravar: \n";
	cin >> FicheiroCondutor;

	ofstream FicheiroCondutores;

	FicheiroCondutores.open(FicheiroCondutor);

	for (unsigned int i = 0; i < Drivers.size(); i++)
	{
		FicheiroCondutores << Drivers.at(i).getId() << " ; " << Drivers.at(i).getName() << " ; " << Drivers.at(i).getShiftMaxDuration() << " ; " << Drivers.at(i).getMaxWeekWorkingTime() << " ; " << Drivers.at(i).getMinRestTime() << endl;
	}
	FicheiroCondutores.close();
	cout << "\n\nFicheiro gravado! Retornando ao Menu Principal...\n";
	"=======================================================================================================\n\n";
	MenuPrincipal();
}
void SaveFileLines() {
	string FicheiroLinha;
	"========================================================================================================\n";
	cout << "Insira o nome do ficheiro de linhas que pretende gravar: \n";
	cin >> FicheiroLinha;

	ofstream FicheiroLinhas;

	FicheiroLinhas.open(FicheiroLinha);

	for (unsigned int i = 0; i < Lines.size(); i++)
	{
		FicheiroLinhas << Lines.at(i).getId() << " ; " << Lines.at(i).getFreq() << " ; ";
		for (unsigned int j = 0; j < Lines.at(i).getBusStops().size(); j++)
		{
			if (j == Lines.at(i).getBusStops().size() - 1)
			{
				FicheiroLinhas << Lines.at(i).getBusStops().at(j) << "; ";
			}
			else {
				FicheiroLinhas << Lines.at(i).getBusStops().at(j) << ", ";
			}
		}
		for (unsigned int k = 0; k < Lines.at(i).getTimings().size(); k++)
		{
			if (k == Lines.at(i).getTimings().size() - 1)
			{
				FicheiroLinhas << Lines.at(i).getTimings().at(k) << "";
			}

			else {
				FicheiroLinhas << Lines.at(i).getTimings().at(k) << ", ";
			}

		}
		FicheiroLinhas << endl;
	}
	FicheiroLinhas.close();
	cout << "\n\nFicheiro gravado! Retornando ao Menu Principal...\n";
	"========================================================================================================\n\n";
	MenuPrincipal();
}

//FUNCTIONS THAT RECEIVE INFORMATION GIVEN BY THE USER THROUGH HIS INPUT(LINES & DRIVERS)
void streamsLinesDrivers() {
	//temporary vector, that will read the information of the pretended file and deposit all in the form of a string
	vector<string> input;
	cin.clear();
	input.clear();
	cout << "========================================================================================================";
	cout << "\n  Bem - Vindo ao programa Escalonamento de Condutores, da Empresa de Transportes Semprarrolar.\n";
	cout << "   ___ ___ __ __ ___ ___ ___ ___ ___ ___ _   ___ ___ " << endl;
	cout << "  / __| __|  \\  | . | . | . | . | . | . | | | . | . \\   TM" << endl;
	cout << "  \\__ | _>|     |  _|   |   |   |   | | | |_|   |   /" << endl;
	cout << "  <___|___|_|_|_|_| |_\\_|_|_|_\\_|_\\_`___|___|_|_|_\\_\\ " << endl;
	cout << "========================================================================================================\n\n";

	//Drivers file

	string name_f1, lined;
	ifstream drivers_f;

	cout << "Introduza o nome do ficheiro de condutores: ";
	cin >> name_f1;
	drivers_f.open(name_f1);

	while (drivers_f.fail())
	{
		cout << "ERRO: nao abriu o ficheiro de condutores" << endl;
		cout << "Introduza de novo o ficheiro de condutores: ";
		cin >> name_f1;
		drivers_f.open(name_f1);
	}

	while (!drivers_f.eof())
	{
		getline(drivers_f, lined);
		Driver driver1(lined);
		Drivers.push_back(driver1);
	}

	drivers_f.close();


	//Lines Files
	string name_f;
	string linel;
	ifstream lines_f;

	cout << "Introduza o nome do ficheiro de linhas: ";
	cin >> name_f;
	lines_f.open(name_f);

	while (lines_f.fail())
	{
		cout << "ERRO: nao abriu o ficheiro de linhas" << endl;
		cout << "Introduza de novo o ficheiro de linhas: ";
		cin >> name_f;
		lines_f.open(name_f);
	}

	while (!lines_f.eof())
	{
		getline(lines_f, linel);
		Line line1(linel);
		Lines.push_back(line1);
	}

	lines_f.close();

	//BusesDistribution();
}

//Functions for the analysis of Schedules
//STOPS & LINES
void ScheduleStops() {
	unsigned int id;
	int flag = 0;
	int indice;
	int horas = 13;
	int minutos = 0;
	int input = -1;
	while (true) {
		cout << "========================================================================================================\n";
		cout << "Introduza o ID da linha que deseja: ";
		cin >> id;

		if (cin.fail()) { //SE N�O FOR INT
			cout << endl << "Numero Invalido." << endl;
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			for (unsigned int i = 0; i < Lines.size(); i++) {
				if (Lines.at(i).getId() == id) {
					flag = 1; // YAY!
					indice = i;
				}
			}
			if (flag == 1) {
				break;
			}
			else {
				cout << "Nao inseriu um ID correto!" << endl;
			}
		}
	}

	cout << "========================================================================================================\n";

	unsigned int opcao;
	for (unsigned int i = 0; i < Lines.at(indice).getBusStops().size(); i++) {
		cout << i << " - " << Lines.at(indice).getBusStops().at(i) << endl;
	}
	//verifying if the input is valid
	while (true) {
		cout << "Introduza a paragem que deseja:\n";
		cin >> opcao;
		if (cin.fail() || (opcao >= Lines.at(indice).getBusStops().size()) || (opcao < 0)) {
			cout << endl << "Invalido!" << endl;
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			break;
		}
	}

	for (unsigned int i = 0; i < opcao; i++) {
		minutos = minutos + Lines.at(indice).getTimings().at(i);
		if (minutos >= 60) {
			minutos = minutos - 60;
			horas = horas + 1; //I mean...
		}
	}
	cout << "HORARIO DESEJADO: (HORAS || ID da LINHA)\n";
	cout << "========================================================================================================\n";
	cout << horas << ":" << setfill('0') << setw(2);
	cout << minutos << "   " << Lines.at(indice).getId() << endl;
	cout << "========================================================================================================\n";
	for (unsigned int i = 0; i < 10; i++) {
		minutos = minutos + Lines.at(indice).getFreq();
		if (minutos >= 60) {
			minutos = minutos - 60;
			horas = horas + 1;
		}
		cout << "========================================================================================================\n";
		cout << horas << ":" << setfill('0') << setw(2) << minutos << "   " << Lines.at(indice).getId() << endl;
		cout << "========================================================================================================\n";
	}
	cout << "Prima 0 para retornar ao Menu Principal...\n";
	cin >> input;
	ErrorErrorError(input);
	if (input == 0)
		MenuPrincipal();
	cout << "========================================================================================================\n";
	system("pause");
}
void ScheduleLines() {
	unsigned int id = 0;
	int flag = 0;
	int indice = 0;
	int input = -1;
	int horas = 13; //Begins at 1:00pm
	int minutos = 0;
	while (true) {
		cout << "Introduza o ID da linha que deseja: ";
		cin >> id;

		if (cin.fail()) {
			cout << endl << "Inv�lido!" << endl;
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {

			for (unsigned int i = 0; i < Lines.size(); i++) {
				if (Lines.at(i).getId() == id) {
					flag = 1;
					indice = i;//YAYX2
				}
			}
			if (flag == 1) {
				break;
			}
			else {
				cout << "Nao inseriu um ID correto!" << endl;
			}
		}
	}
	cout << "HORARIO DESEJADO: (HORAS || PARAGENS)\n";
	cout << "========================================================================================================\n";
	cout << horas << ":" << setfill('0') << setw(2) << minutos << "   " << Lines.at(indice).getBusStops().at(0) << endl;
	cout << "========================================================================================================\n";

	for (unsigned int n = 1; n < Lines.at(indice).getBusStops().size(); n++) {
		minutos = minutos + Lines.at(indice).getTimings().at(n - 1);
		if (minutos >= 60) {
			minutos = minutos - 60;
			horas = horas + 1;
		}
		cout << "========================================================================================================\n";
		cout << horas << ":" << setfill('0') << setw(2) << minutos << "   " << Lines.at(indice).getBusStops().at(n) << endl;
		cout << "========================================================================================================\n";
	}
	cout << "Prima 0 para retornar ao Menu Principal...\n";
	cin >> input;
	ErrorErrorError(input);
	if (input == 0)
		MenuPrincipal();
	cout << "========================================================================================================\n";
};

//FUN��ES for the treatment of information given by the user through his own input (DRIVERS)
//ADDING
void AddDriver() {
	string Nome;
	Driver tempCondutor;
	unsigned int tempid;
	unsigned int tempmaxhours;
	unsigned int tempMaxWeekWorkingTime;
	unsigned int tempMinRestTime;

	cout << "========================================================================================================\n";
	cout << "Indique o ID do motorista a adicionar: " << endl;
	cin >> tempid;
	ErrorErrorError(tempid);
	tempCondutor.setId(tempid);

	cin.ignore(1000, '\n');
	cout << "Indique o nome do motorista:  " << endl;
	getline(cin, Nome);
	tempCondutor.setName(Nome);

	cout << "Indique o numero m�ximo de horas do turno do motorista:\n";
	cin >> tempmaxhours;
	ErrorErrorError(tempmaxhours);
	tempCondutor.setMaxHours(tempmaxhours);

	cout << "Indique o numero de horas semanais do motorista:\n";
	cin >> tempMaxWeekWorkingTime;
	ErrorErrorError(tempMaxWeekWorkingTime);
	tempCondutor.setMaxWeekWorkingTime(tempMaxWeekWorkingTime);

	cout << "Indique o numero de horas de descanso do motorista:\n";
	cin >> tempMinRestTime;
	ErrorErrorError(tempMinRestTime);
	tempCondutor.setMinRestTime(tempMinRestTime);

	cout << "========================================================================================================\n";
	Drivers.push_back(tempCondutor);
	cout << "Condutor adicionado! \nRetornando ao Menu Principal...\n";
	cout << "========================================================================================================\n";
	MenuPrincipal();

}

//REMOVING
void RemoveDriver() {
	int input = 0;
	Driver tempCondutor;
	unsigned int tempId;

	cout << "========================================================================================================\n";
	cout << "Indique o ID do motorista que pretende eliminar: ";
	cin >> tempId;
	ErrorErrorError(tempId);

	while (CheckIDDrivers(tempId) == -1) {
		cin >> tempId;
		CheckIDDrivers(tempId);
	}
	//REMO��O
	Drivers.erase(Drivers.begin() + RetIDDrivers(tempId));
	cout << "========================================================================================================\n";
	cout << "Motorista removido! \nRetornando ao Menu Principal...\n";
	cout << "========================================================================================================\n";
	MenuPrincipal();
}

//EDITING
void ChangeDriverMenu() {
	string Nome;
	int options;
	unsigned int ID_Motorista;
	unsigned int NHoras_Turno;
	unsigned int NHoras_Semanais;
	unsigned int NHoras_Descanso;
	int contagem;
	unsigned int tempid;
	Driver tempCondutor;
	options = -1;
	ID_Motorista = -2;
	NHoras_Turno = -1;
	NHoras_Semanais = -1;
	NHoras_Descanso = -1;
	contagem = -1;
	tempid = 0;


	cout << "========================================================================================================\n";
	cout << "Indique o elemento que pretende alterar na sua linha: \n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) ID do motorista. \n";
	cout << "2) Nome do motorista\n";
	cout << "3) Numero de horas de turno\n";
	cout << "4) Numero de horas semanais\n";
	cout << "5) Numero de horas de descanso\n";
	cout << "0) Menu Principal\n";
	cout << "========================================================================================================\n";

	while (!cin.fail())
	{
		cin >> options;
		switch (options) {
		case 0:
			cout << "\n========================================================================================================\n";
			cout << "Alteracao cancelada! Retornando ao Menu Principal...\n";
			cout << "========================================================================================================\n";
			MenuPrincipal();
			break;

			//ALTERA��O DO ID DO MOTORISTA
		case 1:
			"========================================================================================================\n";
			cout << "Insira o ID do motorista que quer alterar:\n";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
			} while (CheckIDDrivers(tempid) == -1);
			cout << "Insira o numero desejado para o novo ID:\n";
			cin >> ID_Motorista;
			ErrorErrorError(ID_Motorista);
			Drivers.at(RetIDDrivers(tempid)).setId(ID_Motorista);
			"\n========================================================================================================\n";
			cout << "ID alterado! Retornando ao Menu Principal...\n";
			"========================================================================================================\n";
			MenuPrincipal();
			break;

			//ALTERA��O DO NOME DO MOTORISTA
		case 2:
			"========================================================================================================\n";
			cout << "Insira o ID do motorista que pretende alterar:\n";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
				CheckIDDrivers(tempid);
			} while (CheckIDDrivers(tempid) == -1);
			cout << "Insira o nome do motorista: \n";

			//Aqui o cin.ignore n�o pode dar asneira? Tipo ignorar tudo o que o utilizador escreveu
			cin.ignore(1000, '\n');
			getline(cin, Nome);

			Drivers.at(RetIDDrivers(tempid)).setName(Nome);
			"\n========================================================================================================\n";
			cout << "Nome alterado! Retornando ao Menu Principal...\n";
			"========================================================================================================\n";
			MenuPrincipal();
			break;

			//ALTERA��O DO NUMERO DE HORAS NO SEU TURNO
		case 3:
			"========================================================================================================\n";
			cout << "Insira o ID do motorista que quer alterar:\n";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
				CheckIDDrivers(tempid);
			} while (CheckIDDrivers(tempid) == -1);
			cout << "Insira o numero desejado de horas do turno correspondente:\n ";
			cin >> NHoras_Turno;
			ErrorErrorError(NHoras_Turno);

			Drivers.at(RetIDDrivers(tempid)).setMaxHours(NHoras_Turno);
			"\n========================================================================================================\n";
			cout << "Horas do turno alteradas! Retornando ao Menu Principal...\n";
			"========================================================================================================\n";
			MenuPrincipal();
			break;

			//ALTERA��O DO NUMERO DE HORAS SEMANAIS
		case 4:
			"========================================================================================================\n";
			cout << "Insira o ID do motorista que quer alterar:\n";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
				CheckIDDrivers(tempid);
			} while (CheckIDDrivers(tempid) == -1);
			cout << "Insira o numero desejado de horas semanais do motorista:\n ";
			cin >> NHoras_Semanais;
			ErrorErrorError(NHoras_Semanais);

			Drivers.at(RetIDDrivers(tempid)).setMaxWeekWorkingTime(NHoras_Semanais);
			"\n========================================================================================================\n";
			cout << "Horas semanais alteradas! Retornando ao Menu Principal...\n";
			"========================================================================================================\n";
			MenuPrincipal();
			break;

			//ALTERA��O DO NUMERO DE HORAS DE DESCANSO
		case 5:
			"========================================================================================================\n";
			cout << "Insira o ID do motorista que quer alterar:\n ";
			do {
				cin >> tempid;
				ErrorErrorError(tempid);
				CheckIDDrivers(tempid);
			} while (CheckIDDrivers(tempid) == -1);
			cout << "Insira o numero desejado de horas de descanso do motorista: ";
			cin >> NHoras_Descanso;
			ErrorErrorError(NHoras_Descanso);
			Drivers.at(RetIDDrivers(tempid)).setMinRestTime(NHoras_Descanso);
			"\n========================================================================================================\n";
			cout << "Horas de descanso alteradas! Retornando ao Menu Principal...\n";
			"========================================================================================================\n";
			MenuPrincipal();
			break;

		default:
			InvalidInputMenu();
			break;
		}
	}
}

//CALCULATES THE DISTANCE BETWEEN 2 STOPS
void ROUTES()
{
	int exit;
	int indexLine;
	int indexStop1;
	int indexStop2;
	int nTiming;
	int min = 0;
	string stop1, stop2;
	vector<string> vecStop1, vecStop2; 
	//A vector of lines where the stop is met
	do
	{
		cout << "========================================================================================================\n";
		cout << "Introduza a primeira paragem que deseja: " << endl;

		getline(cin, stop1);
		for (unsigned int i1 = 0; i1 < Lines.size(); i1++){
			for (unsigned int i2 = 0; i2 < Lines.at(i1).getBusStops().size(); i2++){
				if (Lines.at(i1).getBusStops().at(i2).compare(stop1) == 0){
					vecStop1.push_back(to_string(Lines.at(i1).getId()));
				}
			}
		}
		if (vecStop1.size() == 0){
			cout << "A paragem nao se encontra em nenhuma linha. Volte a introduzir." << endl;
		}
	} while (vecStop1.size() == 0);

	do{
		cout << "Introduza a segunda paragem que deseja" << endl;
		getline(cin, stop2);

		for (unsigned int i1 = 0; i1 < Lines.size(); i1++){
			for (int i2 = 0; i2 < Lines.at(i1).getBusStops().size(); i2++){
				if (Lines.at(i1).getBusStops().at(i2).compare(stop2) == 0){
					vecStop2.push_back(to_string(Lines.at(i1).getId()));
				}
			}
		}
		if (vecStop2.size() == 0){
			cout << "A paragem nao se encontra em nenhuma linha. Volte a introduzir." << endl;
		}
	} while (vecStop2.size() == 0);

	vector<string> CommonStops;
	bool SameLine = false;
	for (int v1 = 0; v1 < vecStop1.size(); v1++)
	{
		for (int v2 = 0; v2 < vecStop2.size(); v2++)
		{
			if (vecStop1.at(v1) == vecStop2.at(v2))
			{
				SameLine = true;
				CommonStops.push_back(vecStop1.at(v1));
			}
		}
	}

	if (SameLine) //If the stops are in the same line.
	{
		for (int line = 0; line < Lines.size(); line++)
		{
			if (to_string(Lines.at(line).getId()) == CommonStops.at(0))
			{
				indexLine = line;
			}
		}
		for (int stop = 0; stop < Lines.at(indexLine).getBusStops().size(); stop++){
			if (Lines.at(indexLine).getBusStops().at(stop) == stop1){
				indexStop1 = stop;
			}
			if (Lines.at(indexLine).getBusStops().at(stop) == stop2){
				indexStop2 = stop;
			}
		}

		if (indexStop1 < indexStop2){ //FRONT TO BACK, BACK TO FRONT
			nTiming = indexStop2 - indexStop1;
		}
		else{
			nTiming = indexStop1 - indexStop2;

		}

		if (indexStop1 < indexStop2){
			for (int i = 0; i < nTiming; i++){
				min = min + stoi(to_string(Lines.at(indexLine).gettimeBetweenStops().at(indexStop1 + i)));
			}
		}
		else{
			for (int i = 0; i < nTiming; i++){
				min = min + stoi(to_string(Lines.at(indexLine).gettimeBetweenStops().at(indexStop2 + i)));
			}
		}
		cout << "========================================================================================================\n";
		cout << "SENTIDO: \n";
		if (indexStop1 < indexStop2){
			for (int i = indexStop1; i < indexStop2 + 1; i++){
				if (i != indexStop2){
					cout << Lines.at(indexLine).getBusStops().at(i) << " || ";
				}
				else
					cout << Lines.at(indexLine).getBusStops().at(i)<< endl;
			}
		}
		else{
			for (int i = indexStop1; i >= indexStop2; i--){
				if (i != indexStop2){
					cout << Lines.at(indexLine).getBusStops().at(i) << " || ";
				}
				else
					cout << Lines.at(indexLine).getBusStops().at(i) << endl;
			}
		}

		cout << "O tempo de viagem entre " << Lines.at(indexLine).getBusStops().at(indexStop1) << " e " << Lines.at(indexLine).getBusStops().at(indexStop2) << " e de " << min << " minutos.";
		cout << "========================================================================================================\n\n";
		cout << "\n Insira o numero 0 para voltar ao menu principal...\n";
		cin >> exit;
		ErrorErrorError(exit);
		MenuPrincipal();
		cout << "========================================================================================================\n\n";
	}
	else
	{
		//Not a possible connection
		int indexLinha1, indexLinha2, indexParagem1, indexParagem2;
		for (int linha = 0; linha < Lines.size(); linha++)
		{
			if(to_string(Lines.at(linha).getId()) == vecStop1.at(0))
			{
				indexLinha1 = linha;
			}
		}
		for (int linha = 0; linha < Lines.size(); linha++){
			if (to_string(Lines.at(linha).getId()) == vecStop2.at(0)){
				indexLinha2 = linha;
			}
		}
		for (int stop = 0; stop < Lines.at(indexLinha1).getBusStops().size(); stop++){
			if (Lines.at(indexLinha1).getBusStops().at(stop) == stop1){
				indexParagem1 = stop;
			}
		}

		for (int stop = 0; stop < Lines.at(indexLinha2).getBusStops().size(); stop++){
			if (Lines.at(indexLinha2).getBusStops().at(stop) == stop2){
				indexParagem2 = stop;
			}
		}

		//Is there a common stop?
		bool CommonStopExisting = false;
		int CommonLine1, CommonLine2;

		for (int i1 = 0; i1 < Lines.at(indexLinha1).getBusStops().size(); i1++){
			for (int i2 = 0; i2 < Lines.at(indexLinha2).getBusStops().size(); i2++){
				if (Lines.at(indexLinha1).getBusStops().at(i1).compare(Lines.at(indexLinha2).getBusStops().at(i2)) == 0){
					CommonStopExisting = true;
					CommonLine1 = i1;
					CommonLine2 = i2;
				}
			}
		}

		int nTimes1, nTimes2;
		int min1 = 0, min2 = 0, FinalMin = 0;

		if (!CommonStopExisting)
			cout << endl << "Nao ha ligacao entre as duas paragens" << endl << endl;

		else{
			//Calculating minutes from first line
			if (indexParagem1 < CommonLine1){
				nTimes1 = CommonLine1 - indexParagem1;
			}
			else{
				nTimes1 = indexParagem1 - CommonLine1;
			}

			if (indexParagem1 < CommonLine1){
				for (int i = 0; i < nTimes1; i++){
					min1 = min + stoi(to_string(Lines.at(indexLinha1).gettimeBetweenStops().at(indexParagem1 + i)));
				}
			}
			else{
				for (int i = 0; i < nTimes1; i++){
					min1 = min1 + stoi(to_string(Lines.at(indexLinha1).gettimeBetweenStops().at(CommonLine1 + i)));
				}
			}
			//Calculating second trip
			if (indexParagem2 < CommonLine2){
				nTimes2 = CommonLine2 - indexParagem2;
			}

			else {
				nTimes2 = indexParagem2 - CommonLine2;
			}
			if (indexParagem2 < CommonLine2)
			{
				for (int i = 0; i < nTimes2; i++)
				{
					min2 = min2 + stoi(to_string(Lines.at(indexLinha2).gettimeBetweenStops().at(indexParagem2 + i)));
				}
			}
			else
			{
				for (int i = 0; i < nTimes2; i++)
				{
					min2 = min2 + stoi(to_string(Lines.at(indexLinha2).gettimeBetweenStops().at(CommonLine2 + i)));
				}
			}

			FinalMin = min1 + min2;

			cout << "========================================================================================================\n";
			cout << "SENTIDO: \n";

			if (indexParagem1 < CommonLine1){
				for (int i = indexParagem1; i < CommonLine1 + 1; i++){
					if (i != CommonLine1){
						cout << Lines.at(indexLinha1).getBusStops().at(i) << " || ";
					}
					else
						cout << Lines.at(indexLinha1).getBusStops().at(i);
				}
			}
			else {
				for (int i = indexParagem1; i >= CommonLine1; i--){
					if (i != CommonLine1){
						cout << Lines.at(indexLinha1).getBusStops().at(i) << " || ";
					}
					else
						cout << Lines.at(indexLinha1).getBusStops().at(i);
				}
			}

			cout << "\n MUDANCA DE LINHA: " << Lines.at(indexLinha1).getId() << " para a linha " << Lines.at(indexLinha2).getId() << "  /\ ";

			if (indexParagem2 < CommonLine2)
			{
				for (int i = CommonLine2; i >= indexParagem2; i--)
				{
					if (i != indexParagem2)
					{
						cout << Lines.at(indexLinha2).getBusStops().at(i) << " || ";
					}
					else
						cout << Lines.at(indexLinha2).getBusStops().at(i) << endl;
				}
			}
			else
			{
				for (int i = CommonLine2; i <= indexParagem2; i++)
				{
					if (i != indexParagem2)
					{
						cout << Lines.at(indexLinha2).getBusStops().at(i) << " || ";
					}
					else
						cout << Lines.at(indexLinha2).getBusStops().at(i) << endl;
				}
			}

			cout << "O tempo de viagem entre " << Lines.at(indexLinha1).getBusStops().at(indexParagem1) << " e " << Lines.at(indexLinha2).getBusStops().at(indexParagem2) << " e de " << FinalMin << " minutos.";
			cout << "========================================================================================================\n\n";
			cout << "\n Insira o numero 0 para voltar ao menu principal...\n";
			cin >> exit;
			ErrorErrorError(exit);
			MenuPrincipal();
			cout << "========================================================================================================\n\n";
		}
	}
}

//INFORMATIONS (HORARIOS, LINHAS, PERCURSOS)
//Funcions that deal with the treatment of information
//Allows us to see the lines exactly how they are shown in the .txt file
void SeeExistingStops() {
	int exit;
	exit = -1;

	cout << "========================================================================================================";
	cout << "\nPERCURSOS EXISTENTES: \n\n";
	for (unsigned int i = 0; i < Lines.size(); i++) {

		for (unsigned int f = 0; f < Lines.at(i).getBusStops().size(); f++) {

			cout << "||ID - " << Lines.at(i).getId() << "|| ";

			cout << Lines.at(i).getBusStops().at(f);

			cout << ";\n";
		}
		cout << "========================================================================================================\n";
	}
	cout << "\n\n Insira o numero 0 para voltar ao menu principal...\n\n";
	cin >> exit;
	ErrorErrorError(exit);
	MenuPrincipal();
}
void SeeExistingLines() {
	int exit;
	exit = -1;

	cout << "LINHAS EXISTENTES: \n\n";
	for (unsigned int i = 0; i < Lines.size(); i++) {
		cout << "||NR - " << (i + 1) << "|| " << Lines.at(i).getId() << " ; " << Lines.at(i).getFreq() << " ; ";
		for (unsigned int j = 0; j < Lines.at(i).getBusStops().size(); j++) {
			cout << Lines.at(i).getBusStops().at(j);
			if ((j + 1) < Lines.at(i).getBusStops().size()) {
				cout << ", ";
			}
		}
		cout << "; ";
		for (unsigned int j = 0; j < Lines.at(i).getTimings().size(); j++) {
			cout << Lines.at(i).getTimings().at(j);
			if ((j + 1) < Lines.at(i).getTimings().size())
				cout << ", ";
		}
		cout << endl;
	}
	cout << "\n\n Insira o numero 0 para voltar ao menu principal...\n\n";
	cin >> exit;

	MenuPrincipal();
}
void SeeExistingDrivers() {
	int exit;
	exit = -1;

	cout << "|| # || Condutores EXISTENTES || Horas Diarias || Horas Semamanais || Horas Descanso \n\n";

	for (unsigned int i = 0; i < Drivers.size(); i++) {
		cout << "||NR - " << (i + 1) << "|| " << Drivers.at(i).getName() << "\t  " << Drivers.at(i).getShiftMaxDuration() << "\t\t     " << Drivers.at(i).getMaxWeekWorkingTime() << "\t\t        " << Drivers.at(i).getMinRestTime() << endl;
	}
	cout << "\n\n Insira o numero 0 para voltar ao menu principal...\n\n";
	cin >> exit;

	MenuPrincipal();
}
void LinesStops()
{
	bool existe = false;
	string paragem;
	int input;
	cout << "========================================================================================================";
	cout << "\nPara saber que linhas passam numa determinada paragem, insira o seu nome (da paragem): " << endl;
	cin.ignore(1000, '\n');
	getline(cin, paragem);

	while (!existe) {

		for (unsigned int i = 0; i < Lines.size(); i++) {

			for (unsigned int f = 0; f < Lines.at(i).getBusStops().size(); f++) {

				if (paragem == Lines.at(i).getBusStops().at(f)) {
					cout << "Lista de linhas que passam por esta paragem: " << endl;
					cout << Lines.at(i).getId() << endl;
					existe = true;
				}
			}
		}
	}
	cout << "Prima 0 para retornar ao Menu Principal...\n";
	cin >> input;
	ErrorErrorError(input);
	if (input == 0)
		MenuPrincipal();
	cout << "========================================================================================================\n";
}
void nrBusCalculation() {
	unsigned int tempid;
	int exit;
	Line templine;

	cout << "========================================================================================================\n";
	cout << "Insira o ID da linha que pretende pesquisar:\n";
	do {
		cin >> tempid;
		ErrorErrorError(tempid);
		CheckIDLines(tempid);
	} while (CheckIDLines(tempid) == -1);

	cout << "Para esta linha, sao necessarios " << Lines.at(RetIDLines(tempid)).nrBuses() << " autocarros.";
	cout << "\n========================================================================================================\n";
	cout << "\n\n Insira o numero 0 para voltar ao menu principal...\n\n";
	cin >> exit;
	ErrorErrorError(exit);
	MenuPrincipal();
	cout << "========================================================================================================\n\n";
}

//Function that deals with the shifts of the driver
void DriversShifts() {
	unsigned int mins;
	unsigned int id;
	cout << "========================================================================================================\n";
	cout << "Insira o ID do motorista que quer consultar:\n";
	do {
		cin >> id;
		ErrorErrorError(id);
	} while (CheckIDDrivers(id) == -1);
	for (unsigned int i = 0; i < Drivers.at(RetIDDrivers(id)).getShifts().size(); i++) {
		mins = Drivers.at(RetIDDrivers(id)).getShifts().at(i).getStartTime();

		if (mins >= 0 && mins <= 1439) { // monday
			cout << "Segunda feira: \n";
		}
		if (mins >= 1440 && mins <= 2879) { // tuesday
			cout << "Ter�a feira: \n";
		}
		if (mins >= 2880 && mins <= 4319) { // wednesday
			cout << "Quarta feira: \n";
		}
		if (mins >= 4320 && mins <= 5759) { // thursday
			cout << "Quinta feira: \n";
		}
		if (mins >= 5760 && mins <= 7199) { // friday
			cout << "Sexta feira: \n";
		}

		cout << "Das " << hrs2min(mins) << ":" << setfill('0') << setw(2);
		cout << mins << " at� �s ";
		mins = Drivers.at(RetIDDrivers(id)).getShifts().at(i).getEndTime();
		cout << hrs2min(mins) << ":" << setfill('0') << setw(2);
		cout << mins << endl;
		cout << "========================================================================================================\n\n";
	}
}

//Functions that deal with the verification of the index of the corresponding vector
int RetIDLines(unsigned int id) {
	for (unsigned int i = 0; i < Lines.size(); i++) {
		if (Lines.at(i).getId() == id) {
			return i;
		}
	}
	return -1;
}
int RetIDDrivers(unsigned int id) {
	for (unsigned int i = 0; i < Drivers.size(); i++) {
		if (Drivers.at(i).getId() == id) {
			return i;
		}
	}
	return -1;
}

//MENUS MENUS MENUS
//Functions that deal w/Invalid Inputs in the Main Menu & the remaining ones of the company
void ErrorErrorError(int &i) {
	while (cin.fail()) {
		cout << "Introduziu uma resposta errada, introduza novamente. ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> i;
	}
}
void ErrorErrorError(unsigned int &i) {
	while (cin.fail()) {
		cout << "Introduziu uma resposta errada, introduza novamente. ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> i;
	}
}
void InvalidInputMenu() {
	if (cin.fail())
	{
		cout << "\nIntroduziu uma resposta invalida. Por favor, tente de novo. \n\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		MenuPrincipal();
	}
	else
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		MenuPrincipal();
	}
}
void InvalidInputFile()
{
	cout << "\nIntroduziu uma resposta invalida. Por favor, tente de novo. \n\n";
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		streamsLinesDrivers();
	}
	else
	{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		streamsLinesDrivers();
	}
}
int CheckIDLines(unsigned int id) {
	int flag = 0;
	unsigned int newid;
	for (unsigned int i = 0; i < Lines.size(); i++) {
		if (Lines.at(i).getId() == id) {
			flag = 1;
			newid = i;
		}
	}
	if (flag == 1) {
		return newid;
	}
	else {
		cout << "Introduziu um ID incorreto, por favor tente novamente.";
		return -1;
	}
}
int CheckIDDrivers(unsigned int id) {
	int flag = 0;
	unsigned int newid;
	for (unsigned int i = 0; i < Drivers.size(); i++) {
		if (Drivers.at(i).getId() == id) {
			flag = 1;
			newid = i;
		}
	}
	if (flag == 1) {
		return newid;
	}
	else {
		cout << "Introduziu um ID incorreto, por favor tente novamente.";
		return -1;
	}
}

//MENU
//Function for the organization of Schedules
void Schedule() {
	int options;
	options = -1;
	cout << "========================================================================================================";
	cout << "\nHORARIOS\n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) Linhas\n";
	cout << "2) Paragens\n";
	cout << "0) Menu Principal\n";
	cout << "========================================================================================================\n\n";
	while (!cin.fail()) {
		cin >> options;

		switch (options) {

		case 0:
			MenuPrincipal();
			break;

		case 1:
			ScheduleLines();
			break;

		case 2:
			ScheduleStops();
			break;

			//in case of wrong input
		default:
			InvalidInputMenu();
			break;
		}
	}
}
//MENU
//Function for managing Buses
void BusMenu() {
	int options;
	options = -1;;
	cout << "========================================================================================================";
	cout << "\nGESTAO DE AUTOCARROS \n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) Visualizar a informacao de um Autocarro\n";
	cout << "2) Periodos de Autocarros sem condutor atribuido\n";
	cout << "3) Numero de Autocarros necessarios para viagens\n";
	cout << "0) Menu Principal\n";
	cout << "========================================================================================================\n\n";
	while (!cin.fail()) {
		cin >> options;
		switch (options) {
		case 0:
			MenuPrincipal();
			break;
		case 1:
			//BusesDistribution(); inicializar variaveis e cout
			break;
		case 2:
			//BusWithNoDriver();
			break;
		case 3:
			nrBusCalculation();
			break;

			//in case of wrong input
		default:
			InvalidInputMenu();
			break;
		}
	}
}
//MENU
//Function for managing Lines
void LineManagment() {
	int options;
	options = -1;;
	cout << "========================================================================================================";
	cout << "\nGESTAO DE LINHAS \n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) Horarios\n";
	cout << "2) Linhas\n";
	cout << "3) Percursos\n";
	cout << "4) Linhas em Paragens\n";
	cout << "5) Calcular tempo entre Paragens\n";
	cout << "0) Menu Principal\n";
	cout << "========================================================================================================\n\n";
	while (!cin.fail()) {
		cin >> options;
		switch (options) {
		case 0:
			MenuPrincipal();
			break;

		case 1:
			Schedule();
			break;

		case 2:
			SeeExistingLines();
			break;

		case 3:
			SeeExistingStops();
			break;

		case 4:
			LinesStops();
			break;
			//in case of wrong input

		case 5:
			ROUTES();
			break;

			//in case of wrong input
		default:
			InvalidInputMenu();
			break;
		}
	}
}

//MENU
//Function for managing Drivers
void DriverManagment() {
	int options;
	options = -1;
	cout << "========================================================================================================";
	cout << "\nGESTAO DE CONDUTORES \n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) Adicionar Condutores \n";
	cout << "2) Remover Condutores\n";
	cout << "3) Alterar Condutores\n";
	cout << "4) Ver Condutores existentes\n";
	cout << "5) Ver trabalho de um Condutor\n";
	cout << "0) Menu Principal\n";
	cout << "========================================================================================================\n\n";
	while (!cin.fail()) {
		cin >> options;
		switch (options) {
		case 0:
			MenuPrincipal();
			break;
		case 1:
			AddDriver();
		case 2:
			RemoveDriver();
		case 3:
			ChangeDriverMenu();
		case 4:
			SeeExistingDrivers();
			break;
		case 5:
			DriversShifts();
			break;

			//in case of wrong input
		default:
			InvalidInputMenu();
			break;
		}
	}
}

//MENU
//Function for file saving
void SaveFileMenu() {
	int options;
	options = -1;
	cout << "========================================================================================================";
	cout << "\nGRAVAR FICHEIROS \n";
	cout << "Insira a sua opcao (1,2,...)\n";
	cout << "1) Gravar ficheiro de condutores\n";
	cout << "2) Gravar ficheiro de linhas\n";
	cout << "0) Menu Principal\n";
	cout << "========================================================================================================\n\n";

	while (!cin.fail()) {
		cin >> options;
		switch (options) {
		case 0:
			MenuPrincipal();
			break;
		case 1:
			SaveFileDrivers();
		case 2:
			SaveFileLines();
		default:
			InvalidInputMenu();
			break;
		}
	}
}

//MENU
//Function for the Main Menu
void MenuPrincipal() {
	vector<string> input;
	int options;
	options = -1;
	cout << "========================================================================================================";
	cout << " \nBem-Vindo ao Menu Principal do programa Escalonamento de Condutores, da Empresa de Transportes Semprarrolar.\n";
	cout << " Por favor escolha um numero como opcao. \n";
	cout << " 1) Gestao de Linhas.\n";
	cout << " 2) Gestao de Condutores.\n";
	cout << " 3) Gestao de Autocarros.                                __________________\n";
	cout << " 4) Gravar Ficheiro.                                    |            TM  D \\\n";
	cout << " 0) Terminar programa.                                  |SEMPRARROLAR||    |\n";
	cout << "                                                   ooo0O|_ (o) ______|| (o)/\n";
	cout << "========================================================================================================\n\n";


	while (!cin.fail())
	{
		cin >> options;
		switch (options) {
		case 0:
			cout << "=============================================================\n";
			cout << "\nTerminando programa, aguarde...\n\n";
			cout << "=============================================================";
			cout << "\nObrigado pela sua colaboracao, volte em breve!\n\n\n";
			cout << " ___ ___ __ __ ___ ___ ___ ___ ___ ___ _   ___ ___ " << endl;
			cout << "/ __| __|  \\  | . | . | . | . | . | . | | | . | . \\   TM" << endl;
			cout << "\\__ | _>|     |  _|   |   |   |   | | | |_|   |   /" << endl;
			cout << "<___|___|_|_|_|_| |_\\_|_|_|_\\_|_\\_`___|___|_|_|_\\_\\ " << endl;
			cout << "=============================================================";
			cout << "\n\n";
			exit(0);
		case 1:
			LineManagment();
			break;
		case 2:
			DriverManagment();
			break;
		case 3:
			BusMenu();
		case 4:
			SaveFileMenu();
			break;
		default:
			InvalidInputMenu();
			break;
		}
	}
}


//OTHER FUNCTIONS
int Commas(string stringe) {
	char checkCharacter = ',';
	int count = 0;

	for (unsigned int i = 0; i < stringe.size(); i++)
	{
		if (stringe[i] == checkCharacter)
		{
			++count;
		}
	}

	return count;
}

//Function regarding the Hours & minutes in days
unsigned int hrs2min(unsigned int &mins) {
	unsigned int hrs = 0;
	hrs = mins / 60;
	mins = mins % 60;
	return hrs;
}


//MAIN
int main() {
	streamsLinesDrivers();
	MenuPrincipal();

	system("PAUSE");
	return 0;
}