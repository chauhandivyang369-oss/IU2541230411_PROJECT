#ifndef INPUT_H
#define INPUT_H

#include <string>
using namespace std;

// Small helper functions that read and VALIDATE what the user types.
int    readInt(string prompt, int low, int high);   // number inside a range
string readText(string prompt);                     // non-empty text (no '|')
string readName(string prompt);                     // letters, spaces and '.' only
string readPhone(string prompt);                    // exactly 10 digits
string readDate(string prompt);                     // DD-MM-YYYY

#endif
