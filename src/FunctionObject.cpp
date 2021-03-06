#include "FunctionObject.h"

FunctionKlass* FunctionKlass::_instance = NULL;
NativeFunctionKlass* NativeFunctionKlass::_instance = NULL;
MethodKlass* MethodKlass::_instance = NULL;

FunctionKlass* FunctionKlass::get_instance() {
    if (_instance == NULL) {
        _instance = new FunctionKlass();
    }
    return _instance;
}

FunctionKlass::FunctionKlass() {
    set_name(new PyString("function"));
}

FunctionObject::FunctionObject(PyObject* code_object) {
    CodeObject* co = (CodeObject*)code_object;

    _func_code = co;
    _func_name = co->co_name;
    _flags = co->co_flags;

    set_klass(FunctionKlass::get_instance());
}

FunctionObject::FunctionObject(NativeFuncPointer nfp) {
    _func_code = NULL;
    _func_name = NULL;
    _flags     = 0;
    _native_func = nfp;

    set_klass(NativeFunctionKlass::get_instance());
}

PyObject* FunctionObject::call(PyList* args) {
    return (*_native_func)(args);
}

NativeFunctionKlass* NativeFunctionKlass::get_instance() {
    if (_instance == NULL) {
        _instance = new NativeFunctionKlass();
    }
    return _instance;
}

NativeFunctionKlass::NativeFunctionKlass() {
    set_name(new PyString("native function"));
}

FunctionObject::FunctionObject(Klass* klass) : _func_code(NULL), _func_name(NULL), _flags(0), _defaults(NULL) {
    set_klass(klass);
}

void FunctionObject::set_defaults(PyList* defaults) {
    if (defaults == NULL) {
        _defaults = NULL;
        return;
    }

    _defaults = new PyList();

    for (int i = 0; i < defaults->size(); i++) {
        _defaults->set(i, defaults->get(i));
    }
}

MethodKlass::MethodKlass() {
    set_name(new PyString("method"));
    set_klass_dict(new Map<string, PyObject*>());
}

MethodKlass* MethodKlass::get_instance() {
    if (_instance == NULL) {
        _instance = new MethodKlass();
    }
    return _instance;
}

MethodObject::MethodObject(FunctionObject* func) : _owner(NULL), _func(func) {
    set_klass(MethodKlass::get_instance());
}

MethodObject::MethodObject(FunctionObject* func, PyObject* owner) : _owner(owner), _func(func) {
    set_klass(MethodKlass::get_instance());
}

bool MethodObject::is_function(PyObject* x) {
    Klass* klass = x->klass();
    if (klass == FunctionKlass::get_instance() || klass == NativeFunctionKlass::get_instance()) {
        return true;
    }
    return false;
}

PyObject* len(PyList* args) {
    return args->get(0)->len(args);
}

PyObject* print(PyList* args) {
    for (int i = 0; i < args->size() - 1; i++) {
        args->get(i)->print(args);
        printf(" ");
    }
    args->get(args->size() - 1)->print(args);
    printf("\n");
    return NULL;
}

PyObject* string_upper(PyList* args) {
    PyObject* arg0 = args->get(0);
    assert(arg0->klass() == StringKlass::get_instance());

    PyString* s = new PyString(((PyString*)arg0)->value());
    for (auto& i : s->value()) {
        i = toupper(i);
    }

    return (PyObject*)s;
}