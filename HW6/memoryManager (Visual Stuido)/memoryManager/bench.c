//
//  main.c
//  Memory Management
//
//  Created by Tianshu Bao on 2/17/13.
//  Copyright (c) 2013 Tianshu Bao. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mem.h"


#define _CRT_SECURE_NO_WARNINGS


int main(int argc, const char * argv[])
{
	uintptr_t total_size = 0;
	uintptr_t total_free = 0;
	uintptr_t n_free_block = 0;

	void* getmems[6];
	getmems[0] = getmem(7000);
	free_list* temp1 = list;
	printf("Latest allocated thing: %p, Address: %d\n",getmems[0],(uintptr_t)getmems[0]);
	getmems[1] = getmem(5000);
	//free_list* temp2 = list;
	printf("Latest allocated thing: %p, Address: %d\n",getmems[1],(uintptr_t)getmems[1]);
	getmems[2] = getmem(7000);
	//free_list* temp3 = list;
	printf("Latest allocated thing: %p, Address: %d\n",getmems[2],(uintptr_t)getmems[2]);
	getmems[3] = getmem(4000);
	//free_list* temp4 = list;
	printf("Latest allocated thing: %p, Address: %d\n",getmems[3],(uintptr_t)getmems[3]);
 
	freemem(getmems[0]);
	freemem(getmems[1]);
	freemem(getmems[2]);
	freemem(getmems[3]);

	getmems[4] = getmem(8000);
	printf("Latest allocated thing: %p, Address: %d\n",getmems[4],(uintptr_t)getmems[4]);
	getmems[5] = getmem(500);
	printf("Latest allocated thing: %p, Address: %d\n",getmems[5],(uintptr_t)getmems[5]);

	freemem(getmems[4]);
	freemem(getmems[5]);
 
	//FILE *f = fopen_s("/Users/Tianshu/Desktop/test.txt", "w");
 
	get_mem_stats(&total_size, &total_free, &n_free_block);
	//print_heap(f);
    return 0;
}

/*

*/
/*
    int ntrials = 10000;
    int pctget = 50;
    int pctlarge = 10;
    int small_limit = 200;
    int large_limit = 20000;
    unsigned int random_seed = (unsigned int)clock();
    
    if (argc > 1) {
        ntrials = atoi(argv[1]);
    }
    if (argc > 2) {
        pctget = atoi(argv[2]);
    }    
    if (argc > 3) {
        pctlarge = atoi(argv[3]);
    }    
    if (argc > 4) {
        small_limit = atoi(argv[4]);
    }    
    if (argc > 5) {
        large_limit = atoi(argv[5]);
    }
    if (argc > 6) {
        random_seed = atoi(argv[6]);
    }
    
    srand(random_seed);
    uintptr_t size;
    int getmem_num;
	getmem_num= ntrials * (100 / pctget);
    void *getmem_block[getmem_num];
    int index = 0;
    clock_t start_time = clock();
    clock_t end_time;
    double CPU;
    
    for (int i = 1; i <= ntrials; i++) {
        if ((pctget > (rand() % 100)) && (index < getmem_num)) {
            if ((pctlarge > (rand() % 100))) {
                size = rand() % (large_limit - small_limit) + small_limit;
            } else {
                size = (rand() % small_limit) + 1;
            }
            getmem_block[index] = getmem(size);
            index++;
        } else {
            if (index > 0) {
                int j = rand() % index;
                freemem(getmem_block[j]);
                getmem_block[j] = getmem_block[index];
                getmem_block[index] = NULL;
                index--;
            } 
        }
        
        
        if ((i % 10) == 0) {
            end_time = clock();
            CPU = ((double)end_time - (double)start_time) / CLOCKS_PER_SEC;
            
            uintptr_t total_size = 0;
            uintptr_t total_free = 0;
            uintptr_t n_free_block = 0;
            
            get_mem_stats(&total_size, &total_free, &n_free_block);
            
            double average;
            if (n_free_block == 0) {
                average = 0;
            } else {
                average = (double)total_free / (double)n_free_block;
            }
            
            
            printf("%d%%: \n", i);
            printf("Total CPU time: %f\n", CPU);
            printf("Total amount of storage: %d\n", (int)total_size);
            printf("Total number of free blocks: %d\n", (int)total_free);
            printf("Avrage number of free bytes: %f\n", average);
            printf("\n");
            
        }
        
    }
	*/