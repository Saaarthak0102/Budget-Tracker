#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>  // for isdigit

using namespace std;

struct VenueInfo {
    int serial;
    string name, address, unavailableDates;
    int price;
    float rating;
};

struct ServiceInfo {
    int serial;
    string name, type;
    long long contact;
    int price;
    bool availability;
    float rating;
};



// class declarations
class Attendee;
class Services;
class Venue;
class Budget;
class Event;

// class definitions

class Attendee {
// aggregation with event class
public:
    static int serialNo;
    string name;
    string contact;
    bool rsvp;
    bool hasGuest;
    string guestName;
    bool needsSecurity;

public:
    Attendee() : name(""), contact(""), rsvp(false), hasGuest(false), guestName(""), needsSecurity(false) {
        serialNo++;
    }

    Attendee(string name, string contact, bool rsvp,bool hasGuest = false, string guestName = "", bool needsSecurity = false) {
        this->name = name;
        this->contact = contact;
        this->rsvp = rsvp;
        this->hasGuest = hasGuest;
        this->guestName = guestName;
        this->needsSecurity = needsSecurity;
        serialNo++;
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
    // composition with budget class
public:
    string name;
    int contact;
    string type;
    int price;
    bool avaialability;
    int rating;
    static int serialNo;


    // Default constructor
    Services() : name(""), contact(0), type(""), price(0), avaialability(false), rating(0) {
        serialNo++;
    }

    // Constructor for custom services
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
        serialNo++;
        
    }


    
    void display() {
        cout << "\nServices Details:\n";
        cout << "Name: " << name << endl;
        cout << "Contact: " << contact << endl;
        cout << "Type: " << type << endl;
        cout << "Price: " << price << endl;
        cout << "Availability: " << (avaialability ? "Yes" : "No") << endl;
        cout << "Rating: " << rating << endl;
    }



};



class Venue{
    //association with budget class
    public:
    static int serialNo;
    string name;
    string location;
    int contact;
    int capacity;
    int price;
    bool availability;
    string rating;
    

    // Default constructor
    Venue() : name(""), location(""), contact(0), capacity(0), price(0), availability(false),rating(0) {
        serialNo++;
    }

    // Constructor for custom venue
    Venue(string name, string location, int contact, int capacity, int price, bool availability) {
        this->name = name;
        this->location = location;
        this->contact = contact;
        this->capacity = capacity;
        this->price = price;
        this->availability = availability;
        serialNo++;
    }

    //constructor for reading from file
    Venue(int searchSerialNo) {
        ifstream file("venues.csv");
        if (!file.is_open()) {
            cerr << "Error: Could not open venues.csv" << endl;
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
        serialNo++;
        
    }

    void display() {
        cout << "\nVenue Details:\n";
        cout << "Name: " << name << endl;
        cout << "Location: " << location << endl;
        cout << "Contact: " << contact << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Price: " << price << endl;
        cout << "Availability: " << (availability ? "Yes" : "No") << endl;
    }
};

class Budget{
    //composition with event class
public:

    int venueCost;
    int serviceCost;
    int totalCost;
    Services* services; 

    Budget(int venueCost, int serviceCost) {
        this->venueCost = venueCost;
        this->serviceCost = serviceCost;
        this->totalCost = venueCost + serviceCost + 0.1 * (venueCost + serviceCost); // 10% extra for commission
        if (totalCost > 1000000) {
            cout << "5'%' discount" << endl;
            totalCost -= 0.05 * totalCost; // 5% discount
            cout << "Total Cost after discount: " << totalCost << endl;
        }
        services = new Services[10]; // Assuming a maximum of 10 services for simplicity
    }
};

class Event {
    public:
        string name;
        string hostname;
        string hostcontact;
        string location;
        string date;
        string time;
        string type;
        int serialNo; // Serial number for the event
        Attendee* attendees;
        int attendeeCount;
        int maxAttendees;
        Budget* budget;
        Venue* venue;
    
