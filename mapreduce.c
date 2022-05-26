#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapreduce.h"


void init_Disk(Disk* disk, int count) { 
    disk->parition_cout = count ;
    disk->paritions  =  (partition *)calloc(count , sizeof(*partition));     // this has to point to void
}

// Code for testing purpose
void Map(char *file_name) {
    FILE *fp = fopen(file_name, "r");
    assert(fp != NULL);

    char *line = NULL;
    size_t size = 0;
    while (getline(&line, &size, fp) != -1) {
        char *token, *dummy = line;
        while ((token = strsep(&dummy, " \t\n\r")) != NULL) {
            MR_Emit(token, "1");
        }
    }
    free(line);
    fclose(fp);
}

void Reduce(char *key, Getter get_next, int partition_number) {
    int count = 0;
    char *value;
    while ((value = get_next(key, partition_number)) != NULL)
        count++;
    printf("%s %d\n", key, count);
}

void MR_Emit(char *key, char *value) { 
    //TODO: temporary umimplemented  
}

unsigned long MR_DefaultHashPartition(char *key, int num_partitions) { 
    unsigned long hash = 5381 ; 
    int c; 
    while((c  = *key++) != '\0')
        hash = hash * 33 + c; 
    return hash % num_partitions; 
}

// First entry point of the computation 
void
MR_Run(int argc, char *argv[], 

	    Mapper map, int num_mappers, 
	    Reducer reduce, int num_reducers, 
        Partitioner partition) { 

// initialize the threadpool 
    // create threadpool for mapper
    // create threadpool for reducr
  
// intialize the disk for storing key and value pair 
// Initantiate the map reduce tasks ( start all threads )

// wait for all reduce task to finish
}


void on_exit_call(char * message) { 
    printf("ERROR : %s\n", message);
}

int main(int argc, char *argv[]) {
    // map and reduce are user defined function ( that uses mapreduce parallelization)  
    MR_Run(argc, argv, Map, 10, Reduce, 10, MR_DefaultHashPartition);
}



