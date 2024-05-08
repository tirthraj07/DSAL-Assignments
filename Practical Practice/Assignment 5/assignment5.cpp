/*
Implement all the functions of a dictionary (ADT) using open hashing technique: separate 
chaining using linked list Data: Set of (key, value) pairs, Keys are mapped to values, Keys 
must be comparable, and Keys must be unique. Standard Operations: Insert (key, value), 
Find(key), Delete(key). 

Use hash function as H(x) = (3x+5) % 10
*/
#include <iostream>
#include <string>
using namespace std;

class Node{
private:
    string key;
    string value;
    Node* next;    
public:
    Node(string key="",string value="",Node* next=NULL):key(key),value(value),next(next){}
    
    friend ostream & operator << (ostream &out, const Node &node); 
    friend class HashTable;
};

// optional fancy shit 
ostream & operator << (ostream &out, const Node &node){
    out<<node.key<<" : "<<node.value;
    return out;
}

class HashTable{
private:
    Node** arr;
    const int SIZE;

    string toLowerString(string str){
        string newStr = "";
        for(int i=0; i<str.length(); i++){
            char character = str[i];
            newStr += tolower(character);
        }
        return newStr;
    }

    int calculateHash(string str){
        int hash = 0;
        for(int i=0; i<str.length(); i++){
            char character = str[i];
            hash += (int) character;
        }
        return hash;
    }

    int hashFunction(string str){
        if(str=="") return -1;
        int x = calculateHash(str);
        // Given: hash function as H(x) = (3x+5) % 10
        // Here i am assuming that mod 10 means mod SIZE as it wouldn't make any sense if we are creating a table of bigger or smaller size if we mod 10 by default.
        // Also i am assuming that x is the factor by which we determine the key numerically. So it is upto our preference what we want x to be
        return (3 * x + 5 )%SIZE;
    }

public:
    HashTable(int SIZE=10):SIZE(SIZE){
        arr = new Node*[SIZE];
        for(int i=0; i<SIZE; i++){
            arr[i] = NULL;
        }
    }

    void insert(string key, string value){
        key = toLowerString(key);
        Node* newNode = new Node(key, value);
        int hashIndex = hashFunction(key);
        if(hashIndex == -1){
            cout<<"Invalid key. Please enter a valid key"<<endl;
            return;
        }

        if(arr[hashIndex]==NULL){
            arr[hashIndex] = newNode;
            cout<<"Pair inserted successfully"<<endl;
            return;
        }

        Node* curr = arr[hashIndex];
        Node* prev = NULL;
        while(curr){
            prev = curr;
            if(curr->key==key){
                cout<<"Key already exists in the table"<<endl;
                return;
            }
            curr = curr->next;
        }
        prev->next = newNode;
        cout<<"Pair inserted successfully"<<endl;
    }

    void search(string keyToBeSearched){
        string key = toLowerString(keyToBeSearched);
        int hashIndex = hashFunction(key);
        if(hashIndex == -1){
            cout<<"Invalid key entered. Please enter a valid key"<<endl;
            return;
        }
        Node* curr = arr[hashIndex];
        while(curr){
            if(curr->key == key){
                cout<<"Key found in the dictionary"<<endl;
                cout<<*curr<<endl;
                return;
            }
            curr = curr->next;
        }

        cout<<"Key "<<key<<" not in the hash table"<<endl;
        return;
    }

    void deleteKey(string keyToBeSearched){
        string key = toLowerString(keyToBeSearched);

        int hashIndex = hashFunction(key);

        if(hashIndex == -1){
            cout<<"Invalid key entered. Please enter a valid key"<<endl;
            return;
        }

        if(arr[hashIndex]==NULL){
            cout<<"Cannot find the key to delete in table"<<endl;
            return;
        }
        
        if(arr[hashIndex] && arr[hashIndex]->key == key){
            arr[hashIndex] = arr[hashIndex]->next;
            cout<<"Key deleted successfully"<<endl;
            return;
        }
        
        
        Node* prev = arr[hashIndex];
        Node* curr = prev->next;
        while(curr){
            if(curr->key==key){
                prev->next = curr->next;
                cout<<"Key deleted successfully"<<endl;
                return;
            }

            prev = curr;
            curr = curr->next;
        }        

        cout<<"Cannot find the key to delete in table"<<endl;
        return;

    }

    void displayTable(){
        for(int i=0; i<SIZE; i++){
            Node* curr = arr[i];
            cout<<i<<" : "<<endl;
            while(curr){
                cout<<*curr<<endl;
                curr = curr->next;
            }
            cout<<"----------x----------"<<endl;
        }
    }

};



int main(){

    HashTable table;
    // Make the code menu driven. I am too tired.

    string key, value;
    do{
        cout<<"Enter key to be entered (-1 to quit) : ";
        getline(cin, key);
        if(key == "-1") break;
        cout<<"Enter value to be entered : ";
        getline(cin, value);
        table.insert(key, value);
    }while(key != "-1");

    table.displayTable();   

    cout<<"Which key do you want to search?"<<endl;     // try inserting key that exists
    getline(cin, key);
    table.search(key);

    cout<<"Which key do you want to search?"<<endl;     // try inserting key that doesn't exist
    getline(cin, key);
    table.search(key);

    cout<<"Which key do you want to delete?"<<endl;     // try deleting key that exists
    getline(cin, key);
    table.deleteKey(key);

    cout<<"Which key do you want to delete?"<<endl;     // try deleting key that doesn't exist
    getline(cin, key);
    table.deleteKey(key);

    table.displayTable();


}