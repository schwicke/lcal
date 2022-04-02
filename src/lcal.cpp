/*
 * $Id: lcal.C,v 1.5 2004/01/20 19:54:33 ulrich Exp $
 * Copyright (C) Ulrich Schwickerath <ulrich dot Schwickerath at web dot de>
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
 * USAGE:
 * example:
 * lcal "4*atan(1)"
 *
 *  todo:
 *  -include support for variables
 *  -implement rules
 *  ...
 */
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "./parseterm.hpp"


int main(int narg, char *argv[]) {
    if ( narg > 1 ) {
      const char *s = argv[1];
      Term *t = new Term (s);
      std::cout << t->value() << std::endl;
      if ( t->isconst() ) {
        std::cout << "Expression was not numeric" << std::endl;
      }
      // t->print();std::cout <<std::endl;
      delete(t);
    }
}
