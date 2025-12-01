#include "Customer.h"

// Constructor
Customer::Customer(const std::string& license, const std::string& name, const std::string& phone)
    : driverLicense(license), name(name), phone(phone) {}

// Getters
std::string Customer::getDriverLicense() const { return driverLicense; }
std::string Customer::getName() const { return name; }
std::string Customer::getPhone() const { return phone; }

// Operator ==
bool Customer::operator==(const Customer& other) const {
    return driverLicense == other.driverLicense;
}

// Friend print operator
std::ostream& operator<<(std::ostream& os, const Customer& c) {
    os << "Customer[License=" << c.driverLicense
       << ", Name=" << c.name
       << ", Phone=" << c.phone
       << "]";
    return os;
}

// Display function
void Customer::displayInfo() const {
    std::cout << "=== Customer Information ===\n";
    std::cout << "Driver License: " << driverLicense << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Phone: " << phone << "\n";
}
