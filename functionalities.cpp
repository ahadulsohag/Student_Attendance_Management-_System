#include <bits/stdc++.h>
using namespace std;

// Global data structures with dynamic memory allocation
map<string, string> *students = new map<string, string>();  // Stores student ID and Name
map<string, string> *attendance = new map<string, string>(); // Stores attendance {StudentID: "P" or "A"}
bool isAdmin = false;

// Function prototypes
void registerStudent();
void markAttendance();
void viewAttendance();
void generateReport();
void viewAllStudents();
void saveData();
void loadData();
void freeMemory();
void menu();
void login();
string encryptData(const string &data);
string decryptData(const string &data);

int main() {
    login();
    loadData(); // Load data from files at the start
    menu();
    saveData(); // Save data to files before exiting
    freeMemory(); // Free dynamically allocated memory
    return 0;
}

void login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == "admin" && password == "admin123") {
        isAdmin = true;
        cout << "Admin access granted." << endl;
    } else {
        cout << "User access granted. You can only view attendance and student details." << endl;
    }
}

void menu() {
    int choice;
    do {
        cout << "\n--- Simple Student Attendance System ---\n";
        cout << "1. Register Student\n";
        cout << "2. Mark Attendance\n";
        cout << "3. View Attendance\n";
        cout << "4. Generate Report\n";
        cout << "5. View All Students\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (isAdmin)
                    registerStudent();
                else
                    cout << "Access Denied!" << endl;
                break;
            case 2:
                if (isAdmin)
                    markAttendance();
                else
                    cout << "Access Denied!" << endl;
                break;
            case 3:
                viewAttendance();
                break;
            case 4:
                generateReport();
                break;
            case 5:
                viewAllStudents();
                break;
            case 6:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}

void registerStudent() {
    string studentID, name;
    cout << "Enter Student ID: ";
    cin >> studentID;
    cout << "Enter Student Name: ";
    cin.ignore(); // Clear buffer
    getline(cin, name);

    if (students->find(studentID) != students->end()) {
        cout << "Student ID " << studentID << " is already registered." << endl;
    } else {
        (*students)[studentID] = name;
        cout << "Student " << name << " registered successfully." << endl;
    }
}

void markAttendance() {
    string studentID, status;
    cout << "Enter Student ID to mark attendance: ";
    cin >> studentID;

    if (students->find(studentID) == students->end()) {
        cout << "Student ID " << studentID << " is not registered." << endl;
    } else {
        cout << "Mark attendance for " << (*students)[studentID] << " (P for Present, A for Absent): ";
        cin >> status;

        if (status == "P" || status == "A") {
            (*attendance)[studentID] = status;
            cout << "Attendance marked for " << (*students)[studentID] << "." << endl;
        } else {
            cout << "Invalid input. Use 'P' or 'A'." << endl;
        }
    }
}

void viewAttendance() {
    if (attendance->empty()) {
        cout << "No attendance records found." << endl;
        return;
    }

    cout << "\nAttendance Records:\n";
    cout << "Student ID\tName\t\tStatus\n";
    cout << "----------------------------------\n";
    for (const auto &entry : *attendance) {
        string studentID = entry.first;
        string status = entry.second;
        cout << studentID << "\t\t" << (*students)[studentID] << "\t\t" << status << "\n";
    }
}

void generateReport() {
    cout << "\nGenerating attendance report...\n";
    for (const auto &entry : *attendance) {
        cout << "Student ID: " << entry.first << " - "
             << (*students)[entry.first] << " - Attendance: " << entry.second << "\n";
    }
}

void viewAllStudents() {
    cout << "\nTotal number of students: " << students->size() << "\n";
    cout << "Student Details:\n";
    cout << "Student ID\tName\n";
    cout << "-----------------------------\n";
    for (const auto &entry : *students) {
        cout << entry.first << "\t\t" << entry.second << "\n";
    }
}

void saveData() {
    ofstream studentFile("students.txt");
    ofstream attendanceFile("attendance.txt");

    // Save students data with encrypted names
    for (const auto &entry : *students) {
        studentFile << entry.first << "," << encryptData(entry.second) << "\n";
    }

    // Save attendance data
    for (const auto &entry : *attendance) {
        attendanceFile << entry.first << "," << entry.second << "\n";
    }

    studentFile.close();
    attendanceFile.close();
    cout << "Data saved successfully." << endl;
}

void loadData() {
    ifstream studentFile("students.txt");
    ifstream attendanceFile("attendance.txt");

    string line, studentID, name, status;

    // Load students data and decrypt the names
    while (getline(studentFile, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            studentID = line.substr(0, commaPos);
            name = line.substr(commaPos + 1);
            name = decryptData(name);
            (*students)[studentID] = name;
        }
    }

    // Load attendance data
    while (getline(attendanceFile, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            studentID = line.substr(0, commaPos);
            status = line.substr(commaPos + 1);
            (*attendance)[studentID] = status;
        }
    }

    studentFile.close();
    attendanceFile.close();
    cout << "Data loaded successfully." << endl;
}

string encryptData(const string &data) {
    string encrypted = data;
    for (char &c : encrypted) {
        c += 3;  // Simple Caesar cipher for demonstration
    }
    return encrypted;
}

string decryptData(const string &data) {
    string decrypted = data;
    for (char &c : decrypted) {
        c -= 3;
    }
    return decrypted;
}

void freeMemory() {
    delete students;
    delete attendance;
    cout << "Memory freed successfully." << endl;
}
