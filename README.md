# SyntahHighlighter-Threaded
Flexible Syntax Highlighter for source code, with the capability to use multiple threads

## Compilation

This program is written in standard C++, and should be built succesfully with any modern C++ compiler. During development, the GNU G++ compiler was used.

##Usage

Once compiled, this program requires to be executed with 3 arguments to work:
- Input File. The file to be highlighted
- Output File. The name of the destination file, where the resulting HTML will be stored
- Number of threads to be used while highlighting

For example, if we execute the program like this:

`./SyntaxHighlighter ejemplo.c output.html 5`

The program SyntaxHighlighter will open the file `ejemplo.c` (which must be in the same directory as the executable), process it using 5 threads, store the result to `output.html`
