# SyntahHighlighter-Threaded
Flexible Syntax Highlighter for source code, with the capability to use multiple threads. This program reads source code from a file, highlights it according to a user-defined spec and stores the result in HTML form in a file.

## Compilation

This program is written in standard C++, and should be built succesfully with any modern C++ compiler. During development, the GNU G++ compiler was used.

The code to be compiled is in the repository root folder, alongside an example syntax specification, for C/C++. There is also an `Ejemplos` folder, which contains source code for the user to test funtionality.

## Usage

Once compiled, this program requires to be executed with 3 arguments to work:
- Input File. The file to be highlighted
- Output File. The name of the destination file, where the resulting HTML will be stored
- Number of threads to be used while highlighting

For example, if we execute the program like this:

`./SyntaxHighlighter ejemplo.c output.html 5`

The program SyntaxHighlighter will open the file `ejemplo.c` (which must be in the same directory as the executable), process it using 5 threads (according to the rules defined in LexSpec.txt) and store the result to `output.html`, which will be created (or overwritten) in the same directory as the executable.

**NOTE:** In order to work properly, this program requires the file LexSpec.txt to be in the same directory as the executable, since it contains the rules that the program will use to highlight the input file. More details on the _User-defined Specs_ section.
