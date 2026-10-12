#include "Hospital.h"
#include "Input.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Time slots offered by every doctor
static const string SLOTS[6] = {"10:00 AM", "11:00 AM", "12:00 PM", "02:00 PM", "03:00 PM", "04:00 PM"};

Hospital::Hospital()
{
    capacity = 50;
    patients = new Patient[capacity];               // dynamic memory
    doctors = new Doctor[capacity];
    appointments = new Appointment[capacity];
    patientCount = 0;
    doctorCount = 0;
    appointmentCount = 0;
    nextPatientId = 1001;
    nextDoctorId = 2001;
    nextAppointmentId = 3001;
}

Hospital::~Hospital()
{
    delete[] patients;                              // give memory back
    delete[] doctors;
    delete[] appointments;
    cout << "Memory released successfully (delete[] used)." << endl;
}

// Finds the position of a record in its array. Returns -1 if not found.
int Hospital::findIndex(char type, int id) const
{
    if (type == 'P')
    {
        for (int i = 0; i < patientCount; i++)
            if (patients[i].getId() == id)
                return i;
    }
    else if (type == 'D')
    {
        for (int i = 0; i < doctorCount; i++)
            if (doctors[i].getId() == id)
                return i;
    }
    else
    {
        for (int i = 0; i < appointmentCount; i++)
            if (appointments[i].getId() == id)
                return i;
    }
    return -1;
}

// Prints one appointment together with the patient and doctor names.
void Hospital::showAppointment(int index) const
{
    int pi = findIndex('P', appointments[index].getPatientId());
    int di = findIndex('D', appointments[index].getDoctorId());
    string pName = (pi == -1) ? "Removed" : patients[pi].getName();
    string dName = (di == -1) ? "Removed" : doctors[di].getName();
    appointments[index].display(pName, dName);
}

// 1. ADD RECORD
void Hospital::addRecord()
{
    cout << "\n--- ADD RECORD ---\n1. Patient\n2. Doctor\n";
    int choice = readInt("Enter choice: ", 1, 2);

    if (choice == 1)
    {
        if (patientCount >= capacity)
            throw runtime_error("Patient list is full.");
        string name = readName("Patient name: ");
        int age = readInt("Age (1-120): ", 1, 120);
        string phone = readPhone("Phone (10 digits): ");
        string disease = readText("Disease / problem: ");
        patients[patientCount] = Patient(nextPatientId, name, age, phone, disease);
        patientCount++;
        cout << "Patient added successfully. Patient ID = " << nextPatientId << endl;
        nextPatientId++;
    }
    else
    {
        if (doctorCount >= capacity)
            throw runtime_error("Doctor list is full.");
        string name = readName("Doctor name: ");
        int age = readInt("Age (25-80): ", 25, 80);
        string phone = readPhone("Phone (10 digits): ");
        string special = readText("Specialization: ");
        int fee = readInt("Consultation fee (100-5000): ", 100, 5000);
        doctors[doctorCount] = Doctor(nextDoctorId, name, age, phone, special, fee);
        doctorCount++;
        cout << "Doctor added successfully. Doctor ID = " << nextDoctorId << endl;
        nextDoctorId++;
    }
}

// 2. DISPLAY RECORDS
void Hospital::displayRecords()
{
    cout << "\n--- DISPLAY RECORDS ---\n1. Patients\n2. Doctors\n3. Appointments\n4. All People (Patients + Doctors)\n";
    int choice = readInt("Enter choice: ", 1, 4);
    cout << endl;

    if (choice == 1)
    {
        if (patientCount == 0)
            cout << "No patients found." << endl;
        for (int i = 0; i < patientCount; i++)
            patients[i].display();
    }
    else if (choice == 2)
    {
        if (doctorCount == 0)
            cout << "No doctors found." << endl;
        for (int i = 0; i < doctorCount; i++)
            doctors[i].display();
    }
    else if (choice == 3)
    {
        if (appointmentCount == 0)
            cout << "No appointments found." << endl;
        for (int i = 0; i < appointmentCount; i++)
            showAppointment(i);
    }
    else
    {
        // Runtime polymorphism: one Person pointer, different display() is called
        Person *p;
        for (int i = 0; i < patientCount; i++)
        {
            p = &patients[i];
            p->display();               // calls Patient::display()
        }
        for (int i = 0; i < doctorCount; i++)
        {
            p = &doctors[i];
            p->display();               // calls Doctor::display()
        }
    }
}

