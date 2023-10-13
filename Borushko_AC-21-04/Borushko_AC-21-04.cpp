﻿// Borushko_AC-21-04.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;


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

int main()
{
    showMenu();
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