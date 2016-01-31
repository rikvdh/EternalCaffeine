//Copyright 2016 Dakota Simonds
//date: Jan 14, 2016
//description: This library is used for the loading and parsing of drinks.txt
/************************************************************************
* This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*************************************************************************/

#ifndef EC_DRINKS
#define EC_DRINKS


struct drink
{
	char *drinkName;
	double caffeinePerOZ;
};


double caffeine_content(const int drink, const int ounces, struct drink drink_table[])
{
	return drink_table[drink].caffeinePerOZ * ounces;
}

//
//file loading and parsing

unsigned int count_lines(FILE *fp)
{
	if(fp == NULL)
		return 0;
	unsigned int count = 0;
	while(!feof(fp))
		if(fgetc(fp) == '\n')
			count++;
	rewind(fp);
	return count;
}

char* scalpel(char *string, size_t beginpos, size_t endpos) //the bounds are exclusive because we don't want to include the tokens
{
    const int MAKE_EXCLUSIVE = 1;
    const short SPACE_FOR_NULL = 1;
    if(beginpos > 0)
    	    beginpos = beginpos + MAKE_EXCLUSIVE;
    
    size_t buffer = endpos - beginpos + SPACE_FOR_NULL;                          //  *  *  *  *  *  *  *  *
    char *choiceCut = malloc(buffer);          //* REMEMBER TO FREE THIS! *
                                                                 //  *  *  *  *  *  *  *  *
    //pour
    int i;
    size_t offset;
    for(i = 0; i < (buffer - SPACE_FOR_NULL); i++){
    	offset = i+beginpos;
        choiceCut[i] = string[offset];
    }
    choiceCut[buffer] = '\0';
    return choiceCut;
}

size_t lin_search(char *Obj, char findThis)
{
	size_t i = 0;
	while(Obj[i] != '\0'){
		if(Obj[i] == findThis)
			return i;
		i++;
	}
	
	return i;
}

double caffeine_val(char *entry)
{
	size_t begin = lin_search(entry, '=');
	size_t end   = strlen(entry);
	
	char *choicecut = scalpel(entry, begin, end);
	double caf = atof(choicecut);
	//free(choicecut); //if we free this then weird things happen... idk
	return caf;
}

char* drink_name(char *entry)
{
	size_t begin = 0;
	size_t end   = lin_search(entry, '=');
	char *name   = scalpel(entry, begin, end); // We don't need to feer this here
	return name;
}

void load_drinks(FILE *drinkfile, struct drink *drink_table)
{
	const unsigned int LINE_MAX = 512;
	char line[LINE_MAX];
	
	int i = 0;
	while(!feof(drinkfile)){
		fgets(line, LINE_MAX, drinkfile);
		drink_table[i].drinkName     = drink_name(line);
		drink_table[i].caffeinePerOZ = caffeine_val(line);
		i++;
	}
}

#endif
