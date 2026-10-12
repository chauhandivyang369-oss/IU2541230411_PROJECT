#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
using namespace std;

// One appointment = one patient + one doctor + date + time slot
class Appointment
{
private:
    int id;
    int patientId;
    int doctorId;
    string date;
    string slot;
    string status;          // Booked / Cancelled / Completed

public:
    Appointment();
    Appointment(int i, int p, int d, string dt, string sl, string st);
    int getId() const;
    int getPatientId() const;
    int getDoctorId() const;
    string getStatus() const;
    void setStatus(string st);
    void setSchedule(string dt, string sl);
    bool clashesWith(int d, string dt, string sl) const;   // same doctor, date, slot?
    void display(string patientName, string doctorName) const;
    string toFileString() const;
};

#endif