        // Constructor
        Event(string name, string hostname, string hostcontact, string location, string date, string time, string type, int maxAttendees, int venueCost, int serviceCost)
            : name(name), hostname(hostname), hostcontact(hostcontact), location(location), date(date), time(time), type(type), maxAttendees(maxAttendees) {
            attendees = new Attendee[maxAttendees];
            attendeeCount = 0;
            budget = new Budget(venueCost, serviceCost);
            venue = nullptr;
    
            // Determine the next serial number from the file
            serialNo = getNextSerialNo();
    
            // Write event details to event.csv
            ofstream file("event.csv", ios::app); // Open file in append mode
            if (file.is_open()) {
                // Check if the file is empty
                file.seekp(0, ios::end);
                if (file.tellp() == 0) {
                    // Write the header if the file is empty
                    file << "SerialNo,EventName,HostName,HostContact,EventLocation,EventDate,EventTime,EventType,EventBudget\n";
                }
    
                // Write the event data
                file << serialNo << "," << name << "," << hostname << "," << hostcontact << "," << location << ","
                     << date << "," << time << "," << type << "," << budget->totalCost << endl;
                file.close();
            } else {
                cout << "Error: Could not open event.csv for writing." << endl;
            }
        }
    
        // Function to get the next serial number from the file
        int getNextSerialNo() {
            ifstream file("event.csv");
            if (!file.is_open()) {
                return 1; // Start with 1 if the file does not exist
            }
    
            string line;
            int lastSerialNo = 0;
            while (getline(file, line)) {
                stringstream ss(line);
                string temp;
                getline(ss, temp, ','); // Read the serial number
                try {
                    lastSerialNo = stoi(temp); // Update the last serial number
                } catch (const invalid_argument& e) {
                    continue; // Skip invalid lines
                }
            }
            file.close();
            return lastSerialNo + 1; // Increment the last serial number
        }

        // Add an attendee to the event
        void addAttendee() {

            Attendee attendee;
            cout << "Enter Attendee Name: ";
            cin >> attendee.name;
            cout << "Enter Attendee Contact: ";
            cin >> attendee.contact;
            cout << "RSVP (1 for Yes, 0 for No): ";
            cin >> attendee.rsvp;
            cout << "Has Guest (1 for Yes, 0 for No): ";
            cin >> attendee.hasGuest;
            if (attendee.hasGuest) {
                cout << "Enter Guest Name: ";
                cin >> attendee.guestName;
                cout << "Needs Security for Guest (1 for Yes, 0 for No): ";
                cin >> attendee.needsSecurity;
            }

            cout << "Attendee added successfully!" << endl;

            if (attendeeCount < maxAttendees) {
                attendees[attendeeCount++] = attendee;
            } else {
                cout << "Cannot add more attendees. Maximum capacity reached." << endl;
            }
        }

    
        // Display event details
        void display() {
            cout << "\nEvent Details:\n";
            cout << "Name: " << name << endl;
            cout << "Host Name: " << hostname << endl;
            cout << "Host Contact: " << hostcontact << endl;
            cout << "Location: " << location << endl;
            cout << "Date: " << date << endl;
            cout << "Time: " << time << endl;
            cout << "Type: " << type << endl;
    
            if (venue) {
                cout << "\nVenue Details:\n";
                venue->display();
            }
    
            if (budget) {
                cout << "\nBudget Details:\n";
                cout << "Venue Cost: " << budget->venueCost << endl;
                cout << "Service Cost: " << budget->serviceCost << endl;
                cout << "Total Cost: " << budget->totalCost << endl;
            }
    
            cout << "\nAttendees:\n";
            for (int i = 0; i < attendeeCount; i++) {
                attendees[i].display();
            }
        }
    
