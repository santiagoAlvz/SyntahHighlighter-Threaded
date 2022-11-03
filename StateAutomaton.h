/**
 * Syntax Highlighter (Threaded)
 * StateAutomaton.h - Declaración de clase
 * Santiago Álvarez Valdivia - A01640172
 * 26 de mayo de 2022
 */

#ifndef STATE_AUTOMATON
#define STATE_AUTOMATON

#include "OutputFile.h"
#include <vector>
#include <utility>
#include <string>

using std::vector;
using std::pair;
using std::string;

class StateAutomaton{
	private:
		int state;
		vector <vector <pair <char, int> > >* transitions;
		vector <pair <int, string> >* finals;
		
	public:
		void operator()(vector <vector <pair <char, int> > >*, vector <pair <int, string> >*, OutputFile*, vector<string>*,int, int);
		int nextState(char);
		string getFinalStyle();
};

#endif