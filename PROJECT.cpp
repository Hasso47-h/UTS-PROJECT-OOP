// =============================================================================
//          UNIVERSITY TRANSPORT MANAGEMENT SYSTEM
//          C++ OOP Implementation - Production-Ready Console Application
// =============================================================================
//  Module A - Student Module        : Ibad Ullah
//  Module B - Bus & Route Module    : Hassan Khan
//  Module C - Payment & Main Menu   : Izaz Ali Shah
// =============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <limits>
#include <sstream>
#include <ctime>
#include <algorithm>

using namespace std;

// =============================================================================
//  UTILITY HELPERS
// =============================================================================

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getLine(const string& prompt) {
    string val;
    cout << prompt;
    getline(cin, val);
    return val;
}

int getInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            clearInput();
            return val;
        }
        cout << "  [!] Invalid input. Please enter a whole number.\n";
        clearInput();
    }
}

double getDouble(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            clearInput();
            return val;
        }
        cout << "  [!] Invalid input. Please enter a numeric value.\n";
        clearInput();
    }
}

string currentDate() {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&now));
    return string(buf);
}

string generateID(const string& prefix, int n) {
    ostringstream ss;
    ss << prefix << setw(4) << setfill('0') << n;
    return ss.str();
}

void printHeader(const string& title) {
    cout << "\n";
    cout << "  +------------------------------------------------------+\n";
    cout << "  |  " << left << setw(52) << title << "|\n";
    cout << "  +------------------------------------------------------+\n";
}

void printDivider() {
    cout << "  ------------------------------------------------------\n";
}

void printSuccess(const string& msg) {
    cout << "\n  [OK] " << msg << "\n";
}

void printError(const string& msg) {
    cout << "\n  [ERR] " << msg << "\n";
}

