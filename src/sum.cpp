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

/* implementation part for sum */
Sum::Sum() {
  Summanden = 0;
}
Sum::Sum(const char * s, int* pos) {
  ParseSum(s, pos);
}
Sum::~Sum() {
  delete(Summanden);
  Summanden = 0;
}
Sum * Sum::ParseSum(const char * s, int* pos) {
  Fac * faktor = new Fac(s, pos);
  Summanden = new ListOf<Fac> (faktor);
  char action;
  while (remaining(s, pos) >0 && (s[*pos] == '*' || s[*pos] == '/')) {
    action = s[*pos];
    (*pos)++;
    faktor = new Fac(s, pos);
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

