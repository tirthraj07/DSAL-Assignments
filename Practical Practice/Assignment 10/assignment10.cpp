/*
Read the marks obtained by students of second year in an online examination of particular 
subject. Find out minimum/maximum marks obtained in that subject. Use heap data structure. 
Analyze the algorithm.

basically implement minHeap and maxHeap
*/

#include <iostream>
using namespace std;

class Student{
private:
    string name;
    int marks;
public:
    Student(){}
    Student(string name, int marks):name(name),marks(marks){}

    bool operator < (Student obj){
        return this->marks<obj.marks;
    }

    bool operator > (Student obj){
        return this->marks > obj.marks;
    }

    friend class MinHeap;
    friend class MaxHeap;
};


class MaxHeap{
private:
    Student* arr;
    int size;
    int curr;

    void insert(Student s){
        if(curr == size - 1){
            cout<<"Heap overflow"<<endl;
            return;
        }
        curr = curr+1;
        arr[curr] = s;
        int index = curr;
        while(index>1){
            int parent = index/2;

            if(arr[parent]<arr[index]){
                swap(arr[parent],arr[index]);
                index = parent;
            }
            else{
                return;
            }
        }
    }

    
public:
    MaxHeap(int size):size(size){
        arr = new Student[size];
        curr = 0;
    }


    void insert(string name, int marks){
        insert(Student(name, marks));
    }

    void displayMax(){
        if(curr == 0){
            cout<<"Heap Empty"<<endl;
        }
        cout<<arr[1].name<<" : "<<arr[1].marks<<endl;
    }

    void printHeap(){
        for(int i=1; i<=curr; i++){
            cout<<i<<endl;
            cout<<arr[i].name<<" : "<<arr[i].marks<<endl<<endl;
        }
    }

    void removeMax(){
        if(curr == 0){
            cout<<"Heap Underflow"<<endl;
            return;
        }

        arr[1] = arr[curr];
        arr[curr] = Student();
        curr = curr-1;

        int index = 1;
        while(index < curr){
            int leftChildIndex = 2*index;
            int rightChildIndex = 2*index + 1;

            if(leftChildIndex < curr && arr[leftChildIndex] > arr[index] && arr[rightChildIndex] < arr[leftChildIndex]){
                swap(arr[leftChildIndex], arr[index]);
                index = leftChildIndex;
            }
            else if(leftChildIndex == curr && arr[leftChildIndex] > arr[index]){
                swap(arr[leftChildIndex], arr[index]);
                index = leftChildIndex;
            }
            else if( rightChildIndex <= curr && arr[rightChildIndex] > arr[index] && arr[rightChildIndex] > arr[leftChildIndex] ){
                swap(arr[rightChildIndex],arr[index]);
                index = rightChildIndex;
            }
            else{
                return;
            }
        }
        return;
    }

};

class MinHeap{};

int main(){

    MaxHeap heap(6);
    heap.insert("Tirthraj", 10);
    heap.printHeap();
    heap.insert("Vardhan", 20);
    heap.printHeap();
    heap.insert("Mulay", 5);
    heap.printHeap();
    heap.insert("Adikul", 40);
    heap.printHeap();
    heap.insert("Arnav", 15);
    heap.printHeap();
    
    heap.displayMax();

    heap.removeMax();

    heap.printHeap();

    heap.displayMax();



}