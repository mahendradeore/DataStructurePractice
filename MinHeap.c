/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#define MAX 100
typedef struct MaxHeap{
    
    int arr[MAX];
    int size;
}MaxHeap;


typedef struct MinHeap{
    
    int arr[MAX];
    int size;
}MinHeap;


void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void AddMinHeap(MinHeap *heap,int val){
    
    if(heap->size == MAX){
        return;
    }
    
    int i = heap->size++;
    heap->arr[i] = val;
    while(i!=0 && heap->arr[(i-1)/2] > heap->arr[i]){
        swap(&heap->arr[i],&heap->arr[(i-1)/2]);
        i=(i-1)/2;
    }
}

void minify(MinHeap *heap, int i){
    
    int smallest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    
    if(left < heap->size && heap->arr[smallest] > heap->arr[left]){
        smallest = left;
    }
    if(right < heap->size && heap->arr[smallest] > heap->arr[right]){
        smallest=right;
    }
    if(smallest != i){
        swap(&heap->arr[i],&heap->arr[smallest]);
        minify(heap,smallest);
    }
}
int extractMinHeap(MinHeap *heap){
    if(heap->size == 0){
        return -1;
    }
    if(heap->size == 1){
        int i = heap->size-1;
        return heap->arr[i];
    }
    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size-1];
    heap->size--;
    minify(heap,0);
    return root;
}

void AddMaxHeap(MaxHeap *heap, int val){
    
    if(heap->size == MAX ){
       printf("Heap full\n");
        return;
    }
    
    int i =  heap->size++;
    heap->arr[i] = val;
    printf("i = %d, size = %d, val = %d \n", i, heap->size, heap->arr[i]);
    while( i!= 0 && heap->arr[(i-1)/2] < heap->arr[i]){
        swap(&heap->arr[(i-1)/2],&heap->arr[i]);
        i = (i-1)/2;
    }
    
}

void maxify(MaxHeap*heap, int i ){
    int maximum = i;
    int left = 2*i +1;
    int right = 2*i+2;
    
    if(left < heap->size && heap->arr[maximum] < heap->arr[left]){
       maximum = left;
    }
    
    if(right < heap->size && heap->arr[maximum] < heap->arr[right]){
       maximum = right;
    }
    if(maximum != i){
        swap(&heap->arr[maximum],&heap->arr[i]);
        maxify(heap,maximum);
    }
}


int extractMaxHeap(MaxHeap *heap){
    if(heap->size==0){
        return -1;
    }
    if(heap->size == 1){
        heap->size--;
        return heap->arr[heap->size];
    }
    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size-1];
    heap->size--;
    maxify(heap,0);
    return root;
}

void printHeap(MaxHeap *heap){
    if(heap->size == 0){
        printf("Heap is empty");
        return;
    }
    for(int i = 0;i < heap->size;i++){
        printf("%d ",heap->arr[i]);
    }
    printf("\n");
}
int main()
{
    MaxHeap heap;
    heap.size = 0;
    AddMaxHeap(&heap,10);
    AddMaxHeap(&heap,80);
    AddMaxHeap(&heap,40);
    AddMaxHeap(&heap,20);
    AddMaxHeap(&heap,100);
    AddMaxHeap(&heap,200);
    printHeap(&heap);
    printf("Extracted = %d \n",extractMaxHeap(&heap));
    printHeap(&heap);
       printf("Extracted = %d\n",extractMaxHeap(&heap));
    printHeap(&heap);
    printf("Extracted = %d\n",extractMaxHeap(&heap));
    printHeap(&heap);
    
    MinHeap mnheap;
    mnheap.size = 0;
    AddMinHeap(&mnheap,20);
    AddMinHeap(&mnheap,100);
    AddMinHeap(&mnheap,200);
    AddMinHeap(&mnheap,10);
    AddMinHeap(&mnheap,80);
    AddMinHeap(&mnheap,40);
   
    printHeap(&mnheap);
    printf("Min Extracted = %d \n",extractMinHeap(&mnheap));
    printHeap(&mnheap);
       printf("Min Extracted = %d\n",extractMinHeap(&mnheap));
    printHeap(&mnheap);
    printf("Min Extracted = %d\n",extractMinHeap(&mnheap));
    printHeap(&mnheap);

    return 0;
}