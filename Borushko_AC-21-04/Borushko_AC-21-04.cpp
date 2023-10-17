// Borushko_AC-21-04.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "Pipe.h"
#include "Utils.h"
#include "Station.h"
#include <unordered_map>
#include "Borushko_AC-21-04.h"

using namespace std;

enum mainMenu { exitMenu, addPipe, addStation, viewObjects, editPipe, editStation, save, download, pipeSearch, stationSearch };

void showMenu()
{
    cout << endl;
    cout << "______MENU______ \nSelect an option:\n";
    cout << "\n";
    cout << "0. Exit \n1. Add pipe" << endl
        << "2. Add station \n3. View all objects" << endl
        << "4. Edit pipe \n5. Edit station" << endl
        << "6. Pipe search\n7. Station search" << endl
        << "8. Save to file \n9. Download from file \n"
        << "10. Delete pipe \n11. Delete station \n";
    cout << "\n";
}

void editPipeRepair(Pipe& x)
{
    cout << "Re-enter the 'under repair' parameter:" << endl;
    x.repair = getInRange(0, 1);
}
void editStationWorkingWorkshops(Station& x)
{
    cout << "Re-enter the number of workshops in use:" << endl;
    x.numOfWorkingWorkshops = getInRange(1, x.numOfWorkshops);
    x.efficiency = double(x.numOfWorkingWorkshops * 100) / x.numOfWorkshops;
}

void LoadStation(ifstream& fin, Station& s)
{
    uint32_t id;
    fin >> id;
    s.setStationID(id);
    fin >> ws;
    getline(fin, s.name);
    fin >> s.numOfWorkshops;
    fin >> s.numOfWorkingWorkshops;
    fin >> s.efficiency;
}

void LoadPipe(ifstream& fin, Pipe& p)
{
    uint32_t id;
    fin >> id;
    p.setPipeID(id);
    fin >> p.length;
    fin >> p.diameter;
    fin >> p.repair;
}

void saveToFile(unordered_map<int, Pipe>& mP, unordered_map<int, Station>& mS)
{
    cout << "Enter the file name: ";
    string oFileName;
    cin >> ws;
    getline(cin, oFileName);
    oFileName = oFileName + ".txt";
    ofstream fout;
    fout.open(oFileName);
    if (!fout.is_open())
        cerr << "The file cannot be opened\n";
    else
    {
        if (mP.size() != 0)
        {
            for (auto& [pID, p] : mP)
            {
                fout << "pipe" << endl;
                fout << p.getPipeID() << std::endl << p.length << std::endl << p.diameter << std::endl << p.repair << std::endl;
            }

        }
        if (mS.size() != 0)
        {
            for (auto& [sID, s] : mS)
            {
                fout << "station" << endl;
                fout << s.getStationID() << std::endl << s.name << endl << s.numOfWorkshops << endl << s.numOfWorkingWorkshops << endl << s.efficiency << endl;
            }

        }
    }
    fout.close();
    cout << "Data is saved" << endl;
}

void downloadFromFile(unordered_map<int, Pipe>& mP, unordered_map<int, Station>& mS)
{
    Pipe p;
    Station s;
    cout << "Enter the file name (.txt): ";
    string iFileName;
    cin >> ws;
    getline(cin, iFileName);
    iFileName = iFileName + ".txt";
    ifstream fin;
    fin.open(iFileName);
    if (!fin.is_open())
        cerr << "The file is not found\n";
    else
    {
        while (!fin.eof())
        {
            string line;
            fin >> ws;
            getline(fin, line);
            if (line == "station")
            {
                LoadStation(fin, s);
                mS.insert({ s.getStationID(), s });
            }

            if (line == "pipe")
            {
                LoadPipe(fin, p);
                mP.insert({ p.getPipeID(), p });
            }
        }

        cout << "Data is uploaded" << endl;
        fin.close();
    }
}

Pipe& selectPipe(unordered_map<int, Pipe>& mP)
{
    cout << "Enter pipe ID: ";
    uint32_t userID;
    getCorrect(userID);
    while (mP.find(userID) == mP.end())
    {
        cout << "There is no pipe with this ID\n";
        cout << "Enter pipe ID: ";
        getCorrect(userID);
    }
    return mP[userID];
}

Station& selectStation(unordered_map<int, Station>& mS)
{
    cout << "Enter station ID: ";
    uint32_t userID;
    getCorrect(userID);
    while (mS.find(userID) == mS.end())
    {
        cout << "There is no station with this ID\n";
        cout << "Enter station ID: ";
        getCorrect(userID);
    }
    return mS[userID];
}

int main()
{
    unordered_map<int, Pipe> manyPipes;
    unordered_map<int, Station> manyStations;

    while (true)
    {
        showMenu();
        cout << "Enter an operation: ";
        uint32_t operation;
        operation = getInRange(0, 9);
        switch (operation)
        {
        case mainMenu::exitMenu:
            exit(0);
            break;
        case mainMenu::addPipe:
        {
            system("cls");
            Pipe pipe;
            cin >> pipe;
            manyPipes.insert({ pipe.getPipeID(), pipe });
            break;
        }
        case mainMenu::addStation:
        {
            system("cls");
            Station station;
            cin >> station;
            manyStations.insert({ station.getStationID(), station });
            break;
        }
        case mainMenu::viewObjects:
        {
            system("cls");
            if (manyPipes.size() != 0)
            {
                for (const auto& [pID, p] : manyPipes)
                {
                    cout << p << endl;
                }
            }
            if (manyStations.size() != 0)
            {
                for (const auto& [sID, s] : manyStations)
                {
                    cout << s << endl;
                }
            }
            break;
        }  
        case mainMenu::editPipe:
            system("cls");
            editPipeRepair(selectPipe(manyPipes));
            break;

        case mainMenu::editStation:
            system("cls");
            editStationWorkingWorkshops(selectStation(manyStations));
            break;

        case mainMenu::save:
            system("cls");
            saveToFile(manyPipes, manyStations);
            break;

        case mainMenu::download:
            system("cls");
            downloadFromFile(manyPipes, manyStations);
            break;

        case mainMenu::pipeSearch:
            break;

        case mainMenu::stationSearch:
            break;
        }
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
