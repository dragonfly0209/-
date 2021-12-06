#ifndef MsClass_h
#define MsClass_h
#include <iostream>
#include "binary_search.h"
using namespace std;

typedef class classroom *cla;

void Merge(cla A[], int p, int q, int m) 
{
	int n1 = m - p + 1;
	int n2 = q - m;

	cla L[n1];
	cla R[n2];	
	for (int i = 0; i <= n1; i++) 
	{
		L[i] = new classroom;
	}
	for (int i = 0; i <= n2; i++) 
	{
		R[i] = new classroom;
	}

	for (int i = 0; i < n1; i++) 
	{
		L[i] = A[p+i]; 
	}
	for (int i = 0; i < n2; i++) 
	{
		R[i] = A[i+m+1]; 
	}
	L[n1]->priority = 2147483647;
	R[n2]->priority = 2147483647;
	int i = 0, j = 0;
	for (int k = p; k <= q; k++) 
	{
		if (L[i]->priority < R[j]->priority) 
		{
			A[k] = L[i];
			i++;
		}
		else 
		{
			A[k] = R[j];
			j++;
		}
	}
}

void Merge_Sort(cla A[], int p, int q) 
{
	if (p < q) 
	{
		int m = (p + q) / 2;
		Merge_Sort(A, p, m);
		Merge_Sort(A, m + 1, q);
		Merge(A, p, q, m);
	}
}


#endif
