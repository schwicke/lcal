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

#include <math.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include "./parseterm.hpp"

// implementation of Pot
Pot::Pot() {
  Bracket = 0;
  Potenz = 0;
}

Pot::Pot(char * &s) {
  Bracket = 0;
  Potenz = 0;
  ParsePot(s);
}

Pot::~Pot() {
  delete(Bracket);
  delete(Potenz);
  Bracket = 0;
  Potenz = 0;
}

Pot * Pot::ParsePot(char * &s ) {
  // constances
  switch (*s) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case 'e':
  case 'P':
    if (*s !='e' && *s !='P') {
      Constant = strtod(s, &s);
      action = 'c';
    } else if (*s == 'e') {
      if (strlen(s) <= 1 || strlen(s) > 1 && *(s+1) != 'x') {
        Constant = exp(1.);
        s++;
        action = 'c';
      }
    } else if (strlen(s) > 1 && *++s == 'i') {
      Constant = 4.*atan(1.);
      action = 'c';
      s++;
    }
    break;
  case '(':
    s++;
    Bracket = new Term();
    Bracket->ParseTerm(s);
    if (strlen(s) > 0 && *s == ')') {
      s++;
    } else {
      std::cout << "no matching closing Bracket found" << std::endl;
    }
    action = '(';
    break;
  case '-': case '+':
    action = *s;
    s++;
    Potenz = new Pot();
    Potenz->ParsePot(s);
    break;
  case 'x': case 'y': case 'z':
    // variables x, y, z
    VName = *s;
    action = 'V';
    s++;
    break;
  case 's': case 'c': case 't': case 'a': case 'l': case 'p':
    // function call
    if ( strlen(s) > 6 ) {
      if ( !strncmp("log10(", s, 6) ) {
        s+=6;
        Bracket = new Term();
        Bracket->ParseTerm(s);
        if (strlen(s) > 0 && *s == ')') {
    s++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
        }
        action = 'l';
      }
    }
    if (strlen(s) > 5) {
      if (!strncmp("atan(", s, 5)) {
        s+=5;
        Bracket = new Term();
        Bracket->ParseTerm(s);
        if (strlen(s) > 0 && *s == ')') {
          s++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
        }
        action = 'a';
      } else if ( !strncmp("asin(", s, 5) ) {
        s+=5;
        Bracket = new Term();
        Bracket->ParseTerm(s);
        if (strlen(s) > 0 && *s == ')') {
          s++;
        } else {
    std::cout << "no matching closing Bracket found" << std::endl;
        }
        action = '1';
      } else if ( !strncmp("acos(", s, 5) ) {
        s+=5;
        Bracket = new Term();
        Bracket->ParseTerm(s);
        if ( strlen(s) > 0 && *s == ')' ) {
          s++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
        }
        action = '2';
      } else if ( !strncmp("sinh(", s, 5) ) {
        s+=5;
        Bracket = new Term();
        Bracket->ParseTerm(s);
        if ( strlen(s) > 0 && *s == ')' ) {
          s++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
        }
        action = '3';
      } else if ( !strncmp("cosh(", s, 5) ) {
        s+=5;
        Bracket = new Term();
        Bracket->ParseTerm(s);
        if (strlen(s) > 0 && *s == ')') {
          s++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
        }
        action = '4';
      } else if ( !strncmp("tanh(", s, 5) ) {
        s+=5;
        Bracket = new Term();
        Bracket->ParseTerm(s);
        if (strlen(s) > 0 && *s == ')') {
          s++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
        }
        action = '5';
      } else if ( !strncmp("sqrt(", s, 5) ) {
        s+=5;
        Bracket = new Term();
        Bracket->ParseTerm(s);
        if ( strlen(s) > 0 && *s == ')' ) {
          s++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
        }
        action = 'r';
      }
    }
    if (strlen(s) > 4) {
      if ( !strncmp("sin(", s, 4) ) {
        s+=4;
        Bracket = new Term();
        Bracket->ParseTerm(s);
        if (strlen(s) > 0 && *s == ')') {
          s++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
        }
        action = 's';
      } else if ( !strncmp("cos(", s, 4) ) {
        s+=4;
        Bracket = new Term();
        Bracket->ParseTerm(s);
        if (strlen(s) > 0 && *s == ')') {
          s++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
        }
        action = 'o';
      } else if ( !strncmp("tan(", s, 4) ) {
        s+=4;
        Bracket = new Term();
        Bracket->ParseTerm(s);
        if (strlen(s) > 0 && *s == ')') {
          s++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
        }
        action = 't';
      } else if ( !strncmp("log(", s, 4) ) {
        s+=4;
        Bracket = new Term();
        Bracket->ParseTerm(s);
        if (strlen(s) > 0 && *s == ')') {
          s++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
        }
        action = 'e';
      }
    }
    break;

  default:
    std::cout << "Syntax error" << std::endl;
  }
  return this;
}

