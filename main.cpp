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
        static int serialNo;        // Static variable to keep track of event serial number
    
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
            serialNo++; // Increment event serial number

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
int Event::serialNo = 0;

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
// void chooseVenueAndServices(Event &event);
void updateAttendeeList();
void updateEventDetails();
void displayEventDetails();
void updateEventDetails();

void login() {
    cout<<"Login\n";
    string username, password;
    int attempts = 0;

    while (attempts < 3) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (username == "admin" && password == "admin") {
            cout << "Login successful!" << endl;

            //press ENTER key to continue
            cout << "Press ENTER key to continue...\n";
            cin.ignore();
            cin.get();

            // Call the main menu function
            welcome();
            return;
        } else {
            attempts++;
            cout << "Invalid credentials. Attempts remaining: " << (3 - attempts) << endl;
        }
    }

    cout << "Too many failed attempts."<< endl;
    cout << "Exiting the program."<<endl;
    exit(0);
}



// Welcome function
void welcome(){
    cout << "Welcome to the Event Planner and Budget Tracker System!\n";
    cout << "Project By:\n";
    cout << "1. Sarthak Sabharwal\t\t\t\t2401020234\n";
    cout << "1. Sarthak Sabharwal\t\t\t\t2401020234\n";
    cout << "1. Sarthak Sabharwal\t\t\t\t2401020234\n";
    cout << "1. Sarthak Sabharwal\t\t\t\t2401020234\n";

    //press ENTER key to continue
    cout << "Press ENTER key to continue...\n";
    cin.sync();
    cin.get();
    main_menu();

}

// Main menu function
void main_menu() {
    cout << "Main Menu:\n";
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
    cout << "Option Selected: Adding New Event\n";
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
    cin.ignore(); // Fix newline buffer
    cout << "Host Name: ";
    cin >> hostname;
    cin.ignore(); // Fix newline buffer
    cout << "Host Contact: ";
    cin >> hostcontact;
    cin.ignore(); // Fix newline buffer
    cout << "Location: ";
    cin >> location;
    cin.ignore(); // Fix newline buffer
    cout << "Date (YYYY-MM-DD): ";
    cin >> date;
    cin.ignore(); // Fix newline buffer
    cout << "Time (HH:MM): ";
    cin >> time;
    cin.ignore(); // Fix newline buffer
    cout << "Type of Event: ";
    cin >> type;
    cin.ignore(); // Fix newline buffer

   
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
    main_menu();
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
    cout << "Option Selected: Existing Event\n";
    cout << "1. Display Event Booking\n";
    cout << "2. Update Existing Booking\n";
    cout << "3. Return to Main Menu\n";
    cout << "Please select an option: ";
    int choice;
    cin >> choice;

    switch(choice) {
        case 1:
            displayEventDetails();
            break;
        case 2:
            cout << "Updating Existing Booking:\n";
            // Code to update existing booking
            updateExistingEvent();
            break;
        case 3:
            main_menu();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            existingEvent();
    }
}

// Display event booking details
void displayEventDetails(){
    cout << "Displaying Event Booking:\n";
        // Code to display event booking
        ifstream file("event.csv");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "Error: Could not open event.csv" << endl;
        }
        cout<< "Enter Event Serial No to view details: ";
        int serialNo;
        cin >> serialNo;
        //search for event in event.csv
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
                } catch (const invalid_argument& e) {
                    cerr << "Error: Invalid serial number format in the file." << endl;
                    continue; // Skip this line and move to the next
                }
        
                if (currentSerialNo == serialNo) {
                    cout << "Event Details:\n" << line << endl;
        
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
                        string attendeeLine;
                        cout << "Attendee List:\n";
                        while (getline(attendeeFile, attendeeLine)) {
                            cout << attendeeLine << endl;
                        }
                        attendeeFile.close();
                    }
                 } else {
                    cout << "Error: Could not open attendee file." << endl;
                }
                break;
                }
            }
            eventFile.close();
        } else {
            cout << "Error: Could not open event.csv" << endl;
        }
        cout << "Press ENTER key to continue...\n";
        cin.ignore();
        cin.get();
        main_menu();
    }

// Update existing booking    
void updateExistingEvent() {
    cout << "Updating Existing Event:\n";
    // Code to update existing booking
    cout << "1. Update Event Details\n";
    cout << "2. Update Venue\n";
    cout << "3. Update Services\n";
    cout << "4. Update Attendee List\n";
    cout << "5. Return to Main Menu\n";
    cout << "Event successfully updated!\n";
    cout << "Press ENTER key to continue...\n";
    cout << "Please select an option: ";
    int choice;
    cin >> choice;

    switch(choice) {
        case 1:
            cout << "Updating Event Details:\n";
            updateEventDetails();
            break;
        case 2:
            cout << "Updating Venue:\n";
            // Code to update venue
            break;
        case 3:
            cout << "Updating Services:\n";
            // Code to update services
            break;
        case 4:
            cout << "Updating Attendee List:\n";
            updateAttendeeList();
            break;
        case 5:
            main_menu();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            updateExistingEvent();
    }
    cout << "Press ENTER key to continue...\n";
    cin.ignore();
    cin.get();
    existingEvent();
}

// Update event details
void updateEventDetails() {
    cout<< "Option selected: Update Event Details\n";
    // displayEventDetails();
    cout << "Enter Event Serial No to update: ";
    int serialNo;
    cin >> serialNo;
    
    cout << "Do you want to update the event name? (1 for Yes, 0 for No): ";
    int choice;
    cin >> choice;
    string line;
    ifstream file("event.csv");
    if (file.is_open()) {
        stringstream ss;
        while (getline(file, line)) {
            ss << line << endl;
        }
        file.close();
    } else {
        cout << "Error: Could not open event.csv" << endl;
    }
    string updatedLine;
}

void updateAttendeeList(){
    cout<< "Option selected: Update Attendee List\n";
}

// Main function
int main() {
    login();
    return 0;
}

