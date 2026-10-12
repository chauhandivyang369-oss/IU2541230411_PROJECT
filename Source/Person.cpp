#include "Person.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Person::Person()
{
    name = "Unknown";
    age = 0;
    phone = "0000000000";
}

Person::Person(string n, int a, string p)
{
    if (n.empty())
        throw invalid_argument("Name cannot be empty");
    if (a < 0 || a > 120)
        throw invalid_argument("Age must be between 0 and 120");
    name = n;
    age = a;
    phone = p;
}

Person::~Person()
{
}

string Person::getName() const
{
    return name;
}

void Person::setPhone(string p)
{
    phone = p;
}

void Person::display() const
{
    cout << "Name: " << name << " | Age: " << age << " | Phone: " << phone;
}

string Person::toFileString() const
{
    return name + "|" + to_string(age) + "|" + phone;
}
