#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 255
#define CURR_YEAR 2004

int main() {
  char szLine[MAX_LINE_SIZE];
  char* delimiters = " \t\n";
  char* pszName;
  char* pszYear;
  int year;

  while (fgets(szLine, MAX_LINE_SIZE, stdin)) {
    printf("> %s", szLine);
    pszName = strtok(szLine, delimiters);
    pszYear = strtok(NULL, delimiters);
    if (pszName == NULL || pszYear == NULL)
    {
        fprintf(stderr, "Error: Not enough parameters\n");
    }
    year = atoi(pszYear);
    if (year == 0)
    {
        fprintf(stderr, "Error: Invalid year\n");
    }
    printf("%s is %d years old.\n", pszName, CURR_YEAR - year);
  }
  return 0;
}   /* main() */


