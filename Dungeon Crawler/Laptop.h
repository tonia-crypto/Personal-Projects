#ifndef LAPTOP_H
#define LAPTOP_H

#include <iostream>
#include <fstream>
#include <string>

class Laptop{

    private:
    std::string Brand;
    double BatteryLife;
    bool MeetsBYODRequirements;

    public:
    Laptop(std::string Brand,double BatteryLife, bool MeetsBYODRequirements);
    std::string getBrand();
    double getBatteryLife();
    bool getMeetsBYODRequirements();


};

#endif