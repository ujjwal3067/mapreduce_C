
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


// main TODO : container should have mutex


struct Disk disk; 

//FIXME: add mutex
void add_partition(struct Part * partitions, int partition_num, struct Pair * pair){ 
    assert(partition_num > 0);

    struct Part * partition =  &partitions[partition_num]; // get the particular partition
    int size = partition-> size ;  
    partition->size++; 
    struct Pair * tmp = 
        (struct  Pair * ) realloc(partition -> list, sizeof(struct Pair) * size); 
     
    partition -> list= tmp ;  
    *(partition -> list + size )  = *pair ;  
}



//FIXME: add mutex
void add_pair(int partition_num, char * key , int value) { 
    assert(partition_num > 0 );
    struct Part * partitions = disk.partitions; 
    pthread_mutex_lock(&)
    struct Pair * tmp = (struct Pair *)malloc(sizeof(struct Pair)) ;
    if (tmp == NULL) { 
        exit(1); 
    } 
    tmp -> key = key ; 
    tmp -> count = value ;
    // we have pair that we can add in a given parition
    add_partition(partitions, partition_num, tmp);
}

/*
 * count : total number of paritions
 * Disk = pointer to disk struct 
 */
//FIXME: add mutex
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

//FIXME: add mutex
void partition_marker(struct Disk *disk) { 
    for(int i = 0 ;i < disk -> count ; i++) { 
        disk->partitions[i].num = i ; 
    }
}

//FIXME: add mutex
void partition_printer(struct Disk *disk, int partition_num)  { 
    // get partition
    struct Part  partition = disk -> partitions[partition_num]; 
    int size = partition. size ; 

    if (size == 0 ) { 
        printf("Empty\n");
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
} 

//FIXME: add mutex
void print_disk(struct Disk *disk) { 
    int size = disk -> count ; 
    for(int i = 0 ; i < size ; i++) { 
        printf("%d : ", i);
        partition_printer(disk,i);
        printf("\n");
    }
}


/*int test () { 
    init(3 , &disk);
    printf("disk count  = : %d\n", disk.count);
    partition_marker(&disk);
    // printer(&disk);
    printf("adding new element to the container 1 : \n");
    add_pair(disk.partitions , 0, "first", 99);
    add_pair(disk.partitions , 0, "second", 22);
    add_pair(disk.partitions , 1, "first in second container", 32);
    printf("\n");
    printer(&disk);

    printf("================\n");
    print_disk(&disk);
    printf("================\n");
    return  0 ; 
}
*/
