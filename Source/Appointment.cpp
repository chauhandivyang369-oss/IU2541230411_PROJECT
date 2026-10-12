#include "Appointment.h"
#include <iostream>
using namespace std;

Appointment::Appointment()
{
    id = 0;
    patientId = 0;
    doctorId = 0;
    date = "00-00-0000";
    slot = "None";
    status = "None";
}

Appointment::Appointment(int i, int p, int d, string dt, string sl, string st)
{
    id = i;
    patientId = p;
    doctorId = d;
    date = dt;
    slot = sl;
    status = st;
}

int Appointment::getId() const
{
    return id;
}

int Appointment::getPatientId() const
{
    return patientId;
}

int Appointment::getDoctorId() const
{
    return doctorId;
}

string Appointment::getStatus() const
{
    return status;
}

void Appointment::setStatus(string st)
{
    status = st;
}

void Appointment::setSchedule(string dt, string sl)
{
    date = dt;
    slot = sl;
}

bool Appointment::clashesWith(int d, string dt, string sl) const
{
    return status == "Booked" && doctorId == d && date == dt && slot == sl;
}

void Appointment::display(string patientName, string doctorName) const
{
    cout << "[Appointment] ID: " << id << " | Patient: " << patientName << " (" << patientId << ")"
         << " | Doctor: " << doctorName << " (" << doctorId << ")"
         << " | " << date << " " << slot << " | Status: " << status << endl;
}

string Appointment::toFileString() const
{
    return to_string(id) + "|" + to_string(patientId) + "|" + to_string(doctorId) + "|" +
           date + "|" + slot + "|" + status;
}
