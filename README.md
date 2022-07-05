# profiling-intel

This repository houses the course materials for the ARC training course:
"A brief introduction to profiling with the Intel toolchain".

Slides can be found in `slides/`. Materials for excercises can be found in
`auto_tracing/` and `user_instrumentation/`. These excercises are designed to
be run on the Hamilton 8 supercomputer at Durham, but will run on other machines
that offer Intel MPI with only a few tweaks to the job submission scripts.

### Excercise 1

Prerequisites:
- ssh into Hamilton 8.
- clone this repository
- Change into the `auto_tracing/` directory

Have a look at `auto_tracing/itac_test.cpp`. The code is strange (it
doesn't really do any proper computations), but it allows us to experiment with
ITAC. Notice:
- the code is intended to be run with 2 ranks and is not multithreaded
- Rank 0 makes 2 nonblocking sends to rank 1 before doing some physics
- Rank 1 intersperses physics with receiving the messages
- Processes are blocked at the end of the programme until all processes reach the barrier

Tasks:
1) Submit `auto_tracing/submit.sh` to Hamilton (should run very quickly)
2) Open the resulting trace file with `traceanalyzer`
3) Open the event timeline
4) Ungroup the MPI functions and locate the call to `MPI_Barrier`
5) Filter the communications so that you only see messages sent with MPI tag 0

### Exercise 2 (extension)

Change into the `user_instrumentation/` directory. Submit the code to Hamilton
using `submit.sh`. Open the event timeline and ungroup the functions to view
the user defined instrumentation.
