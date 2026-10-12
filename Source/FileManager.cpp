#include "FileManager.h"
#include "Hospital.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

FileManager::FileManager()
{
    // Program is run from the Executable folder, so Data is one level up.
    patientFile = "../Data/patients.txt";
    doctorFile = "../Data/doctors.txt";
    appointmentFile = "../Data/appointments.txt";
}

// Cuts "a|b|c" into parts[0]="a", parts[1]="b", parts[2]="c". Returns how many parts.
int FileManager::splitLine(string line, string parts[], int maxParts)
{
    int count = 0;
    string current = "";
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] == '|')
        {
            if (count < maxParts)
                parts[count] = current;
            count++;
            current = "";
        }
        else
            current += line[i];
    }
    if (count < maxParts)
        parts[count] = current;
    count++;
    return count;
}

void FileManager::saveAll(const Hospital &h)
{
    ofstream pout(patientFile.c_str());
    ofstream dout(doctorFile.c_str());
    ofstream aout(appointmentFile.c_str());
    if (!pout || !dout || !aout)
        throw runtime_error("Cannot open data files. Run the program from the Executable folder.");

    for (int i = 0; i < h.patientCount; i++)
        pout << h.patients[i].toFileString() << endl;
    for (int i = 0; i < h.doctorCount; i++)
        dout << h.doctors[i].toFileString() << endl;
    for (int i = 0; i < h.appointmentCount; i++)
        aout << h.appointments[i].toFileString() << endl;
}

void FileManager::loadAll(Hospital &h)
{
    string line;
    string parts[10];

    // start from an empty system
    h.patientCount = 0;
    h.doctorCount = 0;
    h.appointmentCount = 0;
    h.nextPatientId = 1001;
    h.nextDoctorId = 2001;
    h.nextAppointmentId = 3001;

    // ---- patients: id|name|age|phone|disease ----
    ifstream pin(patientFile.c_str());
    while (getline(pin, line))
    {
        if (line.empty())
            continue;
        try
        {
            if (splitLine(line, parts, 10) != 5)
                throw runtime_error("wrong number of fields");
            if (h.patientCount >= h.capacity)
                throw runtime_error("list is full");
            int id = stoi(parts[0]);
            h.patients[h.patientCount] = Patient(id, parts[1], stoi(parts[2]), parts[3], parts[4]);
            h.patientCount++;
            if (id >= h.nextPatientId)
                h.nextPatientId = id + 1;
        }
        catch (exception &e)
        {
            cout << "Skipped a bad line in patients file (" << e.what() << ")" << endl;
        }
    }

    // ---- doctors: id|name|age|phone|specialization|fee ----
    ifstream din(doctorFile.c_str());
    while (getline(din, line))
    {
        if (line.empty())
            continue;
        try
        {
            if (splitLine(line, parts, 10) != 6)
                throw runtime_error("wrong number of fields");
            if (h.doctorCount >= h.capacity)
                throw runtime_error("list is full");
            int id = stoi(parts[0]);
            h.doctors[h.doctorCount] = Doctor(id, parts[1], stoi(parts[2]), parts[3], parts[4], stoi(parts[5]));
            h.doctorCount++;
            if (id >= h.nextDoctorId)
                h.nextDoctorId = id + 1;
        }
        catch (exception &e)
        {
            cout << "Skipped a bad line in doctors file (" << e.what() << ")" << endl;
        }
    }

    // ---- appointments: id|patientId|doctorId|date|slot|status ----
    ifstream ain(appointmentFile.c_str());
    while (getline(ain, line))
    {
        if (line.empty())
            continue;
        try
        {
            if (splitLine(line, parts, 10) != 6)
                throw runtime_error("wrong number of fields");
            if (h.appointmentCount >= h.capacity)
                throw runtime_error("list is full");
            int id = stoi(parts[0]);
            h.appointments[h.appointmentCount] =
                Appointment(id, stoi(parts[1]), stoi(parts[2]), parts[3], parts[4], parts[5]);
            h.appointmentCount++;
            if (id >= h.nextAppointmentId)
                h.nextAppointmentId = id + 1;
        }
        catch (exception &e)
        {
            cout << "Skipped a bad line in appointments file (" << e.what() << ")" << endl;
        }
    }
}
