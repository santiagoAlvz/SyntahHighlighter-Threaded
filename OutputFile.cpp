/**
 * Syntax Highlighter (Threaded)
 * OutputFile.cpp - Implementación de clase
 * Santiago Álvarez Valdivia - A01640172
 * 26 de mayo de 2022
 */

#include "OutputFile.h"

using std::endl;

OutputFile::OutputFile(){ }

OutputFile::OutputFile(string file){
	//Constructor con parámetros
	
	this->output = ofstream(file);
}

void OutputFile::setBaseStyle(string style){
	//Establecer el estido del documento
	this->baseStyle = style;
}

void OutputFile::addHeader(){
	//Agrega la cabecera al archivo
	
	output<<"<!DOCTYPE HTML>"<<endl;
	output<<"<html>"<<endl;
	output<<"\t<body style=\""<< this->baseStyle <<"\">"<<endl;
	output<<"\t\t<pre style=\"font-family:monospace,monospace\">"<<endl;
}

void OutputFile::addFooter(){
	//Agrega el final al archivo
	output<<"\t\t</pre>"<<endl;
	output<<"\t</body>"<<endl;
	output<<"</html>"<<endl;
}

void OutputFile::addLine(string line, int pos){
	//Añade una línea de código, con su respectivo salto de línea
	buffer[pos] = line + "<br>";
}

void OutputFile::close(){
	//Cierra el archivo
	output.close();
}

void OutputFile::setBufferSize(int size){
	this->buffer.resize(size);
}

void OutputFile::addFromBuffer(){
	for(long unsigned i = 0; i < buffer.size(); i++){
		output<<buffer[i]<<endl;
	}
}