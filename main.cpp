#include <iostream>
#include "Vehicle.h"
#include "Car.h"
#include "Rental.h"
#include "Customer.h"
#include "CarRentalSystem.h"

int main () {


    CarRentalSystem system;
    system.run();


























    return 0;
    //our tests
    //Vehicle* v;
    Car c("ABC123", "Toyota", "Camry", 2021, 40.0, 5, "Gas", true);

    c.displayInfo();
    std::cout << "\nRent for 3 days: $" << c.calculatePrice(3) << "\n\n";

    std::cout << c << "\n";  // using operator<<

    Customer* customer = nullptr;

    Car car("ABC123", "Toyota", "Camry", 2022, 45.0, 5, "Gas", true);

    Rental rental1(1, customer, &car, 10, 13); // days 10–13 => 3 days

    rental1.displayInfo();
    std::cout << "\n" << rental1 << "\n";

    rental1.closeRental();

    Customer c1(101, "Mohamed", "DL12345", "810-555-1122");
    Customer c2(101, "Ali", "DL99999", "313-444-5566");

    c1.displayInfo();
    std::cout << "\n";

    std::cout << c1 << "\n";

    if (c1 == c2)
        std::cout << "Same customer ID!\n";
}