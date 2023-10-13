#include <stdio.h> 
#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;

void swap(int arr[], int a, int b)
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void selectionSort(int arr[], int size) 
{ 
    for(int i = 0; i < size; i++){
        int min_index = i;

        for(int j = i + 1; j < size; j++){

            if(arr[min_index] > arr[j]){
                min_index = j;
            }
        }
        swap(arr, min_index, i);
    }
} 

void insertionSort(int arr[], int size) 
{ 
  for(int sorted = 0; sorted < size - 1; sorted++){
      for(int i = sorted + 1; i > 0; i--){
          if(arr[i - 1] > arr[i]){
              int temp = arr[i];
              arr[i] = arr[i-1];
              arr[i - 1] = temp;
          } else{
              break;
          }
      }
  }
}

int partition(int arr[], int p, int r)
{
    if(p == r){
        return p;
    }

    int pivot = arr[r];
    int low = p - 1;
    int high = r;

    for(;;){
        do{
            low++;
            if(low == r) break;
        }while(arr[low] < pivot);

        do{
            high--;
            if(high == p) break;
        }while (arr[high] > pivot);

        if(low >= high){
            swap(arr, low, r);
            return low;
        }
        swap(arr, low, high);
    }
}

void quicksort(int arr[], int p, int r)
{
    if(p >= 0 && r >= 0 && p < r){
        int q = partition(arr, p, r);
        quicksort(arr, p, q - 1);
        quicksort(arr, q + 1, r);
    }
}

void quickSort(int arr[], int size) 
{ 
    quicksort(arr, 0, size - 1);
}
