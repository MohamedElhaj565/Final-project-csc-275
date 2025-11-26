#include "Customer.h"

//Constructor
Customer::Customer(int id, const std::string& name, const std::string& driverLicense, const std::string& phone)
    : customerId(id), name(name), driverLicense(driverLicense), phone(phone) {}

//Getters
int Customer::getCustomerId() const {
    return customerId;
}
std::string Customer::getName() const {
    return name;
}
std::string Customer::getDriverLicense() const {
    return driverLicense;
}
std::string Customer::getPhone() const {
    return phone;
}


//Setter
void Customer::setPhone(std::string &newPhone) {
    phone = newPhone;
}


// Operator== (compare by customer ID)
bool Customer::operator==(const Customer& other) const {
    return this->customerId == other.customerId;
}


//Friend operator<<
std::ostream& operator<<(std::ostream& os, const Customer& c) {
    os << "Customer[ID=" << c.customerId
     << ", Name=" << c.name
     << ", License=" << c.driverLicense
     << ", Phone=" << c.phone
     << "]";
    return os;
}

//Display function
void Customer::displayInfo() const {
    std::cout << "=== Customer Information ===\n";
    std::cout << "Customer ID: " << customerId << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Driver License: " << driverLicense << "\n";
    std::cout << "Phone: " << phone << "\n";
}
