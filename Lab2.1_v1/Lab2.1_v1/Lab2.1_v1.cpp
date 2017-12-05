// Lab2.1_v1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

int Size_Motiv;
int Count_Examples;
int Exaples_Lenght;
char ** Examples;
int* Counter;
bool CountPlus(int *mas, int count, int lenght, int size)
{
	for (int i = count-1; i >= 0; i--)
	{
		if (mas[i] < (lenght - size))
		{
			mas[i]++;
			return true;
		}
		else
		{
			mas[i] = 0;
		}
	}
	return false;
}
int LocalScore(int step)
{
	char* mas = new char[Count_Examples];
	int * col = new int[4];
	for (int i = 0; i < Count_Examples; i++)
	{
		mas[i] = Examples[i][Counter[i] + step];
	}
	for (int i = 0; i < 4; i++)
	{
		col[i] = 0;
	}
	for (int i = 0; i < Count_Examples; i++)
	{
		if (mas[i] == 'A')
			col[0]++;
		else
			if (mas[i] == 'C')
				col[1]++;
			else
				if (mas[i] == 'G')
					col[2]++;
				else
					if (mas[i] == 'T')
						col[3]++;
	}
	int max = col[0];
	for (int i = 1; i < 4; i++)
	{
		if (col[i] > max)
			max = col[i];
	}
	delete(mas);
	delete(col);
	return max;
}
int Score()
{
	int res = 0;
	for (int i = 0; i < Size_Motiv; i++)
	{
		res += LocalScore(i);
	}
	return res;
}
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
	Counter = new int[Count_Examples];
	for (int i = 0; i < Count_Examples; i++)
	{
		Counter[i] = 0;
		for (int j = 0; j < Exaples_Lenght; j++)
		{
			fscanf_s(pFile, "%c", &Examples[i][j]);
		}
		fscanf_s(pFile, "%c", &chr);
	}
	int max = Score();
	int* res_mas = new int[Count_Examples];
	for (int i = 0; i < Count_Examples; i++)
	{
		res_mas[i] = Counter[i];
	}
	while (CountPlus(Counter, Count_Examples, Exaples_Lenght, Size_Motiv))
	{
		int res = Score();
		if (res > max)
		{
			for (int i = 0; i < Count_Examples; i++)
			{
				res_mas[i] = Counter[i];
			}
			max = res;
		}
		
	}
	for (int i = 0; i < Count_Examples; i++)
	{
		for (int j = 0; j < Size_Motiv; j++)
		{
			printf("%c", Examples[i][res_mas[i] + j]);
		}
		printf("\n");
	}
    return 0;
}

