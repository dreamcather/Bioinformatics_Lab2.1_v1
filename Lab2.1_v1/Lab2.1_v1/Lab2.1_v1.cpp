// Lab2.1_v1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

int Size_Motiv;
int Count_Examples;
int Exaples_Lenght;
char ** Examples;
int main()
{
	FILE * pFile;
	errno_t err;
	err = fopen_s(&pFile, "input.txt", "r");
	fscanf_s(pFile, "%i", &Size_Motiv);
	fscanf_s(pFile, "%i", &Count_Examples);
	char chr = '*';
	int k = 0;
	fseek(pFile, 2, SEEK_CUR);
	while ((chr != '\n')&&(k<20))
	{
		fscanf_s(pFile, "%c", &chr);
		k++;
	}
	k--;
	Exaples_Lenght = k;
	Examples = new char*[Count_Examples];
	for (int i = 0; i < Count_Examples; i++)
	{
		Examples[i] = new char[Exaples_Lenght];
	}
	fseek(pFile, -Exaples_Lenght-2, SEEK_CUR);
	for (int i = 0; i < Count_Examples; i++)
	{
		for (int j = 0; j < Exaples_Lenght; j++)
		{
			fscanf_s(pFile, "%c", &Examples[i][j]);
		}
		fscanf_s(pFile, "%c", &chr);
	}
    return 0;
}

