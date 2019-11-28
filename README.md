HTTP server-side scripting with C - Compiler project

This project implements a server side scripting engine. The subset of ANSI C is chosen as the scripting language. Also it has some extra support to incorporate with web based environment.

The task of the server side scripting engine was achieved in several stages. Firstly, it handles HTTP request to process a file. Then this file is processed to extract the presence of C code, if found it is compiled using the ‘Compiler’ component. The ‘Compiler’ component is constructed using well-established compiler construction theory. It generates intermediate code. HTML portion of CHTML file usually contains calling of a C function that was previously defined in the ‘C Code’ section and it involves interpreting and executing the intermediate code associated with this function as well as generating output at the position of the file, from which the function was called.

The web request may contain query string, which is usually the value of some variables received using built-in function.

The program is designed in such a way that incorporating further support becomes a easy task. The modularized development approach enables this.

Readers are expected to have some theoretical knowledge in compiler construction as well as in server side scripting.
