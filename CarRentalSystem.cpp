#include "CarRentalSystem.h"
#include <iostream>

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

Customer* CarRentalSystem::findCustomerById(int id) {
    for (auto& c : customers) {
        if (c.getCustomerId() == id) {
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
    // sample customers
    customers.emplace_back(1, "Mohamed", "DL12345", "810-555-1111");
    customers.emplace_back(2, "Ali", "DL67890", "810-555-2222");

    // sample vehicles (Car)
    vehicles.push_back(new Car("ABC123", "Toyota", "Camry", 2021, 40.0, 5, "Gas", true));
    vehicles.push_back(new Car("XYZ789", "Tesla", "Model3", 2023, 80.0, 5, "Electric", true));

    std::cout << "Sample data added.\n";
}

// --------- Add Customer / Car ---------

void CarRentalSystem::addCustomer() {
    int id;
    std::string name, license, phone;

    std::cout << "Enter customer ID: ";
    std::cin >> id;
    std::cin.ignore(10000, '\n'); // clear rest of line

    std::cout << "Enter customer name: ";
    std::getline(std::cin, name);

    std::cout << "Enter driver license: ";
    std::getline(std::cin, license);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, phone);

    customers.emplace_back(id, name, license, phone);
    std::cout << "Customer added successfully.\n";
}

void CarRentalSystem::addCar() {
    std::string plate, make, model, fuelType;
    int year, seats;
    double dailyRate;
    char autoChoice;

    std::cout << "Enter plate number: ";
    std::cin >> plate;

    std::cout << "Enter make: ";
    std::cin >> make;

    std::cout << "Enter model: ";
    std::cin >> model;

    std::cout << "Enter year: ";
    std::cin >> year;

    std::cout << "Enter base daily rate: ";
    std::cin >> dailyRate;

    std::cout << "Enter number of seats: ";
    std::cin >> seats;

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

// --------- Create Rental ---------

void CarRentalSystem::createRental() {
    int customerId;
    std::string plate;
    int startDay, endDay;

    std::cout << "Enter customer ID: ";
    std::cin >> customerId;

    Customer* c = findCustomerById(customerId);
    if (!c) {
        std::cout << "Customer not found.\n";
        return;
    }

    std::cout << "Enter vehicle plate number: ";
    std::cin >> plate;

    Vehicle* v = findVehicleByPlate(plate);
    if (!v) {
        std::cout << "Vehicle not found.\n";
        return;
    }

    if (!v->isAvailable()) {
        std::cout << "Vehicle is already rented.\n";
        return;
    }

    std::cout << "Enter start day (int): ";
    std::cin >> startDay;

    std::cout << "Enter end day (int): ";
    std::cin >> endDay;

    rentals.emplace_back(nextRentalId, c, v, startDay, endDay);
    std::cout << "Rental created with ID: " << nextRentalId << "\n";
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