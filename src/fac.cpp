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

/* implementation details fac */
Fac::Fac() {
  Factors = 0;
}
Fac::Fac(const char * s, int* pos) {
  ParseFac(s, pos);
}
Fac::~Fac() {
  delete(Factors);
  Factors = 0;
}
Fac * Fac::ParseFac(const char * s, int* pos) {
  Pot * potenz = new Pot(s, pos);
  Factors = new ListOf<Pot> (potenz);
  while (remaining(s, pos) > 0 && s[*pos] == '^') {
    (*pos)++;
    potenz = new Pot(s, pos);
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
