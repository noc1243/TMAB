/*
 * cmatriz.h
 *
 *  Created on: 15 de out de 2017
 *      Author: nocera
 */

#ifndef CMATRIZ_H_
#define CMATRIZ_H_


#include <vector>

using namespace std;



class CMatriz
{
	public :
	int col, row;
	vector <vector <int> > matriz;
	CMatriz (int, int, vector<vector<int> > matriz);
	CMatriz (int, int);
	CMatriz ();


	friend ostream & operator<<(ostream &os, const CMatriz &rhs);
	CMatriz operator+(const CMatriz &rhs);
	CMatriz operator*(const int &rhs);
	CMatriz operator*(const CMatriz &rhs);
	CMatriz &operator=(const CMatriz &rhs);
	CMatriz operator~();

};



#endif /* CMATRIZ_H_ */
