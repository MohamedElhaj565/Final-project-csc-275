#ifndef FINAL_PROJECT_CSC_275_CUSTOMER_H
#define FINAL_PROJECT_CSC_275_CUSTOMER_H

#include <string>
#include <iostream>

class Customer {
private:
    std::string driverLicense;   // unique ID
    std::string name;
    std::string phone;

public:
    // NEW constructor
    Customer(const std::string& license, const std::string& name, const std::string& phone);

    // Getters
    std::string getDriverLicense() const;
    std::string getName() const;
    std::string getPhone() const;

    // Comparison (based on license)
    bool operator==(const Customer& other) const;

    // Printing
    friend std::ostream& operator<<(std::ostream& os, const Customer& c);

    void displayInfo() const;
};

#endif
