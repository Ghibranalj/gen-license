#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "gen-license.h"


int main() {
  // ask for which license
  puts(LICENSES);
  char *license = ask_user("Select License: ", "");
  int l = atoi(license);
  free(license);

  char const *license_text = get_license_stub(l);

  char *name = ask_user("Enter your full name: ", "");

  // year stuff
  char year[5] = {};
  sprintf(year, "%d", current_year());
  char prompt[128] ={};
  sprintf(prompt, "Enter year (%s): ", year);
  char *year_input = ask_user(prompt, year);
  char* complete_license = replace_stubs(license_text, name, year_input);


  puts(complete_license);

  free(year_input);
  free(complete_license);
  free(name);
}

char* replace_stubs(char const *input, const char *name, const char *year) {
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
  char *ansbuf = malloc(128);
  memset(ansbuf, '\0', 128);

  printf("%s", prompt);

  int i = 0;
  char c = '\0';
  while ((c = getchar()) != '\n' && i < 128 - 1) {
    ansbuf[i++] = c;
  }
  if (i == 0) {
    strcpy(ansbuf, fallback);
  }

  return ansbuf;
}

int current_year(){
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
