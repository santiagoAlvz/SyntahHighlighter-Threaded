/**
 * Syntax Highlighter (Threaded)
 * OutputFile.h - Declaración de clase
 * Santiago Álvarez Valdivia - A01640172
 * 26 de mayo de 2022
 */

#ifndef OUTPUT_FILE
#define OUTPUT_FILE

#include <string>
#include <fstream>
#include <vector>

using std::string;
using std::ofstream;

class OutputFile{
	private:
		string baseStyle;
		ofstream output;
		std::vector <string> buffer;
		
	public:
		OutputFile();
		OutputFile(string);
		void setBaseStyle(string);
		void addHeader();
		void addFooter();
		void addLine(string, int);
		void close();
		void setBufferSize(int);
		void addFromBuffer();
};

#endif