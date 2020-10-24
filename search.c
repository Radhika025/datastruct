//Implementation for session1_seq_search.h
#include<stdio.h>
#include "ss.h"
int seqsearch(int *a, int n, int key)
{
	for(int i =0; i<n; i++)
	{
		if(*(a+i) == key){
	         return i;
	     }
	}
	return -1;
}

