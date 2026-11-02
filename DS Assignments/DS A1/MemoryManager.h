#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "Program.h"
#include "LinkList.h"
#include <iostream>
using namespace std;

class Memory_Manager
{
private:
    LinkList<Program> Memory;
public:
    Memory_Manager();
    void AccessProgram(const int&,const int&);
    void StartProgram(const int&);
    void EndProgram(const int&);
    void Print();
    void PrintProgram(const int&);
    ~Memory_Manager();

};

//---------------------------------------------------------
//              Memory Manager Declearation
//---------------------------------------------------------

Memory_Manager::Memory_Manager(){}

void Memory_Manager::StartProgram(const int& Programid)
{
    Memory.AddtoTail(Programid);
}
void Memory_Manager::AccessProgram(const int& Programid,const int& PageId)
{
    LinkList<Program>::ListIterator it = Memory.SearchByID(Programid);
    
    if(it != nullptr)
    {
        (*it).AccessPage(PageId);
    }
    else
    {
        cout << "Error::Program Not Found" << endl;
        return;
    }


}

void Memory_Manager::EndProgram(const int& key)
{
    LinkList<Program>::ListIterator it = Memory.Begin(),previous = Memory.Begin();
    if(it.IsNull())
    {
        cout << "Error::Program not Found with ID : " << key << endl;
        return;
    }
    it++;

    while(!it.IsNull())
    {
        if(*it == key)
        {
            Memory.DeleteAfter(previous);
            return;
        }
        it++;
        previous++;
    }

    if(!it)
        cout << "Error::Program not Found with ID : " << key << endl;

}

void Memory_Manager::Print()
{
    cout << "Program List :: \n" << Memory << endl;
}

void Memory_Manager::PrintProgram(const int& pid)
{
    LinkList<Program>::ListIterator it = Memory.SearchByID(pid);

    cout << *it << endl;
}

Memory_Manager::~Memory_Manager()
{}

#endif
