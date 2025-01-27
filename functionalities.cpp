#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

// Global data structures
map<string, string> students;  // Stores student ID and Name
map<string, string> attendance; // Stores attendance {StudentID: "P" or "A"}

// Function prototypes
void registerStudent();
void markAttendance();
void viewAttendance();
void saveData();
void loadData();
void menu();

int main() {
    loadData(); // Load data from files at the start
    menu();
    saveData(); // Save data to files before exiting
    return 0;
}

// Function to display menu
void menu() {
    int choice;
    do {
        cout << "\n--- Simple Student Attendance System ---\n";
        cout << "1. Register Student\n";
        cout << "2. Mark Attendance\n";
        cout << "3. View Attendance\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerStudent();
                break;
            case 2:
                markAttendance();
                break;
            case 3:
                viewAttendance();
                break;
            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

// Function to register a new student
void registerStudent() {
    string studentID, name;
    cout << "Enter Student ID: ";
    cin >> studentID;
    cout << "Enter Student Name: ";
    cin.ignore(); // Clear buffer
    getline(cin, name);

    if (students.find(studentID) != students.end()) {
        cout << "Student ID " << studentID << " is already registered.\n";
    } else {
        students[studentID] = name;
        cout << "Student " << name << " registered successfully.\n";
    }
}

// Function to mark attendance
void markAttendance() {
    string studentID, status;
    cout << "Enter Student ID to mark attendance: ";
    cin >> studentID;

    if (students.find(studentID) == students.end()) {
        cout << "Student ID " << studentID << " is not registered.\n";
    } else {
        cout << "Mark attendance for " << students[studentID] << " (P for Present, A for Absent): ";
        cin >> status;

        if (status == "P" || status == "A") {
            attendance[studentID] = status;
            cout << "Attendance marked for " << students[studentID] << ".\n";
        } else {
            cout << "Invalid input. Use 'P' or 'A'.\n";
        }
    }
}

// Function to view attendance
void viewAttendance() {
    if (attendance.empty()) {
        cout << "No attendance records found.\n";
        return;
    }

    cout << "\nAttendance Records:\n";
    cout << "Student ID\tName\t\tStatus\n";
    cout << "----------------------------------\n";
    for (const auto &entry : attendance) {
        string studentID = entry.first;
        string status = entry.second;
        cout << studentID << "\t\t" << students[studentID] << "\t\t" << status << "\n";
    }
}

// Function to save data to files
void saveData() {
    ofstream studentFile("students.txt");
    ofstream attendanceFile("attendance.txt");

    // Save students data
    for (const auto &entry : students) {
        studentFile << entry.first << "," << entry.second << "\n";
    }

    // Save attendance data
    for (const auto &entry : attendance) {
        attendanceFile << entry.first << "," << entry.second << "\n";
    }

    studentFile.close();
    attendanceFile.close();
    cout << "Data saved successfully.\n";
}

// Function to load data from files
void loadData() {
    ifstream studentFile("students.txt");
    ifstream attendanceFile("attendance.txt");

    // Load students data
    string line, studentID, name;
    while (getline(studentFile, line)) {
        size_t commaPos = line.find(',');
        studentID = line.substr(0, commaPos);
        name = line.substr(commaPos + 1);
        students[studentID] = name;
    }

    // Load attendance data
    string status;
    while (getline(attendanceFile, line)) {
        size_t commaPos = line.find(',');
        studentID = line.substr(0, commaPos);
        status = line.substr(commaPos + 1);
        attendance[studentID] = status;
    }

    studentFile.close();
    attendanceFile.close();
    cout << "Data loaded successfully.\n";
}
