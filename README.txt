HOSPITAL APPOINTMENT SYSTEM
Enrollment Number : IU2541230411
Project Code      : CPP02
Language          : C++ (works with g++ and C++11 or newer)

ABOUT
Console program to manage patients, doctors and appointments.
Features: add, display, search, update, delete, book/cancel/complete
appointments (double booking is blocked), report, save/load with files.

OOP CONCEPTS USED
Classes and objects, encapsulation, default and parameterized constructors,
destructors, inheritance (Person -> Patient, Doctor), runtime polymorphism
(virtual display() and toFileString()), dynamic memory (new[] / delete[]),
file handling (persistence), validation, exception handling, modular .h/.cpp.

FOLDER STRUCTURE
Source/       main.cpp and all class .h / .cpp files
Data/         patients.txt, doctors.txt, appointments.txt (sample data)
Diagrams/     UseCase.png, ClassDiagram.png, Sequence1.png, Sequence2.png
Executable/   compiled program
Screenshots/  program screenshots
README.txt
ProjectReport.pdf

HOW TO COMPILE
Open a terminal / command prompt in the Source folder and run:

  Windows (MinGW g++):
    g++ *.cpp -o ../Executable/Project.exe

  Linux / macOS:
    g++ *.cpp -o ../Executable/Project

HOW TO RUN
IMPORTANT: run the program from inside the Executable folder, because the
data files are read from ../Data/

  Windows:        cd Executable        then        Project.exe
  Linux / macOS:  cd Executable        then        ./Project

HOW TO TEST PERSISTENCE
1. Run the program, add a patient, choose 9 (Exit) - data is saved.
2. Run the program again - the message "Data loaded: ..." appears and
   the saved records are shown in Display Records.

MENU
1 Add Record          2 Display Records     3 Search Record
4 Update Record       5 Delete Record       6 Book / Manage Appointment
7 Report              8 Save / Load         9 Exit

SAMPLE IDs IN THE PROVIDED DATA
Patients 1001-1005, Doctors 2001-2003, Appointments 3001, 3002, 3003, 3005, 3006

NOTE
The file in Executable/ was built on Linux (name: Project). To get
Project.exe on Windows, compile with the command shown above.
