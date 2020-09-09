
### To build:
    // build release  
    make -j2 config=release -f Makefile  
    // build debug (uses defaults)  
    make  

### To clean:  
    make clean  

The Makefile might need to be told where boost is.  
Defaults are set to:  
    BOOST_INC = /usr/local/include/boost  
    BOOST_LIB = /usr/local/lib  

### To run:  
    ./job_chain < job_chain.csv  


### Task:  
Given an input file like job_chain.csv, parse the file and produce a report on each "job chain" found.  

The input file is in csv format with each row representing the details of a job run.  Each row in the file  
consists of a job id, the job's runtime (in seconds), and the ID of the next job in the chain.  A zero in  
the next_id column indicates the end of a chain.  Calcualte each chain in the file and report as detailed  
in the Output section.  

For example, an input file consisting of:  
1,15,2  
2,25,3  
3,20,0  
Shows the details of three job runs comprising one chain that took a total of sixty seconds.  
Job 1 ran for 15 seconds, and links to job 2.  
Job 2 ran for 25 seconds, and links to job 3.  
Job 3 took 20 seconds, and is the last job in the chain as indicated by the 0 for the next id.  

Input files are not guaranteed to be sorted in any particular order.  Your program will be run against  
other input files.  It should be fault-tolerant and reasonably efficient.  Above all, it should be correct.  
Bonus points awarded for testing.  

## Output:
Sort decending by total runtime of the chain
> \-  
> start_job: id of the first job in the chain  
> last_job: id of the last job in the chain  
> number_of_jobs: number of jobs in the chain  
> job_chain_runtime: total runtime of the chain in HH:MM:SS  
> average_job_time: average per-job runtime in HH:MM:SS  
> \-  
> start_job: id of the first job in the chain  
> last_job: id of the last job in the chain  
> number_of_jobs: number of jobs in the chain  
> job_chain_runtime: total runtime of the chain in HH:MM:SS  
> average_job_time: average per-job runtime in HH:MM:SS  
> \-  


Output example:
> \-  
> start_job: 1  
> last_job: 23  
> number_of_jobs: 2  
> job_chain_runtime: 00:01:30  
> average_job_time: 00:00:45  
> \-  
> start_job: 2  
> last_job: 3  
> number_of_jobs: 2  
> job_chain_runtime: 00:00:35  
> average_job_time: 00:00:17  
> \-  

