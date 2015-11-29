//Copyright 2015 Dakota Simonds
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


//AUTHOR: Dakota Simonds
//DATE: 10/10/2015
//C99 (I like for-loop initialization)

#define IM_ETERNAL 1

//                   *
//                *******
//             *************
//          *******************
//       *************************
//      _        _       _        _  
//     ( )      ( )     ( )      ( ) 
//    --*--    --*--   --*--    --*--
//      |        |       |        |  
//      |        |       |        |  


//standard libs
#include "stdio.h"   //printf scanf puts putchar
#include "stdlib.h"  //EXIT_SUCCESS NULL exit
#include "time.h"    //time
#include "string.h"  //strcmp

//my libs
//#define WINDOWS //uncomment this line to look real perty in windows
#include "text_interface.c"     //abstracted chars, printToCenter, lineOf, display_in_box, hackysizeof    
#include "halflife.c"           //half_life


//various global constants
const int INPUT_MAX = 32; //arbitrary. Seems like a generous amount.
const double HALFLIFE_OF_CAFFEINE = 20520.0; //Every number involved in the halflife calculation NEEDS double.
                                             //The calculations can potentially be off dealing with this scale

void         display_heading(char *heading);
double       update(void);
unsigned int time_elapsed(unsigned int start);
void         give_report(double caffeineAmount, double caffeineTotal);
int          string_compare(char *compareBase, const char*compareAgainst);

void usage(void)
{
	puts("INTERACTIVE COMMANDS:");
	//tab, string and justify by 9, space, string, newline
	printf("\t%-9s %s\n", "start", "Start a new recording of your caffeine levels");
	printf("\t%-9s %s\n", "update", "Add more consumed caffeine");
	printf("\t%-9s %s\n", "report", "Gives current caffeine in blood stream");
	printf("\t%-9s %s\n", "wipe", "Start over");
	printf("\t%-9s %s\n", "quit", "Exits the program");
	//printf("\t%-9s %s\n", "calc", "Do theoretical caffeine half-life calculation");
}




int main(int argc, char *argv[])
{
	unsigned int startTime;
	short started_flag = 0;
	
	//This is the variable that holds the current amount of caffeine
	//so basicly the whole program is centred around changing this
	//variable. Change with caution!
	double caffeineAmount = 0.0;
	double caffeineTotal  = 0.0;
	double addCaffeine    = 0.0;
	
	display_heading("Eternal Caffeine v0 <copyleft. 2015>\n");
	
	if(argc > 1){ //if any arguments are give at all
		usage();
		exit(EXIT_SUCCESS);
	}
	
	puts("Enter help for usage.\n\n");
	
	
	char command[INPUT_MAX];
	
	while(IM_ETERNAL){
		printf("command");
		input_str(command);
		
		if( string_compare(command, "help") ){
			
			usage();
		
		} else if ( string_compare(command, "start") || string_compare(command, "update") ){
			
			if(started_flag){
				//do halflife before add new amount
				caffeineAmount = half_life(caffeineAmount,
				                           time_elapsed(startTime),
				                           HALFLIFE_OF_CAFFEINE);
			} else {
				started_flag = 1;
			}
			
			startTime      = time(NULL);
			
			//add new amount
			addCaffeine    = update();
			caffeineAmount = caffeineAmount + addCaffeine;
			caffeineTotal  = caffeineTotal + addCaffeine;
			
			printf("Caffeine amount is now %.02lfmg\n", caffeineAmount);
			
		} else if( string_compare(command, "report") ){
			
			if(! started_flag ){
				puts("You have not started yet. Enter the start command!!!");
				continue;
			}
			
			double amountRemaining = half_life(caffeineAmount,
			                                   time_elapsed(startTime),
			                                   HALFLIFE_OF_CAFFEINE);
			
			give_report(amountRemaining, caffeineTotal);
		
		} else if( string_compare(command, "quit") ){
			
			putchar('\n');
			exit(EXIT_SUCCESS);
		
		} else if( string_compare(command, "calc") ){
			
			//note: make sure this can be done while a recording has started and it not interfere with it.
			puts("Command not yet implemented");
			
		} else if( string_compare(command, "wipe") ){
			
			addCaffeine = caffeineAmount = caffeineTotal = 0.0;
			started_flag = 0;
			puts("All values have been reset.");
			
		} else {
			
			puts("Command unknown. Enter help for usage.");
			continue;
			
		}
		
	}
	
	
	
	return EXIT_SUCCESS;
}



unsigned int time_elapsed(unsigned int start)
{
	return (time(NULL) - start);
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
	printf("Total caffeine consumed %.02lfmg\n", caffeineTotal);
	
	double decay = (caffeineTotal - caffeineAmount);
	printf("Total amount decayed %.02lfmg ", decay);
	
	int percent = calc_percentage(caffeineAmount, caffeineTotal);
	printf("(%d%%)\n", percent);
	
	printf("Current amount of caffeine in your body %.02lfmg\n", caffeineAmount);
}

//returns true or false. Much cleaner than the stock strcmp() function.
int string_compare(char *compareBase, const char *compareAgainst)
{
	const int MATCH = 0;
	
	return strcmp(compareBase, compareAgainst) == MATCH;
}

