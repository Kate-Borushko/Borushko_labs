#pragma once
#include <unordered_map>
#include <vector>
#include "Pipe.h"
#include "Station.h"
#include "Utils.h"
class GasTransmissionNetwork
{

public:
	void showConnection(const std::unordered_map<uint32_t, Pipe>&, const std::unordered_map<uint32_t, Station>&);

	void addConnection(std::unordered_map<uint32_t, Pipe>&, std::unordered_map<uint32_t, Station>&);

	void deleteConnection(std::unordered_map<uint32_t, Pipe>&, std::unordered_map<uint32_t, Station>&);

};

template<typename T>
uint32_t SearchId(const T& map, uint32_t id)
{
	if (map.find(id) != map.end()) return id;
	return -1;
}