        // Destructor to clean up dynamically allocated memory
        ~Event() {
            if (budget) {
                delete budget;
            }
            delete[] attendees; // Free dynamically allocated array
            if (venue) {
                delete venue;
            }
            
        }
    };

// inializiing static variables
int Attendee::serialNo = 0;
int Services::serialNo = 0;
int Venue::serialNo = 0;

// Function prototypes
void login();
void welcome();
void addAttendeeList(Event &event,string filename);
void addAttendee(Event &event);
void main_menu();
void newEvent();
void existingEvent();
void enterEventDetails();
void updateExistingEvent();
void chooseVenueAndServices(Event &event);
void updateAttendeeList();
void updateEventDetails();
void displayEventDetails();
void updateEventDetails();

void login() {
    cout << "\n\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\tLOGIN TO THE SYSTEM\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n";

    string username, password;
    int attempts = 0;

    while (attempts < 3) {
        cout << "=========================================================================================================\n";
        cout << "| Enter username: ";
        cin >> username;
        cout << "| Enter password: ";
        cin >> password;
        cout << "=========================================================================================================\n";

        if (username == "admin" && password == "admin") {
            cout << "=========================================================================================================\n";
            cout << "| Login successful!                                                                                   |\n";
            cout << "=========================================================================================================\n";

            // Press ENTER key to continue
            cout << "=========================================================================================================\n";
            cout << "| Press ENTER key to continue...                                                                      |\n";
            cout << "=========================================================================================================\n";
            cin.ignore();
            cin.get();

            // Call the welcome function
            welcome();
            return;
        } else {
            attempts++;
            cout << "=========================================================================================================\n";
            cout << "| Invalid credentials. Attempts remaining: " << (3 - attempts) << "                                      |\n";
            cout << "=========================================================================================================\n";
        }
    }

    cout << "=========================================================================================================\n";
    cout << "| Too many failed attempts. Exiting the program.                                                      |\n";
    cout << "=========================================================================================================\n";
    exit(0);
}


// Welcome function
void welcome() {
    cout << "\n\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\tWELCOME TO THE EVENT PLANNER AND BUDGET TRACKER SYSTEM\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t==========================================================\t\t|\n";
    cout << "|\t\t\t\t|\t   PROJECT BY:\t\t\t\t\t |\t\t|\n";
    cout << "|\t\t\t\t|\t  Batch: A-8         Semester - IInd\t\t |\t\t|\n";
    cout << "|\t\t\t\t|\t  Maulshree Sharma        2401020218\t\t |\t\t|\n";
    cout << "|\t\t\t\t|\t  Pratyaksh Tyagi         2401020232\t\t |\t\t|\n";
    cout << "|\t\t\t\t|\t  Keshav Maini            2401020233\t\t |\t\t|\n";
    cout << "|\t\t\t\t|\t  Sarthak Sabharwal       2401020234\t\t |\t\t|\n";
    cout << "|\t\t\t\t==========================================================\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|  Press ENTER key to continue...                                                                       |\n";
    cout << "=========================================================================================================\n";

    cin.sync();
    cin.get();
    main_menu();
}

// Main menu function
void main_menu() {
    cout << "\n\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\tMAIN MENU\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n";
    cout << "| Choice | Action                                                                                      |\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "|   1    | New Event                                                                                   |\n";
    cout << "|   2    | Existing Event                                                                              |\n";
    cout << "|   3    | Exit                                                                                        |\n";
    cout << "=========================================================================================================\n";

    cout << "Please select an option: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            newEvent();
            break;
        case 2:
            existingEvent();
            break;
        case 3:
            cout << "=========================================================================================================\n";
            cout << "| Exiting the program. Goodbye!                                                                        |\n";
            cout << "=========================================================================================================\n";
            exit(0);
        default:
            cout << "=========================================================================================================\n";
            cout << "| Invalid choice. Please try again.                                                                    |\n";
            cout << "=========================================================================================================\n";
            main_menu();
    }
}

// New customer workflow
void newEvent() {
    cout << "\n\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tADDING NEW EVENT\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n";

    // Press ENTER key to continue
    cout << "=========================================================================================================\n";
    cout << "| Press ENTER key to continue...                                                                       |\n";
    cout << "=========================================================================================================\n";
    cin.ignore();
    cin.get();

    enterEventDetails();
}

