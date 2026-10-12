#include "Input.h"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <stdexcept>
using namespace std;

// Reads one line from the keyboard. If the input ends, the program stops.
static string getLineFromUser(string prompt)
{
    string line;
    cout << prompt;
    if (!getline(cin, line))
    {
        cout << "\nInput ended. Closing program." << endl;
        exit(0);
    }
    return line;
}

int readInt(string prompt, int low, int high)
{
    while (true)
    {
        string line = getLineFromUser(prompt);
        try
        {
            size_t used = 0;
            int value = stoi(line, &used);          // may throw an exception
            if (used != line.size())
                throw invalid_argument("extra characters");
            if (value < low || value > high)
                throw out_of_range("not in range");
            return value;
        }
        catch (exception &e)
        {
            cout << "Invalid input! Enter a number from " << low << " to " << high << "." << endl;
        }
    }
}

string readText(string prompt)
{
    while (true)
    {
        string text = getLineFromUser(prompt);
        if (text.empty())
            cout << "This field cannot be empty." << endl;
        else if (text.find('|') != string::npos)
            cout << "The character '|' is not allowed." << endl;
        else
            return text;
    }
}

string readName(string prompt)
{
    while (true)
    {
        string name = getLineFromUser(prompt);
        bool ok = !name.empty();
        for (size_t i = 0; i < name.size(); i++)
        {
            if (!isalpha((unsigned char)name[i]) && name[i] != ' ' && name[i] != '.')
                ok = false;
        }
        if (ok)
            return name;
        cout << "Name must contain only letters, spaces and '.'" << endl;
    }
}

string readPhone(string prompt)
{
    while (true)
    {
        string phone = getLineFromUser(prompt);
        bool ok = (phone.size() == 10);
        for (size_t i = 0; i < phone.size(); i++)
        {
            if (!isdigit((unsigned char)phone[i]))
                ok = false;
        }
        if (ok)
            return phone;
        cout << "Phone number must be exactly 10 digits." << endl;
    }
}

string readDate(string prompt)
{
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (true)
    {
        string date = getLineFromUser(prompt);
        bool ok = (date.size() == 10 && date[2] == '-' && date[5] == '-');
        for (size_t i = 0; ok && i < date.size(); i++)
        {
            if (i != 2 && i != 5 && !isdigit((unsigned char)date[i]))
                ok = false;
        }
        if (ok)
        {
            int day = stoi(date.substr(0, 2));
            int month = stoi(date.substr(3, 2));
            int year = stoi(date.substr(6, 4));
            bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (month < 1 || month > 12 || year < 2026 || year > 2100)
                ok = false;
            else
            {
                int maxDay = daysInMonth[month - 1];
                if (month == 2 && leap)
                    maxDay = 29;
                if (day < 1 || day > maxDay)
                    ok = false;
            }
        }
        if (ok)
            return date;
        cout << "Invalid date! Use DD-MM-YYYY (example: 15-10-2026)." << endl;
    }
}
