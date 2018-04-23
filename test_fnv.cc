//#include "tbb/concurrent_unordered_map"
//#include "tbb/concurrent_vector"
#include "bitVectorUC.h"
#include <mutex>
#include <vector>
#include <unordered_map>
#include <ext/hash_map>
#include <stdint.h>
#include <iostream>
#include "fnv.hh"


//TODO: delete copy ctor; delete move ctor
// keyEqual
//
class LookupTable
{
	private:
		//tbb::concurrent_unordered_map<std::pair<Key, long>> _map;
		//tbb::concurrent_vector<Key> _store;
		std::vector<char*> _store;
		//std::unordered_map<Key, long> _map;
		__gnu_cxx::hash_map<size_t, long> _map;
		hash::fnv<64> fnv_64;
		//std::mutex m;

	public:
		//LookupTable(LookupTable& t) = delete;
		uint32_t put(char* key, int n);
		char* get(uint32_t index);
		uint32_t size(){ return _store.size();};
};
uint32_t LookupTable::put(char* key, int n)
{
	size_t hash_key = fnv_64(key, n);
	if ( _map.find(hash_key) == _map.end())
	{
		_store.push_back(key);
		_map.insert(std::pair<size_t, long>(hash_key, _store.size()-1));
		return _store.size()-1;
	}else
		return _map[hash_key];
};

char* LookupTable::get(uint32_t index)
{
	return _store.at(index);
};

char*  makeAndFill(int row, int col)
{
	char *storage = new (std::nothrow) char[ row * col * sizeof(double)]; 
	double *data = (double*) storage;
	for(int i = 0; i < row*col; ++i )
	{
		data[i] = (double) (rand() % 13);
		std::cout << data[i] << ",";
	};
	/*for(int i = 0; i < row*col; ++i )
	{
		
		std::cout << &data[i] << ",";
	};*/
	std::cout << std::endl;
	return storage;
};

int main()
{
	std::vector<char*> data;
	int col = 2;
	int measure_col = 1;
	int rows[]={30, 300};
	char* t1 = makeAndFill(30, col+measure_col);
	data.push_back(t1);
	char* t2 = makeAndFill(300, col+measure_col);
	data.push_back(t2);
	LookupTable lookup;
  std::vector<bitVectorUC*> bits;	
	for(int i=0; i < data.size(); ++i)
	{
		bitVectorUC* tmp_bit = new bitVectorUC(440, false, false);
		for(int j=0; j < rows[i]; ++j)
		{
			//std::string tmp((char*) (data[i] + j*col*sizeof(double)), (char*) (data[i]+(j+1)*col*sizeof(double)));
			//std::cout << "data= " << (double *) (data[i] + j * col * sizeof(double)) << std::endl;
			uint32_t bitPos=lookup.put(data[i] + j * col * sizeof(double), sizeof(double) * col);
			//std::cout << "bitPos= " << bitPos << std::endl;
			tmp_bit->SetBit(bitPos);
		}
		//std::cout << "count= " << tmp_bit->CountBitSet() << std::endl;
		bits.push_back(tmp_bit);
	};
	//bitVector result; result.compAND(bits[0], bits[1]);	
	bits[0]->OR(*bits[1]);
	//std::vector<uint16_t> final;
	//std::cout << "final.size = " << final.size() << std::endl;
	//result.toVector(final);
	for(int i = 0 ; i < lookup.size(); ++i)
	{
		if (bits[0]->IsBitOn(i))
		{
			char* r = lookup.get(i);
			for(int i = 0; i < col + measure_col ; ++i )
			{
				double* val = (double*)  (r + i*sizeof(double));
				//std::cout << (double *) (r+ i*sizeof(double)) << ",";
				std::cout << *val << ",";
			};
			std::cout << std::endl;
		};
	};

};
