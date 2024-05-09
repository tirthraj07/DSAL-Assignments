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

    int queryRollNo(int roll){
        /* 
        Note that: since we are allowing deletion of record, there might be vacancy in the probing path while finding a particular student
        That vacancy may not mean that the student doesn't exist.
        Thus we need to check each location from the hashIndex to find the student.
        If deletion was not there, we would have simply exited at the first instance of vacancy in the probing path.
        */

        fstream file(fileName, ios::binary | ios::in);
        if(!file){
            cout<<"Error while opening the file"<<endl;
            return -1;
        }
        int hashIndex = hashFunction(roll);
        size_t sizeOfStudent = sizeof(Student);
        char* buffer = new char[sizeOfStudent];
        Student obj;    // Dummy Object
        int location = hashIndex;
        do{ 
            file.seekg(location * sizeOfStudent, ios::beg);
            file.read(buffer, sizeOfStudent);
            deserialize(obj, buffer);
            if(obj.getRoll()==roll){
                file.close();
                delete[] buffer;        // Clean up used resources;
                return location;        // Object Found
            }
            location = (location + 1)%SIZE;
        }while(location!=hashIndex);

        delete[] buffer;    // Clean up used resources;
        file.close();
        return -1;      // Object not found

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
        int loc = queryRollNo(s.getRoll());
        if(loc != -1){
            cout<<"Student with roll no: "<<s.getRoll()<<" already exists"<<endl;
            return;
        }

        fstream file(fileName, ios::binary | ios::in | ios::out);

        /*
            IMPORTANT NOTE: I spent an entire hour debugging this. So read carefully

            USE ios::in | ios::out as the opening mode, not ios::in | ios::app

            THERE ARE 3 IMPORTANT POINTS FOR THIS:

            1. use of ios::out alone:
            
            Using ios::out alone WILL TRUNCATE your existing data. that you probably know already

            2. use of ios::app:
        
            So you would think that if I don't want to delete my existing data, i should open using ios::app right?
            WRONG!
            Here we want to OVERWRITE the existing data and for that purpose we are changing the PUT pointer at a specific location
            BUT even if you use seekp to change the pointer location, since you opened the file in APPEND mode, it will always write the new content at the end of the file
            THIS means that it will not OVERWRITE the CONTENTS even though you moved the pointer to where you want to overwrite

            In ios::app mode, seekp won't allow you to overwrite existing data because the file pointer is always positioned at the end of the file before any write operation. 
            Therefore, any attempt to use seekp followed by a write operation will result in the data being appended to the end of the file, rather than overwriting existing content.

            3. use of ios::in | ios::out -> CORRECT

            So if you want to OVERWRITE the existing data WITHOUT deleting it, you should open the file using ios::in | ios::out

            You are explicitly indicating that you want to handle both reading and writing operations, and you control the file pointer using seekp() and seekg() to write at specific positions within the file.
            This mode is suitable for scenarios where you need to read from and write to arbitrary positions within the file without truncating its contents.
        
            tl;dr use ios::in | ios:out mode

        */


        if(!file){
            cout<<"Error while opening the file"<<endl;
            return;
        }

        size_t studentSize = sizeof(s);
        const char* byteStream = reinterpret_cast<const char*>(&s);
        char* buffer = new char[studentSize];
        Student obj;
        int hashIndex = hashFunction(s.getRoll());      
        int location = hashIndex;
        do{
            file.seekg(location*studentSize, ios::beg);
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

    void displayStudent(int roll){
        int location = queryRollNo(roll);
        if(location == -1){
            cout<<"Student with roll no: "<<roll<<" does not exists"<<endl;
            return;
        }
        size_t sizeOfStudent = sizeof(Student);
        char* buffer = new char[sizeOfStudent];
        Student obj;
        fstream file(fileName, ios::binary | ios::in);
        if(!file){
            cout<<"Error while opening the file"<<endl;
            return;
        }
        file.seekg(location * sizeOfStudent, ios::beg);
        file.read(buffer, sizeOfStudent);
        deserialize(obj, buffer);
        obj.display();          // We are guaranteed that it is not a dummy object because of the queryRollNo function
        delete[] buffer;
        file.close();
    }

    void deleteStudent(int roll){
        int location = queryRollNo(roll);
        if(location == -1){
            cout<<"Student with roll no: "<<roll<<" does not exists"<<endl;
            return;
        }
        Student obj;        // Dummy Student
        size_t sizeOfStudent = sizeof(obj);
        const char* byteStream = reinterpret_cast<const char*>(&obj);        
        fstream file(fileName, ios::binary | ios::out | ios::in);         // PLEASE OPEN USING ios::in | ios::out and not ios::app
        if(!file){
            cout<<"Error while opening the file"<<endl;
            return;
        }
        file.seekp(location * sizeOfStudent, ios::beg);
        file.write(byteStream, sizeOfStudent);
        file.close();
        cout<<"Student with roll no "<<roll<<" deleted successfully"<<endl;
    }

    void displayListOfStudents(){

        fstream file(fileName, ios::binary | ios::in);

        
        if(!file){
            cout<<"Error while opening the file"<<endl;
            return;
        }

        file.seekg(0,ios::beg);

        size_t studentSize = sizeof(Student);
        char* buffer = new char[studentSize];
        Student obj;
        cout<<endl<<"---------- Displaying List of Student Records ----------"<<endl;

        while(file.read(buffer,studentSize)){
            deserialize(obj, buffer);
            int location = (file.tellg() - fstream::pos_type(studentSize))/studentSize;
            cout<<"Location : "<<location<<endl;
            if(obj.getRoll()==-1){
                cout<<"--- EMPTY ---"<<endl;
                continue;
            }
            obj.display();
            cout<<endl;
        }
        
        

        cout<<endl<<"---------- END ----------"<<endl;

        file.close();
    }



};

int main(){
    FileClass file(10);
    Student arr[] = {
        Student("Tirthraj Mahajan", "Treasure Park, Pune", 21242, 2),
        Student("ABC", "Pune", 21201, 2),
        Student("DEF", "Pune", 21202, 2),
        Student("GHI", "Pune", 21203, 2),
        Student("JKL", "Pune", 21204, 2),
        Student("MNO", "Pune", 21205, 2),
        Student("PQR", "Pune", 21206, 2),
        Student("STU", "Pune", 21207, 2),
        Student("VWX", "Pune", 21208, 2),
        Student("YZ", "Pune", 21209, 2)
    };
    for(int i=0; i<10; i++){
        file.insert(arr[i]);
    }

    file.displayListOfStudents();
    file.displayStudent(21242);     // student exists

    file.displayStudent(21210);     // does not exist
    
    file.deleteStudent(21242);      // deleting student
    file.displayStudent(21242);     // does not exists in file after deletion
    
    file.displayListOfStudents();


}