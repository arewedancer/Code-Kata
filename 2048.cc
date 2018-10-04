#include <iostream>
template <class T>
void deep_copy(T** dest, T** src)
{};
template <class T>
double get_score( T** b)
{
};
int findBestMove()
{
	//choice [up, down, left, right]= (0,1,2,3)
	// score = sum(total number value of board) /sum (total number of non-zero blocks)
	double score[4];
	int b_copy[row][col];
	int * bc_copy[row][col];
	deep_copy(board, b_copy);
	slide_up(b_copy);
	score[0] = get_score(b_copy);
	deep_copy(board, b_copy);
	slide_down(b_copy);
	score[1] = get_score(b_copy);
	deep_copy(boardByCol, bc_copy);
	slide_left(bc_copy);
	score[2] = get_score(bc_copy);
	deep_copy(boardByCol, bc_copy);
	slide_right(bc_copy);
	score[3] = get_score(bc_copy);
};

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
int board[row][col];	
int* boardBycol[col][row];
int main()
{
	for(int i = 0; i < col; i++ )
		for(int j = 0; j < row; i++ )
			boardBycol[i][j] = &board[j][i];
};
