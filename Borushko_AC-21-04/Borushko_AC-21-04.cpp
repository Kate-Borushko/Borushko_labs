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

enum mainMenu { exitMenu, addPipe, addStation, viewObjects, editPipe, editStation, pipeSearch, stationSearch, save, download, deletePipe, deleteStation, packageEdit};

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
         << "10. Delete pipe \n11. Delete station \n"
         << "12. Package editing of pipes\n";
    cout << "\n";
}

//функции для изменения добавленных элементов

void EditPipeRepair(Pipe& x)
{
    cout << "Re-enter the 'under repair' parameter:" << endl;
    x.repair = getInRange(0, 1);
}
void editStationWorkshopsInUse(Station& x)
{
    cout << "Re-enter the number of workshops in use:" << endl;
    x.numOfWorkshopsInUse = getInRange(1, x.numOfWorkshops);
    x.efficiency = double(x.numOfWorkshopsInUse * 100) / x.numOfWorkshops;
}

void LoadStation(ifstream& fin, Station& s)
{
    uint32_t id;
    fin >> id;
    s.setStationID(id);
    fin >> ws;
    getline(fin, s.name);
    fin >> s.numOfWorkshops;
    fin >> s.numOfWorkshopsInUse;
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

//функции для работы с файлами

void SaveToFile(unordered_map<int, Pipe>& mP, unordered_map<int, Station>& mS)
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
                fout << s.getStationID() << std::endl << s.name << endl << s.numOfWorkshops << endl << s.numOfWorkshopsInUse << endl << s.efficiency << endl;
            }
        }
    }
    fout.close();
    cout << "Data is saved" << endl;
}

void DownloadFromFile(unordered_map<int, Pipe>& mP, unordered_map<int, Station>& mS)
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

//выбор и удаление объектов

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

void deleteOnePipe(unordered_map<int, Pipe>& mP)
{
    Pipe p = selectPipe(mP);
    mP.erase(p.getPipeID());
    cout << "Pipe is removed" << endl;
}

void deleteOneStaton(unordered_map<int, Station>& mS)
{
    Station s = selectStation(mS);
    mS.erase(s.getStationID());
    cout << "Station is removed" << endl;
}

//поиск по станциям

template<typename T>
using Filter1 = bool(*)(const Station& s, T parameter);

bool checkByName(const Station& s, string parameter)
{
    return s.name == parameter;
}

bool checkByNotWorkingWorkshops(const Station& s, double parameter)
{
    return (double((s.numOfWorkshops - s.numOfWorkshopsInUse) * 100) / s.numOfWorkshops) >= parameter;
}

template<typename T>
vector<uint32_t> findStationByFilter(unordered_map<int, Station>& mS, Filter1<T> f, T parameter)
{
    vector<uint32_t> result;

    for (auto& [sID, s] : mS)
    {
        if (f(s, parameter))
        {
            result.push_back(s.getStationID());
        }
    }

    if (result.empty())
    {
        cout << "There are no pipes with this parameter\n";
    }

    return result;
}

//поиск по трубам

template<typename T>
using Filter2 = bool(*)(const Pipe& p, T parameter);

bool checkByID(const Pipe& p, uint32_t parameter)
{
    return p.getPipeID() >= parameter;
}

bool checkByRepair(const Pipe& p, uint32_t parameter)
{
    return p.repair == parameter;
}

template<typename T>
vector<uint32_t> findPipeByFilter(unordered_map<int, Pipe>& mP, Filter2<T> f, T parameter)
{
    vector<uint32_t> result;

    for (auto& [pID, p] : mP)
    {
        if (f(p, parameter))
        {
            result.push_back(p.getPipeID());
        }
    }

    if (result.empty())
    {
        cout << "There are no pipes with this parameter\n";
    }

    return result;
}

