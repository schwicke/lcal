/*
 *  This file is part of lcal, a command line calculator 
 *  Author: Ulrich Schwickerath, (C) 12/2000 CERN
 *          ulrich.schwickerath@web.de
 *  
 *  This code comes with absolutly no warranty!
 *  it should not be used for production purposes whatsoever
 *
 */

#ifndef PARSETERM
#define PARSETERM
#include <iostream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "Nodes"

class Term;

class Pot {
 public:
    Term * Klammer;
    Pot * Potenz;
    char  VName;
    double Konstante;
    Pot();
    Pot(char * &s);
    ~Pot();
    Pot * ParsePot(char * &s );
    void print();
    double value();
    int isconst();
 private:
    char action;
};

class Fak {
 public:
    ListOf <Pot> * Faktoren;
    Fak();
    Fak(char * &s);
    ~Fak();
    Fak * ParseFak(char * &s);
    void print();
    double value();
    int ispot();
    int isconst();
};

class Sum {
 public:
    ListOf <Fak> * Summanden;
    Sum();
    Sum(char * &s);
    ~Sum();
    Sum * ParseSum(char * &s);
    void print();
    double value();
    int ispot();
    int isfak();
    int isconst();
};

class Term {
 public:
    ListOf <Sum> * Terme;
    Term();
    Term(char * &s);
    ~Term();
    Term * ParseTerm(char * &s);
    void print();
    double value();
    int ispot();
    int isfak();
    int issum();
    int isconst();
};


#endif
