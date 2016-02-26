//AUTHOR: Dakota Simonds
//DATE: Oct, 2015


/***********************************************************************
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
************************************************************************/



#include "text_interface.h"

int CONSOLE_WIDTH = 79; //makes a bit of an assumption here but this is pretty standard


//abstracted characters
//

#ifdef WINDOWS
const char rightPointingTriangle = 0x10;
const char leftPointingTriangle = 0x11;
const char upPointingTriangle = 0x1E;
const char downPointingTriangle = 0x1F;
const char skinnyHorizontalBrick = 0x16;
const char leftElbow = 0x1C;
const char littleDownRightElbow = 0xA9;
const char littleDownLeftElbow = 0xAA;
const char verySoftCloud = 0xb0;
const char softCloud = 0xB1;
const char hardCloud = 0xB2;
const char pipe = 0xB3;
const char solidBlock = 0xFE;
const char solidTallBlock = 0xDB;
const char threeBars = 0xF0;
const char longDash = 0xC4;
const char topLeftCorner = 0xDA;
const char topRightCorner = 0xBF;
const char bottomLeftCorner = 0xC0;
const char bottomRightCorner = 0xD9;
const char doubledArrows = 0xAF;
#endif

#ifdef UNIVERSAL
//Fill it in with something roughly equivalent so it doesn't look like complete garbage
const char rightPointingTriangle = '>';
const char leftPointingTriangle = '<';
const char upPointingTriangle = '^';
const char downPointingTriangle = ' ';
const char skinnyHorizontalBrick = '=';
const char leftElbow = ' ';
const char littleDownRightElbow = ' ';
const char littleDownLeftElbow = ' ';
const char verySoftCloud = '=';
const char softCloud = '=';
const char hardCloud = '#';
const char pipe = '|';
const char solidBlock = '#';
const char solidTallBlock = '#';
const char threeBars = '=';
const char longDash = '-';
const char topLeftCorner = ' ';
const char topRightCorner = ' ';
const char bottomLeftCorner = ' ';
const char bottomRightCorner = ' ';
const char doubledArrows = '>';
#endif

//
//end abstracted chars



//input functions. self explanitory
//
double input_double(void)
{
	putchar(doubledArrows);
	double inputVal;
	scanf("%lf", &inputVal);
	
	return inputVal;
}

char* input_str(char inputVal[])
{
	putchar(doubledArrows);
	scanf("%32s", inputVal);
	return inputVal;
}


void input_int(int *inputVal)
{
	putchar(doubledArrows);
	scanf("%d", inputVal);
}


void str_mult(char stringToMult, int multBy) //string multiplication. mulitpilcation as in reproduction not math.
{
	for(int i = 0; i < multBy; i++)
		putchar(stringToMult);
}

//like str_mult but returns the string instead of printing it.
char* str_mult_factory(char charToMult, size_t multBy) 
{
	const short SIZE_OF_NULL = 1;                     //   *  *  *  *  *  *  *  *
	char *multstring = malloc(multBy + SIZE_OF_NULL); // * REMEMBER TO FREE THIS *
	                                                  //   *  *  *  *  *  *  *  *
	
	for(int i = 0; i < multBy; i++)
		multstring[i] = charToMult;
	
	//ensure null-termination
	multstring[multBy] = '\0'; //My first solution was to add SIZE_OF_NULL but that is not needed becuase of zero-indexing
	
	return multstring; //remember to free() this after use
}

void lineOf(char material)
{
	str_mult(material, CONSOLE_WIDTH);
	printf("\n");
}

void printToCenter(const char *text, int lengthOfString)
{
	// essentially find center of string and align that with center of console
	int centerOfConsole = CONSOLE_WIDTH / 2;
	int numbSpace = centerOfConsole - (lengthOfString / 2 ); 
	
	for(int i = 0; i < numbSpace;i++)
		printf(" ");
	printf("%s", text);
}

//displays the header. Could be used elsewhere but not much reason too
void display_heading(char *heading)
{
	if(heading == NULL){
		fprintf(stderr, "Invalid heading in function display_heading\n");
		return;
	}
	
	lineOf(longDash);
	printToCenter(heading, strlen(heading));
	lineOf(longDash);
}

//displays a small header that has a border only slightly bigger than the text
void display_small_heading(char *heading)
{
	size_t headSize = strlen(heading);
	
	if(heading == NULL || headSize == 0){
		fprintf(stderr, "Invalid heading in function display_small_heading\n");
		return;
	}
	
	size_t borderSize = headSize + 4; //add 4 because I want a little extra on each side of the border.
	
	char *border = str_mult_factory(solidBlock, borderSize);
	
	printToCenter(border, borderSize);
	putchar('\n');
	printToCenter(heading, headSize);
	putchar('\n');
	printToCenter(border, borderSize);
	putchar('\n');
	
	free(border);
}


void display_menu(struct drink drink_table[], const unsigned long DRINK_COUNT)
{
	printf("Caffeine content in coffee can vary between roast, harvest, and company.\n\n");
	
	for(int i = 0; i < DRINK_COUNT; ++i)
		printf("%-2d %s\n", i, drink_table[i].drinkName);
	
}

//gets new amount of caffeine from the user. Entry point for the menu system.
//I initially intended something a bit more ambitious than an if/else chain
//and plan on doing something fancier in the future.
double update(struct drink drink_table[], const unsigned long DRINK_COUNT, bool drinks_disabled_flag, bool metric_flag) 
{
	enum{
		MANUAL,
		MENU
	};
	
	int choice = MANUAL;
	double caffeine = 0.0;
	const float ML_IN_ONE_OUNCE = 29.5735;
	
	
	if(!drinks_disabled_flag){
		puts("0  Manualy enter caffeine");
		puts("1  Choose from drinks");
		printf("menu");
		input_int(&choice);
	}
	
	if(choice == MANUAL){
		
		do{
			printf("Enter amount of caffeine in milligrams\n");
			printf("amount");
			caffeine = input_double();
		} while(caffeine <= 0.0);
		
	}else if (choice == MENU){
		
		display_small_heading("DRINKS MENU");
		int selection;
		display_menu(drink_table, DRINK_COUNT);
		
		printf("drink");
		input_int(&selection);
		
		int fluidAmount;
		if(metric_flag){
			printf("milliliters");
			input_int(&fluidAmount);
			fluidAmount = fluidAmount / ML_IN_ONE_OUNCE;
		}else{
			printf("fluid ounces");
			input_int(&fluidAmount);
		}
		
		
		caffeine = caffeine_content(selection, fluidAmount, drink_table);
		
	}
	
	return caffeine;
}

//calculates the percentage of the numerator to the denominator. Seems to round up/ceil.
int calc_percentage(double numerator, double denominator) 
{
	if(numerator <= 0.0 || denominator <= 0.0)
		return 0;
	
	//cross multiply and divide
	int percent = numerator * 100;
	percent = percent / denominator;
	percent = 100 - percent;
	
	return percent;
}

//gives a report
void give_report(double caffeineAmount, double caffeineTotal)
{
	printf("Total consumed %.02lfmg\n", caffeineTotal);
	
	double decay = (caffeineTotal - caffeineAmount);
	printf("Total decayed %.02lfmg ", decay);
	
	int percent = calc_percentage(caffeineAmount, caffeineTotal);
	printf("(%d%%)\n", percent);
	
	printf("Current active caffeine %.02lfmg\n", caffeineAmount);
}

