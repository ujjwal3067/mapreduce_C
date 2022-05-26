#ifndef __mapreduce_h__
#define __mapreduce_h__



// Different function pointer types used by MR
typedef char *(*Getter)(char *key, int partition_number);

// functions for worker threads
typedef void (*Mapper)(char *file_name); 
typedef void (*Reducer)(char *key, Getter get_func, int partition_number);

typedef unsigned long (*Partitioner)(char *key, int num_partitions);

// External functions: these are what you must define
// emits intermediate keys
//void MR_Emit(char *key, char *value);
void MR_Emit(char *key, int value);

unsigned long MR_DefaultHashPartition(char *key, int num_partitions);

void MR_Run(int argc, char *argv[], 
	    Mapper map, int num_mappers, 
	    Reducer reduce, int num_reducers, 
	    Partitioner partition);


#endif // __mapreduce_h__
