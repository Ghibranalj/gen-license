#ifndef GEN_LICENSE_H
#define GEN_LICENSE_H

#define NAME_STUB "[fullname]"
#define YEAR_STUB "[year]"

char *ask_user(char *prompt, char *fallback);
char *replace_stubs(char const *input, const char *name, const char *year);
int current_year();
void write_license(const char *license);
char *git_username();
void print_license();

#endif // GEN_LICENSE_H
