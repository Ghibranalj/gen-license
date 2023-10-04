#ifndef GEN_LICENSE_H
#define GEN_LICENSE_H
#include "licenses.h"

#define NAME_STUB "[name]"
#define YEAR_STUB "[year]"

char *ask_user(char *prompt, char *fallback);
char *replace_stubs(char const *input, const char *name, const char *year);
int current_year();
void write_license(const char *license);

static char const *LICENSES = "Available Licenses:\n"
                              "1) MIT"
                              "";

static inline const char *get_license_stub(int input) {
  char const *ret;
  switch (input) {
  case 1:
    ret = MIT;
    break;
  default:
    ret = "";
    break;
  }

  return ret;
}

#endif // GEN_LICENSE_H
