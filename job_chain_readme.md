
To build:
    # build release
    make -j2 config=release -f Makefile
    # build debug (uses defaults)
    make

To clean:
    make clean

The Makefile might need to be told where boost is.
Defaults are set to:
    BOOST_INC = /usr/local/include/boost
    BOOST_LIB = /usr/local/lib

To run
    ./headlands


Output:
sort decending by total runtime of the chain
-
start_job: id of the first job in the chain
last_job: id of the last job in the chain
number_of_jobs: number of jobs in the chain
job_chain_runtime: total runtime of the chain in HH:MM:SS
average_job_time: average per-job runtime in HH:MM:SS
-
start_job: id of the first job in the chain
last_job: id of the last job in the chain
number_of_jobs: number of jobs in the chain
job_chain_runtime: total runtime of the chain in HH:MM:SS
average_job_time: average per-job runtime in HH:MM:SS
-


Output example:
-
start_job: 1
last_job: 23
number_of_jobs: 2
job_chain_runtime: 00:01:30
average_job_time: 00:00:45
-
start_job: 2
last_job: 3
number_of_jobs: 2
job_chain_runtime: 00:00:35
average_job_time: 00:00:17
-