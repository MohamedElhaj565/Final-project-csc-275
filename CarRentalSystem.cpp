#include "CarRentalSystem.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include <sstream>
#include <Rental.h>

// Allowed makes and models
std::map<std::string, std::vector<std::string>> allowedModels = {
    {"Ford",   {"F150", "F250", "Fusion", "Focus", "Escape", "Explorer", "Mustang"}},
    {"Honda",  {"Civic", "Accord", "CRV", "Pilot", "Fit"}},
    {"Toyota", {"Camry", "Corolla", "RAV4", "Highlander", "Tacoma"}},
    {"Chevy",  {"Malibu", "Impala", "Cruze", "Silverado", "Tahoe"}},
    {"Tesla",  {"Model3", "ModelS", "ModelX", "ModelY"}},
    {"Nissan", {"Altima", "Maxima", "Sentra", "Rogue", "Pathfinder"}},
    {"Kia",    {"Optima", "Sorento", "Sportage", "Soul", "Forte"}},
    {"Audi",   {"A4", "A6", "Q5", "Q7", "A3"}},
    {"BMW",    {"320i", "330i", "X3", "X5", "M3"}}
};

// --------- Constructor & Destructor ---------

CarRentalSystem::CarRentalSystem()
    : nextRentalId(1) {}

CarRentalSystem::~CarRentalSystem() {
    // free all vehicles created with new
    for (Vehicle* v : vehicles) {
        delete v;
    }
}

// --------- Helper Find Functions ---------

Customer* CarRentalSystem::findCustomerById(const std::string& license) {
    for (auto& c : customers) {
        if (c.getDriverLicense() == license) {
            return &c;
        }
    }
    return nullptr;
}

Vehicle* CarRentalSystem::findVehicleByPlate(const std::string& plate) {
    for (Vehicle* v : vehicles) {
        if (v->getPlateNumber() == plate) {
            return v;
        }
    }
    return nullptr;
}

Rental* CarRentalSystem::findRentalById(int rentalId) {
    for (auto& r : rentals) {
        if (r.getRentalId() == rentalId) {
            return &r;
        }
    }
    return nullptr;
}

// --------- Sample Data (Optional) ---------
void CarRentalSystem::addSampleData() {

    // --- Customers (Name, License, Phone) ---
    customers.emplace_back("A123456789012", "Mohamed Ali", "8105551111");
    customers.emplace_back("H987654321098", "Ali Hassan", "8105552222");
    customers.emplace_back("M102938475610", "Sarah Miller", "8105553333");
    customers.emplace_back("D564738291045", "Jake Dunda", "8105554444");

    // --- Vehicles ---
    vehicles.push_back(new Car("ABC123", "Toyota", "Camry", 2021, 40.0, 5, "Gas", true));
    vehicles.push_back(new Car("XYZ789", "Tesla", "Model3", 2023, 80.0, 5, "Electric", true));

    vehicles.push_back(new Car("CHE1234", "Chevy", "Malibu", 2018, 40.0, 5, "Gas", true));
    vehicles.push_back(new Car("FOR5678", "Ford", "F150", 2020, 55.0, 2, "Gas", false));
    vehicles.push_back(new Car("CHE9999", "Chevy", "Impala", 2017, 42.0, 5, "Gas", false));

    std::cout << "Sample data added.\n";
}

// --------- Add Customer / Car ---------

