#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

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

    //constructor for custom venue
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
    
        Attendee* attendees;       // Aggregation with Attendee (array)
        int attendeeCount;         // Number of attendees
        int maxAttendees;          // Maximum capacity for attendees

        Budget* budget;            // Composition with Budget

        Venue* venue;              // Association with Venue
    
        // Constructor
        Event(string name, string hostname, string hostcontact, string location, string date, string time, string type, int maxAttendees, int venueCost, int serviceCost)
            : name(name), hostname(hostname), hostcontact(hostcontact), location(location), date(date), time(time), type(type), maxAttendees(maxAttendees) {
            attendees = new Attendee[maxAttendees]; // Dynamically allocate array for attendees
            attendeeCount = 0;                      // Initialize attendee count
            budget = new Budget(venueCost, serviceCost); // Initialize budget
            venue = nullptr; // Initialize venue pointer

            // Write event details to event.csv
            ofstream file("event.csv", ios::app); // Open file in append mode
            if (file.is_open()) {
                file << name << "," << hostname << "," << hostcontact << "," << location << "," 
                    << date << "," << time << "," << type << endl;
                file.close();
            } else {
                cerr << "Error: Could not open event.csv for writing." << endl;
            }
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
void addAttendeeList(Event &event,string filename);
void addAttendee(Event &event);
void main_menu();
void newEvent();
void existingEvent();
void enterEventDetails();
// void chooseVenueAndServices(Event &event);
void maintainAttendeeList(Event &event);

void login() {
    string username, password;
    int attempts = 0;

    while (attempts < 3) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (username == "admin" && password == "admin") {
            cout << "Login successful!" << endl;
            main_menu();
            return;
        } else {
            attempts++;
            cout << "Invalid credentials. Attempts remaining: " << (3 - attempts) << endl;
        }
    }

    cout << "Too mENTER failed attempts. Exiting program." << endl;
    exit(0);
}



// Function to display the main menu and handle user input
void main_menu(){
    cout << "Welcome to the Event Planner and Budget Tracker System!\n";
    cout << "Project By:\n";
    cout << "1. Sarthak Sabharwal\t\t\t\t2401020234\n";
    cout << "1. Sarthak Sabharwal\t\t\t\t2401020234\n";
    cout << "1. Sarthak Sabharwal\t\t\t\t2401020234\n";
    cout << "1. Sarthak Sabharwal\t\t\t\t2401020234\n";

    //press ENTER key to continue
    cout << "Press ENTER key to continue...\n";
    cin.ignore();
    cin.get();


    cout << "1. New Event\n";
    cout << "2. Existing Event\n";
    cout << "3. Exit\n";

    cout << "Please select an option: ";
    int choice;
    cin >> choice;
    switch(choice) {
        case 1:
            newEvent();
            break;
        case 2:
            existingEvent();
            break;
        case 3:
            cout << "Exiting the program. Goodbye!\n";
            exit(0);
        default:
            cout << "Invalid choice. Please try again.\n";
            main_menu();
    }
}

// New customer workflow
void newEvent() {
    cout << "Adding New Event\n";
    //press ENTER key to continue
    cout << "Press ENTER key to continue...\n";
    cin.ignore();
    cin.get();
    enterEventDetails();
}

// Enter event details
void enterEventDetails() {
    cout << "Enter Event Details:\n";
    string name, hostname, hostcontact, location, date, time, type;
    cout << "Event Name: ";
    cin >> name;
    cout << "Host Name: ";
    cin >> hostname;
    cout << "Host Contact: ";
    cin >> hostcontact;
    cout << "Location: ";
    cin >> location;
    cout << "Date (YYYY-MM-DD): ";
    cin >> date;
    cout << "Time (HH:MM): ";
    cin >> time;
    cout << "Type of Event: ";
    cin >> type;

   
    //Budget details
    cout << "Enter Budget Details:\n";
    int venueCost, serviceCost;
    cout << "Venue Cost: ";
    cin >> venueCost;
    cout << "Service Cost: ";
    cin >> serviceCost;

   Event event(name, hostname, hostcontact, location, date, time, type, 100, venueCost, serviceCost); 
   cout << "Event & Budget details saved successfully!\n";

       // Create attendee file
    string filename = name.substr(0, 2) + hostname.substr(0, 2) + "_attendee.csv";
    ofstream attendeeFile(filename);
    if (attendeeFile.is_open()) {
        attendeeFile << "SerialNo,Name,Contact,RSVP,HasGuest,GuestName,NeedsSecurity\n";
        attendeeFile.close();
        cout << "Attendee file created: " << filename << endl;
    } else {
        cout << "Error: Could not create attendee file." << endl;
    }

   //press ENTER key to continue
    cout << "Press ENTER key to continue...\n";
    cin.ignore();
    cin.get();

    // Choose venue and services
    // chooseVenueAndServices(event);
    addAttendeeList(event,filename);
}

void addAttendeeList(Event &event, string filename) {
    cout << "How many attendees do you want to add? ";
    int numAttendees;
    cin >> numAttendees;

    for (int i = 0; i < numAttendees; i++) {
        if (event.attendeeCount >= event.maxAttendees) {
            cout << "Cannot add more attendees. Maximum capacity reached." << endl;
            break;
        }

        cout << "Adding Attendee " << (i + 1) << ":\n";
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
            cout << "Attendee details saved to file: " << filename << endl;
        } else {
            cout << "Error: Could not open attendee file for writing." << endl;
        }
    }

    cout << "Attendee list updated successfully!\n";
    cout << "Press ENTER key to continue...\n";
    cin.ignore();
    cin.get();
}

// Choose venue and services
// void chooseVenueAndServices(Event &event) {
//     cout << "Choose from the budget-friendly choices for venue and services.\n";
//     cout << "Or enter custom details if your desired choices are not listed.\n";
//     // Code to choose venue and services
//     maintainAttendeeList(event);
// }


// Existing customer workflow
void existingEvent() {
    cout << "1. Display Event Booking\n";
    cout << "2. Update Existing Booking\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        enterEventDetails();
    } else if (choice == 2) {
        // updateBooking();
    } else {
        cout << "Invalid choice. Returning to main main_menu.\n";
        main_menu();
    }
}
// Maintain attendee list for existing event
void maintainAttendeeList(Event &event) {
    cout << "Maintaining Attendee List:\n";
    cout << "1. Add Attendee\n";
    cout << "2. Remove Attendee\n";
    cout << "3. Display Attendee List\n";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1: {
            cout << "Adding Attendee:\n";
            event.addAttendee(); // Call the addAttendee method of the Event class
            break;
        }
        case 2: {
            cout << "Removing Attendee:\n";
            // Code to remove attendee
            break;
        }
        case 3: {
            cout << "Displaying Attendee List:\n";
            event.attendees->display(); 
            break;
        }
        default:
            cout << "Invalid choice. Returning to main menu.\n";
            main_menu();
    }
    cout << "Event successfully created!\n";
    main_menu();
}


int main() {
    cout << "Welcome to the Event Management System!\n";
    login();
    return 0;
}

