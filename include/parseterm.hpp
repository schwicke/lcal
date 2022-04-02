/*
 * $Id: parsetemr.hpp,v 1.5 2004/01/20 19:54:33 ulrich Exp $
 * Copyright (C) Ulrich Schwickerath
 *  This file is part of lcal, a command line calculator 
 *  Author: Ulrich Schwickerath, (C) 12/2000 CERN
 *          ulrich.schwickerath@web.de
 *  
 *  This code comes with absolutly no warranty!
 *  it should not be used for production purposes whatsoever
 *
 */

#ifndef INCLUDE_PARSETERM_HPP_
#define INCLUDE_PARSETERM_HPP_
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "./nodes.hpp"

class Term;

class Pot {
 public:
  Term * Bracket;
  Pot * Potenz;
  char  VName;
  double Constant;
  Pot();
  explicit Pot(const char * s);
  ~Pot();
  Pot * ParsePot(const char * s);
  void print();
  double value();
  int isconst();
 private:
  char action;
};

class Fac {
 public:
  ListOf <Pot> * Factors;
  Fac();
  explicit Fac(const char * s);
  ~Fac();
  Fac * ParseFac(const char * s);
  void print();
  double value();
  int ispot();
  int isconst();
};

class Sum {
 public:
  ListOf <Fac> * Summanden;
  Sum();
  explicit Sum(const char * s);
  ~Sum();
  Sum * ParseSum(const char * s);
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
  explicit Term(const char * s);
  ~Term();
  Term * ParseTerm(const char * s);
  void print();
  double value();
  int ispot();
  int isfak();
  int issum();
  int isconst();
};

#endif  // INCLUDE_PARSETERM_HPP_