void CarRentalSystem::addCustomer() {
    std::string name, license, phone;

    // ---- NAME VALIDATION ----
    while (true) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter customer first and last name: ";
        std::getline(std::cin, name);

        // Must contain exactly two words
        std::stringstream ss(name);
        std::string first, last;
        ss >> first >> last;

        if (first.empty() || last.empty()) {
            std::cout << "Name must include FIRST and LAST name.\n";
            continue;
        }

        // Check letters only
        if (!std::all_of(first.begin(), first.end(), ::isalpha) ||
            !std::all_of(last.begin(), last.end(), ::isalpha)) {
            std::cout << "Name must contain LETTERS only.\n";
            continue;
        }

        // Passed validation
        break;
    }

    // ---- DRIVER LICENSE VALIDATION ----
    while (true) {
        std::cout << "Enter driver license (first letter of LAST name + 12 digits): ";
        std::cin >> license;

        if (license.length() != 13) {
            std::cout << "License must be 13 characters and begin with first letter of last name.\n";
            continue;
        }

        char lastInitial = toupper(license[0]);
        char requiredInitial = toupper(name.substr(name.find_last_of(' ') + 1)[0]);

        if (lastInitial != requiredInitial) {
            std::cout << "License must start with FIRST LETTER of LAST NAME ("
                      << requiredInitial << ").\n";
            continue;
        }

        bool digitsValid = true;
        for (int i = 1; i < 13; i++) {
            if (!isdigit(license[i])) digitsValid = false;
        }

        if (!digitsValid) {
            std::cout << "After the first letter, license must contain ONLY digits.\n";
            continue;
        }

        break;
    }

    // ---- PHONE NUMBER VALIDATION ----
    while (true) {
        std::cout << "Enter phone number (10 digits): ";
        std::cin >> phone;

        if (phone.length() != 10) {
            std::cout << "Phone number must be EXACTLY 10 digits.\n";
            continue;
        }

        if (!std::all_of(phone.begin(), phone.end(), ::isdigit)) {
            std::cout << "Phone number must contain ONLY digits.\n";
            continue;
        }

        break;
    }

    customers.emplace_back(license, name, phone);
    std::cout << "Customer added successfully.\n";
}

void CarRentalSystem::addCar() {
    std::string plate, make, model, fuelType, bodyStyle;
    int year, seats;
    double dailyRate;
    char autoChoice;

    // Plate validation
    // Clear leftover input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "Enter plate number (3-7 characters): ";
        std::getline(std::cin, plate);

        // Remove spaces so "ejz 6238" → "ejz6238"
        plate.erase(remove(plate.begin(), plate.end(), ' '), plate.end());

        if (plate.length() >= 3 && plate.length() <= 7)
            break;

        std::cout << "Invalid plate. Try again.\n";
    }

    // Make validation (case insensitive)
    while (true) {
        std::cout << "Enter make (Ford/Honda/Toyota/Chevy/Tesla/Nissan/Kia/Audi/BMW): ";
        std::cin >> make;

        // Convert input to proper format (capitalize first letter)
        make[0] = toupper(make[0]);
        for (int i = 1; i < make.size(); i++)
            make[i] = tolower(make[i]);

        if (allowedModels.count(make) > 0)
            break;

        std::cout << "Invalid make. Try again.\n";
    }

    // Model validation (case insensitive)
    while (true) {
        std::cout << "Available " << make << " models: ";
        for (auto &m : allowedModels[make]) std::cout << m << " ";
        std::cout << "\nEnter model: ";
        std::cin >> model;

        // Normalize model for comparison
        std::string userModelLower = model;
        std::transform(userModelLower.begin(), userModelLower.end(), userModelLower.begin(), ::tolower);

        bool valid = false;

        for (auto &m : allowedModels[make]) {
            std::string sysModelLower = m;
            std::transform(sysModelLower.begin(), sysModelLower.end(), sysModelLower.begin(), ::tolower);

            if (sysModelLower == userModelLower) {
                model = m;  // store official capitalized model
                valid = true;
                break;
            }
        }

        if (valid) break;

        std::cout << "Invalid model for " << make << ". Try again.\n";
    }

    // Year validation (max 25 years old)
    int currentYear = 2024;
    while (true) {
        std::cout << "Enter year: ";
        std::cin >> year;

        if (currentYear - year <= 25 && year >= 1999)
            break;

        std::cout << "Invalid year. Car must be within 25 years.\n";
    }

    // Daily rate validation (40–80)
    while (true) {
        std::cout << "Enter base daily rate (40-80): ";
        std::cin >> dailyRate;

        if (dailyRate >= 40 && dailyRate <= 80)
            break;

        std::cout << "Invalid rate. Must be between $40 and $80.\n";
    }

    // Body style selection
    while (true) {
        std::cout << "Enter body style (coupe/sedan/truck/suv/van): ";
        std::cin >> bodyStyle;

        std::string b = bodyStyle;
        std::transform(b.begin(), b.end(), b.begin(), ::tolower);

        if (b == "coupe" || b == "sedan" || b == "truck" || b == "suv" || b == "van") {
            bodyStyle = b;
            break;
        }
        std::cout << "Invalid body style.\n";
    }

    // Seat validation based on body style
    while (true) {
        std::cout << "Enter number of seats: ";
        std::cin >> seats;

        bool ok = false;

        if (bodyStyle == "coupe" && seats == 2) ok = true;
        if (bodyStyle == "sedan" && seats == 5) ok = true;
        if (bodyStyle == "truck" && (seats == 2 || seats == 5)) ok = true;
        if (bodyStyle == "suv" && seats == 5) ok = true;
        if (bodyStyle == "van" && (seats >= 5 && seats <= 8)) ok = true;

        if (ok) break;

        std::cout << "Invalid seat count for " << bodyStyle << ". Try again.\n";
    }

    std::cout << "Enter fuel type (Gas/Hybrid/Electric): ";
    std::cin >> fuelType;

    std::cout << "Automatic transmission? (y/n): ";
    std::cin >> autoChoice;
    bool automatic = (autoChoice == 'y' || autoChoice == 'Y');

    vehicles.push_back(new Car(plate, make, model, year, dailyRate, seats, fuelType, automatic));
    std::cout << "Car added successfully.\n";
}

