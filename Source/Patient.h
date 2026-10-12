#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"

// Patient IS-A Person (inheritance)
class Patient : public Person
{
private:
    int id;
    string disease;

public:
    Patient();
    Patient(int i, string n, int a, string p, string d);
    ~Patient();
    int getId() const;
    void setDisease(string d);
    void display() const;              // overrides Person::display()
    string toFileString() const;       // overrides Person::toFileString()
};

#endif
