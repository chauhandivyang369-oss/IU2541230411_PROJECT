#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"

// Doctor IS-A Person (inheritance)
class Doctor : public Person
{
private:
    int id;
    string specialization;
    int fee;

public:
    Doctor();
    Doctor(int i, string n, int a, string p, string s, int f);
    ~Doctor();
    int getId() const;
    string getSpecialization() const;
    int getFee() const;
    void setFee(int f);
    void display() const;              // overrides Person::display()
    string toFileString() const;       // overrides Person::toFileString()
};

#endif
