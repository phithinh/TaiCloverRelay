#include <p30f4011.h>
#include "../INCLUDE/system.h"

void qs(int *A, int left,int right) {
   int register i,j;int x,y;
    i=left; j=right;
    x= A[(left+right)/2];
    do {
        while(A[i]<x && i<right) i++;
        while(A[j]>x && j>left) j--;
        if(i<=j){
            y=A[i];A[i]=A[j];A[j]=y;
            i++;j--;
        }
    } while (i<=j);
    if (left<j) qs(A,left,j);
    if (i<right) qs(A,i,right);
}
void Quick_sort(int *A, int n){
    qs(A,0,n-1);
}

int* Find_max(int *Array,int length)
{
	int max_index=0;
	int i=0;
	for(i=0;i<length;i++)
	{
		if(Array[max_index]<Array[i])
			max_index=i;
	}	
	return (&Array[max_index]);
}

int* Find_min(int *Array,int length)
{
	int min_index=0;
	int i=0;
	for(i=0;i<length;i++)
	{
		if(Array[min_index]>Array[i])
			min_index=i;
	}
	return (&Array[min_index]);
} 
