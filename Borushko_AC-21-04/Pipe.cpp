#include "Pipe.h"
#include <iostream>
#include <fstream>
#include "Utils.h"
#include <string>
#include <set>

uint32_t Pipe::newPipeID = 0;

std::istream& operator >> (std::istream& in, Pipe& x)
{
    std::cout << "Add pipe parameters: length, diameter, repair\n";
    std::cout << "Length:\n";
    getCorrect(x.length);
    std::cout << "Diameter:\n";
    x.diameter = getCorrectPipeDiameter();
    std::cout << "Repair:\n";
    x.repair = getInRange(0, 1);
    return in;
}

std::ofstream& operator << (std::ofstream& out, const Pipe& x)
{
    out << x.pipeID << std::endl << x.length << std::endl << x.diameter << std::endl << x.repair << std::endl << x.inStationID << std::endl << x.outStationID;
    return out;
}

std::ifstream& operator>>(std::ifstream& in, Pipe& x)
{
    in >> x.pipeID;
    in >> x.length;
    in >> x.diameter;
    in >> x.repair;
    in >> x.inStationID;
    in >> x.outStationID;
    return in;
}
std::ostream& operator << (std::ostream& out, const Pipe& x)
{
    out << "Pipe:\n";
    out << "ID: " << x.pipeID << " Length: " << x.length
        << " Diameter: " << x.diameter << " Repair: " << x.repair << std::endl
        << "Station ID out: " << x.outStationID << std::endl
        << "Station ID in: " << x.inStationID << std::endl;
    return out;
}

Pipe::Pipe()
{
    pipeID = ++newPipeID;
    length = 10.0;
    diameter = 500;
    repair = 0;
    inStationID = 0;
    outStationID = 0;
}

uint32_t Pipe::getPipeID() const
{
    return pipeID;
}

void Pipe::link(uint32_t newIn, uint32_t newOut)
{
    if (inStationID == 0 && outStationID == 0 && newOut != newIn)
    {
        inStationID = newIn;
        outStationID = newOut;
    }
    else
    {
        std::cout << "Error" << std::endl;
    }
}

void Pipe::clearLink()
{
    inStationID = 0;
    outStationID = 0;
}

bool Pipe::linked() const
{
    return inStationID > 0 && outStationID > 0;
}

bool Pipe::canBeUsed() const
{
    return inStationID > 0 && outStationID > 0 && repair == false;
}

void Pipe::showLink() const
{
    std::cout << "\nPipe's ID: " << pipeID << std::endl;
    std::cout << "Station's ID in: " << inStationID << std::endl;
    std::cout << "Station's ID out: " << outStationID << std::endl;
    std::cout << "Status: " << ((repair == true) ? "repair " : "work ") << std::endl;
}

uint32_t Pipe::getProductivity() const
{
    return round(10000 * sqrt(pow(double(diameter) / 1000, 5) / length));
}