vector<uint32_t> searchPipe(unordered_map<int, Pipe>& mP)
{
    vector<uint32_t> result{};
    cout << "Enter the search parameter: \n"
        << "1 - find pipe by IDs; \n"
        << "2 - find pipe by the repair\n";
    if (getInRange(1, 2) == 1)
    {
        uint32_t pID;
        cout << "Enter pipe IDs: ";
        getCorrect(pID);
        for (uint32_t i : findPipeByFilter(mP, checkByID, pID))
        {
            cout << mP[i];
        }
        result = findPipeByFilter(mP, checkByID, pID);
    }
    else
    {
        uint32_t repair;
        cout << "Enter marker of repair: ";
        repair = getInRange(0, 1);
        for (uint32_t i : findPipeByFilter(mP, checkByRepair, repair))
        {
            cout << mP[i];
        }
        result = findPipeByFilter(mP, checkByRepair, repair);
    }
    return result;
}

void PacketEditPipe(unordered_map<int, Pipe>& mP)
{
    vector<uint32_t> allResult;
    allResult = searchPipe(mP);
    cout << "Enter the edit parameter: \n"
        << "1: edit all find pipes; \n"
        << "2: edit some find pipes\n";
    if (getInRange(1, 2) == 1)
    {
        cout << "Enter the repair parameter: \n"
            << "1: all pipes are working; \n"
            << "2: all pipes are under repair\n";
        if (getInRange(1, 2) == 1)
        {
            for (auto& id : allResult)
                mP[id].repair = 1;
        }
        else
        {
            for (auto& id : allResult)
                mP[id].repair = 0;
        }
    }
    else
    {
        vector <int> someResult;
        while (true)
        {
            cout << "Enter pipe's id to edit or 0 to complete: ";
            uint32_t i;
            i = getInRange(0, *max_element(allResult.begin(), allResult.end()));
            if (i)
            {
                if (mP.find(i) == mP.end())
                    cout << "There is no pipe with this id\n";
                else
                    someResult.push_back(i);
            }
            else
                break;
        }
        cout << "Enter the repair parameter: \n"
            << "1: all pipes are working; \n"
            << "2: all pipes are under repair\n";
        if (getInRange(1, 2) == 1)
        {
            for (auto& id : someResult)
                mP[id].repair = 1;
        }
        else
        {
            for (auto& id : someResult)
                mP[id].repair = 0;
        }
    }
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
        operation = getInRange(0, 12);
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
            EditPipeRepair(selectPipe(manyPipes));
            break;

        case mainMenu::editStation:
            system("cls");
            editStationWorkshopsInUse(selectStation(manyStations));
            break;

        case mainMenu::save:
            system("cls");
            SaveToFile(manyPipes, manyStations);
            break;

        case mainMenu::download:
            system("cls");
            DownloadFromFile(manyPipes, manyStations);
            break;

        case mainMenu::pipeSearch:
            system("cls");
            searchPipe(manyPipes);
            break;

        case mainMenu::stationSearch:
        {
            system("cls");
            cout << "Enter the search parameter: \n"
                << "1: find station by name; \n"
                << "2: find station by the percentage of unused workshops\n";
            if (getInRange(1, 2) == 1)
            {
                string name;
                cout << "Enter station name: ";
                cin >> name;
                for (uint32_t i : findStationByFilter(manyStations, checkByName, name))
                {
                    cout << manyStations[i];
                }
            }
            else
            {
                double percent;
                cout << "Enter percent of not used workshops: ";
                getCorrect(percent);
                for (uint32_t i : findStationByFilter(manyStations, checkByNotWorkingWorkshops, percent))
                {
                    cout << manyStations[i];
                }
            }
            break;
        }
        case mainMenu::deletePipe:
            system("cls");
            deleteOnePipe(manyPipes);
            break;
        case mainMenu::deleteStation:
            system("cls");
            deleteOneStaton(manyStations);
            break;
        case mainMenu::packageEdit:
            system("cls");
            PacketEditPipe(manyPipes);
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
