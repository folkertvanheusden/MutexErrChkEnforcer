# MutexErrChkEnforcer
This forces every pthread mutex to be an error-checking mutex so to track bugs.


# building
* mkdir build
* cd build
* cmake ..
* make
* cd ..


# usage
LD_PRELOAD=build/libmutexerrchkenforcer.so /path/to/my/program-to-test


# example output
    Mutex 0x7ffd9dee6110 lock (by 0x557ab995596b) failed with: Resource deadlock avoided


# note
This wrapper changes the mutex-type in place before doing a regular mutex lock.


written by folkert@vanheusden.com
