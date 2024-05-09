/*
Consider telephone book database of N clients. Make use of a hash table implementation 
to quickly look up client‘s telephone number. Make use of two collision handling 
techniques and compare them using number of comparisons required to find a set of 
telephone numbers (Note: Use linear probing with replacement and without replacement). 
Perform following operations 
Use Hash function as H(x) = (3*x + 5)%10
1. Insert
2. Delete
3. Search
4. Display
*/

// This is a sightly complicated implementation of hash table which i don't think they expect in practicals
// but implementing it just for the sake of it

// My implementation assumes that the name (aka key) is unique. you cannot have the same name (even though u can).
// My other implementation took phoneNo as the key as it is a unique characteristic
// However, the problem statement clearly says that "quickly look up client‘s telephone number"
// This means that the user will enter the clients name and get phone no. in return


/*
In this implementation, if we delete more than a certain threshold, then the table will rehash itself
This is because:
If you don't rehash after deletion and the table becomes densely populated with deleted slots, the performance of searching operations could degrade to O(n) because the linear probing sequence may have to traverse through many deleted slots before finding the desired element or an empty slot.
BUT you don't necessarily need to rehash after every deletion
you can set a threshold. In this implementation, if you delete the records HALF the size of table, the table will rehash all the entries

This way, the time complexity of search is greatly optimized

Also, in this implementation, i also added the feature that if you go beyond the pre defined size of the table, the table will double its size and rehash all the entires according to the new sized
This is similar to how we implement vectors in c++

*/


#include<iostream>
#include<string>
using namespace std;

class Record{
private:
    string name;
    string phoneNo;
public:
    Record():name(""),phoneNo(""){};
    Record(string name, string phoneNo):name(name),phoneNo(phoneNo){}
    friend class HashTable;
    friend ostream& operator<< (ostream& out, const Record& rec);
};

ostream& operator << (ostream& out, const Record& rec){
    out<<rec.name<<" : "<<rec.phoneNo;
    return out;
}


class HashTable{
private:
    Record* arr;
    int SIZE;
    bool replacement;       // 0 -> without replacement and 1 -> with replacement
    int currentRecordCount;      // this is to keep track of the size
    int deletedRecordCount;     // If the deleted count goes beyond a certain threshold, we should rehash the entire table
    int thresholdForDeletion;

    int calculateHash(string key){
        int hash = 0;
        for(int i=0; i<key.length(); i++){
            char character = key[i];
            int asciiVal = (int)character;
            int weight = i+1;                   // OPTIONAL. Basically character * position of character (starting from 1). Thus abc and bca wont have the same hash
            hash += asciiVal*weight;
        }
        return hash;
    }

    bool isEmpty(Record rec){           // Here you should define how you would determine an empty record. Either by name or phone no.
        if(rec.name == "") return true;
        return false;
    }

    int hashFunction(string key){
        // Use Hash function as H(x) = (3*x + 5)%10
        int x = calculateHash(key);
        return (3 * x + 5)%SIZE;
    }
    // Overloading for simplicity (This will be used for rehashing purposes)
    int hashFunction(string key, int tableSize){
        // Use Hash function as H(x) = (3*x + 5)%10
        int x = calculateHash(key);
        return (3 * x + 5)%tableSize;
    }

    void insertIntoArr(Record* &table, int tableSize ,Record rec){
        int hashIndex = hashFunction(rec.name, tableSize);
        
        if(isEmpty(table[hashIndex])){
            table[hashIndex] = rec;
            return;
        }

        // check this condition for replacement only
        if(replacement && !isEmpty(table[hashIndex])){
            string insertedRecordKey = table[hashIndex].name;
            string insertedRecordValue = table[hashIndex].phoneNo;

            int insertedRecordHashIndex = hashFunction(insertedRecordKey, tableSize);
            // if the already inserted key does not belong there.
            if(insertedRecordHashIndex != hashIndex){   
                table[hashIndex] = rec;
                // Reinsert the record into the hash table
                insertIntoArr(table, tableSize,Record(insertedRecordKey, insertedRecordValue));
                return;
            }
        }

        int itr = hashIndex;
        do{
            if(isEmpty(table[itr])){
                table[itr] = rec;
                return;
            }
            // Use linear or quadratic or any other probing mechanism here
            itr = (itr + 1)%tableSize;
        }while(itr != hashIndex);
        

        // this will never be called as if we try to insert beyond the current size, the hash table will increase it's size automatically
        cout<<"Table is full. Cannot insert the following record"<<endl;
        cout<<rec<<endl;
        return;
    }

    void extendHashTable(){     // Basically Creating vector.
        Record* newArr = new Record[2*SIZE];
        // Copy all the records in the new table and rehashing them accordingly
        for(int i=0; i<SIZE; i++){
            if(!isEmpty(arr[i])){
                insertIntoArr(newArr, 2*SIZE, arr[i]);
            }
        }
        delete[] arr;
        arr = newArr;
        SIZE = 2*SIZE;
        // Reset the deletedRecordCount as we have rehashed all the records in the table
        deletedRecordCount = 0;
        thresholdForDeletion = SIZE/2;      // since we modified the size, we need to reset the threshold too.

        return;
    }

