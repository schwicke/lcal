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
#include "parseterm.hpp"
#include "helpers.hpp"

// implementation of Pot
Pot::Pot() {
  Bracket = 0;
  Potenz = 0;
}

Pot::Pot(const char * s, int* pos) {
  Bracket = 0;
  Potenz = 0;
  ParsePot(s, pos);
}

Pot::~Pot() {
  delete(Bracket);
  delete(Potenz);
  Bracket = 0;
  Potenz = 0;
}

Pot * Pot::ParsePot(const char* s, int* pos ) {
  // constances
  switch (s[*pos]) {
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
    if (s[*pos] !='e' && s[*pos] !='P') {
      const char * startpos = &s[*pos];
      char * finalpos;
      Constant = strtod(startpos, &finalpos);  // FIXME
      *pos = *pos + finalpos-startpos;
      action = 'c';
    } else if (s[*pos] == 'e') {
      if (remaining(s, pos) <= 1 || remaining(s, pos) > 1 && s[*pos+1] != 'x') {
        Constant = exp(1.);
        (*pos)++;
        action = 'c';
      }
    } else if (remaining(s, pos) > 1 && s[*pos+1] == 'i') {
      Constant = 4.*atan(1.);
      action = 'c';
      (*pos) += 2;
    }
    break;
  case '(':
    (*pos)++;
    Bracket = new Term();
    Bracket->ParseTerm(s, pos);
    if (remaining(s, pos) > 0 && s[*pos] == ')') {
      (*pos)++;
    } else {
      std::cout << "no matching closing Bracket found" << std::endl;
      exit(2);
    }
    action = '(';
    break;
  case '-': case '+':
    action = s[*pos];
    (*pos)++;
    Potenz = new Pot();
    Potenz->ParsePot(s, pos);
    break;
  case 'x': case 'y': case 'z':
    // variables x, y, z
    VName = s[*pos];
    action = 'V';
    (*pos)++;
    break;
  case 's': case 'c': case 't': case 'a': case 'l': case 'p':
    // function call
    if ( remaining(s, pos) > 6 ) {
      if ( !strncmp("log10(", s+*pos, 6) ) {
        (*pos) += 6;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if (remaining(s, pos) > 0 && s[*pos] == ')') {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = 'l';
      }
    }
    if (remaining(s, pos) > 5) {
      if (!strncmp("atan(", s+*pos, 5)) {
        (*pos) += 5;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if (remaining(s, pos) > 0 && s[*pos] == ')') {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = 'a';
      } else if ( !strncmp("asin(", s+*pos, 5) ) {
        (*pos) += 5;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if (remaining(s, pos) > 0 && s[*pos] == ')') {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = '1';
      } else if ( !strncmp("acos(", s+*pos, 5) ) {
        (*pos) += 5;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if ( remaining(s, pos) > 0 && s[*pos] == ')' ) {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = '2';
      } else if ( !strncmp("sinh(", s+*pos, 5) ) {
        (*pos) += 5;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if ( remaining(s, pos) > 0 && s[*pos] == ')' ) {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = '3';
      } else if ( !strncmp("cosh(", s+*pos, 5) ) {
        (*pos) += 5;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if (remaining(s, pos) > 0 && s[*pos] == ')') {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = '4';
      } else if ( !strncmp("tanh(", s+*pos, 5) ) {
        (*pos) += 5;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if (remaining(s, pos) > 0 && s[*pos] == ')') {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = '5';
      } else if ( !strncmp("sqrt(", s+*pos, 5) ) {
        (*pos) += 5;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if ( remaining(s, pos) > 0 && s[*pos] == ')' ) {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = 'r';
      }
    }
    if (remaining(s, pos) > 4) {
      if ( !strncmp("sin(", s+*pos, 4) ) {
        (*pos) += 4;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if (remaining(s, pos) > 0 && s[*pos] == ')') {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = 's';
      } else if ( !strncmp("cos(", s+*pos, 4) ) {
        (*pos) += 4;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if (remaining(s, pos) > 0 && s[*pos] == ')') {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = 'o';
      } else if ( !strncmp("tan(", s+*pos, 4) ) {
        (*pos) += 4;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if (remaining(s, pos) > 0 && s[*pos] == ')') {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = 't';
      } else if ( !strncmp("log(", s+*pos, 4) ) {
        (*pos) += 4;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if (remaining(s, pos) > 0 && s[*pos] == ')') {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = 'e';
      } else if ( !strncmp("abs(", s+*pos, 4) ) {
        (*pos) += 4;
        Bracket = new Term();
        Bracket->ParseTerm(s, pos);
        if (remaining(s, pos) > 0 && s[*pos] == ')') {
          (*pos)++;
        } else {
          std::cout << "no matching closing Bracket found" << std::endl;
          exit(2);
        }
        action = 'A';
      }
    }
    break;

  default:
    std::cout << "Syntax error" << std::endl;
    exit(1);
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
      int pos = 0;
      Term *t = new Term(VValue, &pos);
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
  case 'A':
    std::cout << "abs("; Bracket->print(); std::cout << ")";
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
      int pos = 0;
      Term *t = new Term(VValue, &pos);
      result = t->value();
      delete(t);
      return(result);
    } else {
      std::cout << "Variable "
       << VName << " is not defined. Assuming 0" << std::endl;
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
  case 'A':
    return abs(Bracket->value());
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
