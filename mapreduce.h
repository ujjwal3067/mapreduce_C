#ifndef __mapreduce_h__
#define __mapreduce_h__


// contains dynamically allocated list
struct entry { 
    int key ; 
    int count ;
};

struct partition { 
    int count ; 
    int list[] ; 
};

struct Disk { 
    // contains list of partitions
    int parition_count ;
    Parition paritions[] ; 
};


// Different function pointer types used by MR
typedef char *(*Getter)(char *key, int partition_number);
typedef void (*Mapper)(char *file_name);
typedef void (*Reducer)(char *key, Getter get_func, int partition_number);
typedef unsigned long (*Partitioner)(char *key, int num_partitions);

// External functions: these are what you must define
// emits intermediate keys
void MR_Emit(char *key, char *value);

unsigned long MR_DefaultHashPartition(char *key, int num_partitions);

void MR_Run(int argc, char *argv[], 
	    Mapper map, int num_mappers, 
	    Reducer reduce, int num_reducers, 
	    Partitioner partition);


#endif // __mapreduce_h__
