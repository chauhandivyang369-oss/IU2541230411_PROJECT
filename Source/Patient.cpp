#include "Patient.h"
#include <iostream>
using namespace std;

Patient::Patient() : Person()
{
    id = 0;
    disease = "None";
}

Patient::Patient(int i, string n, int a, string p, string d) : Person(n, a, p)
{
    id = i;
    disease = d;
}

Patient::~Patient()
{
}

int Patient::getId() const
{
    return id;
}

void Patient::setDisease(string d)
{
    disease = d;
}

void Patient::display() const
{
    cout << "[Patient] ID: " << id << " | ";
    Person::display();
    cout << " | Disease: " << disease << endl;
}

string Patient::toFileString() const
{
    return to_string(id) + "|" + Person::toFileString() + "|" + disease;
}
