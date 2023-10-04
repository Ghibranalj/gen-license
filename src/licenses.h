#ifndef LICENSES_H_
#define LICENSES_H_
#include <stdlib.h>


#include "licenses/gpl2.h"
#include "licenses/mit.h"

static char const *LICENSES = "Available Licenses:\n"
                              "1) MIT License\n"
                              "2) GNU General Public License v2\n"
                              "";

static inline const char *get_license_stub(int input) {
  char const *ret;
  switch (input) {
  case 1:
    ret = MIT;
    break;
  case 2:
    ret = GPL2;
    break;
  default:
    exit(1);
    break;
  }
  return ret;
}

#endif // LICENSES_H_
