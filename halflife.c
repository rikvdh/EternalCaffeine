//AUTHOR: Dakota Simonds
//Date: Oct 24, 2015
//Description: just one function for doing half-life calculations

/*
* This is free and unencumbered software released into the public domain.
*
* Anyone is free to copy, modify, publish, use, compile, sell, or
* distribute this software, either in source code form or as a compiled
* binary, for any purpose, commercial or non-commercial, and by any
* means.
* 
* In jurisdictions that recognize copyright laws, the author or authors
* of this software dedicate any and all copyright interest in the
* software to the public domain. We make this dedication for the benefit
* of the public at large and to the detriment of our heirs and
* successors. We intend this dedication to be an overt act of
* relinquishment in perpetuity of all present and future rights to this
* software under copyright law.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* For more information, please refer to <http://unlicense.org/>
*/

#include "halflife.h"

double half_life(double matterial, time_t timeElapsed, double periodOfHalfLife) // timeElapsed and periodOfHalfLife must be in the same unit eg. seconds
{
	if(timeElapsed <= 0.0 || matterial <= 0.0)
		return matterial;
	
	double completedHalfLifes = (double)timeElapsed  / periodOfHalfLife;
	
	double result;
	
	double reduce = pow(2.0, completedHalfLifes);
	result = matterial / reduce;
	return result;
}

