
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>


void question1( std::int64_t N, std::int64_t a, std::int64_t /*b*/ );
void question2();
void question3();
void question4();
void question5();
void question6();
void question7( std::vector<std::int64_t>& /*v*/, std::int64_t /*min_val*/ );


int main( int /*argc*/, char **/*argv*/ )
{
	question1( 12, 3, 4 );
	question2();
	question3();
	question4();
	question5();
	question6();
	std::vector<std::int64_t> v{1, 7, 3, 6, 5, 2, 4};
	question7( v, 3 );
	return 0;
}
