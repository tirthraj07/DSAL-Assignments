/*
Implement all the functions of a dictionary (ADT) using open hashing technique: separate chaining using linked list Data: Set of
(key, value) pairs, Keys are mapped to values, Keys must be comparable, and Keys must be unique. 
Standard Operations: Insert (key, value), Find(key), Delete(key)
*/
#include<iostream>
#include<string>
#include <limits>
using namespace std;




class Node{
private:
    string key, value;
    Node* next;
public:
    Node(string key, string value):key(key),value(value),next(nullptr){}
    friend class HashTable;
};

class HashTable{
private:
    Node**arr;
    int size;
public:
    HashTable():size(26){
        arr = new Node*[size];
        for(int i=0; i<size; i++){
            arr[i] = nullptr;
        }
    }

    void insert(string key, string value){
        if(key==" "||key==""){
            cout<<"Cannot enter empty key"<<endl;
            return;
        }
        
        Node* newNode = new Node(key, value);
        char c = key[0];
        int asciiVal = int(c);
        int pos = -1;
        if(asciiVal>=65&&asciiVal<=90){
            pos = asciiVal-65;
        }
        else if(asciiVal>=97&&asciiVal<=122){
            pos = asciiVal - 97;
        }
        else{
            cout<<"String contains a non alpha character"<<endl;
            return;
        }

        if(arr[pos]==nullptr){
            arr[pos] = newNode;
        }
        else{
            Node* curr = arr[pos];
            while(curr!=nullptr){
                if(curr->key==key){
                    cout<<"Error: Key "<<key<<" inserted more than once!"<<endl;
                    return;
                }
                curr = curr->next;
            }
            newNode->next = arr[pos];
            arr[pos] = newNode;
        }
        cout<<"Key inserted successfully!"<<endl;
    }

    void search(string key){
        if(key==" "||key==""){
            cout<<"Cannot enter empty key"<<endl;
            return;
        }
        char c = key[0];
        int asciiVal = int(c);
        int pos = -1;
        if(asciiVal>=65&&asciiVal<=90){
            pos = asciiVal-65;
        }
        else if(asciiVal>=97&&asciiVal<=122){
            pos = asciiVal - 97;
        }
        Node* curr = arr[pos];
        while(curr!=nullptr){
            if(curr->key==key){
                cout<<"Key "<<key<<" Found!"<<endl;
                cout<<"Value: "<<curr->value<<endl;
                return;
            }
            curr = curr->next;
        }
        cout<<"Key "<<key<<" Not Found!"<<endl;
        return;
    }

    void deleteKey(string key){
        if(key==" "||key==""){
            cout<<"Cannot enter empty key"<<endl;
            return;
        }
        char c = key[0];
        int asciiVal = int(c);
        int pos = -1;
        if(asciiVal>=65&&asciiVal<=90){
            pos = asciiVal-65;
        }
        else if(asciiVal>=97&&asciiVal<=122){
            pos = asciiVal - 97;
        }
        Node* prev = nullptr;
        Node* curr = arr[pos];
        if(curr==nullptr){
            cout<<"Key Not Found!"<<endl;
            return;
        }
        else if(curr->key==key){
            arr[pos] = curr->next;
            cout<<"Key Deleted Successfully!"<<endl;
            return;
        }
        else{
            while(curr!=nullptr&&curr->key!=key){
                prev = curr;
                curr = curr->next;
            }
            if(curr==nullptr){
                cout<<"Key Not Found!"<<endl;
                return;
            }
            prev->next = curr->next;
            delete curr;
            cout<<"Key Deleted Successfully!"<<endl;
        }

    }


    void viewTable(){
        Node* curr = nullptr;
        cout<<"Index, key:value"<<endl;
        for(int i=0; i<size; i++){
            curr = arr[i];
            cout<<i<<" : "<<endl;
            while(curr!=nullptr){
                cout<<curr->key<<" : "<<curr->value<< ", "<<endl;
                curr=curr->next;
            }
            cout<<endl;
        }
        cout<<endl;
    }

};

class Menu{
private:
    HashTable* table;
    int choice;
public:
    Menu(){
        table = nullptr;
        askChoice();
        initiateChoice();
    }

    void askChoice(){
        cout<<"What do you want to do?"<<endl;
        cout<<"1. Create an empty hash table"<<endl;
        cout<<"2. Insert a record in hash table"<<endl;
        cout<<"3. Search a record in hash table"<<endl;
        cout<<"4. Delete a record in hash table"<<endl;
        cout<<"5. View table"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<">> ";
        cin>>choice;
        cout<<endl;
    }

    void initiateChoice(){
        bool ch;
        string key,value;
        switch(choice){
            case 1:
                if(table!=nullptr){
                    cout<<"Do You want to override the exisiting table?"<<endl;
                    cin>>ch;
                    if(!ch){
                        cout<<"No changes applied!"<<endl;
                        break;
                    }
                }
                table = new HashTable;
                cout<<"Empty hash table created successfully!"<<endl;
                break;
            case 2:
                if(table==nullptr){
                    cout<<"Create an Empty Table first!"<<endl;
                    break;
                }
                cout<<"Enter Key to be inserted"<<endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin,key);
                cout<<"Enter Value to be inserted"<<endl;
                getline(cin,value);
                
                table->insert(key,value);
                break;
            case 3:
                if(table==nullptr){
                    cout<<"Create an Empty Table first!"<<endl;
                    break;
                }
                cout<<"Enter Key to be Searched"<<endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin,key);
                table->search(key);
                break;
            case 4:
                if(table==nullptr){
                    cout<<"Create an Empty Table first!"<<endl;
                    break;
                }
                cout<<"Enter Key to be Deleted"<<endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin,key);
                table->deleteKey(key);
                break;
            case 5:
                if(table==nullptr){
                    cout<<"Create an Empty Table first!"<<endl;
                    break;
                }
                table->viewTable();
                break;
            case 6:
                cout<<"Thank You for using"<<endl;
                return;
                break;
            default:
                cout<<"Invalid Operation"<<endl;
        }
        retry();   

    }

    void retry(){
        askChoice();
        initiateChoice();
    }
};


int main(){
    Menu m;

    // HashTable table;
    // table.viewTable();
    // table.insert("Apple","a fruit");
    // table.insert("Ball", "a solid or hollow spherical or egg-shaped object that is kicked, thrown, or hit in a game.");
    // table.insert("Cat","an animal");
    // table.insert("Dog","an animal");
    // table.insert("apple","a fruit");
    // table.insert("ball", "a solid or hollow spherical or egg-shaped object that is kicked, thrown, or hit in a game.");
    // table.insert("cat","an animal");
    // table.insert("dog","an animal");
    // table.insert("Apple","a fruit");
    // table.viewTable();
    // table.search("apple");
    // table.search("Apple");
    // table.search("Cat");
    // table.search("dog");
    // table.search("zebra");
    // table.deleteKey("apple");
    // table.deleteKey("Cat");
    // table.deleteKey("dog");
    // table.deleteKey("ball");
    // table.viewTable();

    return 0;
}