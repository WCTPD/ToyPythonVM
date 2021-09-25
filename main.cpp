#include "Interpreter.h"
#include "BufferInputStream.h"
#include "BinaryFileParser.h"
#include "Universe.h"
#include <iostream>


using namespace std;

int main() {
    Universe::genesis();
    BufferInputStream* file_stream = new BufferInputStream("/home/wctpd/Desktop/ToyPythonVM/__pycache__/test.cpython-38.pyc");
    BinaryFileParser parser(file_stream);
    CodeObject* code = parser.parse();
    Interpreter interpreter;
    //interpreter.run(code);
}