    void rehashTheEntireTable(){
        // it is the same as extend but the size remains the same
        Record* newArr = new Record[SIZE];
        // Copy all the records in the new table and rehashing them accordingly
        for(int i=0; i<SIZE; i++){
            if(!isEmpty(arr[i])){
                insertIntoArr(newArr, SIZE, arr[i]);
            }
        }
        delete[] arr;
        arr = newArr;
        SIZE = SIZE;
        // Reset the deletedRecordCount as we have rehashed all the records in the table
        deletedRecordCount = 0;
        return;
    }

    Record search(string key){
        int hashIndex = hashFunction(key);
        int itr = hashIndex;
        do{
            if(arr[itr].name == key){
                return arr[itr];
            }
            // probe according to how you inserted into the table
            itr = (itr + 1)%SIZE;
        }while(itr!=hashIndex);
        return Record();
    }


public:
    HashTable(int SIZE=10, bool replacement=0):SIZE(SIZE),replacement(replacement){
        arr = new Record[SIZE];
        currentRecordCount = 0;
        deletedRecordCount = 0;
        thresholdForDeletion = SIZE/2;          // Determine when you should rehash the entire table
    }

    void insert(string key, string phoneNo){
        currentRecordCount++;
        if(currentRecordCount >= SIZE){
            cout<<"Extending the Table..."<<endl;
            extendHashTable();
        }
        insertIntoArr(arr,SIZE,Record(key,phoneNo));
    }

    void searchRecord(string key){
        Record rec = search(key);
        if(isEmpty(rec)){
            cout<<"--- Record "<< key <<" not found! ---"<<endl<<endl;
            return;
        }
        cout<<"----- Record Found! -----"<<endl;
        cout<<rec<<endl<<endl;
    }
    

    void deleteRecord(string key){
        Record rec = search(key);
        if(isEmpty(rec)){
            cout<<"Record does not exist!"<<endl;
            return;
        }
        
        if(deletedRecordCount >= thresholdForDeletion){
            cout<<"Deletion threshold reached max limit! Rehashing the table for optimizations.. "<<endl;
            rehashTheEntireTable();
        }

        // if exists
        currentRecordCount--;
        deletedRecordCount++;

        int hashIndex = hashFunction(key);
        int itr = hashIndex;
        do{
            if(arr[itr].name == key){
                arr[itr] = Record();        // replace the object with dummy object
                cout<<"---- Deleted Record "<< key <<" Successfully ----"<<endl<<endl;
                return;
            }

            itr = (itr+1)%SIZE;
        }while(itr != hashIndex);

        // if this runs, there is an error as we have already verified that the record exists in the table using search Function
        cout<<"Could not find the record"<<endl;
        return;
    }

    void viewTable(){
        cout<<endl<<"---------- Displaying Table ----------"<<endl;
        for(int i=0; i<SIZE; i++){
            cout<<"----- Position "<<i<<" -----"<<endl;
            if(isEmpty(arr[i])){
                cout<<"EMPTY"<<endl<<endl;
                continue;
            }
            cout<<arr[i]<<endl;
            cout<<"Ideal Index : "<<hashFunction(arr[i].name)<<endl<<endl;
        }
        cout<<endl<<"---------- END ----------"<<endl;
    }


};

int main(){
    // Make it menu driven in the practical exam. Check the other implementation for menu driven code

    HashTable table;

    table.viewTable();      // Empty table


    table.insert("Tirthraj Mahajan","1234567890");
    table.insert("Aditya Mulay","1111111111");
    table.insert("Vardhan Dongre","2222222222");
    table.insert("Ninad Palsule","3333333333");
    table.insert("Arnav Vaidya","4444444444");
    table.insert("Kedar Vartak","5555555555");
    table.insert("Amey Kulkarni","6666666666");
    table.insert("Shreyas Nagarkar","7777777777");
    table.insert("Aditya Kulkarni", "8888888888");
    table.viewTable();

    table.deleteRecord("Tirthraj Mahajan");
    table.deleteRecord("Aditya Mulay");
    table.deleteRecord("Ninad Palsule");
    table.deleteRecord("Amey Kulkarni");
    table.deleteRecord("Shreyas Nagarkar"); 
    table.deleteRecord("Aditya Kulkarni");  // this deletion should reach the max limit and you would see change in the indexing of the table

    // You should see the following changes
    /*
        Kedar Vartak went to his ideal position
        Vardhan Dongre went to his ideal position
        Arnav Vaidya went to his ideal position

    */
    table.viewTable();

    // Reinsert the deleted records to test extend table function
    table.insert("Tirthraj Mahajan","1234567890");
    table.insert("Aditya Mulay","111111111");
    table.insert("Ninad Palsule","3333333333");
    table.insert("Amey Kulkarni","6666666666");
    table.insert("Shreyas Nagarkar","7777777777");

    table.viewTable();

    // This entry should automatically extend the table as SIZE(10) == entry no (10)
    table.insert("Harsh B","9999999999");      
    table.insert("Nidhish Kasbekar", "0000000000");


    table.viewTable();

    table.searchRecord("Arnav Vaidya");
    table.deleteRecord("Arnav Vaidya");
    table.searchRecord("Arnav Vaidya");     // test record search after deletion

    table.searchRecord("Vedang Urade");     // test for record that doesn't exist

    table.viewTable();

    // All tests passed successfully!

}





