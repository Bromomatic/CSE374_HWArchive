//
//  print_heap.c
//  Memory Management
//
//  Created by Tianshu Bao on 2/26/13.
//  Copyright (c) 2013 Tianshu Bao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "mem_impl.h"
#include "mem.h"

void print_heap(FILE *f)
{
    free_list *current = list;
	while (current!=NULL) {
		fprintf(f, "%p, 0x%x\n", current, (int)current -> size);
		current = current -> next;
	}
}