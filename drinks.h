#ifndef EC_DRINKS
#define EC_DRINKS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

struct drink
{
	char *drinkName;
	double caffeinePerOZ;
};

double caffeine_content(const int drink, const int ounces, struct drink drink_table[]);
unsigned int count_lines(FILE *fp);
char* scalpel(char *string, size_t beginpos, size_t endpos);
size_t lin_search(char *Obj, char findThis);
double caffeine_val(char *entry);
char* drink_name(char *entry);
void load_drinks(FILE *drinkfile, struct drink *drink_table, bool drinks_disabled_flag);



#endif
