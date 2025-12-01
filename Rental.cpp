#include "Rental.h"
#include <iostream>

// Constructor
Rental::Rental(int id, Customer* c, Vehicle* v, const Date& start, const Date& end)
    : rentalId(id), customer(c), vehicle(v), startDate(start), endDate(end), active(true)
{
    if (vehicle)
        vehicle->setAvailable(false);
}

int Rental::getRentalId() const {
    return rentalId;
}

bool Rental::isActive() const {
    return active;
}

void Rental::closeRental() {
    active = false;
    if (vehicle)
        vehicle->setAvailable(true);
}

// Calculate price based on number of days
double Rental::getTotalPrice() const {
    int start = startDate.year * 365 + startDate.month * 30 + startDate.day;
    int end   = endDate.year * 365 + endDate.month * 30 + endDate.day;
    int days  = end - start;

    if (days < 1) days = 1;  // minimum 1 day

    return vehicle->calculatePrice(days);
}

void Rental::displayInfo() const {
    std::cout << "Rental ID: " << rentalId << "\n";
    std::cout << "Customer: " << customer->getName() << "\n";
    std::cout << "Vehicle: " << vehicle->getPlateNumber() << "\n";
    std::cout << "Start Date: " << startDate.month << "/" << startDate.day << "/" << startDate.year << "\n";
    std::cout << "End Date: " << endDate.month   << "/" << endDate.day   << "/" << endDate.year << "\n";
    std::cout << "Active: " << (active ? "Yes" : "No") << "\n";
}

std::ostream& operator<<(std::ostream& os, const Rental& r) {
    os << "Rental[ID=" << r.rentalId
       << ", Customer=" << r.customer->getName()
       << ", Vehicle=" << r.vehicle->getPlateNumber()
       << ", Start=" << r.startDate.month << "/" << r.startDate.day << "/" << r.startDate.year
       << ", End="   << r.endDate.month   << "/" << r.endDate.day   << "/" << r.endDate.year
       << ", Active=" << (r.active ? "Yes" : "No")
       << "]";
    return os;
}
