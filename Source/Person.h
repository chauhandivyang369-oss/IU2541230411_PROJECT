#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

// Base class: common details of every person in the hospital.
class Person
{
private:                       // encapsulation: data is hidden
    string name;
    int age;
    string phone;

public:
    Person();                                  // default constructor
    Person(string n, int a, string p);         // parameterized constructor
    virtual ~Person();                         // virtual destructor
    string getName() const;
    void setPhone(string p);
    virtual void display() const;              // virtual -> runtime polymorphism
    virtual string toFileString() const;       // text line used for saving
};

#endif
