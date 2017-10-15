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
#include <conio.h>
#include <windows.h>

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

    vector <CMatriz> mainList;
    bool flagExit = false;
    int flagOption = 0;
    int firstMatrix, secondMatrix;
    string fileName;

    while (!flagExit)
    {

        system("cls");
        cout << "TMAB 2017.2 - TRABALHO 3 - CALCULADORA DE MATRIZES" << endl;
        cout << "Autores: Diogo Nocera Magalhaes e Bruno Machado Afonso" << endl;
        cout << "\n" << "M E N U   P R I N C I P A L" << "\n\n" << endl;
        cout << "1 - CARREGAR MATRIZES DE ARQUIVO DE LISTA" << endl;
        cout << "2 - APAGAR LISTA CARREGADA" << endl;
        cout << "3 - GRAVAR LISTA EM NOVO ARQUIVO" << endl;
        cout << "4 - REALIZAR SOMA DE MATRIZES ( + )" << endl;
        cout << "5 - REALIZAR MULTIPLICACAO DE MATRIZ POR ESCALAR ( * )" << endl;
        cout << "6 - REALIZAR MULTIPLICACAO DE MATRIZES ( * )" << endl;
        cout << "7 - TRANSPOSTA DE MATRIZ ( ~ )" << endl;
        cout << "8 - EXIBIR UMA MATRIZ DA LISTA" << endl;
        cout << "9 - EXIBIR A LISTA COMPLETA" << endl;
        cout << "0 - S A I R \n\n" << endl;
        cout << "OPCAO:  ";
        cin >> flagOption;

        if (flagOption == 1)
        {
            system("cls");
            cout << "DIGITE O NOME DO AQUIVO (INCLUINDO '.txt', ARQUIVO PRECISA ESTAR NO MESMO DIRETORIO DO EXECUTAVEL) \n" << endl;
            cout << "NOME DO ARQUIVO:  ";
            cin >> fileName;
            mainList = lerLista(fileName);

            system("cls");
            cout << "LISTA ACESSADA! \n\n" << endl;
            cout << "Pressione ENTER para continuar ... " << endl;
            getch();
        }
        else if (flagOption == 2)
        {
            mainList.resize(0);

            system("cls");
            cout << "LISTA ZERADA! \n\n" << endl;
            cout << "Pressione ENTER para continuar ... " << endl;
            getch();
        }
        else if (flagOption == 3)
        {
            system("cls");
            cout << "DIGITE O NOME DO AQUIVO (INCLUINDO '.txt') \n" << endl;
            cout << "NOME DO ARQUIVO:  ";
            cin >> fileName;
            gravarLista(fileName, mainList);

            system("cls");
            cout << "LISTA GRAVADA! \n\n" << endl;
            cout << "Pressione ENTER para continuar ... " << endl;
            getch();
        }
        else if (flagOption == 4)
        {
            system("cls");
            cout << "ESCOLHA O PRIMEIRO NUMERO DA MATRIZ DA LISTA: \n" << endl;
            cout << "NUMERO:  ";
            cin >> firstMatrix;
            cout << "ESCOLHA O SEGUNDO NUMERO DA MATRIZ DA LISTA: \n" << endl;
            cout << "NUMERO:  ";
            cin >> secondMatrix;

            system("cls");
            cout << "RESULTADO \n\n" << endl;
            CMatriz tmp_mat = mainList[firstMatrix-1] + mainList[secondMatrix-1];
            mainList.push_back(tmp_mat);
            cout << tmp_mat << endl;

            cout << "Pressione ENTER para continuar ... " << endl;
            getch();
        }
        else if (flagOption == 5)
        {
            system("cls");
            cout << "ESCOLHA O PRIMEIRO NUMERO DA MATRIZ DA LISTA: \n" << endl;
            cout << "NUMERO:  ";
            cin >> firstMatrix;
            cout << "ESCOLHA O ESCALAR PARA MULTIPLICACAO: \n" << endl;
            cout << "NUMERO:  ";
            cin >> secondMatrix;

            system("cls");
            cout << "RESULTADO \n\n" << endl;
            CMatriz tmp_mat = mainList[firstMatrix-1] * secondMatrix;
            mainList.push_back(tmp_mat);
            cout << tmp_mat << endl;

            cout << "Pressione ENTER para continuar ... " << endl;
            getch();
        }
        else if (flagOption == 6)
        {
            system("cls");
            cout << "ESCOLHA O PRIMEIRO NUMERO DA MATRIZ DA LISTA: \n" << endl;
            cout << "NUMERO:  ";
            cin >> firstMatrix;
            cout << "ESCOLHA O SEGUNDO NUMERO DA MATRIZ DA LISTA: \n" << endl;
            cout << "NUMERO:  ";
            cin >> secondMatrix;

            system("cls");
            cout << "RESULTADO \n\n" << endl;
            CMatriz tmp_mat = mainList[firstMatrix-1] * mainList[secondMatrix-1];
            mainList.push_back(tmp_mat);
            cout << tmp_mat << endl;

            cout << "Pressione ENTER para continuar ... " << endl;
            getch();
        }
        else if (flagOption == 7)
        {
            system("cls");
            cout << "ESCOLHA O NUMERO DA MATRIZ DA LISTA: \n" << endl;
            cout << "NUMERO:  ";
            cin >> firstMatrix;

            system("cls");
            cout << "RESULTADO \n\n" << endl;
            CMatriz tmp_mat = ~mainList[firstMatrix-1];
            mainList.push_back(tmp_mat);
            cout << tmp_mat << endl;

            cout << "Pressione ENTER para continuar ... " << endl;
            getch();
        }
        else if (flagOption == 8)
        {
            system("cls");
            cout << "ESCOLHA O NUMERO DA MATRIZ DA LISTA: \n" << endl;
            cout << "NUMERO:  ";
            cin >> firstMatrix;

            system("cls");
            cout << "EXIBINDO \n\n" << endl;
            cout << mainList[firstMatrix-1] << endl;

            cout << "Pressione ENTER para continuar ... " << endl;
            getch();
        }
        else if (flagOption == 9)
        {

            system("cls");
            cout << "EXIBINDO \n\n" << endl;

            for (int i = 0; i < mainList.size(); i++)
            {
                cout << "MATRIZ #" << i+1 << endl;
                cout << mainList[i] << endl << endl;
            }

            cout << "Pressione ENTER para continuar ... " << endl;
            getch();
        }
        else if (flagOption == 0)
        {
            flagExit = true;
        }

    }

	return 0;
}


