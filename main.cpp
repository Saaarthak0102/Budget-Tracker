#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Attendee {
// aggregation with event class
public:
    string name;
    string contact;
    bool rsvp;
    bool hasGuest;
    string guestName;
    bool needsSecurity;

public:
    Attendee(string name, string contact, bool rsvp,bool hasGuest = false, string guestName = "", bool needsSecurity = false) {
        this->name = name;
        this->contact = contact;
        this->rsvp = rsvp;
        this->hasGuest = hasGuest;
        this->guestName = guestName;
        this->needsSecurity = needsSecurity;
    }
    
    void display() {
        cout << "\nAttendee Details:\n";
        cout << "Name: " << name << endl;
        cout << "Contact: " << contact << endl;
        cout << "RSVP: " << (rsvp ? "Yes" : "No") << endl;
        if (hasGuest) {
            cout << "Guest Attending: Yes" << endl;
            cout << "Guest Name: " << guestName << endl;
            cout << "Security Needed for Guest: " << (needsSecurity ? "Yes" : "No") << endl;
        } else {
            cout << "Guest Attending: No" << endl;
        }
    }
};


class Services{
    // composition with event class
public:
    string name;
    int contact;
    string type;
    int price;
    bool avaialability;
    int rating;
    static int serialNo;


    //constructor for custom services
    Services(string name, int contact, string type, int price, bool avaialability, int rating) {
        serialNo ++;
        this->name = name;
        this->contact = contact;
        this->type = type;
        this->price = price;
        this->avaialability = avaialability;
        this->rating = rating;
    }

    //constructor for reading from file
    Services(int searchSerialNo) {
        ifstream file("services.csv");
        if (!file.is_open()) {
            cerr << "Error: Could not open services.csv" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string temp;
            int currentSerialNo;
            getline(ss, temp, ',');
            currentSerialNo = stoi(temp);

            if (currentSerialNo == searchSerialNo) {
                getline(ss, name, ',');
                getline(ss, temp, ',');
                contact = stoi(temp);
                getline(ss, type, ',');
                getline(ss, temp, ',');
                price = stoi(temp);
                getline(ss, temp, ',');
                avaialability = (temp == "1");
                getline(ss, temp, ',');
                rating = stoi(temp);
                break;
            }
        }

        file.close();
        
    }


    
    void display() {
        cout << "\nServicses Details:\n";
        cout << "Name: " << name << endl;
        cout << "Contact: " << contact << endl;
        cout << "Type: " << type << endl;
        cout << "Price: " << price << endl;
        cout << "Availability: " << (avaialability ? "Yes" : "No") << endl;
        cout << "Rating: " << rating << endl;
    }



};

int Services::serialNo = 0;

class Venue{
    //association with event class
    public:
    string name;
    string location;
    int contact;
    int capacity;
    int price;
    bool availability;

    //constructor for custom venue
    Venue(string name, string location, int contact, int capacity, int price, bool availability) {
        this->name = name;
        this->location = location;
        this->contact = contact;
        this->capacity = capacity;
        this->price = price;
        this->availability = availability;
    }

    //constructor for reading from file
    Venue(int searchSerialNo) {
        ifstream file("venue.csv");
        if (!file.is_open()) {
            cerr << "Error: Could not open venue.csv" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string temp;
            int currentSerialNo;
            getline(ss, temp, ',');
            currentSerialNo = stoi(temp);

            if (currentSerialNo == searchSerialNo) {
                getline(ss, name, ',');
                getline(ss, location, ',');
                getline(ss, temp, ',');
                contact = stoi(temp);
                getline(ss, temp, ',');
                capacity = stoi(temp);
                getline(ss, temp, ',');
                price = stoi(temp);
                getline(ss, temp, ',');
                availability = (temp == "1");
                break;
            }
        }

        file.close();
        
    }
};