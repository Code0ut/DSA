/*Consider a scenario for Hospital to cater services to different kinds of patients as Serious (top
priority), b) non serious (medium priority), c) General Checkup(least priority). Implement the
priority queue to cater services to the patients.*/

#include<iostream>
#include<string>
using namespace std;

class Patient {
public:
    string name;
    int priority;
    Patient* next;

    Patient(string name, int priority) {
        this->name = name;
        this->priority = priority;
        this->next = nullptr;
    }
};

class PriorityQueue {
    Patient* front;

public:
    PriorityQueue() {
        front = nullptr;
    }

    void insert(string name, int priority) {
        Patient* newPatient = new Patient(name, priority);

        if (front == nullptr || priority < front->priority) {
            newPatient->next = front;
            front = newPatient;
        } else {
            Patient* temp = front;
            while (temp->next != nullptr && temp->next->priority <= priority) {
                temp = temp->next;
            }
            newPatient->next = temp->next;
            temp->next = newPatient;
        }
        cout << "Patient added: " << name << " with priority " << priority << "\n";
    }

    void servePatient() {
        if (front == nullptr) {
            cout << "No patients in queue.\n";
            return;
        }
        cout << "Serving patient: " << front->name << " (Priority " << front->priority << ")\n";
        Patient* temp = front;
        front = front->next;
        delete temp;
    }

    void displayQueue() {
        if (front == nullptr) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Patients in queue:\n";
        Patient* temp = front;
        while (temp != nullptr) {
            cout << "Name: " << temp->name << ", Priority: " << temp->priority << "\n";
            temp = temp->next;
        }
    }

    ~PriorityQueue() {
        while (front != nullptr) {
            Patient* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main() {
    PriorityQueue pq;
    int choice;
    string name;
    int priority;

    do {
        cout << "\n1. Add Patient\n2. Serve Patient\n3. Display Queue\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Patient Name: ";
                cin >> name;
                cout << "Enter Priority (1: Serious, 2: Non-Serious, 3: General): ";
                cin >> priority;
                pq.insert(name, priority);
                break;
            case 2:
                pq.servePatient();
                break;
            case 3:
                pq.displayQueue();
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