// Enter event details
void enterEventDetails() {
    cout << "\n\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tENTER EVENT DETAILS\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n";

    string name, hostname, hostcontact, location, date, time, type;

    cout << "=========================================================================================================\n";
    cout << "| Event Name:                                                                                          |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> name;
    cin.ignore();

    cout << "=========================================================================================================\n";
    cout << "| Host Name:                                                                                           |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> hostname;
    cin.ignore();

    cout << "=========================================================================================================\n";
    cout << "| Host Contact:                                                                                        |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> hostcontact;
    cin.ignore();

    cout << "=========================================================================================================\n";
    cout << "| Location:                                                                                            |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> location;
    cin.ignore();

    cout << "=========================================================================================================\n";
    cout << "| Date (YYYY-MM-DD):                                                                                   |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> date;
    cin.ignore();

    cout << "=========================================================================================================\n";
    cout << "| Time (HH:MM):                                                                                        |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> time;
    cin.ignore();

    cout << "=========================================================================================================\n";
    cout << "| Type of Event:                                                                                       |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> type;
    cin.ignore();

    cout << "\n\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tENTER BUDGET DETAILS\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n";

    int venueCost, serviceCost;

    cout << "=========================================================================================================\n";
    cout << "| Venue Cost:                                                                                          |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> venueCost;

    cout << "=========================================================================================================\n";
    cout << "| Service Cost:                                                                                        |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> serviceCost;

    Event event(name, hostname, hostcontact, location, date, time, type, 100, venueCost, serviceCost);
    cout << "=========================================================================================================\n";
    cout << "| Event & Budget details saved successfully!                                                          |\n";
    cout << "=========================================================================================================\n";

    // Create attendee file
    string filename = name.substr(0, 2) + hostname.substr(0, 2) + "_attendee.csv";
    ofstream attendeeFile(filename);
    if (attendeeFile.is_open()) {
        attendeeFile << "SerialNo,Name,Contact,RSVP,HasGuest,GuestName,NeedsSecurity\n";
        attendeeFile.close();
        cout << "=========================================================================================================\n";
        cout << "| Attendee file created: " << filename << "                                                          |\n";
        cout << "=========================================================================================================\n";
    } else {
        cout << "=========================================================================================================\n";
        cout << "| Error: Could not create attendee file.                                                              |\n";
        cout << "=========================================================================================================\n";
    }

    // Press ENTER key to continue
    cout << "=========================================================================================================\n";
    cout << "| Press ENTER key to continue...                                                                       |\n";
    cout << "=========================================================================================================\n";
    cin.ignore();
    cin.get();

    // Choose venue and services
    addAttendeeList(event, filename);
    chooseVenueAndServices(event);
}

void addAttendeeList(Event &event, string filename) {
    cout << "\n\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tADD ATTENDEE LIST\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n";

    cout << "=========================================================================================================\n";
    cout << "| How many attendees do you want to add?                                                              |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    int numAttendees;
    cin >> numAttendees;

    for (int i = 0; i < numAttendees; i++) {
        if (event.attendeeCount >= event.maxAttendees) {
            cout << "=========================================================================================================\n";
            cout << "| Cannot add more attendees. Maximum capacity reached.                                                |\n";
            cout << "=========================================================================================================\n";
            break;
        }

        cout << "=========================================================================================================\n";
        cout << "| Adding Attendee " << (i + 1) << ":                                                                    |\n";
        cout << "=========================================================================================================\n";
        event.addAttendee(); // Call the addAttendee method of the Event class

        // Append attendee details to the file
        ofstream attendeeFile(filename, ios::app); // Open file in append mode
        if (attendeeFile.is_open()) {
            attendeeFile << Attendee::serialNo << "," << event.attendees[event.attendeeCount - 1].name << ","
                         << event.attendees[event.attendeeCount - 1].contact << ","
                         << event.attendees[event.attendeeCount - 1].rsvp << ","
                         << event.attendees[event.attendeeCount - 1].hasGuest << ","
                         << event.attendees[event.attendeeCount - 1].guestName << ","
                         << event.attendees[event.attendeeCount - 1].needsSecurity << endl;
            attendeeFile.close();

            cout << "=========================================================================================================\n";
            cout << "| Attendee details saved to file: " << filename << "                                                  |\n";
            cout << "=========================================================================================================\n";
        } else {
            cout << "=========================================================================================================\n";
            cout << "| Error: Could not open attendee file for writing.                                                    |\n";
            cout << "=========================================================================================================\n";
        }
    }

    cout << "=========================================================================================================\n";
    cout << "| Attendee list updated successfully!                                                                 |\n";
    cout << "=========================================================================================================\n";

    // Press ENTER key to continue
    cout << "=========================================================================================================\n";
    cout << "| Press ENTER key to continue...                                                                      |\n";
    cout << "=========================================================================================================\n";
    cin.ignore();
    cin.get();    
}


