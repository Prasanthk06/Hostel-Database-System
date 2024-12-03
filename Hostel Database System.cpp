#include <iostream>
#include <string>
using namespace std;

class Hostel {
    int r_id;
    string name;
    int roomno;
    int fee;
    int year;
    static int totalstudent;
    static int current_id;

public:
    Hostel() {
        r_id = ++current_id;
        name = "Kumar";
        roomno = 23;
        fee = 2400;
        year = 2022;
        totalstudent++;
    }

    Hostel(string n, int r) {
        r_id = ++current_id;
        name = n;
        roomno = r;
        fee = 3000;
        year = 2024;
        totalstudent++;
    }

    Hostel(string n, int r, int f, int y) {
        r_id = ++current_id;
        name = n;
        roomno = r;
        fee = f;
        year = y;
        totalstudent++;
    }

    virtual void displayDetails() const {
        cout << "Room id: " << r_id << endl;
        cout << "Student Name: " << name << endl;
        cout << "Room Number: " << roomno << endl;
        cout << "Fees: " << fee << endl;
        cout << "Year of Joining: " << year << endl;
    }

    static int getTotalStudent() {
        return totalstudent;
    }

    Hostel& operator++() {
        r_id++;
        return *this;
    }

    Hostel operator++(int) {
        Hostel temp = *this;
        r_id++;
        return temp;
    }

    Hostel operator+(const Hostel& other) {
        Hostel temp;
        temp.fee = this->fee + other.fee;
        return temp;
    }

    Hostel operator-(const Hostel& other) {
        Hostel temp;
        temp.fee = this->fee - other.fee;
        return temp;
    }

    bool operator==(const Hostel& other) const {
        return this->fee == other.fee && this->roomno == other.roomno;
    }

    string operator[](int index) const {
        switch (index) {
            case 0: return name;
            case 1: return to_string(roomno);
            case 2: return to_string(fee);
            case 3: return to_string(year);
            default: return "Invalid index";
        }
    }

    virtual ~Hostel() {}
};

class Warden : public Hostel {
private:
    string entry_time;
    string exit_time;

public:
    Warden(string n, int r, int f, int y, string et, string xt)
        : Hostel(n, r, f, y), entry_time(et), exit_time(xt) {}

    void displayDetails() const override {
        Hostel::displayDetails();
        cout << "Entry Time: " << entry_time << endl;
        cout << "Exit Time: " << exit_time << endl;
    }
};

class AssistantWarden : public Warden {
private:
    string duties;

public:
    AssistantWarden(string n, int r, int f, int y, string et, string xt, string d)
        : Warden(n, r, f, y, et, xt), duties(d) {}

    void displayDetails() const override {
        Warden::displayDetails();
        cout << "Duties: " << duties << endl;
    }
};

int Hostel::current_id = 0;
int Hostel::totalstudent = 0;

int main() {
    int arrSize;
    cout << "Enter number of residents: ";
    cin >> arrSize;

    Hostel** hostelArray = new Hostel*[arrSize];

    for (int i = 0; i < arrSize; i++) {
        int person_type;
        cout << "Enter person type (1-Student, 2-Warden, 3-Assistant Warden): ";
        cin >> person_type;

        switch (person_type) {
            case 1: {
                int constructorChoice;
                cout << "Choose constructor for student " << (i + 1) << " (1-Default, 2-Name and Room, 3-All details): ";
                cin >> constructorChoice;

                switch (constructorChoice) {
                    case 1:
                        hostelArray[i] = new Hostel();
                        break;
                    case 2: {
                        string name;
                        int roomno;
                        cout << "Enter Name: ";
                        cin >> name;
                        cout << "Enter Room Number: ";
                        cin >> roomno;
                        hostelArray[i] = new Hostel(name, roomno);
                        break;
                    }
                    case 3: {
                        string name;
                        int roomno, year, fee;
                        cout << "Enter Name: ";
                        cin >> name;
                        cout << "Enter Room Number: ";
                        cin >> roomno;
                        cout << "Enter the fee: ";
                        cin >> fee;
                        cout << "Enter Year of Joining: ";
                        cin >> year;
                        hostelArray[i] = new Hostel(name, roomno, fee, year);
                        break;
                    }
                    default:
                        hostelArray[i] = new Hostel();
                }
                break;
            }
            case 2: {
                string name, entry_time, exit_time;
                int roomno, year, fee;
                cout << "Enter Warden Name: ";
                cin >> name;
                cout << "Enter Room Number: ";
                cin >> roomno;
                cout << "Enter Fee: ";
                cin >> fee;
                cout << "Enter Year: ";
                cin >> year;
                cout << "Enter Entry Time: ";
                cin >> entry_time;
                cout << "Enter Exit Time: ";
                cin >> exit_time;
                hostelArray[i] = new Warden(name, roomno, fee, year, entry_time, exit_time);
                break;
            }
            case 3: {
                string name, entry_time, exit_time, duties;
                int roomno, year, fee;
                cout << "Enter Assistant Warden Name: ";
                cin >> name;
                cout << "Enter Room Number: ";
                cin >> roomno;
                cout << "Enter Fee: ";
                cin >> fee;
                cout << "Enter Year: ";
                cin >> year;
                cout << "Enter Entry Time: ";
                cin >> entry_time;
                cout << "Enter Exit Time: ";
                cin >> exit_time;
                cout << "Enter Duties: ";
                cin >> duties;
                hostelArray[i] = new AssistantWarden(name, roomno, fee, year, entry_time, exit_time, duties);
                break;
            }
            default:
                hostelArray[i] = nullptr;
        }

        if (hostelArray[i]) {
            cout << "\nDetails for entry " << (i + 1) << ":\n";
            hostelArray[i]->displayDetails();
        }
    }

    if (arrSize >= 2) {
        cout << "\nAdding fees of Student 1 and Student 2:\n";
        Hostel h_add = *hostelArray[0] + *hostelArray[1];
        h_add.displayDetails();

        cout << "\nSubtracting fees of Student 2 from Student 1:\n";
        Hostel h_sub = *hostelArray[0] - *hostelArray[1];
        h_sub.displayDetails();

        cout << "\nChecking if Student 1 and Student 2 are equal:\n";
        if (*hostelArray[0] == *hostelArray[1])
            cout << "Student 1 and Student 2 have equal fee and room number.\n";
        else
            cout << "Student 1 and Student 2 do not have equal fee or room number.\n";
    }

    cout << "\nAccessing details using subscript operator:\n";
    cout << "Student 1 Name: " << (*hostelArray[0])[0] << endl;
    cout << "Student 1 Room Number: " << (*hostelArray[0])[1] << endl;
    cout << "Student 1 Fee: " << (*hostelArray[0])[2] << endl;
    cout << "Student 1 Year: " << (*hostelArray[0])[3] << endl;

    cout << "\nTotal Students: " << Hostel::getTotalStudent() << endl;

    for (int i = 0; i < arrSize; i++) {
        delete hostelArray[i];
    }
    delete[] hostelArray;

    return 0;
}