void Pot::print() {
  char * VValue;
  switch ( action ) {
  case '+':
    Potenz->print();
    break;
  case '-':
    std::cout << "-";
    Potenz->print();
    break;
  case '(':
    std::cout << "(";
    Bracket->print();
    std::cout << ")";
    break;
  case 'c':
    std::cout << Constant;
    break;
  case 'V':
    VValue = getenv(&VName);
    if (VValue != NULL) {
      std::cout << "(";
      Term *t = new Term(VValue);
      t->print();
      std::cout << ")";
    } else {
      std::cout << &VName;
    }
    break;
  case 'l':
    std::cout << "log10("; Bracket->print(); std::cout << ")";
    break;
  case 'e':
    std::cout << "log("; Bracket->print(); std::cout << ")";
    break;
  case 's':
    std::cout << "log("; Bracket->print(); std::cout << ")";
    break;
  case 'o':
    std::cout << "cos("; Bracket->print(); std::cout << ")";
    break;
  case 't':
    std::cout << "tan("; Bracket->print(); std::cout << ")";
    break;
  case 'a':
    std::cout << "atan("; Bracket->print(); std::cout << ")";
    break;
  case '1':
    std::cout << "asin("; Bracket->print(); std::cout << ")";
    break;
  case '2':
    std::cout << "acos("; Bracket->print(); std::cout << ")";
    break;
  case '3':
    std::cout << "sinh("; Bracket->print(); std::cout << ")";
    break;
  case '4':
    std::cout << "cosh("; Bracket->print(); std::cout << ")";
    break;
  case '5':
    std::cout << "tanh("; Bracket->print(); std::cout << ")";
    break;
  case 'r':
    std::cout << "sqrt("; Bracket->print(); std::cout << ")";
    break;
  }
}
double Pot::value() {
  double result;
  char * VValue;
  switch ( action ) {
  case '+':
    return Potenz->value();
    break;
  case '-':
    return -Potenz->value();
    break;
  case '(':
    return Bracket->value();
    break;
  case 'c':
    return Constant;
    break;
  case 'V':
    result = 0.0;
    VValue = getenv(&VName);
    if (VValue != NULL) {
      Term *t = new Term(VValue);
      return(t->value());
    } else {
      std::cout << "unknown variable" << std::endl;
      return(0.0);
    }
    break;
  case 'l':
    return log10(Bracket->value());
    break;
  case 'e':
    return log(Bracket->value());
    break;
  case 's':
    return sin(Bracket->value());
    break;
  case 'o':
    return cos(Bracket->value());
    break;
  case 't':
    return tan(Bracket->value());
    break;
  case 'a':
    return atan(Bracket->value());
    break;
  case '1':
    return asin(Bracket->value());
    break;
  case '2':
    return acos(Bracket->value());
    break;
  case '3':
    return sinh(Bracket->value());
    break;
  case '4':
    return cosh(Bracket->value());
    break;
  case '5':
    return tanh(Bracket->value());
    break;
  case 'r':
    return sqrt(Bracket->value());
    break;
  }
  return(0);
}

int Pot::isconst() {
  int res = 1;  // default is : it is not a constant!
  switch (action) {
  case '+':
    return Potenz->isconst();
  case '-':
    return Potenz->isconst();
  case '(':
    return Bracket->isconst();
    break;
  case 'c':
    return(0);
    break;
  case 'V':
    return(1);  // a variable
    break;
  case 'l':
    return Bracket->isconst();
    break;
  case 'e':
    return Bracket->isconst();
    break;
  case 's':
    return Bracket->isconst();
    break;
  case 'o':
    return Bracket->isconst();
    break;
  case 't':
    return Bracket->isconst();
    break;
  case 'a':
    return Bracket->isconst();
    break;
  case '1':
    return Bracket->isconst();
    break;
  case '2':
    return Bracket->isconst();
    break;
  case '3':
    return Bracket->isconst();
    break;
  case '4':
    return Bracket->isconst();
    break;
  case '5':
    return Bracket->isconst();
    break;
  case 'r':
    return Bracket->isconst();
    break;
  }
  return(0);
}

/* implementation details fac */
Fac::Fac() {
  Factors = 0;
}
Fac::Fac(char * &s) {
  ParseFac(s);
}
Fac::~Fac() {
  delete(Factors);
  Factors = 0;
}
Fac * Fac::ParseFac(char * &s) {
  Pot * potenz = new Pot(s);
  Factors = new ListOf<Pot> (potenz);
  while (strlen(s) > 0 && *s == '^') {
    s++;
    potenz = new Pot(s);
    Factors->add_elem(potenz, '^');
  }
  return(NULL);
}

double Fac::value() {
  Pot * potenz = (Factors->first_node())->element();
  double val = potenz->value();
  Factors->move_next();
  Node <Pot>* i = Factors->current_node();
  while (i != 0) {
    val = pow(val, i->element()->value());
    Factors->move_next();
    i = Factors->current_node();
  }
  Factors->reset();
  return val;
}

