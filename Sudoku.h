#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstdio>


using namespace std;

class Sudoku{
	public:
		void giveQuestion();
		void readIn();
		void solve();
		bool checkQuestion(int grid[9][9]);
		bool checkanswer(int grid[9][9]);
		bool solutionNum(int compare[9][9]);
		bool compareSolution(int grid[9][9],int compare[9][9]);
		bool solveSudoku(int grid[9][9]);
		bool findBlank(int grid[9][9], int &row, int &col);
		bool checkRow(int grid[9][9], int row, int num);
		bool checkCol(int grid[9][9], int col, int num);
		bool checkCell(int grid[9][9], int cellStartRow, int cellStartCol, int num);
		bool check(int grid[9][9], int row, int col, int num);
		void printGrid(int grid[9][9]);
		
		void changeNum(int a,int b);
		void changeRow(int a,int b);
		void changeCol(int a,int b);
		void rotate(int n);
		void flip(int n);
		
		void printOut(bool isAns);
		void change();
		void transform();
	
	private:
		int array[82];
		int map[82];
	};
