#ifndef FINAL_PROJECT_CSC_275_VEHICLE_H
#define FINAL_PROJECT_CSC_275_VEHICLE_H

#include <string>
#include <iostream>

class Vehicle {
protected:
    std::string plateNumber;
    std::string make;
    std::string model;
    int year;
    double baseDailyRate;
    bool available;
public:
    //Constructor
    Vehicle(const std::string& plate, const std::string& make, const std::string& model, int year, double dailyRate);

    //Destructor for polymorphism cleanup
    virtual ~Vehicle() = default;

    //Encapsulation Getters
    std::string getPlateNumber() const;
    std::string getMake() const;
    std::string getModel() const;
    int getYear() const;
    double getBaseDailyRate() const;
    bool isAvailable() const;

    //Encapsulation setters
    void setAvailable(bool status);

    //Pure virtual functions (which will make this class an abstract class)
    virtual double calculatePrice(int days) const=0;
    virtual void displayInfo() const=0;

};


#endif //FINAL_PROJECT_CSC_275_VEHICLE_H