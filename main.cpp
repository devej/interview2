
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
void job_chain();
void test_min_gates();
int getMinGates( std::vector<int> landingTimes, std::vector<int> takeOffTimes, int maxWaitTime, int initialPlanes );
void test_robo_trade();
std::vector< std::string > robo_trade( std::vector<std::string> text );


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
	// job_chain();
	test_min_gates();
	test_robo_trade();
	return 0;
}


void test_robo_trade()
{
	std::cout << "Testing robo_trader\n";
	std::vector< std::string > input;
	input.emplace_back( "L,AAPL,100,B" );
	input.emplace_back( "Q,AAPL,100,S,100" ); // makes a trade

	auto result = robo_trade( input );
	if( auto r = result.size(); r != 1 )
		std::cout << "Wrong number of trades.  Expected 1, got " << r << '\n';
}


void test_min_gates()
{
	std::cout << "Testing airport\n";

	// no wait
	if( auto r = getMinGates( {630,645,730,1100}, {700,845,1015,1130}, 0, 1); r != 3 )
		std::cout << "Fail airport 1.  Expected 3, got " << r << "\n";

	// 20 min wait
	if( auto r = getMinGates( {630,645,730,1100}, {700,845,1015,1130}, 20, 1); r != 2 )
		std::cout << "Fail airport 2.  Expected 2, got " << r << "\n";

	// no leavers, wait 20
	if( auto r = getMinGates( {630,645,730,1100}, {}, 20, 1); r != 4 )
		std::cout << "Fail airport 3.  Expected 4, got " << r << "\n";

	// no arrivals, wait 20
	if( auto r = getMinGates( {}, {700,845,1015,1130}, 20, 4); r != 4 )
		std::cout << "Fail airport 4.  Expected 4, got " << r << "\n";

	// no nothing
	if( auto r = getMinGates( {}, {}, 0, 1); r != 1 )
		std::cout << "Fail airport 5.  Expected 1, got " << r << "\n";

	// same arrive and leave times, no wait
	if( auto r = getMinGates( {630,630,730,1100}, {845,845,1015,1130}, 0, 1); r != 3 )
		std::cout << "Fail airport 6.  Expected 3, got " << r << "\n";
}
