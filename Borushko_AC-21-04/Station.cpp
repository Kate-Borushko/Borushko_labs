#include "Station.h"
#include <iostream>
#include <fstream>
#include "Utils.h"

uint32_t Station::newStationID = 0;

std::istream& operator >> (std::istream& in, Station& x)
{
    std::cout << "Add compressor station parameters:\nName, number of workshops, number of workshops in use, efficiency: \n";
    std::cout << "Name:\n";
    in >> std::ws;
    getline(in, x.name);
    std::cout << "Number of workshops:\n";
    getCorrect(x.numOfWorkshops);
    std::cout << "Number of workshops in use:\n";
    x.numOfWorkshopsInUse = getInRange(0, x.numOfWorkshops);
    x.efficiency = double(x.numOfWorkshopsInUse * 100) / x.numOfWorkshops;
    return in;
}

std::ostream& operator << (std::ostream& out, const Station& x)
{
    out << "Station:\n";
    out << "ID: " << x.stationID << " Name: " << x.name << " Number of workshops: " << x.numOfWorkshops << std::endl
        << "Number of workshops in use: " << x.numOfWorkshopsInUse << " Efficiency: " << x.efficiency << std::endl;
    return out;
}

std::ifstream& operator>>(std::ifstream& in, Station& x)
{
    in >> x.stationID;
    in >> std::ws;
    getline(in, x.name);
    in >> x.numOfWorkshops;
    in >> x.numOfWorkshopsInUse;
    in >> x.efficiency;
    in >> x.connection;
    return in;
}

std::ofstream& operator << (std::ofstream& out, Station& x)
{
    out << x.stationID << std::endl << x.name << std::endl << x.numOfWorkshops << std::endl
        << x.numOfWorkshopsInUse << std::endl << x.efficiency << std::endl << x.connection;
    return out;
}

Station::Station()
{
    stationID = ++newStationID;
    name = "Unknown";
    numOfWorkshops = 10;
    numOfWorkshopsInUse = 10;
    efficiency = 100;
    connection = false;
}

uint32_t Station::getStationID()
{
    return stationID;
}

void Station::createLink()
{
    if (!connection)
        connection = true;
}

void Station::clearLink()
{
    connection = false;
}

bool Station::linked()
{
    return connection;
}
