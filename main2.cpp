#include <iostream>     
#include <vector>   
#include <string>
#include <fstream>   // file handling write and read
#include <sstream>  // string
#include <iomanip>  // set width
#include <cctype>  // for isdigit
#include <cstdlib>  // for exit
#include <limits>  // for numeric limits
#include <regex>  // for regex
#include <algorithm>  // for all_of

using namespace std;

// colour codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
//#define BLUE \033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"



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
    string contact;
    string type;
    int price;
    bool avaialability;
    int rating;
    static int serialNo;


    // Default constructor
    Services() : name(""), contact(""), type(""), price(0), avaialability(false), rating(0) {
        serialNo++;
    }

    // Constructor for custom services
    Services(string name, string contact, string type, int price, bool avaialability, int rating) {
        serialNo ++;
        this->name = name;
        this->contact = contact;
        this->type = type;
        this->price = price;
        this->avaialability = avaialability;
        this->rating = rating;
    }

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
    vector<Services> services;

    Budget(int venueCost, int serviceCost) {
        this->venueCost = venueCost;
        this->serviceCost = serviceCost;
        this->totalCost = venueCost + serviceCost + 0.1 * (venueCost + serviceCost); // 10% extra for commission
        if (totalCost > 1000000) {
            cout << "5'%' discount" << endl;
            totalCost -= 0.05 * totalCost; // 5% discount
            cout << "Total Cost after discount: " << totalCost << endl;
        }// Assuming a maximum of 10 services for simplicity
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
        
            cout << YELLOW << "Enter Attendee Name: " << RESET;
            cin >> attendee.name;
        
            cout << YELLOW << "Enter Attendee Contact: " << RESET;
            cin >> attendee.contact;
        
            cout << YELLOW << "RSVP (1 for Yes, 0 for No): " << RESET;
            cin >> attendee.rsvp;
        
            cout << YELLOW << "Has Guest (1 for Yes, 0 for No): " << RESET;
            cin >> attendee.hasGuest;
        
            if (attendee.hasGuest) {
                cout << YELLOW << "Enter Guest Name: " << RESET;
                cin >> attendee.guestName;
        
                cout << YELLOW << "Needs Security for Guest (1 for Yes, 0 for No): " << RESET;
                cin >> attendee.needsSecurity;
            }
        
            if (attendeeCount < maxAttendees) {
                attendees[attendeeCount++] = attendee;
                cout << GREEN << "Attendee added successfully!" << RESET << endl;
            } else {
                cout << RED << "Cannot add more attendees. Maximum capacity reached." << RESET << endl;
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
    cout << CYAN << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\tLOGIN TO THE SYSTEM\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n" << RESET;

    string username, password;
    int attempts = 0;

    while (attempts < 3) {
        cout << YELLOW << "=========================================================================================================\n";
        cout << "| Enter username: " << RESET;
        cin >> username;
        cout << YELLOW << "| Enter password: " << RESET;
        cin >> password;
        cout << YELLOW << "=========================================================================================================\n" << RESET;

        if (username == "admin" && password == "admin") {
            cout << GREEN << "=========================================================================================================\n";
            cout << "| Login successful!                                                                                   |\n";
            cout << "=========================================================================================================\n" << RESET;

            // Press ENTER key to continue
            cout << YELLOW << "=========================================================================================================\n";
            cout << "| Press ENTER key to continue...                                                                      |\n";
            cout << "=========================================================================================================\n" << RESET;
            cin.ignore();
            cin.get();

            // Call the welcome function
            welcome();
            return;
        } else {
            attempts++;
            cout << RED << "=========================================================================================================\n";
            cout << "| Invalid credentials. Attempts remaining: " << (3 - attempts) << "                                      |\n";
            cout << "=========================================================================================================\n" << RESET;
        }
    }

    cout << RED << "=========================================================================================================\n";
    cout << "| Too many failed attempts. Exiting the program.                                                      |\n";
    cout << "=========================================================================================================\n" << RESET;
    exit(0);
}


// Welcome function
void welcome() {
    cout << "\n\n";
    cout << CYAN << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\tWELCOME TO THE EVENT PLANNER AND BUDGET TRACKER SYSTEM\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n" << RESET;
    cout << CYAN << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t==========================================================\t\t|\n";
    cout << "|\t\t\t\t|\t   PROJECT BY:\t\t\t\t\t |\t\t|\n";
    cout << "|\t\t\t\t|\t  Batch: G-2         Semester - IInd\t\t |\t\t|\n";
    cout << "|\t\t\t\t|\t  Paridhi Jain             2401200035\t\t |\t\t|\n";
    cout << "|\t\t\t\t|\t  Navya Sachdeva           2401200037\t\t |\t\t|\n";
    cout << "|\t\t\t\t|\t  Leepakshi                2401200046\t\t |\t\t|\n";
    cout << "|\t\t\t\t|\t  Pranjal Srivastava       2401200054\t\t |\t\t|\n";
    cout << "|\t\t\t\t|\t  Gourav Mittal            2401200059\t\t |\t\t|\n";
    cout << "|\t\t\t\t==========================================================\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n" << RESET;
    cout << CYAN << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << YELLOW << "|  Press ENTER key to continue...                                                                       |\n";
    cout << CYAN << "=========================================================================================================\n" << RESET;

    cin.sync();
    cin.get();
    main_menu();
}

// Main menu function
void main_menu() {
    cout << "\n\n";
    cout << CYAN << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\tMAIN MENU\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n" << RESET;
    cout << CYAN << "| Choice | Action                                                                                      |\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "|   1    | New Event                                                                                   |\n";
    cout << "|   2    | Existing Event                                                                              |\n";
    cout << "|   3    | Exit                                                                                        |\n";
    cout << "=========================================================================================================\n" << RESET;

    cout << YELLOW << "Please select an option: " << RESET;
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
            cout << GREEN << "=========================================================================================================\n";
            cout << "| Exiting the program. Goodbye!                                                                        |\n";
            cout << "=========================================================================================================\n" << RESET;
            exit(0);
        default:
            cout << RED << "=========================================================================================================\n";
            cout << "| Invalid choice. Please try again.                                                                    |\n";
            cout << "=========================================================================================================\n" << RESET;
            main_menu();
    }
}

