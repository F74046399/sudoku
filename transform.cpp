#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include"Sudoku.h"

using namespace std;
int main()
{
	Sudoku sudoku;
	sudoku.readIn();
	sudoku.transform();
	
	return 0;
}
