#ifndef FINAL_PROJECT_CSC_275_RENTAL_H
#define FINAL_PROJECT_CSC_275_RENTAL_H

#include <iostream>
#include "Customer.h"
#include "Vehicle.h"

// Date struct shared across system
struct Date {
    int month;
    int day;
    int year;
};

class Rental {
private:
    int rentalId;
    Customer* customer;
    Vehicle* vehicle;
    Date startDate;
    Date endDate;
    bool active;

public:
    Rental(int id, Customer* c, Vehicle* v, const Date& start, const Date& end);

    int getRentalId() const;
    double getTotalPrice() const;
    bool isActive() const;
    void closeRental();

    void displayInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const Rental& r);
};

#endif // FINAL_PROJECT_CSC_275_RENTAL_H
