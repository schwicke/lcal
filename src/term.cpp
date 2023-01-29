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

// implementation part of Term
Term::Term() {
  Terme = 0;
}

Term::Term(const char * s, int* pos) {
  ParseTerm(s, pos);
}

Term::~Term() {
  delete(Terme);
  Terme = 0;
}

Term * Term::ParseTerm(const char * s, int* pos) {
  Sum * summand = new Sum(s, pos);
  Terme = new ListOf<Sum> (summand);
  char action;
  while (remaining(s, pos) > 0 && (s[*pos] =='+' || s[*pos] == '-')) {
    action = s[*pos];
    (*pos)++;
    summand = new Sum(s, pos);
    Terme->add_elem(summand, action);
  }
  if (remaining(s, pos) > 0 &&
      s[*pos] != '+' &&
      s[*pos] != '-' &&
      s[*pos] != ')') {
    std::cout << "Syntax error" << std::endl;
    exit(1);
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
