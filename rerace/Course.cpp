/*
 *  Course.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/28/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "Course.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

Course::Course(int levelNum)
{
	// Read in points from file
	string levelString = "level"+levelNum;
	ifstream level(levelString.c_str());
	if(!level)
	{
		cerr<<"Can not open level file: level"<<levelNum<<endl;
	}
	
	/* Point layout:
	 * End points: A
	 * Control points B and C respectively
	 * Ax Az Bx Bz Cx Cz
	 */
	
	string nextNum;
	while(level>>nextNum)
	{
		for(int i=0; i<8; i++)
		{
			//_points[i
			
		}
	 
	}
}

void Course::draw()
{
	
}