#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gen-license.h"
#include "licenses.h"

int main() {
  // ask for which license
  print_license();
  char *license = ask_user("Select License: ", "");
  int sel = atoi(license) - 1;
  free(license);

  if (sel < 0 || sel > (int)(sizeof(licenses) / sizeof(licenses[0]))) {
    puts("Error: Invalid license");
    return 1;
  }
  char *license_text = licenses[sel].body;

  char prompt[256] = {};
  char *gitname = git_username();
  if (gitname != NULL) {
    sprintf(prompt, "Enter your name (%s): ", gitname);
  } else {
    strcpy(prompt, "Enter your name: ");
  }

  char *name = ask_user(prompt, gitname);
  free(gitname);

  // year stuff
  char year[5] = {};
  sprintf(year, "%d", current_year());
  sprintf(prompt, "Enter year (%s): ", year);
  char *year_input = ask_user(prompt, year);

  char *complete_license = replace_stubs(license_text, name, year_input);

  free(year_input);
  free(name);

  write_license(complete_license);
  free(complete_license);
}

void write_license(const char *license) {
  char filename[256];
  char *git_root = git_root_dir();
  if (git_root == NULL) {
    strcpy(filename, "LICENSE");
  } else {
    strcpy(filename, git_root);
    strcat(filename, "/LICENSE");
    free(git_root);
  }

  FILE *license_file = fopen(filename, "r");

  if (license_file != NULL) {
    char ansbuf[128] = {};
    printf("LICENSE file already exists. Overwrite? (y/N): ");
    fgets(ansbuf, 128, stdin);

    if (ansbuf[0] != 'y' && ansbuf[0] != 'Y') {
      fclose(license_file);
      puts("Aborting");
      return;
    }
  }
  fclose(license_file);

  license_file = fopen(filename, "w");
  if (license_file == NULL) {
    puts("Error: Could not open LICENSE file");
    return;
  }
  fputs(license, license_file);
  fclose(license_file);
}

char *replace_stubs(char const *input, const char *name, const char *year) {
  // copy the input to a new buffer
  char *input_copy = malloc(strlen(input) + 1);
  strcpy(input_copy, input);

  char *pos;

  while ((pos = strstr(input_copy, NAME_STUB)) != NULL) {
    // Calculate the lengths
    size_t nameLen = strlen(NAME_STUB);
    size_t replaceLen = strlen(name);
    size_t remainingLen = strlen(pos + nameLen);

    // Replace [name] with the provided name
    memmove(pos + replaceLen, pos + nameLen, remainingLen + 1);
    memcpy(pos, name, replaceLen);
  }

  while ((pos = strstr(input_copy, YEAR_STUB)) != NULL) {
    // Calculate the lengths
    size_t yearLen = strlen(YEAR_STUB);
    size_t replaceLen = strlen(year);
    size_t remainingLen = strlen(pos + yearLen);

    // Replace [year] with the provided year
    memmove(pos + replaceLen, pos + yearLen, remainingLen + 1);
    memcpy(pos, year, replaceLen);
  }

  return input_copy;
}

// fuck it heap allocated it is
char *ask_user(char *prompt, char *fallback) {
  char ansbuf[128] = {};

  printf("%s", prompt);

  fgets(ansbuf, 128, stdin);

  int len = strlen(ansbuf);
  if (len <= 1) {
    return strdup(fallback);
  }

  return strdup(ansbuf);
}

int current_year() {
  // Declare a tm structure to hold the current date and time
  struct tm *current_time;

  // Get the current time
  time_t now;
  time(&now);

  // Use localtime to convert the current time to a tm structure
  current_time = localtime(&now);

  // Extract the current year
  int year = current_time->tm_year + 1900;

  return year;
}

void print_license() {
  puts("Available licenses: ");
  // loop throgh licenses

  for (int i = 0; i < (int)(sizeof(licenses) / sizeof(License)); i++) {
    char *desc = licenses[i].name;
    printf("%d) %s\n", i + 1, desc);
  }
}
