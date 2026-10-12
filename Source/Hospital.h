#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "FileManager.h"

// The main "system" class. It owns all the records and does all the work.
class Hospital
{
private:
    Patient *patients;              // dynamic arrays (created with new[])
    Doctor *doctors;
    Appointment *appointments;
    int patientCount;
    int doctorCount;
    int appointmentCount;
    int capacity;                   // maximum records of each type
    int nextPatientId;
    int nextDoctorId;
    int nextAppointmentId;
    FileManager fileManager;

    friend class FileManager;       // so FileManager can read/fill the arrays

    int findIndex(char type, int id) const;     // 'P', 'D' or 'A' -> position or -1
    void showAppointment(int index) const;

public:
    Hospital();
    ~Hospital();
    void addRecord();
    void displayRecords();
    void searchRecord();
    void updateRecord();
    void deleteRecord();
    void appointmentProcess();      // main transaction: book / cancel / complete
    void report();
    void saveData();
    void loadData();
};

#endif
