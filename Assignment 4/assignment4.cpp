/*
Consider telephone book database of N clients. Make use of a hash
table implementation to quickly look up client’s telephone number.
Make use of two collision handling techniques and compare them using
number of comparisons required to find a set of telephone numbers
(Note: Use linear probing with replacement and without replacement)
*/

#include <iostream>
#include <string>
using namespace std;

class Record{
public:
    long int key;
    string value;

    Record():key(0),value(""){}
    Record(long int key, string value):key(key), value(value){}
    friend class HashTable;
};


class HashTable{
private:
    int size;
    Record* table;
    bool replacement; /* 0 -> without replacement and 1 -> with replacement */

public:
    HashTable(int size, bool replacement=false):size(size),replacement(replacement){
        table = new Record[size];
    }

    int hashFunction(long int key){
        return key%size;
    }


    bool isRecordEmpty(Record record){
        return record.key==0&&record.value=="";
    }

    void insert(long int key, string value){
        Record newRecord = Record(key,value);
        int index = hashFunction(key);

        if(isRecordEmpty(table[index])){
            table[index] = newRecord;
            return;
        }
        else if(table[index].key==key){
            cout<<"Key "<< key << " has already been inserted"<<endl;
            return;
        }
        else if(replacement==true&&hashFunction(table[index].key)!=index){
            long int replacedKey = table[index].key;
            string replacedValue = table[index].value;
            table[index] = newRecord;
            insert(replacedKey, replacedValue);
            return;
        }
        
        for(int i=(index+1)%size; i<size && i!=index; i=(i+1)%size){
            if(isRecordEmpty(table[i])){
                table[i] = newRecord;
                return;
            }
            else if(table[i].key==key){
                cout<<"Key "<< key << " has already been inserted"<<endl;
                return;
            }
        }

        cout<<"No Empty Space in the Table"<<endl;
        return;

    }

    void printTable(){
        cout<<"index  key  value"<<endl;
        for(int i=0; i<size; i++){
            cout<<i<<"   "<<table[i].key<<"   "<<table[i].value<<endl;
        }
        cout<<endl;
    }

    string search(long int key){
        int index = hashFunction(key);
        if(table[index].key == key){
            cout<<"Key Found! Key:"<<key<<" : Value:"<<table[index].value<<endl;
            return table[index].value;
        }
        
        for(int i = (index+1)%size; i<size&&i!=index; i=(i+1)%size){
            if(table[i].key==key){
                cout<<"Key Found! Key:"<<key<<" : Value:"<<table[i].value<<endl;
                return table[i].value;
            }
        }

        cout<<"Key Not Found"<<endl;
        return "";

    }


};


class Menu{
private:
    int choice;
    HashTable* htableptr;
public:
    Menu(){
        htableptr = nullptr;
        askChoice();
        initiateOperation();
    }

    void askChoice(){
        cout<<"What do you want to do?"<<endl;
        cout<<"1. Create Hash Table"<<endl;
        cout<<"2. Enter Record in Table"<<endl;
        cout<<"3. Search Record in Table"<<endl;
        cout<<"4. Print Table"<<endl;
        cout<<"5. Exit"<<endl;
        cin>>choice;
        cout<<endl;
    }

    void initiateOperation(){
        bool ch;
        int num;
        long int key;
        string value;

        switch(choice){
            case 1:
                if(htableptr!=nullptr){
                    cout<<"Do you want to replace the hash table?"<<endl;
                    cin>>ch;
                    if(!ch) break;
                }
                cout<<"How many total records?"<<endl;
                cin>>num;
                cout<<"Method? With Replacement or Without Replacement? (1/0)"<<endl;
                cin>>ch;
                htableptr = new HashTable(num,ch);
                cout<<"Table Created Successfully!"<<endl;
                break;
            case 2:
                if(htableptr==nullptr){
                    cout<<"Create a Hash table first!"<<endl;
                    break;
                }
                cout<<"Enter Key and value of the new Record"<<endl;
                cin>>key;
                cin>>value;
                htableptr->insert(key,value);
                cout<<endl;
                break;
            case 3:
                if(htableptr==nullptr){
                    cout<<"Create a Hash table first!"<<endl;
                    break;
                }
                cout<<"Enter the key to be searched"<<endl;
                cin>>key;
                htableptr->search(key);
                break;
            case 4:
                if(htableptr==nullptr){
                    cout<<"Create a Hash table first!"<<endl;
                    break;
                }
                htableptr->printTable();
                break;
            case 5:
                cout<<"Thanks for using :)"<<endl;
                return;
                break;
            default:
                cout<<"Enter a valid choice!"<<endl;
        }
        retry();
    }

    void retry(){
        askChoice();
        initiateOperation();
    }

};


int main(){
    Menu m;

    // Record arr[5] = {Record(1,"A"),Record(6,"B"),Record(3,"C"),Record(4,"D"),Record(7,"E")};
    // HashTable table(5,1);
    // for(int i=0; i<5; i++){
    //     table.insert(arr[i].key, arr[i].value);
    // }
    // table.printTable();

    // cout<<table.search(6)<<endl;

}