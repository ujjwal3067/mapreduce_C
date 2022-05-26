// dynamic probing for bucket miss
#include<stdlib.h> 
#include<stdio.h> 
#include<assert.h> 
#include<string.h> 
#include"hashtable.h"

struct entry{ 
    char*key ; 
    void* value ; 
};

struct hashtable { 
    unsigned int  size ; 
    unsigned int  capacity ; 
    entry * body ; 
};


//cont : link : https://github.com/marekweb/datastructs-c
