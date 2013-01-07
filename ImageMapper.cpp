//this is the main app for ImageMapper.cpp
#include "ImageMapper.h"

void main()
{
	int spot(0); // the spot in the input line
	int varnum(0); //the number to the variables being generated for output
	int points(1); //number of points on the polygon
	int regions(0);	//number of regions to be declared	
	int tempReg(1);	//the temp region being generated
	int temp(0); //temp integer for walking through the allotted points
	char tempC('X'); //temp char for walking through the allotted points
	string strLine;
	ifstream fin;
	ofstream fout;
	fin.open("AllPoints.txt");
	fout.open("map.rsk");
	if (fin.fail())
	{
		cout << "Error opening input file - Terminating program.\n";
		exit(1);
	}	
	cout << "Processing \'AllPoints.txt\'\n";
	while (! fin.eof() )
	{		
		getline(fin, strLine);	//grab a line of text from the input file
		if ((strLine.length() > 15) && (strLine.at(1) == 'a') &&  (strLine.at(2) == 'r') && (strLine.at(3) == 'e') && (strLine.at(4) == 'a')
			&& (strLine.at(5) == ' ') && (strLine.at(6) == 's') && (strLine.at(7) == 'h') && (strLine.at(8) == 'a') && (strLine.at(9) == 'p')
			&& (strLine.at(10) == 'e') && (strLine.at(11) == '=') && (strLine.at(12) == '"') && (strLine.at(13) == 'p') && (strLine.at(14) == 'o')
			&& (strLine.at(15) == 'l') && (strLine.at(16) == 'y') && (strLine.at(17) == '"') )
		{	//if the first characters found are: <area shape="poly" then do the following
			regions++;
		}
	}
	fin.close();
	fin.clear(1000);
	fin.open("AllPoints.txt");
	
	cout << "Regions: " << regions << '\n';
	fout << regions << '\n';
	while (! fin.eof() )
	{		
		getline(fin, strLine);	//grab a line of text from the input file
		if ((strLine.length() > 15) && (strLine.at(1) == 'a') &&  (strLine.at(2) == 'r') && (strLine.at(3) == 'e') && (strLine.at(4) == 'a')
			&& (strLine.at(5) == ' ') && (strLine.at(6) == 's') && (strLine.at(7) == 'h') && (strLine.at(8) == 'a') && (strLine.at(9) == 'p')
			&& (strLine.at(10) == 'e') && (strLine.at(11) == '=') && (strLine.at(12) == '"') && (strLine.at(13) == 'p') && (strLine.at(14) == 'o')
			&& (strLine.at(15) == 'l') && (strLine.at(16) == 'y') && (strLine.at(17) == '"') )
		{	//if the first characters found are: <area shape="poly" then do the following
			
			points = 1;
			temp = 0;
			tempC = 'X';			
			for (int i=27; i < strLine.length(); i++)
			{	
				if (strLine.at(i) == ',')		//if there is a comma in the line
				{
					points++;					//  there is another point
				}
			}
			points /= 2;	//number of points is equal to half of those tallied, due to x,y pairs
			fout << points << ',';
			//cout << "Points on polygon: " << points << '\n';

			if (varnum > 0)
			{
				
			}						
			for (i=27; i < strLine.length(); i++)
			{					
				if ((strLine.at(i) != ',') && (strLine.at(i) != '"'))		//if there is NOT a comma AND NOT a double quote in the line
				{
					fout << strLine.at(i);	//output the character
				} 
				else
				{
					if (strLine.at(i) != '"')	//if the character is NOT a double quote
					{
						fout << strLine.at(i);
						/*if (tempC == 'X')		//and tempC is an X
						{
							tempC = 'Y';		//make tempC a Y
							//fout << " + xOff";
							fout << "\nptapi_" << varnum << "(" << temp << ")." << tempC << " = ";//and output a new point def
						}
						else	//else tempC is a Y
						{
							tempC = 'X';		//make tempC an X
							temp++;				//bump up the current point def
							//fout << " + yOff";
							fout << "\nptapi_" << varnum << "(" << temp << ")." << tempC << " = ";//and output that pt def
						}*/
					}
					else	//the character is a double quote
					{
						//fout << " + yOff";						
						//the points-1 part of the above keeps the object from streaking to 0,0												
						fout << ",-1\n";
						tempReg++;
						cout <<"\nPolygon #" << varnum+1 << " complete - " << points << " points.";	//alert the user
						i = strLine.length() + 1;							//kick out of the for loop
						varnum++;											//and increment the variable number
					}
				}
			}
		}
	}	
	fin.close();
	fout.close();	
	cout << "\n\nmap.rsk compiled for Visual Basic 6.0 use.\n";
}