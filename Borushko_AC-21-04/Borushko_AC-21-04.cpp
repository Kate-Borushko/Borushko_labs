// Borushko_AC-21-04.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

enum mainMenu { exitMenu, addPipe, addStation, viewObjects, editPipe, editStation, save, download };

struct pipe
{
    double length, diameter;
    uint32_t repair;
};

struct station
{
    string name;
    uint32_t numOfWorkshops, numOfWorkingWorkshops, efficiency;
};

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

uint32_t getUInt()
{
    uint32_t x;
    while ((cin >> x).fail() || x == 0)
    {
        cout << "Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return x;
}

double_t getDouble()
{
    double_t x;
    while ((cin >> x).fail() || x <= 0)
    {
        cout << "Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return x;
}

uint32_t getInRange(uint8_t x1, uint8_t x2)
{
    uint32_t x;
    while ((cin >> x).fail() || x1 > x || x > x2)
    {
        cout << "Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return x;
}

void addPipes(pipe& x)
{
    cout << "Add pipe parameters: length, diameter, repair\n";
    cout << "Length:\n";
    x.length = getDouble();
    cout << "Diameter:\n";
    x.diameter = getDouble();
    cout << "Repair:\n";
    x.repair = getInRange(0, 1);
}

void addStations(station& x)
{
    cout << "Add compressor station parameters:\nname, number of workshops, number of workshops in use, efficiency \n";
    cout << "Name:\n";
    cin >> ws;
    getline(cin, x.name);
    cout << "Number of workshops:\n";
    x.numOfWorkshops = getUInt();
    cout << "Number of workshops in use:\n";
    x.numOfWorkingWorkshops = getInRange(0, x.numOfWorkshops);
    x.efficiency = double(x.numOfWorkingWorkshops * 100) / x.numOfWorkshops;
}

void viewPipes(const pipe& x)
{
    cout << "Pipe:\n";
    cout << "Length: " << x.length << " Diameter: " << x.diameter << " Repair: " << x.repair << endl;
}

void viewStations(const station& x)
{
    cout << "Station:\n";
    cout << "Name: " << x.name << "\nNumber of workshops: " << x.numOfWorkshops << "\nNumber of workshops in use: " << x.numOfWorkingWorkshops << "\nEfficiency: " << x.efficiency << endl;
}

void editPipeRepair(pipe& x)
{
    cout << "Re-enter the 'under repair' parameter:" << endl;
    x.repair = getInRange(0, 1);
}

void editStationWorkingWorkshops(station& x)
{
    cout << "Re-enter the number of workshops in use:" << endl;
    x.numOfWorkingWorkshops = getInRange(1, x.numOfWorkshops);
    x.efficiency = double(x.numOfWorkingWorkshops * 100) / x.numOfWorkshops;
}

void saveToFile(const pipe& p, const station& s)
{
    cout << "Enter the file name: ";
    string oFileName;
    cin >> ws;
    getline(cin, oFileName);
    oFileName = oFileName + ".txt";
    ofstream fout;
    fout.open(oFileName);
    if (!fout.is_open())
        cerr << "File cannot be opened\n";
    else
    {
        string sFlag, pFlag;
        if (!(s.numOfWorkshops == 0))
        {
            fout << "station" << endl << s.name << endl << s.numOfWorkshops << endl << s.numOfWorkingWorkshops << endl << s.efficiency << endl;
        }

        if (!(p.diameter == 0))
        {
            fout << "pipe" << endl << p.length << endl << p.diameter << endl << p.repair << endl;
        }
    }

    fout.close();
    cout << "Data is saved" << endl;
}

void downloadFromFile(pipe& p, station& s)
{
    cout << "Enter the file name (.txt): ";
    string iFileName;
    cin >> ws;
    getline(cin, iFileName);
    iFileName = iFileName + ".txt";
    ifstream fin;
    fin.open(iFileName);
    if (!fin.is_open())
        cerr << "The file cannot be opened\n";
    else
    {
        while (!fin.eof())
        {
            string line;
            fin >> ws;
            getline(fin, line);
            if (line == "station")
            {
                fin >> ws;
                getline(fin, s.name);
                fin >> s.numOfWorkshops;
                fin >> s.numOfWorkingWorkshops;
                fin >> s.efficiency;
            }

            if (line == "pipe")
            {
                fin >> p.length;
                fin >> p.diameter;
                fin >> p.repair;
            }
        }

        cout << "Data is uploaded" << endl;

        fin.close();
    }
}

int main()
{
    pipe pipe1{};
    station station1{};

    while (true)
    {
        showMenu();
        cout << "Enter an operation: ";
        uint32_t operation;
        operation = getInRange(0, 7);

        switch (operation)
        {
        case mainMenu::exitMenu:
            exit(0);
            break;
        case mainMenu::addPipe:
            system("cls");
            addPipes(pipe1);
            break;
        case mainMenu::addStation:
            system("cls");
            addStations(station1);
            break;
        case mainMenu::viewObjects:
            system("cls");
            viewPipes(pipe1);
            viewStations(station1);
            cout << "\n";
            break;
        case mainMenu::editPipe:
            system("cls");
            editPipeRepair(pipe1);
            break;
        case mainMenu::editStation:
            system("cls");
            editStationWorkingWorkshops(station1);
            break;
        case mainMenu::save:
            system("cls");
            saveToFile(pipe1, station1);
            break;
        case mainMenu::download:
            system("cls");
            downloadFromFile(pipe1, station1);
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