void chooseVenueAndServices(Event &event) {
    cout << "\n\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tCHOOSE VENUE AND SERVICES\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n";

    // Display available venues
    cout << "=========================================================================================================\n";
    cout << "| Serial No | Venue Name         | Address           | Price     | Rating |\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";

    ifstream venueFile("venues.csv");
    vector<VenueInfo> venues;
    string line;

    getline(venueFile, line); // Skip header if present
    while (getline(venueFile, line)) {
        stringstream ss(line);
        string temp;
        VenueInfo v;

        getline(ss, temp, ',');
        v.serial = stoi(temp);
        getline(ss, v.name, ',');
        getline(ss, v.address, ',');
        getline(ss, temp, ',');
        v.price = stoi(temp);
        getline(ss, v.unavailableDates, ',');
        getline(ss, temp, ',');
        v.rating = stof(temp);

        if (v.price <= event.budget->venueCost && v.unavailableDates.find(event.date) == string::npos) {
            venues.push_back(v);
            cout << "| " << setw(9) << left << v.serial
                 << "| " << setw(18) << left << v.name
                 << "| " << setw(16) << left << v.address
                 << "| Rs." << setw(8) << left << v.price
                 << "| " << setw(6) << left << v.rating << "|\n";
        }
    }
    venueFile.close();

    cout << "=========================================================================================================\n";
    cout << "| Enter the serial number of the venue you want to choose:                                             |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    int venueChoice;
    cin >> venueChoice;

    VenueInfo selectedVenue;
    bool found = false;
    for (auto &v : venues) {
        if (v.serial == venueChoice) {
            selectedVenue = v;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Invalid venue selection.\n";
        return;
    }

    // Deduct venue cost and assign venue
    event.budget->venueCost -= selectedVenue.price;
    event.budget->serviceCost += event.budget->venueCost; // Transfer leftover

    event.venue = new Venue(selectedVenue.name, selectedVenue.address, 0, 0, selectedVenue.price, true);

    ofstream outFile("v_and_s_" + string(1, event.hostname[0]) + "_" + event.date + ".csv");
    outFile << "Selected Venue:\n" << selectedVenue.name << "," << selectedVenue.address << "," << selectedVenue.price << "," << selectedVenue.rating << "\n\n";
    outFile << "Selected Services:\n";

    // Display available services
    cout << "\n=========================================================================================================\n";
    cout << "| Serial No | Service Name       | Type             | Price     | Rating |\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";

    ifstream serviceFile("services.csv");
    vector<ServiceInfo> services;

    getline(serviceFile, line); // Skip header
    while (getline(serviceFile, line)) {
        stringstream ss(line);
        ServiceInfo s;
        string temp;

        getline(ss, temp, ',');
        s.serial = stoi(temp);
        getline(ss, s.name, ',');
        getline(ss, temp, ',');
        s.contact = stoll(temp);
        getline(ss, s.type, ',');
        getline(ss, temp, ',');
        s.price = stoi(temp);
        getline(ss, temp, ',');
        s.availability = (temp == "True");
        getline(ss, temp, ',');
        s.rating = stof(temp);

        if (s.availability) {
            services.push_back(s);
            cout << "| " << setw(9) << left << s.serial
                 << "| " << setw(18) << left << s.name
                 << "| " << setw(16) << left << s.type
                 << "| Rs." << setw(8) << left << s.price
                 << "| " << setw(6) << left << s.rating << "|\n";
        }
    }
    serviceFile.close();

    cout << "=========================================================================================================\n";

    int serviceBudget = event.budget->serviceCost;
    int i = 0;
    char input[10];

    while (true) {
        cout << "\nBudget Left: Rs." << serviceBudget << "\n";
        cout << "Enter service serial number to choose or any character to stop:\n";

        cin >> input;

        if (!isdigit(input[0]))
            break;

        int choice = stoi(input);
        bool valid = false;

        for (auto &s : services) {
            if (s.serial == choice && s.price <= serviceBudget) {
                event.budget->services[i++] = Services(s.name, s.contact, s.type, s.price, true, s.rating);
                serviceBudget -= s.price;

                outFile << s.name << "," << s.contact << "," << s.type << "," << s.price << "," << s.rating << "\n";
                valid = true;
                break;
            }
        }

        if (!valid) {
            cout << "Invalid choice or service exceeds remaining budget.\n";
        }

        if (serviceBudget <= 0) {
            cout << "Service budget exhausted.\n";
            break;
        }
    }

    outFile.close();
    cout << "\n=========================================================================================================\n";
    cout << "| Venue and Services selection saved successfully!                                                     |\n";
    cout << "=========================================================================================================\n";



// Press ENTER key to continue
    cout << "=========================================================================================================\n";
    cout << "| Press ENTER key to continue...                                                                       |\n";
    cout << "=========================================================================================================\n";
    cin.ignore();
    cin.get();

    main_menu();
}

// Existing customer workflow
void existingEvent() {
    cout << "\n\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tEXISTING EVENT MENU\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n";
    cout << "| Choice | Action                                                                                      |\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "|   1    | Display Event Booking                                                                       |\n";
    cout << "|   2    | Update Existing Event                                                                   |\n";
    cout << "|   3    | Return to Main Menu                                                                         |\n";
    cout << "=========================================================================================================\n";

    cout << "Please select an option: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            displayEventDetails();
            break;
        case 2:
            cout << "\n\n";
            updateEventDetails();
            break;
        case 3:
            main_menu();
            break;
        default:
            cout << "=========================================================================================================\n";
            cout << "| Invalid choice. Please try again.                                                                    |\n";
            cout << "=========================================================================================================\n";
            existingEvent();
    }
}

