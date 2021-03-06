#ifndef CODE_OBJECT_H
#define CODE_OBJECT_H

#include "PyObject.h"
#include "PyList.h"
#include "PyString.h"

class CodeKlass : public Klass {
private:
    CodeKlass();
    static CodeKlass* _instance;
public:
    static CodeKlass* get_instance();

};

class CodeObject : public PyObject {
public:
    int co_argcount;
    int co_posonlyargcount;
    int co_kwonlyargcount;
    int co_nlocals;
    int co_stacksize;
    int co_flags;

    PyString* co_code;
    PyList* co_consts;
    PyList* co_names;
    PyList* co_varnames;
    PyList* co_freevars;
    PyList* co_cellvars;

    PyString* co_filename;
    PyString* co_name;

    int co_firstlineno;
    PyString* co_lnotab;

    CodeObject(
        int co_argcount,
        int co_posonlyargcount,
        int co_kwonlyargcount,
        int co_nlocals,
        int co_stacksize,
        int co_flags,
        PyString* co_code,
        PyList* co_consts,
        PyList* co_names,
        PyList* co_varnames,
        PyList* co_freevars,
        PyList* co_cellvars,
        PyString* co_filename,
        PyString* co_name,
        int co_firstlineno,
        PyString* co_lnotab);

};

#endif