#pragma once
#include "GasTransmissionNetwork.h"
#include "Pipe.h"
#include "Station.h"
#include "Utils.h"
#include <iostream>
#include <unordered_map>
#include <vector>

void GasTransmissionNetwork::showConnection(const std::unordered_map<uint32_t, Pipe>& mP, const std::unordered_map<uint32_t, Station>& mS)
{
    if (mP.size() > 0 && mS.size() > 1)
    {
        for (auto& [i, p] : mP)
            if (p.linked())
                p.showLink();
    }
    else
        std::cout << "There are no pipes or stations" << std::endl;
}

void GasTransmissionNetwork::addConnection(std::unordered_map<uint32_t, Pipe>&, std::unordered_map<uint32_t, Station>&)
{

}

void GasTransmissionNetwork::deleteConnection(std::unordered_map<uint32_t, Pipe>& mP, std::unordered_map<uint32_t, Station>& mS)
{
    if (mP.size() > 0 && mS.size() > 1)
    {
        std::cout << "Enter pipe id: " << std::endl;
        uint32_t pipeId = SearchId(mP, getCorrect(pipeId));
        if (pipeId != -1 && mP[pipeId].linked())
        {
            mP[pipeId].clearLink();
            std::cout << "Pipe and stations are disconnected\n";
        }
        else
            std::cout << "There are no pipes with this id or pipe isn't connected" << std::endl;
    }
    else
        std::cout << "There are no pipes or stations" << std::endl;
}