
#  map reduce 
-  This is map reduce implementation from [goolge map reduce paper](https://static.googleusercontent.com/media/research.google.com/en//archive/mapreduce-osdi04.pdf), in C . 
- This map-reduce implementation is for single machine and  not for cluster of machines ( original intended purpose).   

## Building 
- To build run command
```sh 
$ ./build.sh 
```
## Running map reduce
```sh
input filename
number of map worker threads
number of reduce worker threads

```


## further details

> This is ostep-project  on map-reduce. original repo : [ostep-projects, 3 easy pieces](https://github.com/remzi-arpacidusseau/ostep-projects) 





## notes : 
- assumes that `argv[1]` ... `argv[n-1]` (with `argc` equal to `n`) all contain files names that are passed to mappers
- `map()` and `reduce()`  are user functions 
- `MR_Emit()` emits intermediate keys after map function   
    - Uses data structures that used by both mapper and reducer threads 
    - mapper threads are used to populate the data structure 
    - and reducer threads are used to consume the data structures
    - use read and write lock.
- What we need : 
    - Thread pool for mapper threads and reducer threads
    - Internal Datastructures that is used to pass key value pairs from mapper to reducer 

- number of threads should be cores/processors on the system + 1 for now [configurable]. 


# References


# TODO

### maybe
- Optimization
    - [ ] Replace paritions with hashtable implementation  (  )


### Backlog

- [  ] Sort the lists in each partitions for iterator ( based on key)
- [  ] Iterator to iterate over paritions list 
- [  ] Getter method to get all pairs of key value pair  
- [  ] Threadpool for reducer and mapper threads

### Doing

- [  ] Unoptimized iterator for the disk  


### Done
- [X] Mutex for container Disk structure