void Fac::print() {
  Pot * potenz = (Factors->first_node())->element();
  potenz->print();
  Factors->move_next();
  Node <Pot>* i = Factors->current_node();
  while (i != 0) {
    std::cout << "^";
    i->element()->print();
    Factors->move_next();
    i = Factors->current_node();
  }
  Factors->reset();
}

int Fac::ispot() {
  return(Factors->is_first() & Factors->is_last());
}

int Fac::isconst() {
  int res = 0;
  Node<Pot> * i = Factors->first_node();
  while (i != 0) {
    res += (i->element())->isconst();
    Factors->move_next();
    i = Factors->current_node();
  }
  return(res);
}

/* implementation part for sum */
Sum::Sum() {
  Summanden = 0;
}
Sum::Sum(char * &s) {
  ParseSum(s);
}
Sum::~Sum() {
  delete(Summanden);
  Summanden = 0;
}
Sum * Sum::ParseSum(char * &s) {
  Fac * faktor = new Fac(s);
  Summanden = new ListOf<Fac> (faktor);
  char action;
  while (strlen(s) >0 && (*s == '*' || *s == '/')) {
    action = *s;
    s++;
    faktor = new Fac(s);
    Summanden->add_elem(faktor, action);
  }
  return(NULL);
}

void Sum::print() {
  Fac * faktor = (Summanden->first_node())->element();
  faktor->print();
  Summanden->move_next();
  Node<Fac>* i = Summanden->current_node();
  while (i !=0) {
    if (i->action == '*') {
      std::cout << "*";
    } else {
      std::cout << "/";
    }
    i->element()->print();
    Summanden->move_next();
    i = Summanden->current_node();
  }
  Summanden->reset();
}

double Sum::value() {
  Fac * faktor = (Summanden->first_node())->element();
  double val = faktor->value();
  Summanden->move_next();
  Node<Fac>* i = Summanden->current_node();
  while (i != 0) {
    if (i->action == '*') {
      val = val * i->element()->value();
    } else {
      val = val / i->element()->value();
    }
    Summanden->move_next();
    i = Summanden->current_node();
  }
  Summanden->reset();
  return val;
}

int Sum::isfak() {
  return(Summanden->is_first() & Summanden->is_last());
}

int Sum::ispot() {
  if (Summanden->is_first() & Summanden->is_last()) {
    return(((Summanden->current_node())->element())->ispot());
  } else {
    return(0);
  }
}

int Sum::isconst() {
  int res = 0;
  Node<Fac> * i = Summanden->first_node();
  while (i != 0) {
    res += (i->element())->isconst();
    Summanden->move_next();
    i = Summanden->current_node();
  }
  return(res);
}

// implementation part of Term
Term::Term() {
  Terme = 0;
}

Term::Term(char * &s) {
  ParseTerm(s);
}

Term::~Term() {
  delete(Terme);
  Terme = 0;
}

Term * Term::ParseTerm(char * &s) {
  Sum * summand = new Sum(s);
  Terme = new ListOf<Sum> (summand);
  char action;
  while (strlen(s) > 0 && (*s =='+'|| *s == '-')) {
    action = *s;
    s++;
    summand = new Sum(s);
    Terme->add_elem(summand, action);
  }
  return(NULL);
}

double Term::value() {
  Sum * summand = (Terme->first_node())->element();
  double val = summand->value();
  Terme->move_next();
  Node<Sum> * i = Terme->current_node();
  while (i != 0) {
    if (i->action == '+') {
      val = val + i->element()->value();
    } else {
      val = val - i->element()->value();
    }
    Terme->move_next();
    i = Terme->current_node();
  }
  Terme->reset();
  return val;
}

void Term::print() {
  Sum * summand = (Terme->first_node())->element();
  summand->print();
  Terme->move_next();
  Node<Sum> * i = Terme->current_node();
  while (i != 0) {
    if (i->action == '+') {
      std::cout << "+";
    } else {
      std::cout << "-";
    }
    i->element()->print();
    Terme->move_next();
    i = Terme->current_node();
  }
  Terme->reset();
}

int Term::issum() {
  return(Terme->is_first() & Terme->is_last());
}

int Term::isfak() {
  if (Terme->is_first() & Terme->is_last()) {
    return(((Terme->current_node())->element())->isfak());
  } else {
    return(0);
  }
}

int Term::ispot() {
  if (Terme->is_first() & Terme->is_last()) {
    return(((Terme->current_node())->element())->ispot());
  } else {
    return(0);
  }
}

int Term::isconst() {
  int res = 0;
  Node<Sum> * i = Terme->first_node();
  while (i != 0) {
    res += (i->element())->isconst();
    Terme->move_next();
    i = Terme->current_node();
  }
  return(res);
}
