/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: CarlosFlo123
 *
 * Created on November 12, 2019, 7:19 PM
 */

#include <iostream>
#include <sstream>
using namespace std;

template<class T>
class Vector {
protected:
    T* items;
    unsigned int size;

    void copy(const Vector<T>& v) {
        int minSize = (size < v.size) ? size : v.size;
        for (int i = 0; i < minSize; i++)
            items[i] = v.items[i];
    }
public:
    Vector(unsigned int n = 10) : size(n) {  //default value if not assigned
        items = new T[size];
    }

    Vector(const Vector<T>& v) : size(v.size), items(new T[v.size]) {
        copy(v);
    }

    Vector<T>& operator=(const Vector<T>& v) {
        size = v.size;
        items = new T[size];
        copy(v);
        return *this;
    }

    T& operator[](unsigned int i) const {
        return items[i];
    }

    unsigned int getsize() {
        return size;
    }

    ~Vector() {
        delete [] items;
    }

    operator string() const {
        stringstream ss;
        for (int i = 0; i < size; i++) {
            ss << items[i] << '\t';
        }
        return ss.str();
    }

    friend ostream& operator<<(ostream& os, const Vector<T>& v) {
        for (int i = 0; i < v.size; i++) {
            os << v.items[i];
        }
        return os;
    }

    T& findmax() {
        T& max = items[0];
        for (int i = 1; i < size; i++) {
            if (max < items[i]) {
                max = items[i];
            }
        }
        return max;
    }

    T& findmin() {
        T& min = items[0];
        //cout << items[0] << endl;
        for (int i = 1; i < size; i++) {
            if (min > items[i]) {
                min = items[i];
            }
        }
        return min;
    }
};

class Book {
private:
    string title;
    double price;
public:

    Book(string t = "", double p = 0.0) : title(t), price(p) {
    }

    friend ostream& operator<<(ostream& os, const Book& b) {
        os << "Title: " << b.title << "\t" << "Price: " << b.price << endl;
        return os;
    }
};

class Student {
private:
    string name;
    int id;
    double gpa;
    int numBooks;
    Vector<Book> books;
public:
    Student(string name = "", int id = 0, double gpa = 0.0) : name(name), id(id), gpa(gpa), books(2){
        numBooks = 0;
    }

    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "Name: " << s.name << "\tID: " << s.id << "\t\tGPA: " << s.gpa << endl;
        for (int i = 0; i < s.numBooks; i++){
            os << "\tBook " << i << ": " << s.books[i];
        }
        return os;
    }

    Vector<Book>& getBooks() {
        return books;
    }

    Student& operator+(const Book& b) {
        books[numBooks++] = b;
        return *this;
    }

    bool operator<(const Student& s) {
        return gpa < s.gpa;
    }
    
    bool operator>(const Student& s) {
        return gpa > s.gpa;
    }
};

class Course{
    string courseTitle;
    Vector<Student> students;
    int numStudents;
public:
    Course(string c = "") : courseTitle(c), numStudents(0), students(3){}
    friend ostream& operator<<(ostream& os, const Course& c) {
        os << "CourseTitle: " << c.courseTitle << endl;
        os << c.students << endl;
        return os;
    }
    Course& operator+(const Student& s){
        students[numStudents++] = s;
        return *this;
    }
    Student& getBestStudent(){
        return students.findmax();
    }
    Student& getWeakestStudent(){
        return students.findmin();
    }
};

int main() {
    /*Vector<int> v;
    for (int i = 0; i < v.getsize(); i++) {
        v[i] = rand() % 100;
    }
    for (int i = 0; i < v.getsize(); i++) {
        cout << v[i] << '\t';
    }

    cout << endl;
    string str = string(v);
    cout << str << endl;
    cout << endl;
    cout << endl;
    cout << "Max Value: " << v.findmax();
    cout << endl;
    cout << "Min Value: " << v.findmin();
    cout << endl;*/
    Book b("C++", 89.9);
  
    Vector<Student> vstudent(3);
    Vector<Book> vbook(2);
    vbook[0] = b;
    vbook[1] = Book("Java", 79.8);
    cout << vbook << endl;
    cout << endl;
    vstudent[0] = Student("Peter", 123, 4.0);
    vstudent[1] = Student("Mike", 321, 3.2);
    vstudent[2] = Student("Ross", 423, 3.6);
    cout << vstudent << endl;

    Course c("CS360");
    
    vstudent[0] + vbook[0];
    vstudent[0] + vbook[1];
    vstudent[1] + vbook[0];
    vstudent[1] + vbook[1];
    vstudent[2] + vbook[0];
    vstudent[2] + vbook[1];
    c + vstudent[0];
    c + vstudent[1];
    c + vstudent[2];
    
    cout << c;
    
    cout << endl << endl;
    
    cout << "Best Student: " << c.getBestStudent() << endl;
    cout << "Worst Student: " << c.getWeakestStudent() << endl;

    return 0;
}