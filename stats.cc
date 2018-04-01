#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;
vector<pair<int,int> > generateCombination(int n)
{
  vector<pair<int, int> > comb;
	for(int i = 0; i < n ; ++i )
  {
		for(int j = i+1; j< n; ++j )
		comb.push_back(pair<int,int>(i,j));
	};
  return comb;
};

static int seq = 1;
static int freq_max = 1;
void output(unordered_map<string, int>& freq, unordered_map<int,string>& idx_to_artist);
int scan(vector<string>& one_line, unordered_map<string,int>& freq, unordered_map<string,int>& artist_to_idx,
				unordered_map<int, string>& idx_to_artist)
{
  unordered_map<int, int> line_freq;
  vector<int> index; unordered_set<int> helper;
  for(auto artist : one_line)
  {
		if (artist_to_idx.find(artist) == artist_to_idx.end())
	  {
			artist_to_idx.insert(pair<string,int>(artist, seq));
			idx_to_artist.insert(pair<int, string>(seq, artist));
			seq++;
		};
	 line_freq[artist_to_idx[artist]]++;
	 helper.insert(artist_to_idx[artist]);
	};
  for(auto e : helper)
		index.emplace_back(e);
	sort(index.begin(), index.end());
	vector<pair<int,int>> comb = generateCombination(index.size());
	for(auto e : comb )
  {
		string key = to_string(index[e.first]) + '-' + to_string(index[e.second]);
		int val = min(line_freq[index[e.first]], line_freq[index[e.second]]);
		if (freq.find(key) != freq.end())
			freq[key] += val;
		else
			freq[key] = val;
		freq_max = freq[key] > freq_max ? freq[key] : freq_max;
	};
};

void input(const string fileName, unordered_map<string,int>& freq, unordered_map<string,int>& artist_to_idx)
{
  unordered_map<int, string> idx_to_artist;
	string line;
	ifstream inputFile (fileName);
	int max;
	if (inputFile.is_open())
	{
		while ( getline (inputFile,line) )
		{
			char delimiter=',';
			vector<string> tokens;
			string token;
			istringstream tokenStream(line);
			while (std::getline(tokenStream, token, delimiter))
			{
				tokens.push_back(token);
			}
			max = scan(tokens, freq, artist_to_idx, idx_to_artist);
		}
		inputFile.close();
	}
	output(freq, idx_to_artist);
};

void output(unordered_map<string, int>& freq, unordered_map<int,string>& idx_to_artist)
{
	cout << "max pair frequency= " << freq_max << endl;
	for(auto e : freq)
	{
		if (e.second > freq_max/2 )
		{
			cout << idx_to_artist[stoi(e.first.substr(0,e.first.find("-")))] << "," 
				<< idx_to_artist[stoi(e.first.substr(e.first.find("-")+1))];
			cout << ": " << e.second << endl;
		};
	};
};

int main()
{
	unordered_map<string,int> artist_to_idx;
	unordered_map<string,int> freq;
	input("input.txt", freq, artist_to_idx);
};
