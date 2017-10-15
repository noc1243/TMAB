/*
 * main.cpp
 *
 *  Created on: 15 de out de 2017
 *      Author: nocera
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include "CMatriz.h"

using namespace std;

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    stringstream ss;
    ss.str(s);
    string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

vector <CMatriz> lerLista (string fileName)
{
	string line;
	ifstream myfile (fileName.c_str());
	bool isFirstLine = true, isReadingMatrixDimension = false, isReadingMatrixValue = false;;
	int numOfMatrixes, col, row, actualLine = 0, actualMatriz = 0;
	vector <CMatriz > matrizes;
	vector<vector <int> > temp (1,vector <int> (1));

	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			if (isFirstLine)
			{
				numOfMatrixes = atoi (line.c_str());
				matrizes.assign(numOfMatrixes, CMatriz ());
				isReadingMatrixDimension = true;
				isFirstLine = false;
				continue;
			}

			if (isReadingMatrixDimension)
			{
				vector<string> dimensions =  split(line, ' ');
				row = atoi (dimensions [0].c_str());
				col = atoi (dimensions [1].c_str());

				temp.resize (row);
				for (int i=0; i<row; i++)
					temp[i].resize(col);

				actualLine = 0;
				isReadingMatrixDimension = false;
				isReadingMatrixValue = true;
				continue;
			}

			if (isReadingMatrixValue)
			{
				vector<string> values =  split(line, ' ');
				for (int i = 0; i< col; i++)
				{
					temp [actualLine] [i] = atoi(values [i].c_str());
				}
				actualLine ++;
				if (actualLine == row)
				{
					matrizes [actualMatriz].matriz.assign(row, vector <int> (col,0));

					for (int i=0; i<row; i++)
						for (int j=0; j<col; j++)
							matrizes[actualMatriz].matriz[i][j] = temp[i][j];

					matrizes[actualMatriz].row = row;
					matrizes[actualMatriz].col = col;


					actualMatriz++;
					actualLine = 0;
					isReadingMatrixValue = false;
					isReadingMatrixDimension = true;
					continue;
				}
			}

	    }
		myfile.close();
	}

	else
	{
		cout << "Unable to open file";
	}

	return matrizes;
}

void gravarLista (string fileName, vector <CMatriz> matrizes)
{
	ofstream ofs (fileName.c_str(), std::ofstream::out);

	ofs << matrizes.size() << endl;

	for (int i=0; i<matrizes.size(); i++)
	{
		ofs << matrizes[i].matriz.size() << " " << matrizes[i].matriz[0].size() << endl;

		for (int j=0; j<matrizes[i].row; j++)
		{
			for (int k=0; k<matrizes[i].col; k++)
			{
				ofs << matrizes[i].matriz[j][k] << " ";
			}
			ofs << endl;
		}

	}

	ofs.close();
}

int main ()
{

	vector <CMatriz> matrizes = lerLista ("lista_1.txt");


	gravarLista ("lista_2.txt", matrizes);


	return 0;
}


