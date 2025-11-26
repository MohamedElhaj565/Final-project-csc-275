#ifndef FINAL_PROJECT_CSC_275_CUSTOMER_H
#define FINAL_PROJECT_CSC_275_CUSTOMER_H

#include <string>
#include <iostream>

class Customer {
private:
    int customerId;
    std::string name;
    std::string driverLicense;
    std::string phone;

public:
    Customer(int id, const std::string& name, const std::string& driverLicense, const std::string& phone);

    //Getters
    int getCustomerId() const;
    std::string getName() const;
    std::string getDriverLicense() const;
    std::string getPhone() const;

    //Setters
    void setPhone(std::string& newPhone);

    //Operator overloading: compare customers by ID
    bool operator==(const Customer& other) const;

    //Friend function to print customer info
    friend std::ostream& operator<<(std::ostream& os, const Customer& c);

    //Utility function for displaying info
    void displayInfo() const;
};


#endif //FINAL_PROJECT_CSC_275_CUSTOMER_H