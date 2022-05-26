
#ifndef __container_h__
#define __container_h__

struct Pair { 
    char* key ;  
    int count ;   
};

struct Part { 
    int num  ; 
    int size ; 
    //struct Node * node ;  // each parition contains  pointer to start of linked list
    struct Pair *list; // dynamic arraylist
};

struct Disk { 
    int count ;
    struct Part *partitions;
    pthread_mutex_t disk_lock; 

}; 


// function prototypes
void add_pair( int parition_num , char * key, int value);
void add_parition( int parition_num , struct Disk *disk  );
void init( int count , struct Disk *disk );
void printer (struct Disk *disk); 
void partition_marker(struct Disk *disk);
void partition_printer(struct Disk *disk, int partition_num); 



#endif 
