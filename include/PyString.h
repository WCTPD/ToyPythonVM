#ifndef PY_STRING_H
#define PY_STRING_H

#include <string>
#include "PyObject.h"

using std::string;

class StringKlass : public Klass {
private:
    StringKlass();
    static StringKlass* _instance;

public:
    static StringKlass* get_instance();
    void initialize();

    virtual PyObject* add(PyObject* x, PyObject* y);    

    virtual PyObject* lt(PyObject* x, PyObject* y);     
    virtual PyObject* le(PyObject* x, PyObject* y);     
    virtual PyObject* eq(PyObject* x, PyObject* y);     
    virtual PyObject* ne(PyObject* x, PyObject* y);     
    virtual PyObject* gt(PyObject* x, PyObject* y);     
    virtual PyObject* ge(PyObject* x, PyObject* y);     
    virtual PyObject* in(PyObject* x, PyObject* y);     
    virtual PyObject* not_in(PyObject* x, PyObject* y);

    virtual PyObject* len(PyObject* x);
    virtual PyObject* print(PyObject* x);
    virtual PyObject* subscr(PyObject* x, PyObject* y);
};

class PyString : public PyObject {
private:
    string _value;

public:
    PyString(const string s);

    string& value() { return _value; } 
    int length() { return _value.size(); }
};

#endif