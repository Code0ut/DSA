/*Department maintains a student information. The file contains roll number, name, division and
address. Allow user to add, delete information of student. Display information of particular
employee. If record of student does not exist an appropriate message is displayed. If it is,
then the system displays the student details. Use sequential file to main the data.*/

#include <iostream>
#include <fstream>
using namespace std;

class Student {
    int roll;
    string name;
    string division;
    string address;

public:
    void input() {
        cout << "Enter Roll No: ";
        cin >> roll;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Division: ";
        cin >> division;
        cout << "Enter Address: ";
        cin >> address;
    }

    void display() {
        cout << "Roll No: " << roll << "\nName: " << name << "\nDivision: " << division << "\nAddress: " << address << "\n";
    }

    int getRoll() {
        return roll;
    }
};

void addStudent() {
    Student s;
    ofstream fout("students.txt", ios::app);
    s.input();
    fout.write((char*)&s, sizeof(s));
    fout.close();
    cout << "Record added successfully.\n";
}

void displayStudent(int rno) {
    ifstream fin("students.txt");
    Student s;
    bool found = false;

    while (fin.read((char*)&s, sizeof(s))) {
        if (s.getRoll() == rno) {
            cout << "Student found:\n";
            s.display();
            found = true;
            break;
        }
    }

    fin.close();
    if (!found)
        cout << "Student with Roll No " << rno << " not found.\n";
}

void deleteStudent(int rno) {
    ifstream fin("students.txt");
    ofstream temp("temp.txt");
    Student s;
    bool deleted = false;

    while (fin.read((char*)&s, sizeof(s))) {
        if (s.getRoll() == rno) {
            deleted = true;
            continue;
        }
        temp.write((char*)&s, sizeof(s));
    }

    fin.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (deleted)
        cout << "Record deleted successfully.\n";
    else
        cout << "Record not found.\n";
}

int main() {
    int choice, rno;

    do {
        cout << "\n--- Student Information Menu ---\n";
        cout << "1. Add Student\n2. Display Student\n3. Delete Student\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll No to search: ";
                cin >> rno;
                displayStudent(rno);
                break;
            case 3:
                cout << "Enter Roll No to delete: ";
                cin >> rno;
                deleteStudent(rno);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
