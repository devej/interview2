
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

void fizbuz( std::int64_t N, std::int64_t a, std::int64_t b );
void operator_plus();
void sigs();
void assignment_operator();
void single();
void queue();
void vub( std::vector<std::int64_t>& /*v*/, std::int64_t /*min_val*/ );


int main( int /*argc*/, char **/*argv*/ )
{
	fizbuz(12, 3, 4);
	operator_plus();
	sigs();
	assignment_operator();
	single();
	queue();
	std::vector<std::int64_t> v{1, 7, 3, 6, 5, 2, 4};
	vub( v, 3 );
	return 0;
}
