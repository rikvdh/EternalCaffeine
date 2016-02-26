#ifndef TEXT_INTERFACE
#define TEXT_INTERFACE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include "drinks.h"


//#define WINDOWS //uncomment this line to look real perty in windows

//default to chars that are supported by all major OS's unless WINDOWS is define'd
#ifndef WINDOWS
#ifndef UNIVERSAL
#define UNIVERSAL
#endif
#endif


double input_double(void);
char* input_str(char inputVal[]);
void input_int(int *inputVal);
void str_mult(char stringToMult, int multBy);
char* str_mult_factory(char charToMult, size_t multBy);
void lineOf(char material);
void printToCenter(const char *text, int lengthOfString);
void display_heading(char *heading);
void display_small_heading(char *heading);
void display_menu(struct drink drink_table[], const unsigned long DRINK_COUNT);
double update(struct drink drink_table[], const unsigned long DRINK_COUNT, bool drinks_disabled_flag, bool metric_flag);
void give_report(double caffeineAmount, double caffeineTotal);
int calc_percentage(double numerator, double denominator);

#endif