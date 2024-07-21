#include "../includes/global.h"
#include "../includes/prototype.h"
void python_draw(int loop_number){

    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    fstream _fileRho,_fileV;
    _fileRho.open("./data/out_rho1_0.m",ios::in);

if(id==1 && _fileRho){
    if(loop_number==1) Py_Initialize();
    PyObject *pModule;
    PyObject *pFunction1;
    PyObject *pArgs;

    PyRun_SimpleString("import matplotlib.pyplot as plt");
    PyRun_SimpleString("import numpy as np");
    PyRun_SimpleString("import os");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./python/')");
    pModule = PyImport_ImportModule("draw");
    pFunction1 = PyObject_GetAttrString(pModule, "draw_rho");
    pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", numprocs));
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", loop_number));
    PyObject_CallObject(pFunction1, pArgs);

    Py_DECREF(pArgs);
    Py_DECREF(pFunction1);
    Py_DECREF(pModule);
}

_fileV.open("./data/out_V1_0.m",ios::in);

if(id==2 && _fileV){
    if(loop_number==1) Py_Initialize();
    PyObject *pModule;
    PyObject *pFunction2;
    PyObject *pArgs;

    PyRun_SimpleString("import matplotlib.pyplot as plt");
    PyRun_SimpleString("import numpy as np");
    PyRun_SimpleString("import os");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./python/')");
    pModule = PyImport_ImportModule("draw");
    pFunction2 = PyObject_GetAttrString(pModule, "draw_v");
    pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", numprocs));
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", loop_number));
    PyObject_CallObject(pFunction2, pArgs);

    Py_DECREF(pArgs);
    Py_DECREF(pFunction2);
    Py_DECREF(pModule);
}

}
