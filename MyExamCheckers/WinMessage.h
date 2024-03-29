#pragma once
#include <iostream>
#include <windows.h>
using namespace std;
////////////////////////////////////////////////////////////////                WinMessage                ///////////////////////////////////////////////////////////////////////////
void WinMessage()
{
    //srand(time(0));

    int size = 100;
    char* str = new char[size] {'C', 'O', 'N', 'G', 'R', 'A', 'T', 'U', 'L', 'A', 'T', 'I', 'O', 'N', 'S', '!', '!', '!'};

    //int color = rand() % 8 + 30;
    int color = 37;

    cout << "\n\n\n\n";
    for (size_t i = 0; i < strlen(str); i++)
    {
        cout << "\033[" << color << "m";
        cout << "\t" << str[i] << " ";
        cout << "\033[0m";
        Sleep(100);
    }
    cout << "\n";
    delete[] str;
}