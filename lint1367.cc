#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> policeDistance(vector<vector<int>> &matrix ) {
	int m = matrix.size();
	int n = matrix[0].size();
	vector<vector<int>> res;
	if (m == 0 || n ==0 ) return res;
	for(int i = 0; i < m; i++)
		res.push_back(vector<int>(n, -2));
	bool notStop = true;
	int loop = -1;
	while (notStop)
	{
		notStop = false;
		loop++;
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n ; j++)
			{
				if (res[i][j] == -2)
				{
					notStop = true;
					if (matrix[i][j] == -1) res[i][j] = -1;
					if (matrix[i][j] == 1) res[i][j] = 0;

				}else if ( res[i][j] >= 0)
				{
					int update = res[i][j] + 1;
					if (update != loop) continue;
					if (i < n-1 && res[i+1][j] == -2) res[i+1][j] = update;
					if (i > 0 &&res[i-1][j] == -2) res[i-1][j] = update;
					if (j < m -1 && res[i][j+1] == -2) res[i][j+1] = update;
					if (j > 0 && res[i][j-1] == -2) res[i][j-1] = update;
				}
			}
	}
	return res;
};
int main()
{
	vector<vector<int>> input = {{0,-1,0}, {0, 1, 1}, {0, 0, 0}};
	vector<vector<int>> res = policeDistance(input);
};