// Display event booking details
void displayEventDetails() {
    cout << "\n\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tDISPLAY EVENT DETAILS\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n";

    // Display all event bookings
    cout << "=========================================================================================================\n";
    cout << "| Serial No | Event Name       | Host Name       | Host Contact | Location       | Date       | Time   |\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";

    ifstream file("event.csv");
    if (file.is_open()) {
        string line;
        bool isHeader = true; // Skip the header row
        while (getline(file, line)) {
            if (isHeader) {
                isHeader = false;
                continue;
            }

            stringstream ss(line);
            string serialNo, eventName, hostName, hostContact, location, date, time, type, budget;

            getline(ss, serialNo, ',');
            getline(ss, eventName, ',');
            getline(ss, hostName, ',');
            getline(ss, hostContact, ',');
            getline(ss, location, ',');
            getline(ss, date, ',');
            getline(ss, time, ',');
            getline(ss, type, ',');
            getline(ss, budget, ',');

            // Format and display the event details
            cout << "| " << setw(9) << left << serialNo
                 << "| " << setw(16) << left << eventName
                 << "| " << setw(15) << left << hostName
                 << "| " << setw(12) << left << hostContact
                 << "| " << setw(14) << left << location
                 << "| " << setw(10) << left << date
                 << "| " << setw(7) << left << time << "|\n";
        }
        file.close();
    } else {
        cout << "=========================================================================================================\n";
        cout << "| Error: Could not open event.csv                                                                      |\n";
        cout << "=========================================================================================================\n";
        return;
    }

    cout << "=========================================================================================================\n";
    cout << "| Enter Event Serial No to view details:                                                              |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    int serialNo;
    cin >> serialNo;

    // Search for the event in event.csv
    ifstream eventFile("event.csv");
    if (eventFile.is_open()) {
        string line;
        bool isHeader = true; // Flag to skip the header row
        while (getline(eventFile, line)) {
            if (isHeader) {
                isHeader = false; // Skip the first line (header)
                continue;
            }

            stringstream ss(line);
            string temp;
            int currentSerialNo;
            getline(ss, temp, ',');

            // Validate and parse the serial number
            try {
                currentSerialNo = stoi(temp);
            } catch (const invalid_argument &e) {
                cerr << "Error: Invalid serial number format in the file." << endl;
                continue; // Skip this line and move to the next
            }

            if (currentSerialNo == serialNo) {
                cout << "=========================================================================================================\n";
                cout << "| Event Details:                                                                                       |\n";
                cout << "=========================================================================================================\n";
                cout << "| Serial No | Event Name       | Host Name       | Host Contact | Location       | Date       | Time   |\n";
                cout << "---------------------------------------------------------------------------------------------------------\n";
                cout << line << endl; // Display the event details
                cout << "=========================================================================================================\n";
                

                // Extract the first two characters after the first comma and the second comma
                size_t firstComma = line.find(','); // Find the position of the first comma
                size_t secondComma = line.find(',', firstComma + 1); // Find the position of the second comma

                // Check if both commas were found
                if (firstComma != string::npos && secondComma != string::npos) {
                    string part1 = line.substr(firstComma + 1, 2); // Extract 2 characters after the first comma
                    string part2 = line.substr(secondComma + 1, 2); // Extract 2 characters after the second comma
                    string filename = part1 + part2 + "_attendee.csv";

                    // Display attendees from attendee file
                    ifstream attendeeFile(filename);
                    if (attendeeFile.is_open()) {
                        cout << "=========================================================================================================\n";
                        cout << "| Attendee List:                                                                                       |\n";
                        cout << "=========================================================================================================\n";
                        cout << "| Serial No | Name            | Contact       | RSVP | Has Guest | Guest Name      | Needs Security |\n";
                        cout << "---------------------------------------------------------------------------------------------------------\n";

                        string attendeeLine;
                        bool isAttendeeHeader = true;
                        while (getline(attendeeFile, attendeeLine)) {
                            if (isAttendeeHeader) {
                                isAttendeeHeader = false; // Skip the header row
                                continue;
                            }

                            stringstream attendeeSS(attendeeLine);
                            string serialNo, name, contact, rsvp, hasGuest, guestName, needsSecurity;

                            getline(attendeeSS, serialNo, ',');
                            getline(attendeeSS, name, ',');
                            getline(attendeeSS, contact, ',');
                            getline(attendeeSS, rsvp, ',');
                            getline(attendeeSS, hasGuest, ',');
                            getline(attendeeSS, guestName, ',');
                            getline(attendeeSS, needsSecurity, ',');

                            // Format and display the attendee details
                            cout << "| " << setw(9) << left << serialNo
                                 << "| " << setw(16) << left << name
                                 << "| " << setw(13) << left << contact
                                 << "| " << setw(4) << left << rsvp
                                 << "| " << setw(9) << left << hasGuest
                                 << "| " << setw(15) << left << guestName
                                 << "| " << setw(14) << left << needsSecurity << "|\n";
                        }
                        cout << "=========================================================================================================\n";
                        attendeeFile.close();
                    } else {
                        cout << "=========================================================================================================\n";
                        cout << "| Error: Could not open attendee file.                                                                |\n";
                        cout << "=========================================================================================================\n";
                    }
                }
                break;
            }
        }
        eventFile.close();
    } else {
        cout << "=========================================================================================================\n";
        cout << "| Error: Could not open event.csv                                                                      |\n";
        cout << "=========================================================================================================\n";
    }

    // Press ENTER key to continue
    cout << "=========================================================================================================\n";
    cout << "| Press ENTER key to continue...                                                                       |\n";
    cout << "=========================================================================================================\n";
    cin.ignore();
    cin.get();
    main_menu();
}




