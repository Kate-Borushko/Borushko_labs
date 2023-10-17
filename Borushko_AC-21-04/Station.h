#pragma once
#include <cstdint>
#include <string>

class Station
{
	uint32_t stationID;
public:

	static uint32_t newStationID;

	std::string name;
	uint32_t numOfWorkshops, numOfWorkingWorkshops, efficiency;

	friend std::ostream& operator << (std::ostream& out, const Station& x);
	friend std::istream& operator >> (std::istream& in, Station& x);

	Station();

	uint32_t getStationID();
	void setStationID(uint32_t);
};

