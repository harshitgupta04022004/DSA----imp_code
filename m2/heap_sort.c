#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void swap(int*a,int*b)
{
    int swap = *a;
    *a =*b;
    *b = swap;
}



void Max_Heapify(int *a,int i,int n)
{
    int l = 2*i;
    int r = 2*i+1;
    int largest;
    if(l<=n && a[l]>a[i])
    {
        largest = l;
    }
    else{
        largest = i;
    }
    if(r<=n && a[r]>a[largest])
    {
        largest = r;
    }
    
    if(largest!=i)
    {
        swap((a+i),(a+largest));
        Max_Heapify(a,largest,n);
    }
}

void Build_Max_Heap_n(int *a, int n)
{
    for(int i=n/2;i>=1;i--)
    {
        Max_Heapify(a,i,n);
    }
}

void HeapSort(int *a,int n)
{
    Build_Max_Heap_n(a,n);
    for(int i=n;i>=2;i--)
    {
        swap((a+n),(a+1));
        n = n-1;
        Max_Heapify(a,1,n);
    }
}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Max_Heap_Inc_Key(int *a,int i, int k)
{
    if(k<a[i])
    {
         printf("new key is smaller than the current key.");
    }
   a[i]=k;

    while(i>1 && a[i/2]<a[i])
    {
        swap((a+i),(a+i/2));
        i = i/2;
    }
}

void Max_Heap_Insert(int *a, int *heap_size, int k) {
    // Increase the size of the heap
    *heap_size += 1;
    a = (int *)realloc(a, (*heap_size + 1) * sizeof(int));

    if (a == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Assign the new element to a placeholder value (-∞)
    (a)[*heap_size] = INT_MIN;

    // Increase the key to the desired value
    Max_Heap_Inc_Key(a, *heap_size, k);
}


// Function to build a Max-Heap using O(n log n) approach
void Build_Max_Heap_nlogn(int *a, int n) {
    int *heap = (int *)malloc(sizeof(int)); // Start with an empty heap
    int heap_size = 0;

    for (int i = 1; i <= n; i++) {
        Max_Heap_Insert(heap, &heap_size, a[i]);
    }

    // Copy the heap back to the original array
    for (int i = 1; i <= heap_size; i++) {
        a[i] = heap[i];
    }

    free(heap);
}

void printHeap(int *a, int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Enter the size :");
    scanf("%d",&n);

    int* a = (int*)malloc(n*sizeof(int*));
    for(int i=1;i<=n;i++)
    {
        scanf("%d",(a+i));
    }

    Build_Max_Heap_n(a,n);
    // Build_Max_Heap_nlogn(a,n);
    // HeapSort(a,n);
    printHeap(a, n);


}