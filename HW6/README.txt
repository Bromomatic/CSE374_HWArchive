1. 	Responsiblities:
	Tianshu - getmem, bench, mem.h, mem_impl.h

	Shawn - freemem, print_heap, get_mem_stats

2. 	The freelist is organized in order of ascending address with the block with
	the smallest address at the head of the list. New blocks are obtained by 
	traversing the free list and looking for a large enough block (cutting off 
	a chunk of the block if its larger than needed by a threshold). If a request
	can't be met, getmem uses malloc to add a new, larger node to the free list.
	Blocks are freed by recasting the given pointer to a free_list type so we can 
	look at its size field, and the address is taken so we can determine its 
	proper location in the sorted free list. If the free block is inserted into
	the list and is adjacent to the nodes before and/or after it, the nodes are
	combined, sizes adjusted, and pointers are properly removed/reassigned.
	
3.	No additional features implemented, however 

4.	Program seems to run reliably for large tests ranging from 1,000 to 10,000 to
	even 100,000 without any noticable hiccups. Time is not being reported properly 
	because of the linux clock, so we are unsure of how 'fast' it is and don't exactly
	have a benchmark to compare it to anyway. Freelist is fairly fragments after 
	running, but that wasn't a part of the design so it's a nonfactor.

5. 	No outside resources consulted, code based on the schemes discussed in lecture.