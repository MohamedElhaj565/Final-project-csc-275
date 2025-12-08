#ifndef FINAL_PROJECT_CSC_275_CARRENTALSYSTEM_H
#define FINAL_PROJECT_CSC_275_CARRENTALSYSTEM_H

#include <vector>
#include <string>
#include "Vehicle.h"
#include "Car.h"
#include "Customer.h"
#include "Rental.h"

class CarRentalSystem {
private:
    std::vector<Vehicle*> vehicles;  // polymorphic: can store Car*, later maybe SUV*
    std::vector<Customer> customers;
    std::vector<Rental> rentals;
    int nextRentalId;

    // helper methods
    Customer* findCustomerById(const std::string& license);
    Vehicle* findVehicleByPlate(const std::string& plate);
    Rental* findRentalById(int rentalId);

    // NEW: Fuel-type information screen
    void showFuelTypeInfo() const;

public:
    CarRentalSystem();
    ~CarRentalSystem();   // deletes Vehicle* to avoid memory leaks

    // interface functions
    void addSampleData();
    void addCustomer();
    void addCar();

    void listCustomers() const;
    void listVehicles() const;
    void listRentals() const;

    void createRental();
    void closeRental();

    void run();  // main menu loop
};
#endif // FINAL_PROJECT_CSC_275_CARRENTALSYSTEM_H