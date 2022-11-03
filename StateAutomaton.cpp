/**
 * Syntax Highlighter (Threaded)
 * StateAutomaton.cpp - Implementación de clase
 * Santiago Álvarez Valdivia - A01640172
 * 26 de mayo de 2022
 */

#include "StateAutomaton.h"
#include <iostream>

void StateAutomaton::operator()(vector <vector <pair <char, int> > >* trans, vector <pair <int, string> >* fin, OutputFile* output, vector<string>* input, int start, int end){
	//Constructor del autómata
	this->transitions = trans;
	this->finals = fin;
	
	string result;
	string temp;
	int next;
	bool stay = false;

	for(int j = start; j < end; j++){


		result = "";
		temp = "";
		this->state = 0; //Estado inicial
		
		//Para cada caracter
		for(long unsigned i = 0; i < (*input)[j].length(); i++){
			
			next = nextState((*input)[j][i]); //Obtiene el estado siguiente
			
			if(next == -1){ //Si el caracter rompe con la "racha"
			
				if(this->state != 0){ //Si se estaba en un estado que no fuera uno
				
					//Guarda los caracteres de la "racha" con su estilo
					result.append("<span style=\""+getFinalStyle()+"\">"+temp+"</span>");
					//Reinicia el buffer
					temp = "";
					//Y repite el mismo caracter, para que no se "pierda"
					stay = true;
					
				} else {
					//Si no había "racha" en primer lugar, sólo añade el caracter al resultado
					result.push_back((*input)[j][i]);
				} 
				next = 0; //Y manda al estado inicial
				
			} else { //Añade el caracter al buffer
				
				//Añade el caracter, y verifica si es < o >, para escribirlo de manera correcta
				if((*input)[j][i] == '<'){
					temp.append("&lt");
				} else if ((*input)[j][i] == '>'){
					temp.append("&gt");
				} else temp.push_back((*input)[j][i]);
			}
			
			this->state = next; //Actualiza el estado
			
			if(stay){ //Si se había marcado pertenecer en la misma casilla
				stay = false;
				i--;
			}
		}
		
		//Para la última "racha"
		result.append("<span style=\""+getFinalStyle()+"\">"+temp+"</span>");
		
		output->addLine(result, j);
	}
}

int StateAutomaton::nextState(char next){
	//Calcula el próximo estado
	
	char temp;
		
	//Recorre las transiciones para el estado actual, hasta encontrar una que coincida
	for(long unsigned i = 0; i < (*this->transitions)[this->state].size(); i++){
		temp = (*this->transitions)[this->state][i].first;
		if(temp == next){
			return (*this->transitions)[this->state][i].second;
		}
		if(temp == '|'){
			return (*this->transitions)[this->state][i].second;
		}
		if(temp == ':' && (isalpha(next) || isdigit(next))){
			return (*this->transitions)[this->state][i].second;
		}
		if(temp == '~' && isdigit(next)){
			return (*this->transitions)[this->state][i].second;
		}			
	}
	
	return -1; //Si no se encuentra ninguna que coincida
}

string StateAutomaton::getFinalStyle(){
	//Obtiene el estilo del estado actual, si es que es final
	for(long unsigned i = 0; i < (*this->finals).size(); i++){
		if((*this->finals)[i].first == this->state){
			return (*this->finals)[i].second;
		}
	}
	
	return "";
}
