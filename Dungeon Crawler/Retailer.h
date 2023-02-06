#ifndef RETAILER_H
#define RETAILER_H

#include <iostream>
#include <fstream>
#include <string>

class Retailer{
    private:
    std::string Name;
    std::vector<int> Laptop();

    public:
    Retailer(std::string Name);
    std::string getName() const;
    void addLaptop(Laptop newLaptop);

};

#endif