// --------- List Functions ---------

void CarRentalSystem::listCustomers() const {
    if (customers.empty()) {
        std::cout << "No customers found.\n";
        return;
    }

    std::cout << "=== Customers ===\n";
    for (const auto& c : customers) {
        std::cout << c << "\n";
    }
}

void CarRentalSystem::listVehicles() const {
    if (vehicles.empty()) {
        std::cout << "No vehicles found.\n";
        return;
    }

    std::cout << "=== Vehicles ===\n";
    for (const Vehicle* v : vehicles) {
        v->displayInfo();
        std::cout << "\n";
    }
}

void CarRentalSystem::listRentals() const {
    if (rentals.empty()) {
        std::cout << "No rentals found.\n";
        return;
    }

    std::cout << "=== Rentals ===\n";
    for (const auto& r : rentals) {
        std::cout << r << "\n";
    }
}

// Data Parsing makes input for data 03/15/2024
bool parseDate(const std::string& input, Date& date) {
    if (input.length() != 10 || input[2] != '/' || input[5] != '/')
        return false;

    try {
        date.month = std::stoi(input.substr(0, 2));
        date.day   = std::stoi(input.substr(3, 2));
        date.year  = std::stoi(input.substr(6, 4));
    } catch (...) {
        return false;
    }

    if (date.month < 1 || date.month > 12) return false;
    if (date.day < 1 || date.day > 31) return false;
    if (date.year < 1900 || date.year > 2100) return false;

    return true;
}

// comparsion function make sure end data isn't before start date
bool isAfterOrSame(const Date& end, const Date& start) {
    if (end.year != start.year)
        return end.year > start.year;
    if (end.month != start.month)
        return end.month > start.month;
    return end.day >= start.day;
}

// --------- Fuel-type Info Screen ---------

void CarRentalSystem::showFuelTypeInfo() const {
    std::cout << "\n================ IMPORTANT RENTAL INFORMATION ================\n";
    std::cout << "Before choosing a vehicle, please note how fuel type and\n";
    std::cout << "transmission affect your final rental price:\n\n";

    std::cout << " • Automatic Transmission:\n"
              << "     + $5.00 PER DAY added to the rental cost.\n\n";

    std::cout << " • Electric Vehicles (EV):\n"
              << "     + 10% ECO FEE added to the total rental price.\n"
              << "       (EVs must also be charged at charging stations.)\n\n";

    std::cout << " • Gasoline Vehicles:\n"
              << "     No extra fees. Customer must refuel before returning.\n\n";

    std::cout << " • Hybrid Vehicles:\n"
              << "     No extra fees. More fuel-efficient than gas.\n\n";

    std::cout << "You may go back to the main menu if you are not ready to rent.\n";
    std::cout << "==============================================================\n\n";
}

