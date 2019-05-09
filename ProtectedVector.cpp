#include <exception>
#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename  T, typename _Alloc = std::allocator<T> >
class ProtectedVector : public std::vector<T, _Alloc>
{
	public:
		typedef size_t size_type;
		typename std::vector<T>::reference operator[] (size_type n)
		{
			if ( readOnly )
				throw std::logic_error("this vector is readonly");
			else
				return std::vector<T>::operator[](n);
		};
		ProtectedVector() : readOnly(false){};
		void setProtection() {readOnly = true;};
	private:
		bool readOnly;
};

int main()
{
	ProtectedVector<int> tv;
	tv.push_back(1); tv.push_back(2);
	tv.setProtection();
	tv[0] = 12;
};
