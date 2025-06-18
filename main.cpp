#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class User {
protected:
    string username, password;
public:
    User(string u, string p) : username(u), password(p) {}
    virtual bool login(string u, string p) { return username == u && password == p; }
    virtual void menu() = 0;
    string getUsername() { return username; }
};

class Appointment {
public:
    string doctor, patient, date, status;
    Appointment(string d, string p, string dt, string s) : doctor(d), patient(p), date(dt), status(s) {}
};

class MedicalRecord {
public:
    string patient, notes;
    MedicalRecord(string p, string n) : patient(p), notes(n) {}
};

class Billing {
public:
    string patient;
    double amount;
    bool paid;
    Billing(string p, double a, bool pay) : patient(p), amount(a), paid(pay) {}
};

class Room {
public:
    int number;
    string patient;
    bool available;
    Room(int n) : number(n), available(true), patient("") {}
};

class HospitalManager {
private:
    vector<Appointment> appointments;
    vector<MedicalRecord> records;
    vector<Billing> bills;
    vector<Room> rooms;
public:
    HospitalManager() {
        for (int i = 1; i <= 5; ++i)
            rooms.push_back(Room(i));
    }

    void addAppointment(string d, string p, string dt) {
        appointments.push_back(Appointment(d, p, dt, "Scheduled"));
    }

    void addRecord(string patient, string notes) {
        records.push_back(MedicalRecord(patient, notes));
    }

    void addBilling(string patient, double amount) {
        bills.push_back(Billing(patient, amount, false));
    }

    void payBill(string patient) {
        for (auto& bill : bills)
            if (bill.patient == patient) bill.paid = true;
    }

    void assignRoom(string patient) {
        for (auto& room : rooms)
            if (room.available) {
                room.available = false;
                room.patient = patient;
                cout << "Room " << room.number << " assigned to " << patient << endl;
                return;
            }
        cout << "No available rooms.\n";
    }

    void viewAppointments() {
        if (appointments.empty()) {
            cout << "No appointments.\n";
            return;
        }
        for (auto& a : appointments)
            cout << "Doctor: " << a.doctor << ", Patient: " << a.patient << ", Date: " << a.date << ", Status: " << a.status << endl;
    }

    void viewBills() {
        if (bills.empty()) {
            cout << "No bills.\n";
            return;
        }
        for (auto& b : bills)
            cout << b.patient << ": Rs." << b.amount << (b.paid ? " [PAID]" : " [UNPAID]") << endl;
    }

    void viewPatientRecords(string patient) {
        bool found = false;
        for (auto& r : records) {
            if (r.patient == patient) {
                cout << "Patient: " << r.patient << ", Notes: " << r.notes << endl;
                found = true;
            }
        }
        if (!found) cout << "No records found for " << patient << endl;
    }

    void viewPatientBills(string patient) {
        bool found = false;
        for (auto& b : bills) {
            if (b.patient == patient) {
                cout << "Amount: Rs." << b.amount << (b.paid ? " [PAID]" : " [UNPAID]") << endl;
                found = true;
            }
        }
        if (!found) cout << "No bills found for " << patient << endl;
    }

    void viewRooms() {
        for (auto& room : rooms) {
            cout << "Room " << room.number << ": ";
            if (room.available)
                cout << "Available\n";
            else
                cout << "Occupied by " << room.patient << endl;
        }
    }
};

HospitalManager hm;

class Admin : public User {
public:
    Admin(string u, string p) : User(u, p) {}
    void menu() {
        int c;
        do {
            cout << "\nAdmin Menu:\n1. View All Appointments\n2. View All Bills\n0. Logout\nChoice: ";
            cin >> c;
            if (c == 1) hm.viewAppointments();
            if (c == 2) hm.viewBills();
        } while (c != 0);
    }
};

class Doctor : public User {
public:
    Doctor(string u, string p) : User(u, p) {}
    void menu() {
        int c;
        string patient, notes;
        do {
            cout << "\nDoctor Menu:\n1. Add Medical Record\n2. View Patient Records\n0. Logout\nChoice: ";
            cin >> c;
            cin.ignore();
            if (c == 1) {
                cout << "Patient Name: "; getline(cin, patient);
                cout << "Notes: "; getline(cin, notes);
                hm.addRecord(patient, notes);
            }
            if (c == 2) {
                cout << "Patient Name: "; getline(cin, patient);
                hm.viewPatientRecords(patient);
            }
        } while (c != 0);
    }
};

class Patient : public User {
public:
    Patient(string u, string p) : User(u, p) {}
    void menu() {
        int c;
        string doctor, date;
        do {
            cout << "\nPatient Menu:\n1. Book Appointment\n2. Pay Bill\n3. View My Records\n4. View My Bills\n0. Logout\nChoice: ";
            cin >> c;
            cin.ignore();
            if (c == 1) {
                cout << "Doctor Name: "; getline(cin, doctor);
                cout << "Date: "; getline(cin, date);
                hm.addAppointment(doctor, username, date);
            }
            if (c == 2) hm.payBill(username);
            if (c == 3) hm.viewPatientRecords(username);
            if (c == 4) hm.viewPatientBills(username);
        } while (c != 0);
    }
};

class Receptionist : public User {
public:
    Receptionist(string u, string p) : User(u, p) {}
    void menu() {
        int c;
        string name;
        double amount;
        do {
            cout << "\nReceptionist Menu:\n1. Assign Room\n2. Add Billing\n3. View Rooms\n0. Logout\nChoice: ";
            cin >> c;
            cin.ignore();
            if (c == 1) {
                cout << "Patient Name: "; getline(cin, name);
                hm.assignRoom(name);
            }
            if (c == 2) {
                cout << "Patient Name: "; getline(cin, name);
                cout << "Amount: "; cin >> amount; cin.ignore();
                hm.addBilling(name, amount);
            }
            if (c == 3) hm.viewRooms();
        } while (c != 0);
    }
};

int main() {
    map<string, User*> users;
    users["admin"] = new Admin("admin", "123");
    users["doctor"] = new Doctor("doctor", "123");
    users["patient"] = new Patient("patient", "123");
    users["receptionist"] = new Receptionist("reception", "123");

    string uname, pass;
    cout << "Username: "; cin >> uname;
    cout << "Password: "; cin >> pass;

    if (users.count(uname) && users[uname]->login(uname, pass))
        users[uname]->menu();
    else
        cout << "Invalid login." << endl;

    for (auto& u : users) delete u.second;
    return 0;
}
