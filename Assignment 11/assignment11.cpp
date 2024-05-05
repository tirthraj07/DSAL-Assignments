/*
Assignment 11: Sequential File

Name: Tirthraj Mahajan
Class: SE-02
Roll no: 21242

Problem Statement
Department maintains a student information. 

The file contains roll number, name, division and address. 

Allow user to add, delete information of student. Display information of particular student. 
If record of student does not exist an appropriate message is displayed. 
If it is, then the system displays the student details. 

Use Sequential File to maintain the data.
*/


#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

/*
Step 1: Create a Student Class

Related Theory:
There are two types of file records: 
1. Fixed Length File Record
2. Variable Length File Record

In this program, I am implementing the fixed length file record instead of variable length file record for following reason:

If the record size if fixed, then there is a fast access to any desired record. Because the starting address and ending address is known

The only disadvantage is that there will be either overflow of memory is the string entered is greater than the predefined max length or there will be memory wastage.

Thus we will be using C-Style string, meaning we will be using Char array rather than C++ std::string class

*/

/*
Create a student class
The sizeof student class is 180 because
Name -> 21 bytes        : 20 characters and + 1 '\0' termination char
Address -> 151 bytes    : 150 characters and + 1 '\0' termination char
Division -> 4 bytes     
Roll No -> 4 bytes

However the size may vary depending upon the os and system architecture

But all the objects of the class will be of the same size
Thus we can easily find the starting and the ending address of a particular record
*/

class Student{
private:
    char name[20];
    char address[150];
    int division;
    int roll;
public: 
    // Setup getters and setters
    // Note that you cannot just use the = operator as you are dealing with pointers and not std::string
    // Also the 'const' in parameter is optional. It is a good practice to specify that the function does not indent to change the value of the parameter. It is okay if you just write char* name
    
    void setName(const char* name){
        if(name==nullptr){
            cout<<"Error: Name given in parameter is NULL"<<endl;
            return;
        }
        // We are using strncpy instead of strcpy to avoid overflow, so we specify the size of characters we want to copy using the sizeof operator. However, strncpy does not always copy terminating null character '\0'. So we will explicitly do that

        strncpy(this->name, name, sizeof(this->name)-1);
        this->name[sizeof(this->name)-1] = '\0';

    }
    void setAddress(const char* address){
        if(address == nullptr){
            cout<<"Error: Address Entered is NULL"<<endl;
            return;
        }

        strncpy(this->address, address, sizeof(this->address)-1);
        this->address[sizeof(this->address)-1] = '\0';
    }
    void setDivision(const int division){
        this->division = division;
    }
    void setRoll(const int roll){
        this->roll = roll;
    }


    char* getName(){
        return name;
    }
    char* getAddress(){
        return address;
    }
    int getDivision(){
        return division;
    }
    int getRoll(){
        return roll;
    }

    void display(){
        cout<<endl;
        cout<<"Name : "<<name<<endl;
        cout<<"Address : "<<address<<endl;
        cout<<"Roll No : "<<roll<<endl;
        cout<<"Division : "<<division<<endl;
        cout<<endl;
    }

    friend class FileClass;
};

