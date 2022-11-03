/**
 * Syntax Highlighter (Threaded)
 * main.cpp - Función Principal del programa
 * Santiago Álvarez Valdivia - A01640172
 * 26 de mayo de 2022
 */

#include "SyntaxHighlighter.h"
#include <iostream>

int main(int argc, char **argv)
{
	if(argc > 3){

		SyntaxHighlighter highlighter(argv[1],argv[2]);
	
		highlighter.loadSpecs("LexSpec.txt");
		highlighter.highlightFile(std::stoi(argv[3]));
		
		return 0;
		
	} else {
		std::cout<< "Error. Faltan parámetros a especificar" <<std::endl;
	}
}
