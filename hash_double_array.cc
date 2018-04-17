#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
	double a[] = {1.1, 2.2}; 
	double b[] ={2.2, 3.3};
	char * p = (char*) a;
	std::string sa(p, p+16);
	std::unordered_map<std::string, int> map;
	map.insert(std::pair<std::string,int>(sa, 1));
	p = (char*) b;
	std::string sb(p, p+16);
	if (map.find(sb) == map.end())
	{
		map.insert(std::pair<std::string,int>(sb,2));
	};
	for(auto p : map )
	{
		std::string tmp = p.first;
		char const *char_tmp = tmp.c_str();
		double *v = (double*) char_tmp;
		std::cout << "key= " << *v << ",";
		v = (double*) (char_tmp + 8);
		std::cout << "key= " << *v << " value =" << p.second << std::endl;
	};

};
