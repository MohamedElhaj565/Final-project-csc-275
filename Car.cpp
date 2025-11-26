#include "Car.h"
#include<iostream>
#include <iomanip>

/*total = baseDailyRate * days
if automatic --> + $5 per day
if fuelType = "Electric" --> +10% eco fee*/

Car::Car(const std::string& plate, const std::string& make, const std::string& model,
        int year, double dailyRate, int seats, const std::string& fuelType, bool automatic)
        :Vehicle(plate, make,model, year, dailyRate),
        seats(seats),
        fuelType(fuelType),
        automaticTransmission(automatic) {}


//------------ Price Calculation ------------
double Car::calculatePrice(int days) const {
        double total = baseDailyRate * days;

        //automatic transmission adds $5 per day
        if (automaticTransmission) {
                total += (5.0 * days);
        }

        //electirc cars add 10% eco fee
        if (fuelType== "Electric") {
                total *= 1.10;
        }
        return total;
}


//------------ Display Info ------------
void Car::displayInfo() const {
        std::cout <<"=== Car Information ===\n";
        std::cout <<"Plate: " << plateNumber << std::endl;
        std::cout <<"Make: " << make << std::endl;
        std::cout <<"Model: " << model << std::endl;
        std::cout <<"Year: " << year << std::endl;
        std::cout <<"Daily Rate: $"<< std::fixed << std::setprecision(2)
        << baseDailyRate << "/day\n";
        std::cout <<"Seats: " << seats << std::endl;
        std::cout <<"Fuel Type: " << fuelType << std::endl;
        std::cout <<"Transmission: " << (automaticTransmission ? "Automatic" : "Manual") << std::endl;
        std::cout <<"Available: " << (available ? "Yes" : "No") << std::endl;
}

//---------- Encapsulation getters ---------
int Car::getseats() const {
        return seats;
}

std::string Car::getFuelType() const {
        return fuelType;
}

bool Car::isAutomatic() const {
        return automaticTransmission;
}

//---------- Operator << (Friend) ---------
std::ostream& operator<<(std::ostream& os, const Car& c) {
     os <<"Car[" << c.year << " " << c.make << " " << c.model
        << ", Plate=" << c.plateNumber
        << ", Rate=$" << c.baseDailyRate << "/day"
        << ", Seats=" << c.seats
        << ", Fuel=" << c.fuelType
        << ", Trans=" << (c.automaticTransmission ? "Automatic" : "Manual")
        << "]";
        return os;
}
