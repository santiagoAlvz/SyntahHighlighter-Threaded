/**
 * Syntax Highlighter (Threaded)
 * SyntaxHighlighter.cpp - Implementación de clase
 * Santiago Álvarez Valdivia - A01640172
 * 26 de mayo de 2022
 */

#include "SyntaxHighlighter.h"
#include "StateAutomaton.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>

using std::ifstream;
using std::istringstream;
using std::make_pair;

SyntaxHighlighter::SyntaxHighlighter(string file, string destination){
	//Constructor de la clase
	
	vector <pair<char, int> > temp;
	this->transitions.push_back(temp);
	
	this->inputFile = file;
	this->outputFile = OutputFile(destination);
}

void SyntaxHighlighter::loadSpecs(string lexSpecFile){
	//Carga las definiciones del archivo
	
	string temp, spec, style;
	
	ifstream lexSpec(lexSpecFile);
	
	getline(lexSpec, temp);
	outputFile.setBaseStyle(temp);
	
	while(getline(lexSpec, temp)){
		
		istringstream line(temp);
	
		getline(line, spec, ' ');
		getline(line, style, ' ');
		this->addSpec(spec, style);
	}
	
	lexSpec.close();
	
	normalizeTransitions();	//Normaliza las transiciones
	//printTransitions(); //Imprime las transiciones, con fines de debug
}

void SyntaxHighlighter::addSpec(string spec, string style){
	//Añade una definición individual a la máquina de estados
	
	int currentState = 0; //Iniciamos siempre en 0
	
	while(spec.length() > 1){
		//Para cada caracter, crear la transición correspondiente
		
		currentState = this->addTransition(currentState, spec.front());
		
		spec.erase(0,1);
	}
	
	//Crear la última transición
	this->addFinalTransition(currentState, spec.front(), style);
	
}

int SyntaxHighlighter::addTransition(int state, char next){
	//Añade una transición individual
	
	//Primero verifica si la transición a crear no existe ya, si lo hace
	//regresa el resultado de dicha transición
	for(long unsigned i = 0; i < this->transitions[state].size(); i++){
		if(this->transitions[state][i].first == next){
			return this->transitions[state][i].second;
		}
	}
	
	vector <pair<char, int> > temp; //Vector vacío para crear nuevos estados
	
	//Si el caracter es un comodín
	if(next == '|' || next == ':' || next == '~'){
		if(state > 0){
			//y no es el único caracter de la definición, se crea una transición
			//circular al mismo estado
			this->transitions[state].push_back(make_pair(next,state));
			return state;
		} else {
			//y SI es el único caracter de la definición, se crea un nuevo estado
			// con una transición circular
			this->transitions.push_back(temp);
			this->transitions[state].push_back(make_pair(next, numStates));
			this->transitions[numStates].push_back(make_pair(next, numStates));
			this->numStates++;
			return numStates-1;	
		}
	} else {
		//Si es un caracter común sin transición ya existente, crea un estado nuevo
		// y la transición correspondiente
		this->transitions.push_back(temp);
		this->transitions[state].push_back(make_pair(next, numStates));
		this->numStates++;
		return numStates-1;
	}
}

int SyntaxHighlighter::addFinalTransition(int state, char next, string style){
	//Añade una transición final, es idéntico al método anterior, sólo que también 
	//añade el estado a la lista de estados finales, con su respectivo estilo
	
	for(long unsigned i = 0; i < this->transitions[state].size(); i++){
		if(this->transitions[state][i].first == next){
			this->finals.push_back(make_pair(this->transitions[state][i].second,style));
			return this->transitions[state][i].second;
		}
	}
	
	vector <pair<char, int> > temp;
	
	if(next == '|' || next == ':' || next == '~'){
		if(state > 0){
			this->transitions[state].push_back(make_pair(next,state));
			this->finals.push_back(make_pair(state,style));
			return state;
		}
		
		this->transitions.push_back(temp);
		this->transitions[state].push_back(make_pair(next, numStates));
		this->transitions[numStates].push_back(make_pair(next, numStates));
		this->numStates++;
		this->finals.push_back(make_pair(numStates-1,style));
		return numStates-1;	
	}
	
	this->transitions.push_back(temp);
	this->transitions[state].push_back(make_pair(next, numStates));
	this->numStates++;
	this->finals.push_back(make_pair(numStates-1,style));
	return numStates-1;	
	
}

void SyntaxHighlighter::normalizeTransitions(){
	//Normaliza la tabla de transiciones, es decir, coloca los comodines hasta
	//el final de la misma
	char temp;
	
	//Recorre todos los elementos de la tabla
	for(long unsigned i = 0; i < this->transitions.size(); i++){
		for(long unsigned j = 0; j < this->transitions[i].size(); j++){
			
			//Si encuentra un comodín, lo coloca al final de su columna
			temp = transitions[i][j].first;
			if(temp == '|' || temp == ':' || temp == '~'){
				transitions[i].push_back(transitions[i][j]);
				transitions[i].erase(transitions[i].begin() + j);
			}
		}
	}
}

void SyntaxHighlighter::printTransitions(){
	//Imprime todas las transiciones registradas, en formato
	// estadoOrigen:Caracter,estadoDestino
	
	for(long unsigned i = 0; i < this->transitions.size(); i++){
		for(long unsigned j = 0; j < this->transitions[i].size(); j++){
			std::cout<<i<<":"<<transitions[i][j].first<<","<<transitions[i][j].second<<std::endl;
			
		}
	}
	
	//Imprime todos los estados registrados como finales
	std::cout<<"Estados Finales"<<std::endl;
	
	for(long unsigned i = 0; i < this->finals.size(); i++){
		std::cout<<finals[i].first<<", "<<finals[i].second<<std::endl;
	}
}

void SyntaxHighlighter::highlightFile(int threads){
	//Remarca el archivo

	std::thread myThreads[threads]; //Arreglo para almacenar los objetos hilo
	
	int lines = 0, acum, partition, extra;

	//Crea un vector de cadenas con el archivo de entrada, a su vez, cuenta las líneas del archivo
	// de entrada
	ifstream inputFileObject(this->inputFile);
	vector<string> input;
    string str;
    while(getline(inputFileObject,str)){
    	lines++;
        input.push_back(str);
    }

    //Calcula la cantidad de líneas a procesar por cada archivo
    partition = lines/threads;
	extra = lines - (partition*threads);

	this->outputFile.setBufferSize(lines);
	this->outputFile.addHeader(); //Añade el principio del archivo

	//Inicia el primer hilo
	acum = partition + extra;
	std::cout<<"Starting thread 0"<<std::endl;
	myThreads[0] = std::thread(StateAutomaton(), &this->transitions, &this->finals, &this->outputFile, &input, 0, partition + extra);

	//Inicia el resto de los hilos
	for(int i = 1; i < threads; i++){
		std::cout<<"Starting thread "<<i<<std::endl;
		myThreads[i] = std::thread(StateAutomaton(), &this->transitions, &this->finals, &this->outputFile, &input, acum, acum + partition);
		acum += partition;
	}

	//Espera a que los hilos terminen de ejecutarse
	for(int i = 0; i < threads; i++){
		myThreads[i].join();
		std::cout<<"Thread "<<i<<" has finished operation"<<std::endl;

	}
	
	this->outputFile.addFromBuffer();
	this->outputFile.addFooter();  //Añade el final del archivo
	this->outputFile.close();
}