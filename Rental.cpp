#include "Rental.h"
#include "Vehicle.h"
#include "Customer.h"
#include <iostream>

//Constructor
Rental::Rental(int rentalId, Customer* customer, Vehicle* vehicle, int startDay, int endDay)
    :rentalId(rentalId), customer(customer), vehicle(vehicle), startDay(startDay), endDay(endDay),
    totalPrice(0.0),active(true) {
    if (vehicle != nullptr) {
        vehicle->setAvailable(false); //car is now rented
    }

    computeTotalPrice();
}


//Getters
int Rental::getRentalId() const {
    return rentalId;
}
Customer* Rental::getCustomer() const {
    return customer;
}
Vehicle* Rental::getVehicle() const {
    return vehicle;
}
int Rental::getStartDay() const {
    return startDay;
}
int Rental::getEndDay() const {
    return endDay;
}
double Rental::getTotalPrice() const {
    return totalPrice;
}
bool Rental::isActive() const {
    return active;
}

//compute total price using polymrphism
void Rental::computeTotalPrice() {
    if (vehicle != nullptr) {
        totalPrice= 0.0;
        return;
    }
    int days = endDay - startDay;
    if (days <= 0) {
        days = 1; //minimum 1 day
    }
    totalPrice = vehicle->calculatePrice(days);
}

//closing the rental and making the car free for future rent
void Rental::closeRental() {
    active = false;
    if (vehicle != nullptr) {
        vehicle->setAvailable(true);
    }
}

void Rental::displayInfo() const {
    std::cout << "=== Rental Information ===\n";
    std::cout << "Rental ID: " << rentalId << "\n";
    std::cout << "Active: " << (active ? "Yes" : "No") << "\n";
    std::cout << "Start Day: " << startDay << "\n";
    std::cout << "End Day: " << endDay << "\n";
    std::cout << "Total Price: $" << totalPrice << "\n";

    std::cout << "--- Customer ---\n";
    if (customer != nullptr) {
        customer->displayInfo();
    } else {
        std::cout << "No customer assigned.\n";
    }

    std::cout << "\n--- Vehicle ---\n";
    if (vehicle != nullptr) {
        vehicle->displayInfo();   // polymorphic call
    } else {
        std::cout << "No vehicle assigned.\n";
    }
}

//Friend operator<<
std::ostream& operator<<(std::ostream &os, const Rental &r) {
    os << "Rental[ID=" << r.rentalId
      << ", Active=" << (r.active ? "Yes" : "No")
      << ", StartDay=" << r.startDay
      << ", EndDay=" << r.endDay
      << ", Total=$" << r.totalPrice
      << "]";
    return os;
}