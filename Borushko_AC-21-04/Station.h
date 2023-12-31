#pragma once
#include <cstdint>
#include <string>

class Station
{
	uint32_t stationID;
public:

	static uint32_t newStationID;

	std::string name;
	uint32_t numOfWorkshops, numOfWorkshopsInUse, efficiency;
	bool connection;

	friend std::ostream& operator << (std::ostream& out, const Station& x);
	friend std::istream& operator >> (std::istream& in, Station& x);
	friend std::ofstream& operator << (std::ofstream& out, Station& x);
	friend std::ifstream& operator >> (std::ifstream& in, Station& x);

	Station();

	uint32_t getStationID();
	void createLink();
	void clearLink();
	bool linked();
};

