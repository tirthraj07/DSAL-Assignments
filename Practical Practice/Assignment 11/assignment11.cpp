#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

class Student{
private:
    char name[20];
    char address[150];
    int roll;
    int division;
public:
    Student(){}
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

    void deserialize(Student &obj, char* byteStream){
        memcpy(&obj,byteStream,sizeof(Student));
    }

    streampos queryRollNo(int roll){
        fstream file(fileName, ios::binary | ios::in);
        if(!file){
            cout<<"Error while opening the file"<<endl;
            return fstream::pos_type(-1);
        }

        size_t studentSize = sizeof(Student);
        char* buffer = new char[studentSize];
        Student obj;

        while(file.read(buffer, studentSize)){
            deserialize(obj, buffer);
            if(obj.getRoll()==roll){
                streampos location = file.tellg() - fstream::pos_type(studentSize);
                file.close();
                return location;
            }
        }

        file.close();
        return fstream::pos_type(-1);
    }

public:
    FileClass(string fileName="records.bin"):fileName(fileName){}

    void insert(Student s){
        // Instead of directly entering, you can also check that the roll number hasn't been entered before
        if(queryRollNo(s.getRoll())!=fstream::pos_type(-1)){
            cout<<"A Student with roll no: "<<s.getRoll()<<" already exists"<<endl;
            return;
        }

        const char* byteStream = reinterpret_cast<const char*>(&s);
        size_t objSize = sizeof(s);

        fstream file(fileName, ios::binary | ios::app);
        if(!file){
            cout<<"Error while opening the file"<<endl;
            return;
        }

        file.write(byteStream, objSize);

        file.close(); 

        cout<<"Student inserted successfully"<<endl;
    }

    void displayRecords(){
        fstream file(fileName, ios::binary | ios::in);
        if(!file){
            cout<<"Error while opening the file"<<endl;
            return;
        }

        cout<<"---------- Displaying Records ----------"<<endl;

        size_t studentSize = sizeof(Student);
        char* buffer = new char[studentSize];
        Student obj;
        while(file.read(buffer,studentSize)){
            deserialize(obj, buffer);
            obj.display();
        }

        cout<<"---------- END ----------"<<endl;
        file.close();
    }

    void displayStudent(int roll){
        streampos location = queryRollNo(roll);
        if(location == fstream::pos_type(-1)){
            cout<<endl<<"-- x -- x -- x -- x -- x -- x -- x --"<<endl<<endl;
            cout<<"Student with roll no "<<roll<<" does not exist in the database"<<endl;
            cout<<endl<<"-- x -- x -- x -- x -- x -- x -- x --"<<endl<<endl;
            return;
        }

        fstream file(fileName, ios::binary | ios::in);
        if(!file){
            cout<<"Error while opening the file"<<endl;
            return;
        }

        file.seekg(location, ios::beg);
        size_t studentSize = sizeof(Student);
        char* buffer = new char[studentSize];
        Student obj;
        file.read(buffer, studentSize);
        file.close();
        deserialize(obj,buffer);

        cout<<"---------- Displaying Student Information ----------"<<endl;
        obj.display();
    }


    void deleteStudent(int roll){
        string tempFileName = "temp" + fileName;
        fstream file(fileName, ios::binary | ios::in);
        fstream temp(tempFileName, ios::binary | ios::out);
        size_t studentSize = sizeof(Student);
        char* buffer = new char[studentSize];
        Student obj;

        while(file.read(buffer,studentSize)){
            deserialize(obj, buffer);
            if(obj.getRoll()==roll) continue;
            temp.write(buffer,studentSize);
        }

        file.close();
        temp.close();

        remove(fileName.c_str());
        rename(tempFileName.c_str(), fileName.c_str());
        cout<<"Deletion Successful"<<endl;
    }

};

int main(){
    FileClass file;
    file.insert(Student("Tirthraj Mahajan", "Pune 09",21242,2));
    file.insert(Student("ABC","Pune",0000,10));
    file.insert(Student("CDE","Mumbai",1000,20));
    file.insert(Student("FGH","Nashik",2000,30));
    file.displayRecords();
    file.displayStudent(21242);
    file.deleteStudent(21242);
    file.displayStudent(21242);
    file.displayRecords();
}