// New customer workflow
void newEvent() {
    cout << "\n\n";
    cout << CYAN << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tADDING NEW EVENT\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n" << RESET;

    // Press ENTER key to continue
    cout << YELLOW << "=========================================================================================================\n";
    cout << "| Press ENTER key to continue...                                                                       |\n";
    cout << "=========================================================================================================\n" << RESET;
    cin.ignore();
    cin.get();

    enterEventDetails();
}

// Enter event details
void enterEventDetails() {
    cout << "\n\n";
    cout << CYAN << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tENTER EVENT DETAILS\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n" << RESET;

    string name, hostname, hostcontact, location, date, time, type;

    // Input Event Name
    cout << YELLOW << "=========================================================================================================\n";
    cout << "| Event Name:                                                                                          |\n";
    cout << "=========================================================================================================\n" << RESET;
    cout << "| ";
    cin >> name;
    cin.ignore();

    // Input Host Name
    cout << YELLOW << "=========================================================================================================\n";
    cout << "| Host Name:                                                                                           |\n";
    cout << "=========================================================================================================\n" << RESET;
    cout << "| ";
    cin >> hostname;
    cin.ignore();

    // Input and Validate Host Contact
    while (true) {
        cout << YELLOW << "=========================================================================================================\n";
        cout << "| Host Contact (10-digit number):                                                                      |\n";
        cout << "=========================================================================================================\n" << RESET;
        cout << "| ";
        cin >> hostcontact;
        cin.ignore();

        if (hostcontact.length() == 10 && all_of(hostcontact.begin(), hostcontact.end(), ::isdigit)) {
            break; // Valid contact number
        } else {
            cout << RED << "Invalid contact number. Please enter a 10-digit number." << RESET << endl;
        }
    }

    // Input Location
    cout << YELLOW << "=========================================================================================================\n";
    cout << "| Location:                                                                                            |\n";
    cout << "=========================================================================================================\n" << RESET;
    cout << "| ";
    cin >> location;
    cin.ignore();

    // Input and Validate Date
    while (true) {
        cout << YELLOW << "=========================================================================================================\n";
        cout << "| Date (YYYY-MM-DD):                                                                                   |\n";
        cout << "=========================================================================================================\n" << RESET;
        cout << "| ";
        cin >> date;
        cin.ignore();

        regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
        if (regex_match(date, datePattern)) {
            break; // Valid date format
        } else {
            cout << RED << "Invalid date format. Please enter the date in YYYY-MM-DD format." << RESET << endl;
        }
    }

    // Input and Validate Time
    while (true) {
        cout << YELLOW << "=========================================================================================================\n";
        cout << "| Time (HH:MM):                                                                                        |\n";
        cout << "=========================================================================================================\n" << RESET;
        cout << "| ";
        cin >> time;
        cin.ignore();

        regex timePattern(R"(^\d{2}:\d{2}$)");
        if (regex_match(time, timePattern)) {
            break; // Valid time format
        } else {
            cout << RED << "Invalid time format. Please enter the time in HH:MM format." << RESET << endl;
        }
    }

    // Input Type of Event
    cout << YELLOW << "=========================================================================================================\n";
    cout << "| Type of Event:                                                                                       |\n";
    cout << "=========================================================================================================\n" << RESET;
    cout << "| ";
    cin >> type;
    cin.ignore();

    cout << "\n\n";
    cout << CYAN << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tENTER BUDGET DETAILS\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n" << RESET;

    int venueCost, serviceCost;

    // Input Venue Cost
    cout << YELLOW << "=========================================================================================================\n";
    cout << "| Venue Cost:                                                                                          |\n";
    cout << "=========================================================================================================\n" << RESET;
    cout << "| ";
    cin >> venueCost;

    // Input Service Cost
    cout << YELLOW << "=========================================================================================================\n";
    cout << "| Service Cost:                                                                                        |\n";
    cout << "=========================================================================================================\n" << RESET;
    cout << "| ";
    cin >> serviceCost;

    // Create Event Object
    Event event(name, hostname, hostcontact, location, date, time, type, 100, venueCost, serviceCost);
    cout << GREEN << "=========================================================================================================\n";
    cout << "| Event & Budget details saved successfully!                                                          |\n";
    cout << "=========================================================================================================\n" << RESET;

    // Create Attendee File
    string filename = name.substr(0, 2) + hostname.substr(0, 2) + "_attendee.csv";
    ofstream attendeeFile(filename);
    if (attendeeFile.is_open()) {
        attendeeFile << "SerialNo,Name,Contact,RSVP,HasGuest,GuestName,NeedsSecurity\n";
        attendeeFile.close();
        cout << GREEN << "=========================================================================================================\n";
        cout << "| Attendee file created: " << filename << "                                                          |\n";
        cout << "=========================================================================================================\n" << RESET;
    } else {
        cout << RED << "=========================================================================================================\n";
        cout << "| Error: Could not create attendee file.                                                              |\n";
        cout << "=========================================================================================================\n" << RESET;
    }

    // Press ENTER key to continue
    cout << YELLOW << "=========================================================================================================\n";
    cout << "| Press ENTER key to continue...                                                                       |\n";
    cout << "=========================================================================================================\n" << RESET;
    cin.ignore();
    cin.get();

    // Choose Venue and Services
    addAttendeeList(event, filename);
    chooseVenueAndServices(event);
}