// 3. SEARCH RECORD
void Hospital::searchRecord()
{
    cout << "\n--- SEARCH RECORD ---\n1. Patient by ID\n2. Doctor by ID\n3. Doctors by specialization\n4. Appointment by ID\n";
    int choice = readInt("Enter choice: ", 1, 4);

    if (choice == 3)
    {
        string word = readText("Enter specialization: ");
        bool found = false;
        for (int i = 0; i < doctorCount; i++)
        {
            if (doctors[i].getSpecialization() == word)
            {
                doctors[i].display();
                found = true;
            }
        }
        if (!found)
            cout << "No doctor found with this specialization." << endl;
        return;
    }

    int id = readInt("Enter ID: ", 1, 999999);
    if (choice == 1)
    {
        int pos = findIndex('P', id);
        if (pos == -1)
            throw runtime_error("Patient not found.");
        patients[pos].display();
    }
    else if (choice == 2)
    {
        int pos = findIndex('D', id);
        if (pos == -1)
            throw runtime_error("Doctor not found.");
        doctors[pos].display();
    }
    else
    {
        int pos = findIndex('A', id);
        if (pos == -1)
            throw runtime_error("Appointment not found.");
        showAppointment(pos);
    }
}

// 4. UPDATE RECORD
void Hospital::updateRecord()
{
    cout << "\n--- UPDATE RECORD ---\n1. Patient (phone and disease)\n2. Doctor (fee)\n3. Reschedule appointment\n";
    int choice = readInt("Enter choice: ", 1, 3);
    int id = readInt("Enter ID: ", 1, 999999);

    if (choice == 1)
    {
        int pos = findIndex('P', id);
        if (pos == -1)
            throw runtime_error("Patient not found.");
        patients[pos].setPhone(readPhone("New phone (10 digits): "));
        patients[pos].setDisease(readText("New disease / problem: "));
        cout << "Patient updated successfully." << endl;
    }
    else if (choice == 2)
    {
        int pos = findIndex('D', id);
        if (pos == -1)
            throw runtime_error("Doctor not found.");
        doctors[pos].setFee(readInt("New fee (100-5000): ", 100, 5000));
        cout << "Doctor fee updated successfully." << endl;
    }
    else
    {
        int pos = findIndex('A', id);
        if (pos == -1)
            throw runtime_error("Appointment not found.");
        if (appointments[pos].getStatus() != "Booked")
            throw runtime_error("Only a Booked appointment can be rescheduled.");
        string date = readDate("New date (DD-MM-YYYY): ");
        for (int i = 0; i < 6; i++)
            cout << i + 1 << ". " << SLOTS[i] << "   ";
        cout << endl;
        string slot = SLOTS[readInt("Choose new slot (1-6): ", 1, 6) - 1];
        for (int i = 0; i < appointmentCount; i++)
            if (i != pos && appointments[i].clashesWith(appointments[pos].getDoctorId(), date, slot))
                throw runtime_error("Doctor is already booked at that date and time.");
        appointments[pos].setSchedule(date, slot);
        cout << "Appointment rescheduled successfully." << endl;
    }
}

// 5. DELETE RECORD
void Hospital::deleteRecord()
{
    cout << "\n--- DELETE RECORD ---\n1. Patient\n2. Doctor\n3. Appointment\n";
    int choice = readInt("Enter choice: ", 1, 3);
    int id = readInt("Enter ID to delete: ", 1, 999999);

    if (choice == 1)
    {
        int pos = findIndex('P', id);
        if (pos == -1)
            throw runtime_error("Patient not found.");
        for (int i = 0; i < appointmentCount; i++)
            if (appointments[i].getPatientId() == id && appointments[i].getStatus() == "Booked")
                throw runtime_error("Patient has a booked appointment. Cancel it first.");
        for (int i = pos; i < patientCount - 1; i++)     // shift records left
            patients[i] = patients[i + 1];
        patientCount--;
        cout << "Patient deleted successfully." << endl;
    }
    else if (choice == 2)
    {
        int pos = findIndex('D', id);
        if (pos == -1)
            throw runtime_error("Doctor not found.");
        for (int i = 0; i < appointmentCount; i++)
            if (appointments[i].getDoctorId() == id && appointments[i].getStatus() == "Booked")
                throw runtime_error("Doctor has a booked appointment. Cancel it first.");
        for (int i = pos; i < doctorCount - 1; i++)
            doctors[i] = doctors[i + 1];
        doctorCount--;
        cout << "Doctor deleted successfully." << endl;
    }
    else
    {
        int pos = findIndex('A', id);
        if (pos == -1)
            throw runtime_error("Appointment not found.");
        for (int i = pos; i < appointmentCount - 1; i++)
            appointments[i] = appointments[i + 1];
        appointmentCount--;
        cout << "Appointment deleted successfully." << endl;
    }
}

