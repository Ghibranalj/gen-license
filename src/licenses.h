#ifndef LICENSES_H_
#define LICENSES_H_
#include <stdio.h>
#include <stdlib.h>

#include "licenses/agpl3.h"
#include "licenses/apache2.h"
#include "licenses/boost.h"
#include "licenses/bsd2.h"
#include "licenses/bsd3.h"
#include "licenses/cc.h"
#include "licenses/epl2.h"
#include "licenses/gpl2.h"
#include "licenses/gpl3.h"
#include "licenses/lgpl2_1.h"
#include "licenses/mit.h"
#include "licenses/mpl2.h"
#include "licenses/unlicense.h"

static char const *LICENSES = "Available Licenses:\n"
                              "1)  Apache License v2.0\n"
                              "2)  BSD 2-Clause \"Simplified\" License\n"
                              "3)  BSD 3-Clause \"New\" or \"Revised\" License\n"
                              "4)  Boost Software License v1.0\n"
                              "5)  Creative Commons Zero v1.0 Universal\n"
                              "6)  Eclipse Public License v2.0\n"
                              "7)  GNU General Public License v2\n"
                              "8)  GNU General Public License v3\n"
                              "9)  GNU Affero General Public License v3\n"
                              "10) GNU Lesser General Public License v2.1\n"
                              "11) MIT License\n"
                              "12) Mozilla Public License v2.0\n"
                              "13) Unlicense\n"
                              "";

static inline const char *get_license_stub(int input) {
  char const *ret;
  switch (input) {
  case 1:
    ret = APACHE2;
    break;
  case 2:
    ret = BSD2;
    break;
  case 3:
    ret = BSD3;
    break;
  case 4:
    ret = BOOST;
    break;
  case 5:
    ret = CC;
    break;
  case 6:
    ret = EPL2;
    break;
  case 7:
    ret = GPL2;
    break;
  case 8:
    ret = GPL3;
    break;
  case 9:
    ret = AGPL3;
    break;
  case 10:
    ret = LGPL2_1;
    break;
  case 11:
    ret = MIT;
    break;
  case 12:
    ret = MPL2;
    break;
  case 13:
    ret = UNLICENSE;
    break;
  default:
    fprintf(stderr, "%d is not valid\n", input);
    exit(1);
    break;
  }
  return ret;
}

#endif // LICENSES_H_
