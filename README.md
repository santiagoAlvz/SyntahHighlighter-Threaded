# SyntahHighlighter (Threaded)
Flexible Syntax Highlighter for source code, with the capability to use multiple threads. This program reads source code from a file, highlights it according to a user-defined spec and stores the result in HTML form in a file.

## Compilation

This program is written in standard C++, and should be built succesfully with any modern C++ compiler. During development, the GNU G++ compiler was used.

The code to be compiled is in the repository root folder, alongside an example syntax specification, for C/C++. There is also an `Ejemplos` folder, which contains source code for the user to test functionality.

## Usage

Once compiled, this program requires to be executed with 3 arguments to work:
- Input File. The file to be highlighted
- Output File. The name of the destination file, where the resulting HTML will be stored
- Number of threads to be used while highlighting

For example, if we execute the program like this:

`./SyntaxHighlighter ejemplo.c output.html 5`

The program SyntaxHighlighter will open the file `ejemplo.c` (which must be in the same directory as the executable), process it using 5 threads (according to the rules defined in `LexSpec.txt`) and store the result to `output.html`, which will be created (or overwritten) in the same directory as the executable.

**NOTE:** In order to work properly, this program requires the file LexSpec.txt to be in the same directory as the executable, since it contains the rules that the program will use to highlight the input file. More details on the _User-defined Specs_ section.

## User defined specs

A relevant part of this program is the posibility of modifying the included syntax specification (which is in the file `LexSpec.txt`) or creating a new one altogether. The syntax Specification defines the patterns that this program will use to highlight code. It is worth mentioning that said patterns are read during runtime, so, while a recompilation of the program isn't necessary when changing specs, the presence of the `LexSpec.txt` file in the executable location is. The name of the Syntax Specification file must always be `LexSpec.txt`.

The first line in the spec file is the style -in CSS form- that the whole document will follow. From the second line onwards, each line will be treated as a pattern definition, with the form \[_pattern_\] \[_style to be applied_\] \[_comment_\]. Each section follows its own set of rules:
- **Pattern:** it is what the program will search to highlight, it can contain either regular characters (as 'a' or '5') or a wildcard. Available wildcards are
  - **|** which means every possible character (except line jumps), any number of times
  - **~** which means every possible numeric character from 0 to 9, any number of times
  - **:** which means every alphanumeric character, any number of times (Useful for identifiers)
- **Style:** must be written in CSS form, will the applied to the matches of the pattern
- **Comment:** it is not actually used by the program, and it's there for human readability purposes

For example, the line

`if color:#FF9D00;font-weight:bold PalabrasReservadas`

means that every ocurrence of the word 'if' will be written with bold characters in the color #FF9D00. Here 'PalabrasReservadas' is used as a comment by the programmer.

Another example is

`/*|*/ color:#0088FF;font-style:italic Comentario`

which will highlight all the text that is between \/\* \*\/ with the corresponding style.

It is worth mentioning that this program doesn't support multi-line patterns, such as multiline comments. It is -as of now at least- limited to patterns that span only one line.

## Operation Summary

When executed, this program will go through a series of steps
1. Read the arguments specified by the user. If there aren't enough of them, an error message will be displayed.
2. Read the syntax specification from the file `LexSpec.txt`, and build an state automaton with it. The state automaton will be used in order to recognize patterns and highlight them
3. Execute the specified amount of threads, where every thread gets assigned a certain number of lines from the file, and processes them according to the state automaton generated on the last step. Every threads goes on appending its results to a buffer.
4. The buffer gets written into the output file.