void addAttendeeList(Event &event, string filename) {
    cout << "\n\n";
    cout << CYAN << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tADD ATTENDEE LIST\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n" << RESET;

    cout << YELLOW << "=========================================================================================================\n";
    cout << "| How many attendees do you want to add?                                                              |\n";
    cout << "=========================================================================================================\n" << RESET;
    cout << "| ";
    int numAttendees;
    cin >> numAttendees;

    for (int i = 0; i < numAttendees; i++) {
        if (event.attendeeCount >= event.maxAttendees) {
            cout << RED << "=========================================================================================================\n";
            cout << "| Cannot add more attendees. Maximum capacity reached.                                                |\n";
            cout << "=========================================================================================================\n" << RESET;
            break;
        }

        cout << CYAN << "=========================================================================================================\n";
        cout << "| Adding Attendee " << (i + 1) << ":                                                                    |\n";
        cout << "=========================================================================================================\n" << RESET;
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

            cout << GREEN << "=========================================================================================================\n";
            cout << "| Attendee details saved to file: " << filename << "                                                  |\n";
            cout << "=========================================================================================================\n" << RESET;
        } else {
            cout << RED << "=========================================================================================================\n";
            cout << "| Error: Could not open attendee file for writing.                                                    |\n";
            cout << "=========================================================================================================\n" << RESET;
        }
    }

    cout << GREEN << "=========================================================================================================\n";
    cout << "| Attendee list updated successfully!                                                                 |\n";
    cout << "=========================================================================================================\n" << RESET;

    // Press ENTER key to continue
    cout << YELLOW << "=========================================================================================================\n";
    cout << "| Press ENTER key to continue...                                                                      |\n";
    cout << "=========================================================================================================\n" << RESET;
    cin.ignore();
    cin.get();    
}


