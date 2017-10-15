/*
 * matriz.cpp
 *
 *  Created on: 15 de out de 2017
 *      Author: nocera
 */

#include <iostream>
#include "CMatriz.h"

using namespace std;


CMatriz::CMatriz (int col, int row, vector <vector <int> > matriz): col(col), row(row), matriz (matriz) {}

CMatriz::CMatriz (int col, int row): col(col), row(row) {}

CMatriz::CMatriz (): col(4), row(4) {}

ostream &operator<<(ostream &os, const CMatriz &rhs)
{
	for(int i(0); i < rhs.row; ++i)
	{
		for(int j(0); j < rhs.col; ++j)
			os << rhs.matriz[i][j] << '\t';
		os << endl;
	}
	return os;
}

CMatriz CMatriz::operator+(const CMatriz &rhs)
{
	vector<vector<int> > temp(row, vector<int>(col, 0));
	CMatriz Temp(col, row, temp);
	if((row != rhs.row) || (col != rhs.col))
	{
		cout << "Addition cannot be done on these matrices (dims not equal)" << endl;
		exit(1);
	}
	for(unsigned int i(0); i < Temp.row; i++)
		for(unsigned int j(0); j < Temp.col; j++)
			Temp.matriz[i][j] = matriz[i][j] + rhs.matriz[i][j];
	return Temp;
}

CMatriz &CMatriz::operator=(const CMatriz &rhs)
{
	this->matriz.resize(rhs.row);
	for(int i(0); i < this->row; ++i)
		this->matriz[i].resize(rhs.col);
	for(int i(0); i < this->row; ++i)
		for(int j(0); j < this->col; ++j)
			this->matriz[i][j] = rhs.matriz[i][j];
	this->col = rhs.col;
	this->row = rhs.row;
	return *this;
}

CMatriz CMatriz::operator*(const int &rhs)
{
	CMatriz Temp(col, row, matriz);
	for (int i=0; i< Temp.col; i++)
	{
		for (int j=0; j< Temp.row; j++)
		{
			Temp.matriz[i][j]*=rhs;
		}
	}
	return Temp;
}

CMatriz CMatriz::operator*(const CMatriz &rhs)
{
	int i, j, k;
	vector<vector<int> > temp(rhs.col, vector<int>(row, 0));
	CMatriz Temp (rhs.col, row, temp);

	if (col != rhs.row)
	{
		cout << "Wrong matrix dimensions!!" << endl;
		return Temp;
	}

	for(i = 0; i < row; ++i)
	{
		for(j = 0; j < rhs.col; ++j)
		{
			for(k=0; k<col; ++k)
			{
				Temp.matriz[i][j] += matriz[i][k] * rhs.matriz[k][j];
			}
		}
	}

	return Temp;
}

CMatriz CMatriz::operator~()
{
	CMatriz Temp(col, row, matriz);
	for (int i=0; i <col; i++)
	{
		for (int j=0; j<row; j++)
		{
			Temp.matriz [i][j] = matriz[j][i];
		}
	}
	return Temp;
}




