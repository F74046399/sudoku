#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include"Sudoku.h"


using namespace std;
		void Sudoku:: giveQuestion()
		{
			int i,j;
			int array[82]={0,3,7,9,2,1,4,5,8,6,
							4,8,1,5,7,6,3,2,9,
							5,6,2,3,8,9,4,1,7,
							8,2,3,4,9,5,7,6,1,
							9,1,4,7,6,8,2,5,3,
							7,5,6,1,3,2,9,4,8,
							2,3,7,6,5,1,8,9,4,
							1,4,8,9,2,7,6,3,5,
							6,9,5,8,4,3,1,7,2};	

			srand(time(NULL));
			for(j=0;j<=(rand()%40+18);j++)
			{
				if(array[(rand()%81+1)]!=0)
					array[(rand()%81+1)]=0;
				else j--;
			}	
				
			for(i=1;i<=81;i++)
			{
				printf("%d ",array[i]);
				if(i%9==0)
					printf("\n");
			}					
		}
		void Sudoku:: readIn()
		{
			int i;
			for(i=1;i<=81;i++)
			{
				scanf("%d",&array[i]);	
				map[i]=array[i];
			}
		}

		void Sudoku:: solve()
		{
			int i=1;
			int grid[9][9]={0};
			int compare[9][9]={0};
			int row,col,num,cellStartRow, cellStartCol;
		
			for(int row=0;row<9;row++)
			{
				for(int col=0;col<9;col++)//1D to 2D
				{
					grid[row][col]=array[i];
					compare[row][col]=grid[row][col];
					i++;
				}
			} 
			
			if(checkQuestion(grid)==false ||solveSudoku(grid)==false || checkanswer(grid)== false)
			{	 
        		printf("0");
			}
			else
			{
				if(!solutionNum(compare) ||compareSolution(grid,compare)==true )
				{
					printf("1\n");
					printGrid(grid);
				}
				else
				{
					printf("2\n");
				}
			}
		}
		bool Sudoku:: checkQuestion(int grid[9][9])
		{
			int row,column;
			int temp[9]={0};
			int a[82]={0};
			int i=1;
			
			for(int r=0;r<9;r++)
			{
				for(int c=0;c<9;c++)
				{
					a[i]=grid[r][c];
					i++;
				}
			}
		
			
			for(row=0;row<9;row++)//check row
			{
				for(int i=0;i<9;i++)
					temp[i]=0;
				for(column=0;column<9;column++)
				{
					if(grid[row][column]!=0)
					{
						if(temp[grid[row][column]-1]!=1)
							temp[grid[row][column]-1]=1;
						else//unsolvable 
						{
							return false;
						}
					}
				}
			}
			for(column=0;column<9;column++)//check column
			{
				for(int i=0;i<9;i++)
					temp[i]=0;
				for(row=0;row<9;row++)
				{
					if(grid[row][column]!=0)
					{
						if(temp[grid[row][column]-1]!=1)
							temp[grid[row][column]-1]=1;
						else//unsolvable 
						{
							
							return false;
						}
					}
				}
			}
			return true;
		/*	i=1;//check cell
			int count=0;
			for(int i=0;i<9;i++)
				temp[i]=0;
			
			while(i<=81)
			{
				if(a[i]!=0)
				{
					if(temp[a[i]-1]!=1)
						temp[a[i]-1]=1;
					else
					{
						return false;
					}
				}
				if(i%3==0)
				{
					i+=7;				
					count++;
				}
				else i++;
				if(count==2)
				{
					count=0;
					for(int i=0;i<9;i++)
					temp[i]=0;
					if(i==27||i==54)
						i+=1;
					else i-=17;
				}	
			}*/
		}
		/* assign values to all unassigned locations for Sudoku solution */
		bool Sudoku:: solveSudoku(int grid[9][9])
		{	
			int row,col,num;
			if (!findBlank(grid, row, col))//have been assigned number, not zero
       			return true;
    		num=1;
			while (num <= 9)
    		{
				if (check(grid, row, col, num))
        		{
            		grid[row][col] = num;//fill in the number
            		if (solveSudoku(grid))
						   return true;
					grid[row][col] = 0;	
        		}
        		num++;
    		}
    		return false;
		}
 
		/* find the blank*/
		bool Sudoku:: findBlank(int grid[9][9], int &row, int &col)
		{
    		for (row = 0; row < 9; row++)
    		{
        		for (col = 0; col < 9; col++)
            	{
					if (grid[row][col] == 0)//zero means a blank
               			 return true;
            	}
			}
    		return false;
		}
 
		/*row*/			
		bool Sudoku:: checkRow(int grid[9][9], int row, int num)
		{
    		for (int col = 0; col < 9; col++)
    		{
        		if (grid[row][col] == num)
           			 return true;
           	}
    		return false;//this number does not exist in this row
		}
 
		/*col*/
		bool Sudoku:: checkCol(int grid[9][9], int col, int num)
		{
    		for (int row = 0; row < 9; row++)
        	{
				if (grid[row][col] == num)
            		return true;
			}
    		return false;//this number does not exist in this column
		}
 
		/*cell*/
		bool Sudoku:: checkCell(int grid[9][9], int cellStartRow, int cellStartCol, int num)
		{
    		for (int row = 0; row < 3; row++)
    		{
        		for (int col = 0; col < 3; col++)
        		{
            		if (grid[row+cellStartRow][col+cellStartCol] == num)
                		return true;
                }
			}
			return false;//this number does not exist in this cell
		}
 
		/* Returns when the number can be filled in the blank. */
		bool Sudoku:: check(int grid[9][9], int row, int col, int num)
		{
			return !checkRow(grid, row, num) && !checkCol(grid, col, num) && !checkCell(grid, (row - row % 3), (col - col % 3), num);//if all fault ,return. the number can be filled in the blank
		}
		
		bool Sudoku:: checkanswer(int grid[9][9])
		{
			int row, col;
			int sum;
			int a[82];
			int i=1;
			
			for(row=0;row<9;row++)
			{
				for(col=0;col<9;col++)
				{
					a[i]=grid[row][col];
					i++;
				}
			} 
			
			for(row=0;row<9;row++)//check row
			{
				sum=0;
				for(col=0;col<9;col++)
				{
					sum+=grid[row][col];
				}
				if(sum!=45)
				{
					return false;
				}
			}
			for(col=0;col<9;col++)//check column
			{
				sum=0;
				for(row=0;row<9;row++)
				{
					sum+=grid[row][col];
				}
				if(sum!=45)
				{
					return false;
				}
			}
			return true;		
		}
		bool Sudoku::solutionNum(int compare[9][9])
		{
			int row,col,num;
			if (!findBlank(compare, row, col))//have been assigned number, not zero
       			return true;
    		num = 9;
			while (num >= 1)
    		{
        	
				if (check(compare, row, col, num))
        		{
            		compare[row][col] = num;//fill in the number
            		if (solutionNum(compare))
						   return true;
					compare[row][col] = 0;
        		}
        		num--;
    		}
    		return false;
		}
		
		bool Sudoku::compareSolution(int grid[9][9],int compare[9][9])
		{
			int same=0;
			/*for(int r=0;r<9;r++)
			{
				for(int c=0;c<9;c++)
				{
					printf("%d ",grid[r][c]);
				}
				printf("\n");
			}
			printf("compare\n");
			for(int r=0;r<9;r++)
			{
				for(int c=0;c<9;c++)
				{
					printf("%d ",compare[r][c]);
				}
				printf("\n");
			}*/
			
			for(int r=0;r<9;r++)
			{
				for(int c=0;c<9;c++)
				{
					if(grid[r][c]==compare[r][c])
						same++;
				}
			}
			if(same==81)
				return true;
			else return false;
		}
 
		/* output grid  */
		void Sudoku::printGrid(int grid[9][9])
		{
    		for (int row = 0; row < 9; row++)
    		{
       			for (int col = 0; col < 9; col++)
            		printf("%d ",grid[row][col]);
            	printf("\n");	
    		}
		}
		void Sudoku::changeNum(int a,int b)
		{
			
			int i;
			for(i=1;i<82;i++)
			{
				if(array[i]==a)
					array[i]=b;	
				else if(array[i]==b)
					array[i]=a;		
			}
			for(int i=1;i<82;i++)
			{		
				array[i];
				if(i%9==0)
					printf("\n");
			}
		}
		
		
		void Sudoku::changeRow(int a,int b)
		{
			int i=0;
			int j=0;
			int row,count;
			int targetA,targetB;
			int temp;
			int changeTimes=0;
			
			if((a==0 &&b==1)||(a==1 &&b==0))
			{
				targetA=1;
				targetB=28;
			}
			if((a==0 &&b==2)||(a==2 &&b==0))
			{
				targetA=1;
				targetB=55;	
			}
			if((a==1 &&b==2)||(a==2 &&b==1))
			{
				targetA=28;
				targetB=55;	
			}
			while(changeTimes<3)//change 9x3
			{
				changeTimes++;
				count=0;
				i=0; 
			
				while(count<9)//just change a row
				{	
					count++;
					temp=array[targetA];
					array[targetA]=array[targetB];
					array[targetB]=temp;
					targetA++;
					targetB++;		
				}
			}
		/*	for(int i=1;i<82;i++)
			{		
				array[i];
				if(i%9==0)
					printf("\n");
			}*/
		}
		void Sudoku::changeCol(int a,int b)
		{	 
			int	targetA,targetB;
			int i;
			
			if((a==0 &&b==1)||(a==1 &&b==0))
			{
				targetA=1;
				targetB=4;
			}
			if((a==0 &&b==2)||(a==2 &&b==0))
			{
				targetA=1;
				targetB=7;	
			}
			if((a==1 &&b==2)||(a==2 &&b==1))
			{
				targetA=4;
				targetB=7;	
			}
			while(targetA<82 && targetB<82)
			{
				int temp;
				i=0;
				
				while(i<3)//fill 3x1
				{
					temp=array[targetA];
					array[targetA]=array[targetB];
					array[targetB]=temp;
					i++;
					targetA++;
					targetB++;
				}
				
				targetA+=6;
				targetB+=6; 
			}
		}
		void Sudoku::rotate(int n)
		{
			
			int j=0;
			int i;
			int temp[81];
			
			if(n%4==0)
				return ;
			if(n%4==1)
			{	
				i=73;
				while(j<81)
				{
					while(i>0)
					{
						temp[j]=array[i];
						j++;
						i-=9;
					}
					i+=82;
				}
			}
			if(n%4==2)
			{
				for(i=0;i<81;i++)
				{
					temp[i]=array[81-i];
				}
			}
			if(n%4==3)
			{
				i=9;
				while(j<81)
				{
					while(i<82)
					{
						temp[j]=array[i];
						j++;
						i+=9;
					}
					i-=82;
				}
			}
			for(i=0;i<81;i++)
				array[i+1]=temp[i];
		}
		void Sudoku::flip(int n)// 0 vertically. Otherwise horizontally. 
		{
			
			int temp;
			int j=1;
			int i;
			int count=0;
			int d=1;
			
			if(n==0)
			{
				while(j!=37)
				{
					for(i=0;i<9;i++)
					{	
						temp=array[j+i];
						array[j+i]=array[j+(9*(10-2*d))+i];
						array[j+(9*(10-2*d))+i]=temp;
					}
					d++;
					j+=9;
				}
			} 
			else
			{
				while(j!=5)
				{
					for(i=0;i<9;i++)
					{
						temp=array[j];
						array[j]=array[j+(10-2*d)];
						array[j+(10-2*d)]=temp;
						j+=9;
					}
					d++;
					j=j-80;
				}
			}
		}
		void Sudoku::printOut(bool isAns)
		{
			printf("\n");
			
			int i;
			if(!isAns)
			for(i=1;i<82;i++)
				printf("%d%c",map[i],i%9==0?'\n':' ');
			else
				for(i=1;i<82;i++)
					printf("%d%c",array[i],i%9==0?'\n':' ');						
				
		}
	/*	void Sudoku::printOut()
		{
			for(int i=1;i<82;i++)
				printf("%d%c",array[i],i%9==0?'\n':' ');						
				
		}*/
		void Sudoku::change()
		{
			srand(time(NULL));
			changeNum(rand()%9+1,rand()%9+1);
			changeRow(rand()%3,rand()%3);
			changeCol(rand()%3,rand()%3);
			rotate(rand()%101);
			flip(rand()%2);
		}
		void Sudoku::transform()
		{
			change();
			
			printOut(true);
		}