void pressEnter() {
    cout << "\n  Press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


// =============================================================================
//  ABSTRACT BASE CLASS - Person
//  Pillar: Abstraction + Encapsulation
// =============================================================================

class Person {
protected:
    string name;
    string id;
    string contactNumber;

public:
    // Constructor
    Person(const string& name, const string& id, const string& contact)
        : name(name), id(id), contactNumber(contact) {}

    virtual ~Person() = default;

    // --- Pure Virtual Function (Abstraction + Polymorphism) ---
    virtual void displayProfile() const = 0;

    // --- Getters ---
    string getName()          const { return name; }
    string getID()            const { return id; }
    string getContactNumber() const { return contactNumber; }

    // --- Setters with basic validation ---
    void setName(const string& n) {
        if (!n.empty()) name = n;
        else cout << "  [!] Name cannot be empty.\n";
    }
    void setContactNumber(const string& c) {
        if (c.length() >= 7) contactNumber = c;
        else cout << "  [!] Contact number too short.\n";
    }
};


// =============================================================================
//  CLASS - Route
//  Module B - Hassan Khan
// =============================================================================

class Route {
private:
    string routeID;
    string pickupPoint;
    string destinationPoint;
    string scheduleTime;

public:
    Route(const string& id, const string& pickup,
          const string& dest,  const string& time)
        : routeID(id), pickupPoint(pickup),
          destinationPoint(dest), scheduleTime(time) {}

    // Getters
    string getRouteID()          const { return routeID; }
    string getPickupPoint()      const { return pickupPoint; }
    string getDestinationPoint() const { return destinationPoint; }
    string getScheduleTime()     const { return scheduleTime; }

    // Setters
    void setPickupPoint(const string& p)      { pickupPoint = p; }
    void setDestinationPoint(const string& d) { destinationPoint = d; }
    void setScheduleTime(const string& t)     { scheduleTime = t; }

    void display() const {
        cout << "  Route ID   : " << routeID          << "\n";
        cout << "  Pickup     : " << pickupPoint       << "\n";
        cout << "  Destination: " << destinationPoint  << "\n";
        cout << "  Schedule   : " << scheduleTime      << "\n";
    }
};


// =============================================================================
//  CLASS - Bus
//  Module B - Hassan Khan
// =============================================================================

class Bus {
private:
    string busNumber;
    int    totalCapacity;
    int    bookedSeats;
    string currentRouteID;   // "" means unassigned

public:
    Bus(const string& number, int capacity)
        : busNumber(number), totalCapacity(capacity),
          bookedSeats(0), currentRouteID("") {}

    // --- Core Methods ---
    bool hasAvailableSeats() const {
        return bookedSeats < totalCapacity;
    }

    bool allocateSeat() {
        if (!hasAvailableSeats()) return false;
        bookedSeats++;
        return true;
    }

    void releaseSeat() {
        if (bookedSeats > 0) bookedSeats--;
    }

    // Getters
    string getBusNumber()    const { return busNumber; }
    int    getTotalCapacity()const { return totalCapacity; }
    int    getBookedSeats()  const { return bookedSeats; }
    int    getAvailableSeats()const{ return totalCapacity - bookedSeats; }
    string getCurrentRouteID()const{ return currentRouteID; }

    // Setters
    void assignRoute(const string& routeID) { currentRouteID = routeID; }
    void unassignRoute()                    { currentRouteID = ""; }

    void display() const {
        cout << "  Bus No.    : " << busNumber    << "\n";
        cout << "  Capacity   : " << totalCapacity << "\n";
        cout << "  Booked     : " << bookedSeats   << "\n";
        cout << "  Available  : " << getAvailableSeats() << "\n";
        cout << "  Route ID   : " << (currentRouteID.empty() ? "Unassigned" : currentRouteID) << "\n";
    }
};


// =============================================================================
//  CLASS - Payment
//  Module C - Izaz Ali Shah
// =============================================================================

class Payment {
private:
    string transactionID;
    string studentID;
    double amountPaid;
    string paymentDate;

public:
    Payment(const string& txID, const string& stdID,
            double amount,       const string& date)
        : transactionID(txID), studentID(stdID),
          amountPaid(amount),  paymentDate(date) {}

    // Getters
    string getTransactionID() const { return transactionID; }
    string getStudentID()     const { return studentID; }
    double getAmountPaid()    const { return amountPaid; }
    string getPaymentDate()   const { return paymentDate; }

    void printReceipt() const {
        cout << "\n";
        cout << "  +---------------------------------------------+\n";
        cout << "  |            PAYMENT RECEIPT                  |\n";
        cout << "  |---------------------------------------------|\n";
        cout << "  |  Transaction ID : " << left << setw(26) << transactionID << "|\n";
        cout << "  |  Student ID     : " << left << setw(26) << studentID     << "|\n";
        cout << "  |  Amount Paid    : PKR " << left << setw(22) << fixed << setprecision(2) << amountPaid << "|\n";
        cout << "  |  Date           : " << left << setw(26) << paymentDate   << "|\n";
        cout << "  +---------------------------------------------+\n";
    }
};


// =============================================================================
//  CLASS - Student  (Derived from Person)
//  Module A - Ibad Ullah
//  Pillar: Inheritance + Encapsulation + Polymorphism
// =============================================================================

class Student : public Person {
private:
    string enrolledRoute;
    int    assignedSeatNumber;
    bool   feePaidStatus;
    double balanceDue;

public:
    Student(const string& name, const string& id,
            const string& contact, double balance = 15000.0)
        : Person(name, id, contact),
          enrolledRoute(""), assignedSeatNumber(0),
          feePaidStatus(false), balanceDue(balance) {}

    // --- Polymorphic Override ---
    void displayProfile() const override {
        printDivider();
        cout << "  [STUDENT PROFILE]\n";
        cout << "  Name        : " << name            << "\n";
        cout << "  ID          : " << id              << "\n";
        cout << "  Contact     : " << contactNumber   << "\n";
        cout << "  Route       : " << (enrolledRoute.empty() ? "Not Assigned" : enrolledRoute) << "\n";
        cout << "  Seat No.    : " << (assignedSeatNumber == 0 ? "Not Booked" : to_string(assignedSeatNumber)) << "\n";
        cout << "  Fee Status  : " << (feePaidStatus ? "PAID" : "UNPAID") << "\n";
        cout << "  Balance Due : PKR " << fixed << setprecision(2) << balanceDue << "\n";
        printDivider();
    }

    // --- Seat Allocation ---
    void allocateSeat(const string& routeID, int seatNo) {
        enrolledRoute      = routeID;
        assignedSeatNumber = seatNo;
    }

    void clearSeat() {
        enrolledRoute      = "";
        assignedSeatNumber = 0;
    }

    // --- Payment Update ---
    void updatePayment(double amount) {
        if (amount <= 0) {
            cout << "  [!] Amount must be positive.\n";
            return;
        }
        balanceDue -= amount;
        if (balanceDue <= 0.0) {
            balanceDue     = 0.0;
            feePaidStatus  = true;
        }
    }

    // Getters
    string getEnrolledRoute()    const { return enrolledRoute; }
    int    getAssignedSeatNumber()const{ return assignedSeatNumber; }
    bool   getFeePaidStatus()    const { return feePaidStatus; }
    double getBalanceDue()       const { return balanceDue; }

    // Setters
    void setBalanceDue(double b)    { if (b >= 0) balanceDue = b; }
    void setFeePaidStatus(bool s)   { feePaidStatus = s; }
};


// =============================================================================
//  CLASS - Driver  (Derived from Person)
//  Module B - Hassan Khan
//  Pillar: Inheritance + Polymorphism
// =============================================================================

class Driver : public Person {
private:
    string employeeID;
    string assignedBusNumber;   // "" = unassigned
    string assignedRouteID;     // "" = unassigned

public:
    Driver(const string& name, const string& id,
           const string& contact, const string& empID)
        : Person(name, id, contact),
          employeeID(empID),
          assignedBusNumber(""), assignedRouteID("") {}

    // --- Polymorphic Override ---
    void displayProfile() const override {
        printDivider();
        cout << "  [DRIVER PROFILE]\n";
        cout << "  Name        : " << name        << "\n";
        cout << "  ID          : " << id          << "\n";
        cout << "  Contact     : " << contactNumber << "\n";
        cout << "  Employee ID : " << employeeID  << "\n";
        cout << "  Bus No.     : " << (assignedBusNumber.empty() ? "Unassigned" : assignedBusNumber) << "\n";
        cout << "  Route ID    : " << (assignedRouteID.empty()   ? "Unassigned" : assignedRouteID)   << "\n";
        printDivider();
    }

    // --- Bind / Unbind Vehicle ---
    void bindToBus(const string& busNumber) {
        assignedBusNumber = busNumber;
    }
    void unbindFromBus() {
        assignedBusNumber = "";
    }

    // --- Bind / Unbind Route ---
    void bindToRoute(const string& routeID) {
        assignedRouteID = routeID;
    }
    void unbindFromRoute() {
        assignedRouteID = "";
    }

    // Getters
    string getEmployeeID()       const { return employeeID; }
    string getAssignedBusNumber()const { return assignedBusNumber; }
    string getAssignedRouteID()  const { return assignedRouteID; }
};


// =============================================================================
//  CLASS - TransportSystem  (Manager / Façade)
//  Compositional aggregation of all entities
// =============================================================================

class TransportSystem {
private:
    // ── Composited Collections ──────────────────────────────────────────────
    vector<Student> students;
    vector<Driver>  drivers;
    vector<Bus>     buses;
    vector<Route>   routes;
    vector<Payment> payments;

    // ── ID Counters ──────────────────────────────────────────────────────────
    int studentCounter  = 1;
    int driverCounter   = 1;
    int txCounter       = 1;

    // ════════════════════════════════════════════════════════════════════════
    //  INTERNAL LOOKUP HELPERS
    // ════════════════════════════════════════════════════════════════════════

    Student* findStudent(const string& id) {
        for (auto& s : students)
            if (s.getID() == id) return &s;
        return nullptr;
    }

    Driver* findDriver(const string& id) {
        for (auto& d : drivers)
            if (d.getID() == id) return &d;
        return nullptr;
    }

    Bus* findBus(const string& busNo) {
        for (auto& b : buses)
            if (b.getBusNumber() == busNo) return &b;
        return nullptr;
    }

    Route* findRoute(const string& routeID) {
        for (auto& r : routes)
            if (r.getRouteID() == routeID) return &r;
        return nullptr;
    }

    // ════════════════════════════════════════════════════════════════════════
    //  MODULE A - STUDENT MODULE   (Ibad Ullah)
    // ════════════════════════════════════════════════════════════════════════

public:
    //  A-1  Register a new student
    void registerStudent() {
        printHeader("MODULE A  >  Register New Student");

        string name    = getLine("  Full Name       : ");
        string contact = getLine("  Contact Number  : ");
        double balance = getDouble("  Transport Fee Due (PKR) : ");

        string newID = generateID("STD", studentCounter++);
        students.emplace_back(name, newID, contact, balance);

        printSuccess("Student registered successfully!");
        cout << "  Assigned ID : " << newID << "\n";
    }

    //  A-2  Book a seat for a student
    void bookSeat() {
        printHeader("MODULE A  >  Book a Seat");

        if (routes.empty() || buses.empty()) {
            printError("No routes or buses available in the system.");
            return;
        }

        string stdID = getLine("  Enter Student ID : ");
        Student* student = findStudent(stdID);
        if (!student) { printError("Student not found."); return; }

        if (!student->getEnrolledRoute().empty()) {
            printError("Student already has a seat booked on Route " + student->getEnrolledRoute());
            return;
        }

        // Show available routes with buses that have free seats
        cout << "\n  ── Available Routes ─────────────────────────────────\n";
        bool anyAvailable = false;
        for (size_t i = 0; i < routes.size(); i++) {
            // Find a bus linked to this route with available seats
            Bus* linkedBus = nullptr;
            for (auto& b : buses) {
                if (b.getCurrentRouteID() == routes[i].getRouteID() && b.hasAvailableSeats()) {
                    linkedBus = &b;
                    break;
                }
            }
            if (linkedBus) {
                anyAvailable = true;
                cout << "  [" << i + 1 << "] ";
                routes[i].display();
                cout << "      Bus: " << linkedBus->getBusNumber()
                     << "  |  Free Seats: " << linkedBus->getAvailableSeats() << "\n\n";
            }
        }

        if (!anyAvailable) {
            printError("No available seats on any route right now.");
            return;
        }

        int choice = getInt("  Select Route Number : ");
        if (choice < 1 || choice > (int)routes.size()) {
            printError("Invalid selection.");
            return;
        }

        Route& selectedRoute = routes[choice - 1];

        // Find bus linked to selected route
        Bus* targetBus = nullptr;
        for (auto& b : buses) {
            if (b.getCurrentRouteID() == selectedRoute.getRouteID() && b.hasAvailableSeats()) {
                targetBus = &b;
                break;
            }
        }

        if (!targetBus) {
            printError("No available bus for the selected route.");
            return;
        }

        int seatNo = targetBus->getBookedSeats() + 1;
        targetBus->allocateSeat();
        student->allocateSeat(selectedRoute.getRouteID(), seatNo);

        printSuccess("Seat booked successfully!");
        cout << "  Route  : " << selectedRoute.getRouteID()
             << "  (" << selectedRoute.getPickupPoint()
             << " -> " << selectedRoute.getDestinationPoint() << ")\n";
        cout << "  Seat No: " << seatNo << "\n";
        cout << "  Bus    : " << targetBus->getBusNumber() << "\n";
    }

    //  A-3  View a student's profile
    void viewStudentProfile() {
        printHeader("MODULE A  >  Student Profile Viewer");
        string id = getLine("  Enter Student ID : ");
        Student* s = findStudent(id);
        if (s) s->displayProfile();   // Polymorphic dispatch
        else printError("Student not found.");
    }

    //  A-4  List all students
    void listAllStudents() {
        printHeader("MODULE A  >  All Registered Students");
        if (students.empty()) { printError("No students registered."); return; }
        for (const auto& s : students) {
            s.displayProfile();   // Polymorphic dispatch
        }
    }


    // ════════════════════════════════════════════════════════════════════════
    //  MODULE B - BUS & ROUTE MODULE   (Hassan Khan)
    // ════════════════════════════════════════════════════════════════════════

    //  B-1  Add a new route
    void addRoute() {
        printHeader("MODULE B  >  Add New Route");

        string routeID = getLine("  Route ID      : ");
        if (findRoute(routeID)) { printError("Route ID already exists."); return; }

        string pickup  = getLine("  Pickup Point  : ");
        string dest    = getLine("  Destination   : ");
        string time    = getLine("  Schedule Time : ");

        routes.emplace_back(routeID, pickup, dest, time);
        printSuccess("Route '" + routeID + "' added successfully.");
    }

    //  B-2  Add a new bus
    void addBus() {
        printHeader("MODULE B  >  Add New Bus");
        string busNo = getLine("  Bus Number  : ");
        if (findBus(busNo)) { printError("Bus already exists."); return; }
        int cap = getInt("  Capacity    : ");
        if (cap <= 0) { printError("Capacity must be positive."); return; }
        buses.emplace_back(busNo, cap);
        printSuccess("Bus '" + busNo + "' added with capacity " + to_string(cap) + ".");
    }

    //  B-3  Assign bus to route
    void assignBusToRoute() {
        printHeader("MODULE B  >  Assign Bus to Route");

        string busNo  = getLine("  Bus Number : ");
        string routeID = getLine("  Route ID   : ");

        Bus*   bus   = findBus(busNo);
        Route* route = findRoute(routeID);

        if (!bus)   { printError("Bus not found."); return; }
        if (!route) { printError("Route not found."); return; }

        bus->assignRoute(routeID);
        printSuccess("Bus '" + busNo + "' has been assigned to Route '" + routeID + "'.");
    }

    //  B-4  Assign driver to bus + route
    void assignDriverToBus() {
        printHeader("MODULE B  >  Assign Driver to Bus");

        string driverID = getLine("  Driver ID  : ");
        string busNo    = getLine("  Bus Number : ");

        Driver* driver = findDriver(driverID);
        Bus*    bus    = findBus(busNo);

        if (!driver) { printError("Driver not found."); return; }
        if (!bus)    { printError("Bus not found."); return; }

        driver->bindToBus(busNo);

        // If bus is on a route, bind driver to that route too
        if (!bus->getCurrentRouteID().empty())
            driver->bindToRoute(bus->getCurrentRouteID());

        printSuccess("Driver '" + driver->getName() + "' assigned to Bus '" + busNo + "'.");
    }

    //  B-5  Register a new driver
    void registerDriver() {
        printHeader("MODULE B  >  Register New Driver");
        string name    = getLine("  Full Name       : ");
        string contact = getLine("  Contact Number  : ");
        string empID   = generateID("EMP", driverCounter);
        string drvID   = generateID("DRV", driverCounter++);

        drivers.emplace_back(name, drvID, contact, empID);
        printSuccess("Driver registered!");
        cout << "  Driver ID   : " << drvID  << "\n";
        cout << "  Employee ID : " << empID  << "\n";
    }

    //  B-6  View driver profile
    void viewDriverProfile() {
        printHeader("MODULE B  >  Driver Profile Viewer");
        string id = getLine("  Enter Driver ID : ");
        Driver* d = findDriver(id);
        if (d) d->displayProfile();   // Polymorphic dispatch
        else printError("Driver not found.");
    }

    //  B-7  List all buses
    void listAllBuses() {
        printHeader("MODULE B  >  Fleet Status");
        if (buses.empty()) { printError("No buses in fleet."); return; }
        for (const auto& b : buses) {
            b.display();
            cout << "\n";
        }
    }

    //  B-8  List all routes
    void listAllRoutes() {
        printHeader("MODULE B  >  Route Schedule");
        if (routes.empty()) { printError("No routes defined."); return; }
        for (const auto& r : routes) {
            r.display();
            cout << "\n";
        }
    }

    //  B-9  Unassign driver from bus
    void unassignDriver() {
        printHeader("MODULE B  >  Unassign Driver from Bus");
        string driverID = getLine("  Driver ID : ");
        Driver* d = findDriver(driverID);
        if (!d) { printError("Driver not found."); return; }
        d->unbindFromBus();
        d->unbindFromRoute();
        printSuccess("Driver '" + d->getName() + "' has been unassigned.");
    }


    // ════════════════════════════════════════════════════════════════════════
    //  MODULE C - PAYMENT MODULE   (Izaz Ali Shah)
    // ════════════════════════════════════════════════════════════════════════

    //  C-1  Process a payment
    void processPayment() {
        printHeader("MODULE C  >  Process Payment");

        string stdID = getLine("  Student ID      : ");
        Student* student = findStudent(stdID);
        if (!student) { printError("Student not found."); return; }

        cout << "  Current Balance : PKR " << fixed << setprecision(2) << student->getBalanceDue() << "\n";

        if (student->getBalanceDue() <= 0) {
            printSuccess("Account is fully cleared. No payment needed.");
            return;
        }

        double amount = getDouble("  Amount to Pay (PKR) : ");
        if (amount <= 0) { printError("Invalid amount."); return; }
        if (amount > student->getBalanceDue()) {
            cout << "  [!] Amount exceeds balance. Capping to PKR "
                 << fixed << setprecision(2) << student->getBalanceDue() << ".\n";
            amount = student->getBalanceDue();
        }

        // Update student's balance
        student->updatePayment(amount);

        // Create payment record
        string txID = generateID("TXN", txCounter++);
        payments.emplace_back(txID, stdID, amount, currentDate());

        // Print receipt
        payments.back().printReceipt();

        if (student->getFeePaidStatus())
            printSuccess("Account fully settled. Fee status: PAID.");
        else
            cout << "\n  Remaining Balance: PKR " << fixed << setprecision(2) << student->getBalanceDue() << "\n";
    }

    //  C-2  View payment history
    void viewPaymentHistory() {
        printHeader("MODULE C  >  Payment Transaction History");
        if (payments.empty()) { printError("No transactions recorded."); return; }
        for (const auto& p : payments)
            p.printReceipt();
    }

    //  C-3  View payments for a specific student
    void viewStudentPayments() {
        printHeader("MODULE C  >  Student Payment History");
        string stdID = getLine("  Student ID : ");
        bool found = false;
        for (const auto& p : payments) {
            if (p.getStudentID() == stdID) {
                p.printReceipt();
                found = true;
            }
        }
        if (!found) printError("No payment records found for Student ID: " + stdID);
    }


    // ════════════════════════════════════════════════════════════════════════
    //  MOCK DATA INITIALISATION  (called from main)
    // ════════════════════════════════════════════════════════════════════════

    void loadMockData() {
        // ── Routes ──
        routes.emplace_back("RT01", "Abbottabad City Centre", "University Main Gate",  "07:30 AM");
        routes.emplace_back("RT02", "Mandian Bazar",          "University Main Gate",  "07:45 AM");
        routes.emplace_back("RT03", "Nawan Shahr",            "University Back Gate",  "08:00 AM");
        routes.emplace_back("RT04", "Havelian",               "University Main Gate",  "07:15 AM");

        // ── Buses ──
        buses.emplace_back("BUS-A1", 30);
        buses.emplace_back("BUS-A2", 40);
        buses.emplace_back("BUS-B1", 35);
        buses.emplace_back("BUS-B2", 25);

        // Assign buses to routes
        buses[0].assignRoute("RT01");
        buses[1].assignRoute("RT02");
        buses[2].assignRoute("RT03");
        buses[3].assignRoute("RT04");

        // ── Drivers ──
        drivers.emplace_back("Khalid Mehmood", "DRV0001", "03001234567", "EMP0001");
        drivers.emplace_back("Tariq Hussain",  "DRV0002", "03009876543", "EMP0002");
        drivers.emplace_back("Nasir Ahmed",    "DRV0003", "03335556677", "EMP0003");
        driverCounter = 4;

        drivers[0].bindToBus("BUS-A1"); drivers[0].bindToRoute("RT01");
        drivers[1].bindToBus("BUS-A2"); drivers[1].bindToRoute("RT02");
        drivers[2].bindToBus("BUS-B1"); drivers[2].bindToRoute("RT03");

        // ── Students ──
        students.emplace_back("Ayesha Tariq",   "STD0001", "03111234567", 12000.0);
        students.emplace_back("Bilal Ashraf",   "STD0002", "03221234568",  8000.0);
        students.emplace_back("Fatima Noor",    "STD0003", "03331234569", 15000.0);
        students.emplace_back("Hamza Ali",      "STD0004", "03441234560",     0.0);
        studentCounter = 5;

        // Pre-booked seats for 2 students
        students[0].allocateSeat("RT01", 1); buses[0].allocateSeat();
        students[1].allocateSeat("RT02", 1); buses[1].allocateSeat();
        students[3].setFeePaidStatus(true);

        // ── Payments ──
        txCounter = 1;
        payments.emplace_back("TXN0001", "STD0004", 15000.0, "2025-01-10");
        txCounter = 2;
    }


    // ════════════════════════════════════════════════════════════════════════
    //  PANEL MENUS
    // ════════════════════════════════════════════════════════════════════════

    // ── Admin Panel ─────────────────────────────────────────────────────────
    void adminPanel() {
        int choice;
        do {
            printHeader("ADMIN PANEL");
            cout << "  Bus & Route Management  (Module B - Hassan Khan)\n";
            printDivider();
            cout << "   1. Add New Route\n";
            cout << "   2. Add New Bus\n";
            cout << "   3. Assign Bus to Route\n";
            cout << "   4. Register New Driver\n";
            cout << "   5. Assign Driver to Bus\n";
            cout << "   6. Unassign Driver from Bus\n";
            cout << "   7. View Driver Profile\n";
            cout << "   8. List All Buses\n";
            cout << "   9. List All Routes\n";
            cout << "  10. List All Students\n";
            printDivider();
            cout << "  Payment Management  (Module C - Izaz Ali Shah)\n";
            printDivider();
            cout << "  11. View All Payment History\n";
            cout << "   0. Back to Main Menu\n";
            printDivider();

            choice = getInt("  Select Option : ");

            switch (choice) {
                case  1: addRoute();          break;
                case  2: addBus();            break;
                case  3: assignBusToRoute();  break;
                case  4: registerDriver();    break;
                case  5: assignDriverToBus(); break;
                case  6: unassignDriver();    break;
                case  7: viewDriverProfile(); break;
                case  8: listAllBuses();      break;
                case  9: listAllRoutes();     break;
                case 10: listAllStudents();   break;
                case 11: viewPaymentHistory();break;
                case  0: break;
                default: printError("Invalid option. Please try again.");
            }
            if (choice != 0) pressEnter();

        } while (choice != 0);
    }

    // ── Student Panel ────────────────────────────────────────────────────────
    void studentPanel() {
        int choice;
        do {
            printHeader("STUDENT PANEL  (Module A - Ibad Ullah)");
            cout << "   1. Register New Student\n";
            cout << "   2. Book a Seat on a Route\n";
            cout << "   3. View My Profile\n";
            cout << "   4. View All Routes\n";
            printDivider();
            cout << "  Fee & Payment  (Module C - Izaz Ali Shah)\n";
            printDivider();
            cout << "   5. Pay Transport Fee\n";
            cout << "   6. View My Payment History\n";
            cout << "   0. Back to Main Menu\n";
            printDivider();

            choice = getInt("  Select Option : ");

            switch (choice) {
                case 1: registerStudent();     break;
                case 2: bookSeat();            break;
                case 3: viewStudentProfile();  break;
                case 4: listAllRoutes();       break;
                case 5: processPayment();      break;
                case 6: viewStudentPayments(); break;
                case 0: break;
                default: printError("Invalid option. Please try again.");
            }
            if (choice != 0) pressEnter();

        } while (choice != 0);
    }

    // ── Driver Panel ─────────────────────────────────────────────────────────
    void driverPanel() {
        int choice;
        do {
            printHeader("DRIVER PANEL  (Module B - Hassan Khan)");
            cout << "   1. View My Profile\n";
            cout << "   2. View My Assigned Route\n";
            cout << "   3. View All Routes\n";
            cout << "   0. Back to Main Menu\n";
            printDivider();

            choice = getInt("  Select Option : ");

            switch (choice) {
                case 1: viewDriverProfile(); break;
                case 2: {
                    string id = getLine("  Enter Your Driver ID : ");
                    Driver* d = findDriver(id);
                    if (d) {
                        cout << "\n  Assigned Bus   : " << (d->getAssignedBusNumber().empty() ? "None" : d->getAssignedBusNumber()) << "\n";
                        cout << "  Assigned Route : " << (d->getAssignedRouteID().empty()   ? "None" : d->getAssignedRouteID())   << "\n";
                        if (!d->getAssignedRouteID().empty()) {
                            Route* r = findRoute(d->getAssignedRouteID());
                            if (r) { cout << "\n"; r->display(); }
                        }
                    } else { printError("Driver not found."); }
                    break;
                }
                case 3: listAllRoutes(); break;
                case 0: break;
                default: printError("Invalid option. Please try again.");
            }
            if (choice != 0) pressEnter();

        } while (choice != 0);
    }
};


// =============================================================================
//  MAIN DRIVER FUNCTION
//  Module C - Master Navigation Console   (Izaz Ali Shah)
// =============================================================================

int main() {
   

    // ── Initialise System with Mock Data ──────────────────────────────────
    TransportSystem system;
    system.loadMockData();

    cout << "  System initialised with sample routes, buses, drivers,\n";
    cout << "  and students. Ready for operations.\n\n";
    pressEnter();

    // ── Main Navigation Loop ───────────────────────────────────────────────
    int mainChoice;
    do {
        printHeader("MAIN MENU  >  Select Access Panel");
        cout << "   1. Admin Panel\n";
        cout << "   2. Student Panel\n";
        cout << "   3. Driver Panel\n";
        cout << "   0. Exit System\n";
        printDivider();

        mainChoice = getInt("  Select Panel : ");

        switch (mainChoice) {
            case 1: system.adminPanel();   break;
            case 2: system.studentPanel(); break;
            case 3: system.driverPanel();  break;
            case 0:
                cout << "\n  Thank you for using UTMS. Goodbye!\n\n";
                break;
            default:
                printError("Invalid selection. Please enter 0, 1, 2, or 3.");
                pressEnter();
        }

    } while (mainChoice != 0);

    return 0;
}

