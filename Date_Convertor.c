#include <iostream>
#include <vector>

using namespace std;

// Structure to represent a date
struct Date {
    int year;
    int month;
    int day;
};

// Number of days in each month for the Georgian (Gregorian) calendar
vector<int> daysInGeorgianMonth = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Number of days in each month for the Shamsi (Solar Hijri) calendar
vector<int> daysInShamsiMonth = {0, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29, 30};

// Function to check if a year is a leap year in the Georgian calendar
bool isLeapGeorgian(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to convert a Georgian date to a Shamsi date
Date georgianToShamsi(Date georgianDate) {
    int shYear = georgianDate.year - 621; // Offset between Georgian and Shamsi years
    int shMonth = 3;
    int shDay = 21;

    int georgianDays = 0;
    for (int i = 1; i < georgianDate.year; i++) {
        georgianDays += isLeapGeorgian(i) ? 366 : 365;
    }
    for (int i = 1; i < georgianDate.month; i++) {
        georgianDays += daysInGeorgianMonth[i];
    }
    georgianDays += georgianDate.day;

    int shamsiDays = georgianDays - (georgianDate.year % 4 == 1 ? 80 : 79);

    while (shamsiDays > (isLeapGeorgian(georgianDate.year) ? 366 : 365)) {
        shamsiDays -= isLeapGeorgian(georgianDate.year) ? 366 : 365;
        shYear++;
    }

    for (int i = 1; i <= 12; i++) {
        int monthDays = daysInShamsiMonth[i];
        if (i == 12 && !isLeapGeorgian(georgianDate.year)) {
            monthDays--;
        }
        if (shamsiDays <= monthDays) {
            shMonth = i;
            shDay = shamsiDays;
            break;
        }
        shamsiDays -= monthDays;
    }

    Date shamsiDate = {shYear, shMonth, shDay};
    return shamsiDate;
}

// Function to convert a Shamsi date to a Georgian date
Date shamsiToGeorgian(Date shamsiDate) {
    int geYear = shamsiDate.year + 621; // Offset between Shamsi and Georgian years
    int geMonth = 1;
    int geDay = 1;

    int shamsiDays = 0;
    for (int i = 1; i < shamsiDate.year; i++) {
        shamsiDays += isLeapGeorgian(geYear) ? 366 : 365;
    }
    for (int i = 1; i < shamsiDate.month; i++) {
        shamsiDays += daysInShamsiMonth[i];
    }
    shamsiDays += shamsiDate.day;

    int georgianDays = shamsiDays + (geYear % 4 == 0 ? 80 : 79);

    while (georgianDays > (isLeapGeorgian(geYear) ? 366 : 365)) {
        georgianDays -= isLeapGeorgian(geYear) ? 366 : 365;
        geYear++;
    }

    for (int i = 1; i <= 12; i++) {
        int monthDays = daysInGeorgianMonth[i];
        if (i == 2 && isLeapGeorgian(geYear)) {
            monthDays++;
        }
        if (georgianDays <= monthDays) {
            geMonth = i;
            geDay = georgianDays;
            break;
        }
        georgianDays -= monthDays;
    }

    Date georgianDate = {geYear, geMonth, geDay};
    return georgianDate;
}

int main() {
    Date inputDate;

    cout << "Enter a date in Georgian calendar (YYYY MM DD): ";
    cin >> inputDate.year >> inputDate.month >> inputDate.day;

    Date shamsiResult = georgianToShamsi(inputDate);
    cout << "In Shamsi calendar: " << shamsiResult.year << " " << shamsiResult.month << " " << shamsiResult.day << endl;

    cout << "Enter a date in Shamsi calendar (YYYY MM DD): ";
    cin >> inputDate.year >> inputDate.month >> inputDate.day;

    Date georgianResult = shamsiToGeorgian(inputDate);
    cout << "In Georgian calendar: " << georgianResult.year << " " << georgianResult.month << " " << georgianResult.day << endl;

    return 0;
}
