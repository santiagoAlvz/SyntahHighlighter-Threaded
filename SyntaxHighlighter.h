/**
 * Syntax Highlighter (Threaded)
 * SyntaxHighlighter.h - Declaración de clase
 * Santiago Álvarez Valdivia - A01640172
 * 26 de mayo de 2022
 */

#ifndef SYNTAX_HIGHLIGHTER
#define SYNTAX_HIGHLIGHTER

#include <string>
#include <vector>
#include <utility>
#include "OutputFile.h"

using std::string;
using std::vector;
using std::pair;

class SyntaxHighlighter{
	
	private:
		string inputFile;
		OutputFile outputFile;
		vector <vector <pair <char, int> > > transitions; //Tabla de transiciones
		vector <pair <int, string> > finals; //Tabla de estados finales
		int numStates = 1;
	
public:
		SyntaxHighlighter(string, string);
		void loadSpecs(string);
		void addSpec(string, string);
		int addTransition(int, char);
		int addFinalTransition(int, char, string);
		void normalizeTransitions();
		void printTransitions();
		void highlightFile(int);
	
};

#endif