// 6. MAIN TRANSACTION: book / cancel / complete an appointment
void Hospital::appointmentProcess()
{
    cout << "\n--- APPOINTMENT PROCESS ---\n1. Book Appointment\n2. Cancel Appointment\n3. Mark Appointment Completed\n";
    int choice = readInt("Enter choice: ", 1, 3);

    if (choice == 1)
    {
        if (appointmentCount >= capacity)
            throw runtime_error("Appointment list is full.");
        if (patientCount == 0 || doctorCount == 0)
            throw runtime_error("Add at least one patient and one doctor first.");

        int pid = readInt("Patient ID: ", 1, 999999);
        if (findIndex('P', pid) == -1)
            throw runtime_error("Patient ID not found.");
        int did = readInt("Doctor ID: ", 1, 999999);
        int dpos = findIndex('D', did);
        if (dpos == -1)
            throw runtime_error("Doctor ID not found.");

        string date = readDate("Appointment date (DD-MM-YYYY): ");
        for (int i = 0; i < 6; i++)
            cout << i + 1 << ". " << SLOTS[i] << "   ";
        cout << endl;
        string slot = SLOTS[readInt("Choose slot (1-6): ", 1, 6) - 1];

        for (int i = 0; i < appointmentCount; i++)
            if (appointments[i].clashesWith(did, date, slot))
                throw runtime_error("This doctor is already booked at that date and time.");

        appointments[appointmentCount] = Appointment(nextAppointmentId, pid, did, date, slot, "Booked");
        appointmentCount++;
        cout << "Appointment booked! Appointment ID = " << nextAppointmentId
             << " | Fee to pay: Rs." << doctors[dpos].getFee() << endl;
        nextAppointmentId++;
    }
    else
    {
        int id = readInt("Appointment ID: ", 1, 999999);
        int pos = findIndex('A', id);
        if (pos == -1)
            throw runtime_error("Appointment not found.");
        if (appointments[pos].getStatus() != "Booked")
            throw runtime_error("Only a Booked appointment can be changed.");
        if (choice == 2)
        {
            appointments[pos].setStatus("Cancelled");
            cout << "Appointment cancelled." << endl;
        }
        else
        {
            appointments[pos].setStatus("Completed");
            cout << "Appointment marked as Completed." << endl;
        }
    }
}

// 7. REPORT
void Hospital::report()
{
    int booked = 0, completed = 0, cancelled = 0, revenue = 0;
    for (int i = 0; i < appointmentCount; i++)
    {
        string st = appointments[i].getStatus();
        if (st == "Booked")
            booked++;
        else if (st == "Cancelled")
            cancelled++;
        else if (st == "Completed")
        {
            completed++;
            int di = findIndex('D', appointments[i].getDoctorId());
            if (di != -1)
                revenue += doctors[di].getFee();
        }
    }

    cout << "\n========== HOSPITAL REPORT ==========" << endl;
    cout << "Total Patients     : " << patientCount << endl;
    cout << "Total Doctors      : " << doctorCount << endl;
    cout << "Total Appointments : " << appointmentCount << endl;
    cout << "  Booked           : " << booked << endl;
    cout << "  Completed        : " << completed << endl;
    cout << "  Cancelled        : " << cancelled << endl;
    cout << "Revenue (completed): Rs." << revenue << endl;
    cout << "-------- Appointments per Doctor --------" << endl;
    for (int d = 0; d < doctorCount; d++)
    {
        int total = 0;
        for (int i = 0; i < appointmentCount; i++)
            if (appointments[i].getDoctorId() == doctors[d].getId())
                total++;
        cout << doctors[d].getName() << " (" << doctors[d].getSpecialization() << ") : " << total << endl;
    }
    cout << "=====================================" << endl;
}

// 8. SAVE / LOAD
void Hospital::saveData()
{
    fileManager.saveAll(*this);
    cout << "Data saved to files successfully." << endl;
}

void Hospital::loadData()
{
    fileManager.loadAll(*this);
    cout << "Data loaded: " << patientCount << " patients, " << doctorCount << " doctors, "
         << appointmentCount << " appointments." << endl;
}
