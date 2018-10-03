#include <iostream>

void slide(int start, int end, int step, int *b )
{
	int i,j;
	i = j = start;
	while ( j != end )
	{
		if ( b[i] == 2048  || b[j] == 2048)
		{
			std::cout << "bingo!" <<std::endl;
			break;
		};	
		if ( (b[i] == 0 && b[j] != 0)  ||  b[i] == b[j] )
		{
			b[i] += b[j];
			b[j] = 0;
		};
		if ( b[i] != 0 && b[j] != 0 && b[i] != b[j] )
		{
			int pos = j;
			while (pos != i+step ) pos+= step; 
			b[pos] = b[j];
			i+= step;
		};
		j+= step;
	};
}

void slide_up()
{
	for(int i = 0; i < row; i++)
	slide(col-1, 0, -1, board[i]);
};
void slide_down()
{
	for(int i = 0; i < row; i++)
	slide(0, col-1, 1, board[i]);
};
void slide_left()
{
	for(int i = 0; i < col; i++)
	slide(0, row-1, 1, boardBycol[i]);
	
};
void slide_right()
{
	for(int i = 0; i < col; i++)
	slide(row-1, 0, -1, boardBycol[i]);
};

const int row = 8;
const int col = 8;
int main()
{
	int board[row][col];	
	int* boardBycol[col][row];
  for(int i = 0; i < col; i++ )
  	for(int j = 0; j < row; i++ )
		boardBycol[i][j] = &board[j][i];
};
