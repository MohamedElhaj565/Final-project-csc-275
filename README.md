# Final-project-csc-275
Hi guys, I will give you a simple idea to understand the mechanism of this project.
This Car Rental System is designed using full Object-Oriented Programming principles, so each part of the system is represented by its own class. The Vehicle class is an abstract base class that defines what every vehicle must have, while the Car class inherits from it and adds more details. We store all vehicles, customers, and rental contracts inside STL vectors, making it easy to add, search, and manage data.

When the system creates a rental, it uses polymorphism — meaning it treats all cars as Vehicle* pointers but still calls the correct overridden functions like calculatePrice() and displayInfo(). The CarRentalSystem class acts as the “manager” and handles the whole workflow: adding vehicles, registering customers, creating rentals, and listing active bookings.

Overall, the project shows how inheritance, encapsulation, pure virtual functions, operator overloading, and vectors all work together to form a clean and scalable OOP application.
Also i wnated to mention that you can test your class under the our tests comment in the main cpp. and i tried to put comments so you can understand what i did.