/* 
Step2 : Now lets create a file class that will handle all the I/O Operations

Note that we have to deal with binary files here.

Steps to Write and Read contents in binary file:

Step 1:
Open the file in Binary Mode

fstream file("records.bin", ios::binary | ios::in | ios::out | ios::app);

Step 2:
Now create the object of the Student class and provide necessary info using setters
Student obj

Step 3:
Now find the sizeof object using the sizeof operator.
The size will be the same every time as we have used the fixed sized file record system
But it is a convention.

Note that the sizeof operator returns the value in 'size_t' datatype and not int

Difference between size_t and int/unsigned int

The size_t type is the unsigned integer type that is the result of the sizeof operator (and the offsetof operator), so it is guaranteed to be big enough to contain the size of the biggest object your system can handle (e.g., a static array of 8Gb).

The size_t type may be bigger than, equal to, or smaller than an unsigned int, and your compiler might make assumptions about it for optimization.

For our purposes, even if you use int, that would be okay

size_t dataSize = sizeof(obj);


Step 4: Convert the object's data into byte stream. This process is called serialization
It converts the data into byte stream and is stored in character array
So we are basically CASTING the obj of STUDENT into CHARACTERS

char* data = (char*)&obj;
OR:
const char* data = reinterpret_cast<const char*>(&obj)


What is the use of the reinterpret_cast instead of normal type casting?
Using reinterpret_cast provides a more explicit indication to the compiler and potentially makes the code more readable, especially in complex scenarios. However, (char*) is a shorthand notation commonly used for type casts in C and C++ codebase.


Step 5: Write the data into the file

Now that you have the byte stream and the size of the stream, you can write that into the file

file.write(data, dataSize);

Step 6: Create a empty student object to store the deserialized data

Student deserializedObj

Step 7: Create a buffer to store object byte stream in the file

char* byteStreamObject = new char[sizeof(deserializedObj)]

Step 8: Read the Contents of the file

file.read(byteStreamObject,sizeof(deserializedObj))

Step 9: Copy the byte contents stored in the byteStreamObject into the actual deserializedObj

memcpy(&deserializedObj, byteStreamObject, sizeof(deserializedObj))

Step 10:
Close the file
*/

class FileClass{
private:    
    string fileName;

    void deserialize(Student &obj, char* byteStream){
        memcpy(&obj, byteStream, sizeof(obj));
    }

    Student retrieveObject(streampos pos){
        fstream file(fileName, ios::binary | ios::in);
        if(!file){
            cout<<"Error while opening the file"<<endl;
            return Student();
        }

        file.seekg(pos, ios::beg);
        
        Student deserializedObject;
        char* byteStream = new char[sizeof(deserializedObject)];

        file.read(byteStream,sizeof(deserializedObject));

        deserialize(deserializedObject, byteStream);

        file.close();
        delete[] byteStream;

        return deserializedObject;
    }

    streampos getStudentPosition(int roll){
        fstream file(fileName, ios::binary | ios::in);

        if(!file){
            cout<<"Error while opening the file"<<endl;
            return fstream::pos_type(-1);
        }

        file.seekg(0,ios::beg);
        Student obj;
        char* byteStream = new char[sizeof(obj)];

        while(file.read(byteStream,sizeof(obj))){
            deserialize(obj, byteStream);
            if(obj.getRoll()==roll){
                streampos location = file.tellg() - fstream::pos_type(sizeof(obj)); 
                file.close();
                delete[] byteStream;
                return location;
            }
        }


        file.close();
        delete[] byteStream;
        return fstream::pos_type(-1);
    }
    
    
public:
    FileClass(string fileName="records.bin"):fileName(fileName){}

    void insert(Student &obj){
        fstream file(fileName, ios::binary | ios::app);

        if(!file){
            cout<<"Error while opening the file"<<endl;
            return;
        }


        size_t objSize = sizeof(obj);
        
        const char* byteStream = reinterpret_cast<const char*>(&obj);

        file.write(byteStream, objSize);

        file.close();
    }

    Student query(int roll){
        streampos pos = getStudentPosition(roll);
        if(pos == fstream::pos_type(-1)){
            cout<<"Couldn't find the student"<<endl;
            return Student();
        }

        return retrieveObject(pos);

    }

};



int main(){
    FileClass f;
    Student s;
    char name[] = "Vardhan Dongre";
    char address[] = "Somewhere in sahakar nagar";
    int roll = 21300;
    int division = 3;

    s.setName(name);
    s.setAddress(address);
    s.setRoll(roll);
    s.setDivision(division);

    // f.insert(s);

    Student obj = f.query(21230);
    obj.display();


}


