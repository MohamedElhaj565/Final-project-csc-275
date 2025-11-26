#ifndef FINAL_PROJECT_CSC_275_CAR_H
#define FINAL_PROJECT_CSC_275_CAR_H
#include "Vehicle.h"
#include <string>

class Car : public Vehicle {
private:
    int seats;
    std::string fuelType; //e.g. Gas, Hybrid, Electric.
    bool automaticTransmission; //True= automatic, false= manual

public:
    //Constructor
    Car(const std::string& plate, const std::string& make, const std::string& model,
        int year, double dailyRate, int seats, const std::string& fuelType, bool automatic);

    //Override pure virtual functions
    double calculatePrice(int days) const override;
    void displayInfo() const override;

    //Getters (encapsulation)
    int getseats() const;
    std::string getFuelType() const;
    bool isAutomatic() const;

    //Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Car& c);
};

#endif //FINAL_PROJECT_CSC_275_CAR_H