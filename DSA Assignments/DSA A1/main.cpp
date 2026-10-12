#include <iostream>
using namespace std;

#include "MemoryManager.h"

int main()
{
    Memory_Manager M1;

    M1.StartProgram(1);   
    M1.AccessProgram(1,1);
    M1.AccessProgram(1,9);
    M1.AccessProgram(1,7);
    M1.AccessProgram(1,6);
    M1.AccessProgram(1,4);
    M1.AccessProgram(1,5);
    M1.PrintProgram(1);

    M1.StartProgram(2);
    M1.AccessProgram(2,5);
    M1.AccessProgram(2,4);
    M1.AccessProgram(2,7);
    M1.AccessProgram(2,5);
    M1.AccessProgram(2,4);
    M1.PrintProgram(2);
    
    M1.StartProgram(3);
    M1.AccessProgram(3,8);
    M1.AccessProgram(3,2);
    M1.AccessProgram(3,4);
    M1.AccessProgram(3,5);
    M1.AccessProgram(3,2);
    M1.AccessProgram(3,4);
    M1.PrintProgram(3);

    cout << "Before List 2 Delete \n\n";
    M1.Print();
    
    M1.EndProgram(2);

    cout << "After List 2 Delete \n\n";
    M1.Print();
    
}