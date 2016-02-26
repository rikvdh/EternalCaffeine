/************************************************************************
* Copyright 2015-2016 Dakota Simonds
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
//DATE CREATED: 10/10/2015
//C99 (I like for-loop initialization)

#define IM_ETERNAL 1

//                     *
//                  *******
//               *************
//            *******************
//         *************************
//     * *            * *            * *     
//    *   *          *   *          *   *    
//     * *            * *            * *     
//* * * * * * *  * * * * * * *  * * * * * * *
//      *              *              *      
//      *              *              *      
//      *              *              *      


//standard libs
#include <stdio.h>   //printf(), scanf(), puts(), putchar()
#include <stdlib.h>  //EXIT_SUCCESS, NULL, exit(), FILE, fopen(), fclose()
#include <time.h>    //time(), time_t
#include <string.h>  //strcmp(), strlen()
#include <stdbool.h> //bool, true, false

//my libs
#include "drinks.h"             //struct drink, caffeine_content(), count_lines(), scalpel(), 
#include "text_interface.h"     //abstracted chars, lin_search(), caffeine_val(), drink_name(), load_drinks()
#include "halflife.h"           //half_life()


//various global constants
const int INPUT_MAX = 32; //arbitrary. Seems like a generous amount.
//Biological halflife of caffeine in seconds
const double HALFLIFE_OF_CAFFEINE = 20520.0; //Every number involved in the halflife calculation NEEDS double.
                                             //The calculations can potentially be off dealing with this scale
const char *DRINK_PATH_CURRENT = "./drinks.txt";
const char *DRINK_PATH_INSTALL = "/usr/sbin/drinks.txt";


time_t  time_elapsed(time_t start);
int     string_compare(char *compareBase, const char*compareAgainst);

void usage(void)
{
	puts("INTERACTIVE COMMANDS:");
	//tab, string and justify by 7, space, string, newline
	printf("\t%-7s %s\n", "start", "Start a new recording of your caffeine levels.");
	printf("\t%-7s %s\n", "update", "Add more consumed caffeine.");
	printf("\t%-7s %s\n", "report", "Gives current caffeine in blood stream.");
	printf("\t%-7s %s\n", "wipe", "Start over.");
	printf("\t%-7s %s\n", "metric", "Toggles metric mode on and off. Default is off.");
	printf("\t%-7s %s\n", "quit", "Exits the program.");
}




int main(int argc, char *argv[])
{
	time_t startTime;
	bool started_flag = false;
	bool drinks_disabled_flag = false;
	bool metric_flag = false;
	
	//This is the variable that holds the current amount of caffeine
	//so basicly the whole program is centred around changing this
	//variable. Change with caution!
	double caffeineAmount  = 0.0;
	double caffeineTotal   = 0.0;
	double addCaffeine     = 0.0;
	double amountRemaining = 0.0;
	
	display_heading("Eternal Caffeine v2.0 <copyleft. 2015-2016>\n");
	
	if(argc > 1){ //if any arguments are give at all
		printf("I don't know what `%s' is but here is the help menu.\n", argv[1]);
		usage();
		exit(EXIT_SUCCESS);
	}
	
	puts("Enter help for usage.\n\n");
	
	
	
	
	FILE *drinkfile = fopen(DRINK_PATH_CURRENT, "r");
	
	if(drinkfile == NULL){ //try the install path
		drinkfile = fopen(DRINK_PATH_INSTALL, "r");
	}
	
	const unsigned int DRINK_COUNT = count_lines(drinkfile); //we must count the number of entries so we know how much to allocate
	struct drink drink_table[DRINK_COUNT];
	
	if(DRINK_COUNT == 0 || drinkfile == NULL){
		puts("No drinks found! Disabling drinks feature...");
		drinks_disabled_flag = true;
	} else {
		load_drinks(drinkfile, drink_table, drinks_disabled_flag);
		fclose(drinkfile);
	}
	
	
	
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
				started_flag = true;
			}
			
			startTime      = time(NULL);
			
			//add new amount
			addCaffeine    = update(drink_table, DRINK_COUNT, drinks_disabled_flag, metric_flag);
			caffeineAmount = caffeineAmount + addCaffeine;
			caffeineTotal  = caffeineTotal + addCaffeine;
			
			printf("Caffeine amount is now %.02lfmg\n", caffeineAmount);
			
		} else if( string_compare(command, "report") ){
			
			if(! started_flag ){
				puts("You have not started yet. Enter the start command!!!");
				continue;
			}
			
			amountRemaining = half_life(caffeineAmount,
			                            time_elapsed(startTime),
			                            HALFLIFE_OF_CAFFEINE);
			
			give_report(amountRemaining, caffeineTotal);
		
		} else if( string_compare(command, "quit") ){
			
			putchar('\n');
			exit(EXIT_SUCCESS);
		
		} else if( string_compare(command, "metric") ){
			metric_flag = !metric_flag; //toggle
			
			printf("Metric is now ");
			if(metric_flag){
				printf("on.\n");
			}else{
				printf("off.\n");
			}
			
		} else if( string_compare(command, "wipe") ){
			
			addCaffeine = caffeineAmount = caffeineTotal = 0.0;
			metric_flag = started_flag = false;
			
			puts("All values have been reset.");
			
		} else {
			
			puts("Command unknown. Enter help for usage.");
			continue;
			
		}
		
	}
	
	
	
	return EXIT_SUCCESS;
}



time_t time_elapsed(time_t start)
{
	return (time(NULL) - start);
}


//returns true or false. Much cleaner than the stock strcmp() function.
int string_compare(char *compareBase, const char *compareAgainst)
{
	const int MATCH = 0;
	
	return strcmp(compareBase, compareAgainst) == MATCH;
}

