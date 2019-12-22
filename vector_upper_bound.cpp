
/******************************************************************************
Write a function which takes a vector<int> and an int, and erases all elements
from said vector that are larger than the int parameter.

Note:
	 - Feel free to use a text editor or IDE of your choice to do this instead.
	 - If you do, simply just copy-paste your code here when you're done.
******************************************************************************/
#include <vector>
#include <algorithm>
#include <cstdint>
#include <iostream>


void vub( std::vector<std::int64_t>& v, std::int64_t val )
{
	std::sort( v.begin(), v.end() );
	auto iter = std::upper_bound( v.begin(), v.end(), val );
	v.erase( iter, v.end() );

	for( auto i : v ) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}
