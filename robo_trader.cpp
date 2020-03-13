#include <bits/stdc++.h>
#include <map>
#include <string>


using namespace std;

using Price = double;

enum class Side : uint8_t
{
	Undef = 0,
	Buy = 1,
	Sell = 2
};

struct Limit
{
	Limit( Side s, Price p ) : _side(s), _price(p) {}
	Limit() : _side(Side::Undef), _price(0.0) {}
	Side _side;
	Price _price;
};

inline vector< string > Split( string s, string delims = "," )
{
	vector< string > rv;
	size_t first = 0;

	while( first < s.size() )
	{
		const auto second = s.find_first_of( delims, first );
		if( first != second )
			rv.emplace_back( s.substr( first, second-first ) );

		if( second == string::npos )
			break;

		first = second + 1;
	}

	return rv;
}

using Buy = Limit;
using Sell = Limit;

map< string, pair< Buy, Sell > > Book;


vector<string> robo_trade( vector<string> text )
{
	vector< string > trades;

	for( auto& line: text )
	{
		auto parts = Split( line );
		auto& limits = Book[ parts[1] ];
		auto price = static_cast<double>( stoi(parts[2]) );
		Side side = parts[3] == "S" ? Side::Sell : Side::Buy;

		if( parts[0] == "L" ) // it's a limit
		{
			if( side == Side::Buy )
			{
				limits.first._side = Side::Buy;
				limits.first._price = price;
			}
			else // is a sell
			{
				limits.second._side = Side::Sell;
				limits.second._price = price;
			}
		}
		else // it's a quote
		{
			auto symbol = parts[1];
			auto size = stoi( parts[4] );

			if( side == Side::Sell )
			{
				if( limits.first._side != Side::Undef && limits.first._price >= price )
				{
					ostringstream trade_message;
					trade_message << "T," << symbol << ",B," << size << "," << std::fixed << std::setprecision(1) << price;
					trades.emplace_back( trade_message.str() );
					limits.first._side = Side::Undef;
					limits.first._price = 0.0;
				}
			}
			else // is a buy
			{
				if( limits.second._side != Side::Undef && limits.second._price <= price )
				{
					ostringstream trade_message;
					trade_message << "T," << symbol << ",S," << size << "," << std::fixed << std::setprecision(1) << price;
					trades.emplace_back( trade_message.str() );
					limits.second._side = Side::Undef;
					limits.second._price = 0.0;
				}
			}
		}
	}


	return trades;
}
