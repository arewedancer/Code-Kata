#include <vector>
#include <iostream>
#include <string>
#include <unordered_set>
#include <cstdlib>

using namespace std;
int width;
int height;
struct Point
{
	int x, y;
	Point(int x_, int y_): x(x_),y(y_){};
};

char court[1000];
struct Ball
{
	int strike;
	std::vector<int> path;
	void set_path (int pos)
	{
		path.push_back(pos);
	};
};

Point dirs[4] = {Point(0,1), Point(1,0), Point(0,-1), Point(-1,0)};

char getDir(std::pair<int, int> i)
{
	if (i.first == 0 && i.second > 0 ) return 'V';
	if (i.first == 0 && i.second < 0 ) return '^';
	if (i.second == 0 && i.first > 0 ) return '>';
	if (i.second == 0 && i.first > 0 ) return '<';
};

void printPath(int height, int width)
{
};

int check(vector<bool> ball_mark)
{
	for (int i = 0; i < ball_mark.size(); i++)
		if (!ball_mark[i]) return i;
	return 9999;
};

Point toPoint(int current)
{
	return Point(current / width, current % height);
};

void mark_hole(std::unordered_set<int>& hole_mark, int i )
{
	hole_mark.insert(i);
};
void mark_ball(vector<bool>&  ball_mark, int i )
{
	ball_mark[i] = true;
};
void mark_path(unordered_set<int>& path_mark, Point start, Point end, Point dir)
{
	if ( start.x == end.x )
	{
				int step = start.y;
				while ( step < end.y )
				{
					path_mark.insert(start.x * width + step);
					step += dir.y;
				};
				return;
	};
	if ( start.y == end.y )
	{
				int step = start.x;
				while ( step < end.x )
				{
					path_mark.insert(step * width + start.y);
					step += dir.x;
				};
	};
};

void solve(unordered_set<int> hole_mark, vector<bool> ball_mark, unordered_set<int> path_mark, std::vector<Ball> balls, int ball, bool next_ball)
{
	if (next_ball)
	{
		next_ball = false;
		int next = check(ball_mark);
		if ( next == 9999 ){
			//printPath(balls); 
			exit(0);
		};
		ball = next;
	};
	{
		// last path
		Point cur = toPoint(balls[ball].path[balls[ball].path.size()-1]); 
		bool go;
		for( Point dir: dirs )
		{
			go = true;
			Point new_pos = Point(dir.x == 0 ? cur.x : cur.x + dir.x * balls[ball].strike >= width ? width -1 :
					cur.x + dir.x * balls[ball].strike < 0 ? 0 : cur.x + dir.x * balls[ball].strike, 
					dir.y == 0 ? cur.y : cur.y + dir.y * balls[ball].strike >= height ? height -1 :
					cur.y + dir.y * balls[ball].strike < 0 ? 0 : cur.y + dir.y * balls[ball].strike); 
			if ( new_pos.x == cur.x && new_pos.y == cur.y )
				continue;
			//check along the path 
			if ( new_pos.x == cur.x )
			{
				int step = cur.y;
				while ( step != new_pos.y + dir.y )
				{
					// marked, backtrack
					if (path_mark.count( new_pos.x * width + step ) != 0 ) { go = false; break;};
					// if hole
					if (court[new_pos.x * width + step] == 'H' )
					{
						if ( hole_mark.count(new_pos.x * width + step) == 0 )
						{
							next_ball = true;	
							mark_hole(hole_mark, new_pos.x * width + step);
							mark_ball(ball_mark, ball);
							mark_path(path_mark, cur, Point(new_pos.x, step), dir); 
							balls[ball].set_path(new_pos.x * width + step);
							balls[ball].strike--;
						}
						else{
							go = false;
						};
						break;
					};
					// if dest
					if ( step == new_pos.y )
					{
						if (balls[ball].strike == 0 ) 
						{
							go = false; break;
						};
						if (court[new_pos.x * width + new_pos.y] != 'X')
						{
							mark_path(path_mark, cur, new_pos, dir); 
							balls[ball].set_path(new_pos.x * width + step);
							balls[ball].strike--;
						} else{
							go = false; break;
						};
					};
					step += dir.y;
				};
			};
			// y
			if ( new_pos.y == cur.y )
			{
				int step = cur.x;
				while ( step != new_pos.x + dir.x )
				{
					// marked, backtrack
					if (path_mark.count( step * width + new_pos.y ) != 0 ) { go = false; break;};
					// if hole
					if (court[step * width + new_pos.y] == 'H' )
					{
						if ( hole_mark.count(step * width + new_pos.y) == 0)
						{
							next_ball = true;	
							mark_hole(hole_mark, step * width + new_pos.y);
							mark_ball(ball_mark, ball);
							mark_path(path_mark, cur, Point(step, new_pos.y), dir); 
							balls[ball].set_path(step * width + new_pos.y);
							balls[ball].strike--;
						}
						else{
							go = false;
						};
						break;
					};
					// if dest
					if ( step == new_pos.x )
					{
						if ( balls[ball].strike == 0 ) 
						{
							go = false; break;
						};
						if (court[step * width + new_pos.y] != 'X' )
						{
							mark_path(path_mark, cur, new_pos, dir); 
							balls[ball].set_path(step * width + new_pos.y);
							balls[ball].strike--;
						} else{
							go = false; break;
						};
					};
					step += dir.x;
				};
			};
			if (!go) continue;
			solve(hole_mark, ball_mark, path_mark, balls, ball, next_ball);
		};
	};
};

int main()
{
	//int width;
	//int height;
	std::unordered_set<int> path_mark;
	std::unordered_set<int> hole_mark;
	cin >> width >> height; cin.ignore();
	cerr << width <<"," << height << std::endl;
	std::vector<Ball> balls;
	std::vector<bool> ball_mark;
	std::vector<int> hold_mark;
	// mark balls, holes
	for (int i = 0; i < height; i++) {
		string row;
		cin >> row; cin.ignore();
		for(int j = 0; j < width; j++)
		{
			if (isdigit(row.at(j)))
			{
				Ball b; b.strike = atoi(&row.at(j));
				b.path.push_back(i * width + j);
				balls.push_back(b);
			}
			if ( row.at(j) == 'X' || row.at(j) == 'H' )
				court[i * width + j] = row.at(j);
		}
		cerr << row << std::endl;
	}
	for(int i = 0; i < balls.size(); i++ )
		ball_mark.push_back(false);
	solve(hole_mark, ball_mark, path_mark, balls, 0, false);
	//printPath(height, width);
}
