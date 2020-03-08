#include <bits/stdc++.h>
#include <set>
#include <list>

using namespace std;


enum class Direction : uint8_t
{
	takeoff = 0,
	landing = 1
};

struct Plane
{
	Plane( Direction io, int t ) : _io(io), _time(t) {}
	Direction	_io;
	int			_time;
};

bool operator<( const Plane& lhs, const Plane& rhs )
{
	return lhs._time < rhs._time;
}


int getMinGates( vector<int> landingTimes, vector<int> takeOffTimes, int maxWaitTime, int initialPlanes )
{
	int planes_at_gates = initialPlanes;
	int min_gates = initialPlanes;

	std::set< Plane > all_planes;

	for( auto this_landing_time : landingTimes )
		all_planes.emplace( Plane{Direction::landing, this_landing_time} );

	for( auto this_takeoff_time : takeOffTimes )
		all_planes.emplace( Plane{Direction::takeoff, this_takeoff_time} );


	std::list< Plane > waiting_planes;

	auto CheckWaiting = [&]( const Plane& new_plane )
	{
		while( !waiting_planes.empty() )
		{
			if( new_plane._time - waiting_planes.front()._time >= maxWaitTime )
			{
				++planes_at_gates;
				waiting_planes.pop_front();
			}
			else
			{
				break;
			}
		}
	};


	for( auto& plane : all_planes )
	{
		if( plane._io == Direction::takeoff )
		{
			--planes_at_gates;
		}
		else
		{
			waiting_planes.push_back( plane );
		}

		CheckWaiting( plane );
		min_gates = std::max( planes_at_gates, min_gates );
	}

	return min_gates;
}
