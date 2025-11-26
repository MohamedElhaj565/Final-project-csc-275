#include "Vehicle.h"

Vehicle::Vehicle(
    const std::string& plate,
    const std::string& make,
    const std::string& model,
    int year,
    double dailyRate)
        :plateNumber(plate),
        make(make),
        model(model),
        year(year),
        baseDailyRate(dailyRate),
        available(true){}


std::string Vehicle::getPlateNumber() const {
    return plateNumber;
}
std::string Vehicle::getMake() const {
    return make;
}
std::string Vehicle::getModel() const {
    return model;
}
int Vehicle::getYear() const {
    return year;
}
double Vehicle::getBaseDailyRate() const {
    return baseDailyRate;
}
bool Vehicle::isAvailable() const {
    return available;
}
void Vehicle::setAvailable(bool status) {
    available = status;
}