#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
using namespace std;

class Hospital;     // only a declaration (Hospital.h includes this file)

// Takes care of saving and loading all records in text files.
class FileManager
{
private:
    string patientFile;
    string doctorFile;
    string appointmentFile;

public:
    FileManager();
    void saveAll(const Hospital &h);
    void loadAll(Hospital &h);
    int splitLine(string line, string parts[], int maxParts);   // splits at '|'
};

#endif
