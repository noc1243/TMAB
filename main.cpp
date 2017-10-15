/*
 * main.cpp
 *
 *  Created on: 15 de out de 2017
 *      Author: nocera
 */

#include <iostream>
#include "CMatriz.h"

using namespace std;

int main ()
{
	vector<vector<int> > A(4,vector<int>(4,0));
	vector<vector<int> > B(4,vector<int>(4,0));
	vector<vector<int> > C(1,vector<int>(1,0));
	for(int i(0); i < 4; ++i)
	    for(int j(0); j < 4; ++j)
	    {
	        A[i][j] = i;
	        B[j][i] = i;
	    }
	CMatriz test(4, 4, A);
	CMatriz test2(4, 4, B);
	CMatriz test3(4, 4);
	test3 = ~test;


	cout << test3;

	return 0;
}


