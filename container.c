
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<ctype.h>
#include<assert.h>
#include<stdarg.h>
#include<time.h>
#include<stdarg.h>
#include<pthread.h>


#include "container.h"

struct Disk disk; 

//NOTE : not used at the moment
int compare(const void* a, const void *b) { 
    // casting to Pair
    const Pair * p1  =  (Pair *)a; 
    const Pair * p2  =  (Pair *)b; 
    // extract keys
    const char *key1 = p1->key ; 
    const char *key2 = p2->key ; 
    return strcmp(key1, key2);
}


/*
 * NOTE : This function is only called by add_pair(...) function
 * */
void add_partition(struct Part * partitions, int partition_num, struct Pair * pair){ 
    assert(partition_num >= 0);
    struct Part * partition =  &partitions[partition_num]; // get the particular partition
    int size = partition-> size ;  
    partition->size++; 
    struct Pair * tmp = 
        (struct  Pair * ) realloc(partition -> list, sizeof(struct Pair) * size); 
    if (tmp == NULL) { 
        disk_failure_message("failure while dynamically reallocating new memory block to parition");
        exit(1);
    } 
    partition -> list= tmp ;  
    *(partition -> list + size )  = *pair ;  
}

void add_pair(struct Disk *disk ,  int partition_num, char * key , int value) { 
    assert(partition_num >= 0);
    struct Part * partitions = disk->partitions; 
    pthread_mutex_lock(&disk->disk_lock);
    struct Pair * tmp = (struct Pair *)malloc(sizeof(struct Pair)) ;
    if (tmp == NULL) { 
        pthread_mutex_unlock(&disk -> disk_lock);
        exit(1); 
    } 
    tmp -> key = key ; 
    tmp -> count = value ;
    // we have pair that we can add in a given parition
    add_partition(partitions, partition_num, tmp);
    pthread_mutex_unlock(&disk -> disk_lock);
}

/*
 * count : total number of paritions
 * Disk = pointer to disk struct 
 */
void init(int count, struct Disk *disk) { 
    assert(count > 0); 
    disk -> count = count ; 
    disk -> partitions = (struct Part*)malloc(count * sizeof(struct Part));
    if (disk -> partitions == NULL) { 
        exit(1);  // exit with failure
    }
    pthread_mutex_init(&disk->disk_lock, NULL);
}

void printer( struct Disk *disk ) { 
    for(int i = 0 ; i < disk -> count ; i++) { 
        printf("i = %d and num = %d, size = %d\n", i, disk->partitions[i].num, disk -> partitions[i].size);
    }
}

void partition_marker(struct Disk *disk) { 
    for(int i = 0 ;i < disk -> count ; i++) { 
        disk->partitions[i].num = i ; 
    }
}

void partition_printer(struct Disk *disk, int partition_num)  { 

    pthread_mutex_lock(disk -> disk_lock);
    struct Part  partition = disk -> partitions[partition_num]; 
    int size = partition. size ; 
    if (size == 0 ) { 
        printf("Empty\n");
        pthread_mutex_unlock(disk -> disk_lock);
        return  ; 
    }

    // start printing list inside parition
    struct Pair * list = partition.list ; 
    for(int i = 0 ; i < size ; i++) { 
        char * key = list[i].key ; 
        int count= list[i].count ;
        printf("(%s, %d) , ",key , count);
    }

    printf("\n");
    pthread_mutex_unlock(disk -> disk_lock);
} 

void print_disk(struct Disk *disk) { 
    pthread_mutex_lock(disk -> disk_lock);
    int size = disk -> count ; 
    for(int i = 0 ; i < size ; i++) { 
        printf("%d : ", i);
        partition_printer(disk,i);
        printf("\n");
    }
    pthread_mutex_unlock(disk -> disk_lock);
}

// This function is called  when programme terminates
void disk_failure_message(char * message) { 
    printf("[ERROR] : %s\n", message);
}


/* int test () { */  
/*     init(3 , &disk); */
/*     printf("disk count  = : %d\n", disk.count); */
/*     partition_marker(&disk); */
/*     // printer(&disk); */
/*     printf("adding new element to the container 1 : \n"); */
/*     add_pair(&disk, 0, "first", 99); */  
/*     add_pair(&disk, 0, "second", 22); */
/*     /1* add_pair(&disk, 1, "first in second container", 32); *1/ */
/*     /1* printf("\n"); *1/ */
/*     /1* printer(&disk); *1/ */

/*     /1* printf("================\n"); *1/ */
/*     print_disk(&disk); */
/*     printf("================\n"); */
/*     return  0 ; */ 
/* } */

