
#include <algorithm>
#include <chrono>
#include <charconv>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <map>
#include <string_view>
#include <vector>


// boost::split doesn't seem to handle string_view yet
std::vector< std::string_view > split( std::string_view line, const std::string& delims = "," )
{
	std::vector< std::string_view > result;
	size_t first{0};

	while( first < line.size() )
	{
		const auto second = line.find_first_of( delims, first );
		if( first != second )
			result.emplace_back( line.substr( first, second-first ) );

		if( second == std::string_view::npos )
			break;

		first = second + 1;
	}

	return result;
}

int64_t to_int( std::string_view s )
{
	int64_t result{0};

	if( auto [p, ec] = std::from_chars( s.data(), s.data() + s.size(), result ); ec == std::errc() )
		return result;

	throw std::runtime_error( "bad conversion" );
}

struct Job
{
	int64_t _jobid;
	int64_t _runtime;
	int64_t _nextjob;
};


Job make_job( std::string_view id, std::string_view runtime, std::string_view next )
{
	return {
		to_int( id ),
		to_int( runtime ),
		to_int( next )
		};
}


int job_chain()
{
	std::vector< Job > all_jobs;

	// read from stdin
	for( std::string line; std::getline( std::cin, line ); )
	{
		// ignore comments & empty lines
		if( line.empty() || line[0] == '#' )
			continue;

		// split the input
		auto parts = split( line, "," );
		if( parts.size() != 3 ) { // require 3 fields
			std::cout << "Malformed input\n";
			continue;
		}

		// make and save each job
		try {
			all_jobs.emplace_back( make_job( parts[0], parts[1], parts[2] ) );
		} catch( ... ) {
			std::cout << "Malformed input\n";
			continue;
		}
	}


	// find the job with a nextid equal to this
	auto find_job =[&]( int64_t nextjobid ) {
		return std::find_if( all_jobs.begin(), all_jobs.end(), [nextjobid](const Job& job) { return job._nextjob == nextjobid; } );
	};


	using Chain = std::vector< Job >;
	std::map< int64_t, Chain, std::greater<int64_t> > chains;


	while( !all_jobs.empty() )
	{
		// start with the end of a chain and work back up
		auto itr = find_job(0);
		Chain chain;
		int64_t tot_runtime = 0;

		while( itr != all_jobs.end() )
		{
			chain.emplace_back( std::move(*itr) );
			auto& j = chain.back();
			tot_runtime += j._runtime; // keep a running total of this chain's runtime
			all_jobs.erase( itr );
			itr = find_job( j._jobid );
		}

		if( !chain.empty() )
		{
			chains.insert( {tot_runtime, chain} );
		}
		else
		{
			// didn't actually make a chain - are there any jobs left?
			if( !all_jobs.empty() ) {
				std::cout << all_jobs.size() << " orphaned jobs\n";
				for( auto& x : all_jobs ) {
					std::cout << "\tJob: " << x._jobid << "," << x._runtime << "," << x._nextjob << '\n';
				}
			}
			break;
		}
	}


	// report
	for( auto& [time,chain] : chains )
	{
		std::cout << "-\n"
			<< "start_job: " << chain[chain.size() - 1]._jobid << "\n";

		// looking forward to c++20 and chrono::format instead of this
		std::chrono::seconds secs{ time };
		std::time_t t = secs.count();
		std::tm tottim = *std::gmtime(&t);

		std::chrono::seconds avg{ time / chain.size() };
		std::time_t a = avg.count();
		std::tm avgtim = *std::gmtime(&a);

		std::cout << "last_job: " << chain[0]._jobid << "\n"
				<< "number_of_jobs: " << chain.size() << "\n"
				<< "job_chain_runtime: " << std::setw(2) << std::setfill('0') << tottim.tm_hour << ":"
					<< std::setw(2) << std::setfill('0') << tottim.tm_min << ":"
					<< std::setw(2) << std::setfill('0') << tottim.tm_sec << "\n"
				<< "average_job_runtime: " << std::setw(2) << std::setfill('0') << avgtim.tm_hour << ":"
				  << std::setw(2) << std::setfill('0') << avgtim.tm_min << ":"
				  << std::setw(2) << std::setfill('0') << avgtim.tm_sec << "\n";
	}
	std::cout << "-\n";

	return 0;
}