void chooseVenueAndServices(Event &event) {
    ifstream venueFile("venues.csv");
    if (!venueFile.is_open()) {
        cerr << RED << "Error: Could not open venues.csv" << RESET << endl;
        return;
    }

    vector<Venue*> availableVenues;
    string line;

    cout << CYAN << "\n=========================================================================================================\n";
    cout << "| Serial No | Venue Name         | Location           | Price     | Rating |\n";
    cout << "---------------------------------------------------------------------------------------------------------\n" << RESET;

    getline(venueFile, line); // Skip header

    while (getline(venueFile, line)) {
        stringstream ss(line);
        string serialStr, name, location, priceStr, unavailableDates, ratingStr;

        try {
            getline(ss, serialStr, ',');
            getline(ss, name, ',');
            getline(ss, location, ',');
            getline(ss, priceStr, ',');
            getline(ss, unavailableDates, ',');
            getline(ss, ratingStr, ',');

            int price = stoi(priceStr);

            if (price <= event.budget->venueCost && unavailableDates.find(event.date) == string::npos) {
                Venue* v = new Venue(name, location, 0, 0, price, true);
                v->rating = ratingStr;
                availableVenues.push_back(v);

                cout << "| " << setw(9) << left << serialStr
                     << "| " << setw(18) << left << name
                     << "| " << setw(16) << left << location
                     << "| Rs." << setw(8) << left << price
                     << "| " << setw(6) << left << ratingStr << "|\n";
            }
        } catch (const exception& e) {
            cerr << RED << "Warning: Error processing venue line: " << line << " - " << e.what() << RESET << endl;
            continue;
        }
    }

    venueFile.close();

    if (availableVenues.empty()) {
        cout << RED << "No available venues found." << RESET << endl;
        return;
    }

    cout << CYAN << "=========================================================================================================\n" << RESET;

    int venueChoice = 0;
    while (true) {
        cout << YELLOW << "\nEnter the serial number of the venue to choose: " << RESET;
        string input;
        cin >> input;

        try {
            venueChoice = stoi(input);
            if (venueChoice >= 1 && venueChoice <= static_cast<int>(availableVenues.size())) {
                break;
            }
            cout << RED << "Invalid choice. Please enter a number between 1 and " << availableVenues.size() << "." << RESET << endl;
        } catch (...) {
            cout << RED << "Invalid input. Please enter a number." << RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    Venue* selectedVenue = availableVenues[venueChoice - 1];

    // Deduct venue price and transfer remaining to service budget
    event.budget->venueCost -= selectedVenue->price;
    event.budget->serviceCost += event.budget->venueCost;
    event.venue = selectedVenue;

    string filename = "v_and_s_" + string(1, event.hostname[0]) + "_" + event.date + ".csv";
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << RED << "Error: Could not create output file" << RESET << endl;
        return;
    }

    outFile << "Selected Venue:\n";
    outFile << selectedVenue->name << "," << selectedVenue->location << "," << selectedVenue->price << "," << selectedVenue->rating << "\n\n";
    outFile << "Selected Services:\n";

    // Read services from CSV into Services objects
    ifstream serviceFile("services.csv");
    if (!serviceFile.is_open()) {
        cerr << RED << "Error: Could not open services.csv" << RESET << endl;
        outFile.close();
        return;
    }

    vector<Services> availableServices;
    getline(serviceFile, line); // Skip header

    while (getline(serviceFile, line)) {
        stringstream ss(line);
        string serialStr, name, contactStr, type, priceStr, availableStr, ratingStr;

        try {
            getline(ss, serialStr, ',');
            getline(ss, name, ',');
            getline(ss, contactStr, ',');
            getline(ss, type, ',');
            getline(ss, priceStr, ',');
            getline(ss, availableStr, ',');
            getline(ss, ratingStr, ',');

            if (availableStr == "True" || availableStr == "true") {
                int price = stoi(priceStr);
                int rating = stoi(ratingStr);
                Services s(name, contactStr, type, price, true, rating);
                availableServices.push_back(s);
            }
        } catch (const exception& e) {
            cerr << RED << "Warning: Error processing service line: " << line << " - " << e.what() << RESET << endl;
            continue;
        }
    }

    serviceFile.close();

    // Service selection loop
    int serviceBudget = event.budget->serviceCost;

    while (true) {
        cout << CYAN << "\n=========================================================================================================\n";
        cout << "| Serial No | Service Name       | Type             | Price     | Rating |\n";
        cout << "---------------------------------------------------------------------------------------------------------\n" << RESET;

        if (availableServices.empty()) {
            cout << RED << "No more services available." << RESET << endl;
            break;
        }

        for (size_t i = 0; i < availableServices.size(); i++) {
            const auto& s = availableServices[i];
            cout << "| " << setw(9) << left << i + 1
                 << "| " << setw(18) << left << s.name
                 << "| " << setw(16) << left << s.type
                 << "| Rs." << setw(8) << left << s.price
                 << "| " << setw(6) << left << s.rating << "|\n";
        }

        cout << CYAN << "=========================================================================================================\n" << RESET;

        cout << YELLOW << "Enter service number to add (or any non-number to stop): " << RESET;
        string input;
        cin >> input;
        if (!isdigit(input[0])) break;

        try {
            int choice = stoi(input);
            if (choice < 1 || choice > static_cast<int>(availableServices.size())) {
                cout << RED << "Invalid service choice." << RESET << endl;
                continue;
            }

            Services selected = availableServices[choice - 1];

            if (selected.price <= serviceBudget) {
                serviceBudget -= selected.price;

                event.budget->services.push_back(selected);  // Store selected service
                outFile << selected.name << "," << selected.contact << "," << selected.type << "," << selected.price << "," << selected.rating << "\n";

                availableServices.erase(availableServices.begin() + choice - 1);
            } else {
                cout << RED << "Not enough budget for this service." << RESET << endl;
            }

            if (serviceBudget <= 0) {
                cout << RED << "Service budget exhausted." << RESET << endl;
                break;
            }

        } catch (...) {
            cout << RED << "Invalid input." << RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    outFile.close();
    cout << GREEN << "\nVenue and selected services saved to: " << filename << RESET << endl;

    // Press ENTER to continue
    cout << YELLOW << "=========================================================================================================\n";
    cout << "| Press ENTER key to continue...                                                                       |\n";
    cout << "=========================================================================================================\n" << RESET;
    cin.ignore();
    cin.get();
    cout << GREEN << "=========================================================================================================\n";
    cout << "| Event and budget details saved successfully!                                                        |\n";
    cout << "=========================================================================================================\n" << RESET;

    main_menu();
}

// Existing customer workflow
void existingEvent() {
    cout << "\n\n";
    cout << CYAN << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tEXISTING EVENT MENU\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n" << RESET;
    cout << CYAN << "| Choice | Action                                                                                      |\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "|   1    | Display Event Booking                                                                       |\n";
    cout << "|   2    | Update Existing Event                                                                       |\n";
    cout << "|   3    | Return to Main Menu                                                                         |\n";
    cout << "=========================================================================================================\n" << RESET;

    cout << YELLOW << "Please select an option: " << RESET;
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
            cout << RED << "=========================================================================================================\n";
            cout << "| Invalid choice. Please try again.                                                                    |\n";
            cout << "=========================================================================================================\n" << RESET;
            existingEvent();
    }
}

// Display event booking details
void displayEventDetails() {
    cout << "\n\n";
    cout << CYAN << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tDISPLAY EVENT DETAILS\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n" << RESET;

    // Display all event bookings
    cout << CYAN << "=========================================================================================================\n";
    cout << "| Serial No | Event Name       | Host Name       | Host Contact | Location       | Date       | Time   |\n";
    cout << "---------------------------------------------------------------------------------------------------------\n" << RESET;

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
    }
    // } else {
    //     cout << RED << "=========================================================================================================\n";
    //     cout << "| Error: Could not open event.csv                                                                      |\n";
    //     cout << "=========================================================================================================\n" << RESET;
    //     return;
    // }

    cout << CYAN << "=========================================================================================================\n";
    cout << "| Enter Event Serial No to view details:                                                              |\n";
    cout << "=========================================================================================================\n" << RESET;
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
                cerr << RED << "Error: Invalid serial number format in the file." << RESET << endl;
                continue; // Skip this line and move to the next
            }

            if (currentSerialNo == serialNo) {
                cout << GREEN << "=========================================================================================================\n";
                cout << "| Event Details:                                                                                       |\n";
                cout << "=========================================================================================================\n" << RESET;
                cout << CYAN << "| Serial No | Event Name       | Host Name       | Host Contact | Location       | Date       | Time   |\n";
                cout << "---------------------------------------------------------------------------------------------------------\n" << RESET;
                
                // Example data parsing and display
                stringstream ss(line);
                string serialNo, eventName, hostName, hostContact, location, date, time;
                
                // Extract the required fields
                getline(ss, serialNo, ',');
                getline(ss, eventName, ',');
                getline(ss, hostName, ',');
                getline(ss, hostContact, ',');
                getline(ss, location, ',');
                getline(ss, date, ',');
                getline(ss, time, ',');
                
                // Display the extracted fields in a tabular format
                cout << "| " << setw(9) << left << serialNo
                     << "| " << setw(16) << left << eventName
                     << "| " << setw(15) << left << hostName
                     << "| " << setw(12) << left << hostContact
                     << "| " << setw(14) << left << location
                     << "| " << setw(10) << left << date
                     << "| " << setw(7) << left << time << "|\n";
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
                        cout << CYAN << "=========================================================================================================\n";
                        cout << "| Attendee List:                                                                                       |\n";
                        cout << "=========================================================================================================\n" << RESET;
                        cout << CYAN << "| Serial No | Name            | Contact       | RSVP | Has Guest | Guest Name      | Needs Security |\n";
                        cout << "---------------------------------------------------------------------------------------------------------\n" << RESET;

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
                        cout << CYAN << "=========================================================================================================\n" << RESET;
                        attendeeFile.close();
                    } else {
                        cout << RED << "=========================================================================================================\n";
                        cout << "| Error: Could not open attendee file.                                                                |\n";
                        cout << "=========================================================================================================\n" << RESET;
                    }
                }
                break;
            }
        }
        eventFile.close();
    } else {
        cout << RED << "=========================================================================================================\n";
        cout << "| Error: Could not open event.csv                                                                      |\n";
        cout << "=========================================================================================================\n" << RESET;
    }

    // Press ENTER key to continue
    cout << YELLOW << "=========================================================================================================\n";
    cout << "| Press ENTER key to continue...                                                                       |\n";
    cout << "=========================================================================================================\n" << RESET;
    cin.ignore();
    cin.get();
    main_menu();
}



