
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <string_view>


// would have preferred boost::split
std::vector< std::string_view > split( std::string_view line, const std::string& delim )
{
	size_t last{0};
	size_t next{0};
	std::vector< std::string_view > result;

	while( (next = line.find(delim, last)) != std::string_view::npos )
	{
		result.emplace_back( line.substr(last, next - last) );
		last = next + delim.size();
	}

	result.emplace_back( line.substr(last) );
	return result;
}


struct Job
{
	uint64_t _jobid;
	uint64_t _runtime;
	uint64_t _nextjob;
};


Job make_job( std::string_view id, std::string_view runtime, std::string_view next )
{
	// stoul might throw (that's intentional)
	return Job{
		std::stoul( std::string(id) ),
		std::stoul( std::string(runtime) ),
		std::stoul( std::string(next) )
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


	auto find_job =[&]( uint64_t nextjobid ) {
		return std::find_if( all_jobs.begin(), all_jobs.end(), [nextjobid](const Job& job) { return job._nextjob == nextjobid; } );
	};


	using Chain = std::vector< Job >;
	std::map< uint64_t, Chain, std::greater<uint64_t> > chains;


	while( !all_jobs.empty() )
	{
		// start with the end of a chain and work back up
		auto itr = find_job(0);
		Chain chain;

		while( itr != all_jobs.end() )
		{
			chain.emplace_back( *itr );
			const Job j = *itr;
			all_jobs.erase( itr );
			itr = find_job( j._jobid );
		}

		if( !chain.empty() )
		{
			// have a full chain.  calc chain runtime and store
			uint64_t tot{ 0 };
			for( auto& c : chain )
			{
				tot += c._runtime;
			}
			chains.insert( {tot, chain} );
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
