
#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// custom header
#include "container.h"
#include "mapreduce.h"

int num_partitions; 

// Code for testing purpose
void Map(char *file_name) {
    FILE *fp = fopen(file_name, "r");
    assert(fp != NULL);

    char *line = NULL;
    size_t size = 0;
    while (getline(&line, &size, fp) != -1) {
        char *token, *dummy = line;
        while ((token = strsep(&dummy, " \t\n\r")) != NULL) {
            MR_Emit(token, 1); // MR_Emit should store this pair in disk (paritiion)
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

void MR_Emit(char *key, int value) { 
    unsigned long container_hash = MR_DefaultHashPartition(key, num_partitions);
    add_pair(container_hash, key, value);
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

// create a linked list of the filenames for the threads to pick to run Map function 
// create a data structure that has linked list of filesname and mutex for concurrent processing

}


void on_exit_call(char * message) { 
    printf("ERROR : %s\n", message);
}


int main(int argc, char *argv[]) {
    // map and reduce are user defined function ( that uses mapreduce parallelization)  
    MR_Run(argc, argv, Map, 10, Reduce, 10, MR_DefaultHashPartition);
}

