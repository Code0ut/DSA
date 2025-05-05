/*Company maintains employee information as employee ID, name, designation and salary.
Allow user to add, delete information of employee. Display information of particular employee.
If employee does not exist an appropriate message is displayed. If it is, then the system
displays the employee details. Use index sequential file to maintain the data.*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Employee class to store employee data
class Employee {
private:
    int id;
    string name;
    string designation;
    double salary;

public:
    Employee() : id(0), name(""), designation(""), salary(0.0) {}

    // Setters and getters
    void setId(int id) { this->id = id; }
    int getId() const { return id; }

    void setName(string name) { this->name = name; }
    string getName() const { return name; }

    void setDesignation(string designation) { this->designation = designation; }
    string getDesignation() const { return designation; }

    void setSalary(double salary) { this->salary = salary; }
    double getSalary() const { return salary; }

    // Save employee details to file
    void saveToFile(ofstream &file) const {
        file << id << endl;
        file << name << endl;
        file << designation << endl;
        file << salary << endl;
    }

    // Read employee details from file
    void readFromFile(ifstream &file) {
        file >> id;
        file.ignore(); // To ignore the newline character after reading the id
        getline(file, name);
        getline(file, designation);
        file >> salary;
        file.ignore(); // To handle the new line after reading the salary
    }

    // Display employee details
    void display() const {
        cout << "Employee ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Designation: " << designation << endl;
        cout << "Salary: " << salary << endl;
    }
};

// EmployeeDatabase class to handle file operations
class EmployeeDatabase {
public:
    // Add an employee to both the data file and index file
    void addEmployee(const Employee &emp) {
        ofstream dataFile("employees.txt", ios::app); // Open in append mode
        ofstream indexFile("index.txt", ios::app); // Open in append mode

        if (!dataFile || !indexFile) {
            cout << "Error opening files!" << endl;
            return;
        }

        // Write employee data to the data file
        long pos = dataFile.tellp();  // Get the current position in the file (record position)
        emp.saveToFile(dataFile);

        // Write employee ID and position to the index file
        indexFile << emp.getId() << " " << pos << endl;

        cout << "Employee added successfully!" << endl;

        dataFile.close();
        indexFile.close();
    }

    // Display employee details using ID
    void displayEmployee(int empID) {
        ifstream dataFile("employees.txt");
        ifstream indexFile("index.txt");

        if (!dataFile || !indexFile) {
            cout << "Error opening files!" << endl;
            return;
        }

        int id;
        long position;
        bool found = false;

        // Search for the employee ID in the index file
        while (indexFile >> id >> position) {
            if (id == empID) {
                // If ID matches, retrieve employee data from the data file
                dataFile.seekg(position, ios::beg);  // Move the file pointer to the correct position
                Employee emp;
                emp.readFromFile(dataFile);
                emp.display();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Employee not found!" << endl;
        }

        dataFile.close();
        indexFile.close();
    }

    // Delete employee by ID
    void deleteEmployee(int empID) {
        ifstream dataFile("employees.txt");
        ifstream indexFile("index.txt");
        ofstream tempDataFile("temp_employees.txt");
        ofstream tempIndexFile("temp_index.txt");

        if (!dataFile || !indexFile || !tempDataFile || !tempIndexFile) {
            cout << "Error opening files!" << endl;
            return;
        }

        int id;
        long position;
        bool found = false;

        // Copy records to temporary files, skipping the deleted employee
        while (indexFile >> id >> position) {
            if (id == empID) {
                found = true;  // Skip the employee to be deleted
                continue;
            }
            // Copy data from data file to temp data file
            dataFile.seekg(position, ios::beg);
            Employee emp;
            emp.readFromFile(dataFile);
            emp.saveToFile(tempDataFile);
            // Copy index data to temp index file
            tempIndexFile << id << " " << position << endl;
        }

        dataFile.close();
        indexFile.close();
        tempDataFile.close();
        tempIndexFile.close();

        if (found) {
            // Delete original files and rename temporary files
            remove("employees.txt");
            remove("index.txt");
            rename("temp_employees.txt", "employees.txt");
            rename("temp_index.txt", "index.txt");

            cout << "Employee deleted successfully!" << endl;
        } else {
            cout << "Employee not found!" << endl;
        }
    }
};

int main() {
    EmployeeDatabase db;
    int choice;

    do {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // Add employee
            Employee emp;
            int id;
            string name, designation;
            double salary;
            cout << "Enter Employee ID: ";
            cin >> id;
            emp.setId(id);
            cin.ignore(); // To ignore the newline after reading ID
            cout << "Enter Employee Name: ";
            getline(cin, name);
            emp.setName(name);
            cout << "Enter Designation: ";
            getline(cin, designation);
            emp.setDesignation(designation);
            cout << "Enter Salary: ";
            cin >> salary;
            emp.setSalary(salary);
            db.addEmployee(emp);
            break;
        }
        case 2: {
            // Display employee
            int empID;
            cout << "Enter Employee ID to display: ";
            cin >> empID;
            db.displayEmployee(empID);
            break;
        }
        case 3: {
            // Delete employee
            int empID;
            cout << "Enter Employee ID to delete: ";
            cin >> empID;
            db.deleteEmployee(empID);
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
