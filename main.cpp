#include <iostream>
#include "Vehicle.h"
#include "Car.h"

int main () {































    return 0;
    //our tests
    //Vehicle* v;
    Car c("ABC123", "Toyota", "Camry", 2021, 40.0, 5, "Gas", true);

    c.displayInfo();
    std::cout << "\nRent for 3 days: $" << c.calculatePrice(3) << "\n\n";

    std::cout << c << "\n";  // using operator<<
}