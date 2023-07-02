/*
 * $Id: parseterm.cpp,v 1.5 2004/01/20 19:54:33 ulrich Exp $
 * Copyright (C) Ulrich Schwickerath
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * This code comes with absolutly no warranty!
 * it should not be used for production purposes whatsoever
 *
 */

#ifndef INCLUDE_PARSETERM_HPP_
#define INCLUDE_PARSETERM_HPP_
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "./nodes.hpp"

class Term;  // forward declaration

class Pot {
 public:
  Term * Bracket;
  Pot * Potenz;
  char  VName;
  double Constant;
  Pot();
  explicit Pot(const char * s, int* pos);
  ~Pot();
  Pot * ParsePot(const char * s, int* pos);
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
  explicit Fac(const char * s, int* pos);
  ~Fac();
  Fac * ParseFac(const char * s, int* pos);
  void print();
  double value();
  int ispot();
  int isconst();
};

class Sum {
 public:
  ListOf <Fac> * Summanden;
  Sum();
  explicit Sum(const char * s, int* pos);
  ~Sum();
  Sum * ParseSum(const char * s, int* pos);
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
  explicit Term(const char * s, int* pos);
  ~Term();
  Term * ParseTerm(const char * s, int* pos);
  void print();
  double value();
  int ispot();
  int isfak();
  int issum();
  int isconst();
};

#endif  // INCLUDE_PARSETERM_HPP_