// --------- Create Rental ---------

void CarRentalSystem::createRental() {

    // ---------- STEP 0: Fuel-type explanation + option to exit ----------
    showFuelTypeInfo();

    int startChoice = -1;
    while (true) {
        std::cout << "Press 1 to continue creating a rental.\n";
        std::cout << "Press 0 to go back to the main menu.\n";
        std::cout << "Your choice: ";
        std::cin >> startChoice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter 0 or 1.\n";
            continue;
        }

        if (startChoice == 0) {
            std::cout << "Returning to main menu...\n";
            return; // user decided not to create a rental
        }

        if (startChoice == 1) {
            break;  // continue with normal rental flow
        }

        std::cout << "Please enter 1 to continue or 0 to exit.\n";
    }

    // ---------- STEP 1: CUSTOMER LOOKUP ----------
    std::string license;
    Customer* c = nullptr;

    while (true) {
        std::cout << "Enter customer driver license: ";
        std::cin >> license;

        c = findCustomerById(license);
        if (c) break;

        std::cout << "License does not match system. Try again.\n";
    }

    // ---------- STEP 2: VEHICLE LOOKUP ----------
    std::string plate;
    Vehicle* v = nullptr;

    while (true) {
        std::cout << "Enter vehicle plate number: ";
        std::cin >> plate;

        v = findVehicleByPlate(plate);
        if (!v) {
            std::cout << "Plate does not match system. Try again.\n";
            continue;
        }

        if (!v->isAvailable()) {
            std::cout << "Vehicle is currently rented. Choose another vehicle.\n";
            continue;
        }

        break;
    }

    // ---------- STEP 3: DATE INPUT ----------
    Date startDate, endDate;
    std::string startInput, endInput;

    // START DATE LOOP
    while (true) {
        std::cout << "Enter start date (MM/DD/YYYY): ";
        std::cin >> startInput;

        if (parseDate(startInput, startDate)) break;

        std::cout << "Invalid date format. Try again.\n";
    }

    // END DATE LOOP
    while (true) {
        std::cout << "Enter end date (MM/DD/YYYY): ";
        std::cin >> endInput;

        if (!parseDate(endInput, endDate)) {
            std::cout << "Invalid date format. Try again.\n";
            continue;
        }

        if (!isAfterOrSame(endDate, startDate)) {
            std::cout << "End date cannot be before start date. Try again.\n";
            continue;
        }

        break;
    }

    // ---------- STEP 4: CREATE RENTAL ----------
    rentals.emplace_back(nextRentalId, c, v, startDate, endDate);

    Rental& r = rentals.back();
    std::cout << "Rental created with ID: " << nextRentalId << "\n";
    std::cout << "Total price: $" << r.getTotalPrice() << "\n";

    ++nextRentalId;
}

// --------- Close Rental ---------

void CarRentalSystem::closeRental() {
    int rentalId;
    std::cout << "Enter rental ID to close: ";
    std::cin >> rentalId;

    Rental* r = findRentalById(rentalId);
    if (!r) {
        std::cout << "Rental not found.\n";
        return;
    }

    if (!r->isActive()) {
        std::cout << "Rental is already closed.\n";
        return;
    }

    r->closeRental();
    std::cout << "Rental closed. Vehicle is now available again.\n";
}

// --------- Main Menu ---------

void CarRentalSystem::run() {
    bool running = true;

    while (running) {
        std::cout << "\n=== Car Rental System Menu ===\n";
        std::cout << "1. Add sample data\n";
        std::cout << "2. Add customer\n";
        std::cout << "3. Add car\n";
        std::cout << "4. List customers\n";
        std::cout << "5. List vehicles\n";
        std::cout << "6. Create rental\n";
        std::cout << "7. List rentals\n";
        std::cout << "8. Close rental\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                addSampleData();
                break;
            case 2:
                addCustomer();
                break;
            case 3:
                addCar();
                break;
            case 4:
                listCustomers();
                break;
            case 5:
                listVehicles();
                break;
            case 6:
                createRental();
                break;
            case 7:
                listRentals();
                break;
            case 8:
                closeRental();
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
}