// Hospital Appointment System  (Enrollment: IU2541230411, Project: CPP02)
// main.cpp only shows the menu and calls the Hospital class functions.

#include <iostream>
#include <stdexcept>
#include "Hospital.h"
#include "Input.h"
using namespace std;

void showMenu()
{
    cout << "\n=======================================" << endl;
    cout << "     HOSPITAL APPOINTMENT SYSTEM" << endl;
    cout << "=======================================" << endl;
    cout << "1. Add Record" << endl;
    cout << "2. Display Records" << endl;
    cout << "3. Search Record" << endl;
    cout << "4. Update Record" << endl;
    cout << "5. Delete Record" << endl;
    cout << "6. Book / Manage Appointment (Main Process)" << endl;
    cout << "7. Report" << endl;
    cout << "8. Save / Load" << endl;
    cout << "9. Exit" << endl;
}

int main()
{
    Hospital hospital;
    int choice = 0;

    hospital.loadData();                    // load old records at start

    do
    {
        showMenu();
        try
        {
            choice = readInt("Enter your choice (1-9): ", 1, 9);
            switch (choice)
            {
            case 1: hospital.addRecord(); break;
            case 2: hospital.displayRecords(); break;
            case 3: hospital.searchRecord(); break;
            case 4: hospital.updateRecord(); break;
            case 5: hospital.deleteRecord(); break;
            case 6: hospital.appointmentProcess(); break;
            case 7: hospital.report(); break;
            case 8:
                cout << "\n1. Save data now\n2. Load data from files\n";
                if (readInt("Enter choice: ", 1, 2) == 1)
                    hospital.saveData();
                else
                    hospital.loadData();
                break;
            }
        }
        catch (exception &e)                // every error from the classes lands here
        {
            cout << "\nError: " << e.what() << endl;
        }
    } while (choice != 9);

    try
    {
        hospital.saveData();                // save before leaving
    }
    catch (exception &e)
    {
        cout << "Error while saving: " << e.what() << endl;
    }
    cout << "Thank you for using the Hospital Appointment System." << endl;
    return 0;
}
