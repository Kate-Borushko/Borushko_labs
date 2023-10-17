#pragma once
#include <cstdint>
#include <iostream>
class Pipe
{
	uint32_t pipeID;
public:

	static uint32_t newPipeID;

	double length, diameter;
	uint32_t repair;

	friend std::ostream& operator << (std::ostream& out, const Pipe& x);
	friend std::istream& operator >> (std::istream& in, Pipe& x);

	Pipe();

	uint32_t getPipeID() const;
	void setPipeID(uint32_t);
};

