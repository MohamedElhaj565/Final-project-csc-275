#ifndef FINAL_PROJECT_CSC_275_RENTAL_H
#define FINAL_PROJECT_CSC_275_RENTAL_H

#include <string>
#include <iostream>
#include "Vehicle.h"

class Customer;

class Rental {
private:
    int rentalId;
    Customer* customer;  //pointer so we don't copy whole object
    Vehicle* vehicle;    //base-class pointer --> polymorphism
    int startDay;        //you can treat days as simple ints (e.g. 1...365)
    int endDay;
    double totalPrice;
    bool active;

public:
    //Constructor
    Rental(int rentalId, Customer* customer, Vehicle* vehicle, int startDay, int endDay);


    //Getters
    int getRentalId() const;
    Customer* getCustomer() const;
    Vehicle* getVehicle() const;
    int getStartDay() const;
    int getEndDay() const;
    double getTotalPrice() const;
    bool isActive() const;


    //Behaviour
    void computeTotalPrice();  //uses vehicle--> to calculatePrice()
    void closeRental();        //mark inactive, free vehicle

    void displayInfo() const;

    //Friend: print rental easily
    friend std::ostream& operator<<(std::ostream& os, const Rental& r);
};


#endif //FINAL_PROJECT_CSC_275_RENTAL_H