void updateEventDetails() {
    cout << "\n\n";
    cout << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tUPDATE EVENT DETAILS\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n";

    // Display current events
    cout << "=========================================================================================================\n";
    cout << "| Event Bookings:                                                                                      |\n";
    cout << "=========================================================================================================\n";

    ifstream file("event.csv");
    if (!file.is_open()) {
        cout << "=========================================================================================================\n";
        cout << "| Error: Could not open event.csv                                                                      |\n";
        cout << "=========================================================================================================\n";
        return;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        cout << line << endl;
        lines.push_back(line);
    }
    file.close();

    cout << "=========================================================================================================\n";
    cout << "| Enter Event Serial No to update:                                                                    |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    int serialNo;
    cin >> serialNo;

    string updatedName = "", updatedHostName = "", updatedHostContact = "";
    string updatedLocation = "", updatedDate = "", updatedTime = "", updatedType = "";
    int choice;

    cout << "=========================================================================================================\n";
    cout << "| Do you want to update the event name? (1 for Yes, 0 for No):                                         |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> choice;
    if (choice == 1) {
        cout << "Enter updated event name: ";
        cin.ignore();
        getline(cin, updatedName);
    }

    cout << "=========================================================================================================\n";
    cout << "| Do you want to update the host name? (1 for Yes, 0 for No):                                          |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> choice;
    if (choice == 1) {
        cout << "Enter updated host name: ";
        cin.ignore();
        getline(cin, updatedHostName);
    }

    cout << "=========================================================================================================\n";
    cout << "| Do you want to update the host contact? (1 for Yes, 0 for No):                                       |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> choice;
    if (choice == 1) {
        cout << "Enter updated host contact: ";
        cin.ignore();
        getline(cin, updatedHostContact);
    }

    cout << "=========================================================================================================\n";
    cout << "| Do you want to update the location? (1 for Yes, 0 for No):                                           |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> choice;
    if (choice == 1) {
        cout << "Enter updated location: ";
        cin.ignore();
        getline(cin, updatedLocation);
    }

    cout << "=========================================================================================================\n";
    cout << "| Do you want to update the date? (1 for Yes, 0 for No):                                               |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> choice;
    if (choice == 1) {
        cout << "Enter updated date (YYYY-MM-DD): ";
        cin.ignore();
        getline(cin, updatedDate);
    }

    cout << "=========================================================================================================\n";
    cout << "| Do you want to update the time? (1 for Yes, 0 for No):                                               |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> choice;
    if (choice == 1) {
        cout << "Enter updated time (HH:MM): ";
        cin.ignore();
        getline(cin, updatedTime);
    }

    cout << "=========================================================================================================\n";
    cout << "| Do you want to update the type? (1 for Yes, 0 for No):                                               |\n";
    cout << "=========================================================================================================\n";
    cout << "| ";
    cin >> choice;
    if (choice == 1) {
        cout << "Enter updated type: ";
        cin.ignore();
        getline(cin, updatedType);
    }

    // Update the event in the vector
    bool found = false;
    for (size_t i = 0; i < lines.size(); ++i) {
        stringstream ss(lines[i]);
        string temp;
        getline(ss, temp, ',');
        int currentSerialNo = stoi(temp);

        if (currentSerialNo == serialNo) {
            vector<string> fields;
            fields.push_back(to_string(serialNo)); // updated serial no

            getline(ss, temp, ','); fields.push_back(updatedName.empty() ? temp : updatedName);
            getline(ss, temp, ','); fields.push_back(updatedHostName.empty() ? temp : updatedHostName);
            getline(ss, temp, ','); fields.push_back(updatedHostContact.empty() ? temp : updatedHostContact);
            getline(ss, temp, ','); fields.push_back(updatedLocation.empty() ? temp : updatedLocation);
            getline(ss, temp, ','); fields.push_back(updatedDate.empty() ? temp : updatedDate);
            getline(ss, temp, ','); fields.push_back(updatedTime.empty() ? temp : updatedTime);
            getline(ss, temp, ','); fields.push_back(updatedType.empty() ? temp : updatedType);

            string updatedLine;
            for (size_t j = 0; j < fields.size(); ++j) {
                updatedLine += fields[j];
                if (j < fields.size() - 1) updatedLine += ",";
            }

            lines[i] = updatedLine;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "=========================================================================================================\n";
        cout << "| Error: Event with serial number " << serialNo << " not found.                                        |\n";
        cout << "=========================================================================================================\n";
        return;
    }

    // Write updated lines to file
    ofstream outFile("event.csv");
    for (const string& l : lines) {
        outFile << l << endl;
    }
    outFile.close();

    cout << "=========================================================================================================\n";
    cout << "| Event details updated successfully!                                                                  |\n";
    cout << "=========================================================================================================\n";


    // Press ENTER key to continue
    cout << "=========================================================================================================\n";
    cout << "| Press ENTER key to continue...                                                                       |\n";
    cout << "=========================================================================================================\n";
    cin.ignore();
    cin.get();
    existingEvent();
}


// Main function
int main() {
    login();
    return 0;
}