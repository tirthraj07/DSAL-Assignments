/*
Implement the Heap sort algorithm for demonstrating heap data structure with modularity 
of programming language (consider integer data)
*/

#include <iostream>
using namespace std;

class Heap{
private:
    int* arr;
    int size;

    void heapify(int i, int n){
        int largest = i;
        int leftChild = 2*i;
        int rightChild = 2*i + 1;

        if(leftChild <= n && arr[leftChild] > arr[largest]){
            largest = leftChild;
        }

        if(rightChild <= n && arr[rightChild] > arr[largest]){
            largest = rightChild;
        }

        if(i != largest){
            swap(arr[largest],arr[i]);
            heapify(largest, n);
        }

    }

public:
    Heap(int* arr, int size){
        this->size = size+1;
        this->arr = new int[size+1];
        this->arr[0] = -1;
        for(int i=0; i<size; i++){
            this->arr[i+1] = arr[i];
        }
    }

    void make_heap(){
        int n = size-1;
        for(int i=n/2; i>0; i-- ){
            heapify(i,n);
        }
    }

    void heapSort(){
        int n = size-1;
        while(n>1){
            swap(arr[1],arr[n]);
            n--;
            heapify(1,n);
        }
    }

    void print(){
        for(int i=1; i<size; i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
};

int main(){
    int arr[] = {10,20,30,40,50};
    int size = 5;
    Heap h(arr,size);
    h.print(); 
    h.make_heap();
    h.print();
    h.heapSort();
    h.print();
}   