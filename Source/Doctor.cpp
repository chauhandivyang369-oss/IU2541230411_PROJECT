#include "Doctor.h"
#include <iostream>
using namespace std;

Doctor::Doctor() : Person()
{
    id = 0;
    specialization = "None";
    fee = 0;
}

Doctor::Doctor(int i, string n, int a, string p, string s, int f) : Person(n, a, p)
{
    id = i;
    specialization = s;
    fee = f;
}

Doctor::~Doctor()
{
}

int Doctor::getId() const
{
    return id;
}

string Doctor::getSpecialization() const
{
    return specialization;
}

int Doctor::getFee() const
{
    return fee;
}

void Doctor::setFee(int f)
{
    fee = f;
}

void Doctor::display() const
{
    cout << "[Doctor]  ID: " << id << " | ";
    Person::display();
    cout << " | Speciality: " << specialization << " | Fee: Rs." << fee << endl;
}

string Doctor::toFileString() const
{
    return to_string(id) + "|" + Person::toFileString() + "|" + specialization + "|" + to_string(fee);
}