// Function to display event booking details
void updateEventDetails() {
    cout << "\n\n";
    cout << CYAN << "=========================================================================================================\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\tUPDATE EVENT DETAILS\t\t\t\t\t|\n";
    cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
    cout << "=========================================================================================================\n" << RESET;

    // Display current events
    ifstream file("event.csv");
    if (!file.is_open()) {
        cout << RED << "=========================================================================================================\n";
        cout << "| Error: Could not open event.csv                                                                      |\n";
        cout << "=========================================================================================================\n" << RESET;
        return;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    // Display events
    cout << CYAN << "=========================================================================================================\n";
    cout << "| Serial No | Event Name       | Host Name       | Host Contact | Location       | Date       | Time   |\n";
    cout << "---------------------------------------------------------------------------------------------------------\n" << RESET;
    for (size_t i = 1; i < lines.size(); ++i) { // Skip header
        stringstream ss(lines[i]);
        string serialNo, eventName, hostName, hostContact, location, date, time, type;
        getline(ss, serialNo, ',');
        getline(ss, eventName, ',');
        getline(ss, hostName, ',');
        getline(ss, hostContact, ',');
        getline(ss, location, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        getline(ss, type, ',');
        cout << "| " << setw(9) << left << serialNo
             << "| " << setw(16) << left << eventName
             << "| " << setw(15) << left << hostName
             << "| " << setw(12) << left << hostContact
             << "| " << setw(14) << left << location
             << "| " << setw(10) << left << date
             << "| " << setw(7) << left << time << "|\n";
    }
    cout << CYAN << "=========================================================================================================\n" << RESET;

    // Get the serial number of the event to update
    cout << YELLOW << "| Enter Event Serial No to update: " << RESET;
    int serialNo;
    cin >> serialNo;

    // Find the event in the file
    bool found = false;
    for (size_t i = 1; i < lines.size(); ++i) { // Skip header
        stringstream ss(lines[i]);
        string temp;
        getline(ss, temp, ',');
        if (stoi(temp) == serialNo) {
            found = true;

            // Update fields
            string updatedName, updatedHostName, updatedHostContact, updatedLocation, updatedDate, updatedTime, updatedType;
            cout << YELLOW << "Enter updated Event Name (leave blank to keep current): " << RESET;
            cin.ignore();
            getline(cin, updatedName);
            cout << YELLOW << "Enter updated Host Name (leave blank to keep current): " << RESET;
            getline(cin, updatedHostName);
            cout << YELLOW << "Enter updated Host Contact (leave blank to keep current): " << RESET;
            getline(cin, updatedHostContact);
            cout << YELLOW << "Enter updated Location (leave blank to keep current): " << RESET;
            getline(cin, updatedLocation);
            cout << YELLOW << "Enter updated Date (YYYY-MM-DD, leave blank to keep current): " << RESET;
            getline(cin, updatedDate);
            cout << YELLOW << "Enter updated Time (HH:MM, leave blank to keep current): " << RESET;
            getline(cin, updatedTime);
            cout << YELLOW << "Enter updated Type (leave blank to keep current): " << RESET;
            getline(cin, updatedType);

            // Update the line
            vector<string> fields;
            fields.push_back(temp); // Preserve the serial number
            string field;
            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }

            if (!updatedName.empty()) fields[1] = updatedName;
            if (!updatedHostName.empty()) fields[2] = updatedHostName;
            if (!updatedHostContact.empty()) fields[3] = updatedHostContact;
            if (!updatedLocation.empty()) fields[4] = updatedLocation;
            if (!updatedDate.empty()) fields[5] = updatedDate;
            if (!updatedTime.empty()) fields[6] = updatedTime;
            if (!updatedType.empty()) fields[7] = updatedType;

            string updatedLine = fields[0];
            for (size_t j = 1; j < fields.size(); ++j) {
                updatedLine += "," + fields[j];
            }
            lines[i] = updatedLine;

            break;
        }
    }

    if (!found) {
        cout << RED << "=========================================================================================================\n";
        cout << "| Error: Event with serial number " << serialNo << " not found.                                        |\n";
        cout << "=========================================================================================================\n" << RESET;
        return;
    }

    // Write updated lines back to the file
    ofstream outFile("event.csv");
    for (const string &l : lines) {
        outFile << l << endl;
    }
    outFile.close();

    cout << GREEN << "=========================================================================================================\n";
    cout << "| Event details updated successfully!                                                                  |\n";
    cout << "=========================================================================================================\n" << RESET;

    // Press ENTER key to continue
    cout << YELLOW << "=========================================================================================================\n";
    cout << "| Press ENTER key to continue...                                                                       |\n";
    cout << "=========================================================================================================\n" << RESET;
    cin.ignore();
    cin.get();
    main_menu();
}


// Main function
int main() {
    login();
    return 0;
}