/*

Name : Tirthraj Mahajan
Class: SE-02
Roll No: 21242

Implement the Heap sort algorithm using heap data structure with
modularity of programming language.
*/

/*
In the assignment we are only asked to create heap sort but i also added insertion and deletion as well creating a dynamic array aka vector
They are extra features
*/




#include <iostream>
using namespace std;

class Heap{
private:
    int* arr;       // Implementing the heap -> aka CBT using array where the first node is at index 1
    int size;       // Total size of the array created
    int curr;       // Pointer to the last index inserted. Default 0 if empty

    void extendHeap(){
        // Increase the arr size by 2
        int* newArr = new int[2*size];
        // Copy elements from old array to new array
        for(int i=0; i<curr; i++){
            newArr[i] = arr[i];
        }
        // Update the size
        size = size*2;
        // Delete the original arr
        delete[] arr;
        // Point to the new memory location
        arr = newArr;
    }

    void heapify(int i, int n){
        int largest = i;
        int leftChildIndex = 2*i;
        int rightChildIndex = 2*i + 1;

        if(leftChildIndex <= n && arr[leftChildIndex] > arr[largest]){
            largest = leftChildIndex;
        }
        
        if(rightChildIndex <= n && arr[rightChildIndex] > arr[largest]){
            largest = rightChildIndex;
        }

        if(largest != i){
            swap(arr[i],arr[largest]);
            heapify(largest, n);
        }
    }




public:
    Heap(int size=10):size(size){   // You don't need to specify the size of the heap as I have make a vector
        arr = new int[size];        // Initializing array
        arr[0] = -1;                // Let the first index be empty as we start inserting from index 1
        curr = 0;                   // Initializing the current pointer
    }


    void insert(int num){
        curr = curr + 1;        // Increase the current pointer by 1
        if(curr==size){
            extendHeap();       // Double the size of array if the array goes beyond the limit. Basically implementing vector
        }

        arr[curr] = num;

        int index = curr;
        while(index > 1){
            int parent = index/2;

            if(arr[parent]<arr[index]){
                swap(arr[parent],arr[index]);
                index = parent;
            }
            else{
                break;
            }
            
        } 
    }

    void deleteFromHeap(){
        if(curr==0){
            cout<<"Heap Empty Already"<<endl;
            return;
        }
        
        // Replace the root with the last leaf node
        arr[1] = arr[curr];
        // delete the last leaf node;
        arr[curr] = 0;
        curr = curr - 1;

        // Now place the root at its appropriate position
        int i = 1;
        while(i<curr){
            int leftNodeIndex = 2*i;
            int rightNodeIndex = 2*i + 1;

            /*
                Check for 3 conditions
                1. Check if the child index is not beyond the range (aka curr)
                2. Check if the child is greater than the parent (i)
                3. Check if the child is greater than the sibling (2*i , 2*i+1)
            */

            if(leftNodeIndex<=curr&&arr[leftNodeIndex]>arr[i]&&arr[leftNodeIndex]>=arr[rightNodeIndex]){
                swap(arr[i],arr[leftNodeIndex]);
                i = leftNodeIndex;
            }else if(rightNodeIndex<=curr&&arr[rightNodeIndex]>arr[i]&&arr[rightNodeIndex]>=arr[leftNodeIndex]){
                swap(arr[i],arr[rightNodeIndex]);
                i = rightNodeIndex;
            }
            else{
                return;
            }

        }

    }

    void make_heap(int nums[], int n){
        /*
            Copy the array provided with its size into our arr and accordingly update the variables curr,size
        */

        size = n+1;        // Cause we have the 0th index empty
        curr = 0;             // Reinitialize the curr pointer to point to 0
        delete[] arr;               // Delete the previous arr
        arr[0] = -1;                // Initialize the arr[0] to -1
        for(int i=0; i<size-1; i++){
            arr[i+1] = nums[i];     // Arr: 1 to size; nums 0 to size-1;
            curr+=1;                // Or you can directly set curr = n;
        }


        /*
            Since we are making a CBT with heap order property, we don't need to process (n/2+1)th to n nodes as they are going to be leaf nodes

            Therefore, we will process the n/2 nodes from backwards and verify that they are heaps
            Thus, we will call heapify from n/2 to 1

            Note: here n = curr as it the the index of the last nodes. It also shows how many nodes are present in the tree
        */

        for(int i=curr/2; i>0; i--){
            heapify(i, curr);
        }
    }

    void heapSort(){
        if(curr == 0){
            cout<<"The Heap is empty"<<endl;
            return;
        }
        if(curr == 1) return;

        int n = curr;

        while(n>1){
        
            // Swap the root with the last index as the root is the largest element
            swap(arr[n], arr[1]);

            n--;

            // Call Heapify on the new root to bring it in the correct position
            heapify(1,n);

        }


    }


    void print(){
        for(int i=1; i<=curr; i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }


};


int main(){
    Heap hp;
    hp.insert(50);
    hp.insert(55);
    hp.insert(53);
    hp.insert(52);
    hp.insert(54);
    hp.print();

    hp.deleteFromHeap();
    hp.print();

    int arr[] = {10,20,30,40,50,60,70,80,90,100};
    hp.make_heap(arr,10);
    hp.print();

    hp.heapSort();
    hp.print();


}