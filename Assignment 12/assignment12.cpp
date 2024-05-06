/*
Name : Tirthraj Mahajan
Class: SE-02
Roll No: 21242

Problem Statement:
Implementation of a direct access file -Insertion and deletion of a
record from a Direct Access File.

*/

/*
Direct access file is also known as Random access or relative file organization. 
In direct access file, all records are stored in direct access storage device, such as hard disk. 
The records are randomly placed throughout the file. The record does not need to be in sequence because they
are updated directly and rewritten back in the same location.

*/

#include<iostream>
#include<cstring>
#include<string>
#include<fstream>
using namespace std;

class Student{
private:
    char name[20];
    char address[150];
    int roll;
    int division;
public:
    // "Dummy Student" 
    Student(){
        roll = -1;

        // no need for this actually, you can just update the roll number if you want as that is the way we are going to identify dummy student
        strcpy(name,"dummy student");   
        strcpy(address, "XYZ");
        division = -1;
    }

    // Actual student info
    Student(const char* name,const char* address,const int roll,const int division){
        strncpy(this->name, name, sizeof(this->name) - 1);
        this->name[sizeof(this->name)-1] = '\0';
        strncpy(this->address, address, sizeof(this->address) - 1);
        this->address[sizeof(this->address)-1] = '\0';
        this->roll = roll;
        this->division = division;
    }

    int getRoll(){
        return roll;
    }

    void display(){
        cout<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Address: "<<address<<endl;
        cout<<"Roll No: "<<roll<<endl;
        cout<<"Division: "<<division<<endl;
        cout<<endl;
    }

};

class FileClass{
private:
    string fileName;
    const int SIZE;

    bool exists(string fname){
        ifstream file(fname);
        return file.good();
    }

    int hashFunction(int roll){
        return roll%SIZE;
    }

    void deserialize(Student &obj, char* byteStream){
        memcpy(&obj, byteStream, sizeof(obj));
    }

public:
    FileClass(int SIZE=10, string fileName = "records.bin"):fileName(fileName),SIZE(SIZE){

        // Check if the file exists. If it does, then return as rest of the function will overwrite the previous contents of the file
        if(exists(fileName)) return;
        
        Student obj;
        size_t studentSize = sizeof(obj);
        const char* byteStream = reinterpret_cast<const char*>(&obj);
        fstream file(fileName, ios::binary | ios::out);
        if(!file){
            cout<<"Error while creating file"<<endl;
        }

        // Write the entire file with dummy students
        for(int i=0; i<SIZE; i++){
            file.write(byteStream,studentSize);
        }

        file.close();
    }
    
    // We will be using linear probing without replacement for collision handling technique, but you can use whatever suites u 
    void insert(Student s){
        if(s.getRoll()==-1){
            cout<<"Insertion blocked. Trying to enter a dummy student"<<endl;
            return;
        }
        fstream file(fileName, ios::binary | ios::in | ios::app);
        if(!file){
            cout<<"Error while opening the file"<<endl;
            return;
        }

        size_t studentSize = sizeof(Student);
        const char* byteStream = reinterpret_cast<const char*>(&s);
        char* buffer = new char[studentSize];
        Student obj;
        int hashIndex = hashFunction(s.getRoll());
        int location = hashIndex;
        do{
            file.seekg(location * studentSize, ios::beg);
            file.read(buffer, studentSize);
            deserialize(obj, buffer);
            if(obj.getRoll()==-1){
                file.seekp(location * studentSize, ios::beg);
                file.write(byteStream,studentSize);
                file.close();
                cout<<"Student inserted successfully"<<endl;
                delete[] buffer;
                return;
            }
            location = (location + 1)%SIZE;
        }while(location!=hashIndex);

        cout<<"Cannot insert Student!"<<endl;
        cout<<"File size has reached its the maximum limit"<<endl;
        file.close();
        return;
    }



};

int main(){
    FileClass file(20);
}