#ifndef PROGRAM_H
#define PROGRAM_H

#include "LinkList.h"
#include <iostream>
using namespace std;

class Program
{
private:
    const int ID;
    LinkList<int> MemoryManager;
public:
    Program(const int&);
    Program& operator=(const Program&);
    bool operator==(const int&) const;
    friend bool operator==(const int&,const Program&);
    friend ostream& operator<<(ostream&,Program&);
    void AccessPage(const int&);
    void Deletepage();
    ~Program();
};

//---------------------------------------------------------
//                  Program Declearation
//---------------------------------------------------------

Program::Program(const int& id) : ID(id){}

Program& Program::operator=(const Program& other)
{
    return *this;
}

bool Program::operator==(const int& key) const
{
    return key == ID;
}

bool operator==(const int& key,const Program& program)
{
    return key == program.ID;
}

ostream& operator<<(ostream& out,Program& p)
{
    out << "Program ID : " << p.ID << endl;
    out << "Page List : ";
    out << p.MemoryManager << endl;

    return out;
}

void Program::AccessPage(const int& data)
{
    LinkList<int>::ListIterator it = MemoryManager.ReturnPrevious(data);
    
    if(it != nullptr)
        MemoryManager.MovetoHead(it);
    else
        MemoryManager.AddtoHead(data);
}

void Program::Deletepage()
{
    MemoryManager.DeleteTail();
}

Program::~Program(){}

#endif