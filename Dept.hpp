#ifndef DEPT_H
#define DEPT_H
using namespace std;
#include <string>

class Programmer; 
class Department
{
private:
    const int id;
    Programmer* programmer;
    bool paired;
    int prefs[5];
public:
    Department(int id, string prefs);
    ~Department();
    int * getPrefs();
    Programmer* getProgrammer();
    void setPaired(bool a);
    void setPaired();
    bool wouldPrefer(int pID);
    void setProgrammer(Programmer* prog);
    bool isPaired();
    int   getID();
};

Department::Department(int id, string prefs) : id(id)
{
    for(int i = 0; i < 5; i++)
    {
        //We subtract '1' because the input is going to be the ASCII value of the number, so '1' is actually '49'
        //We want the id to match with its arr index, so we subtract '1' instead of '0'
        //So in this case '5' - '0' = 5, but '5' - '1' = 4
        this->prefs[i] = prefs[i*2] - '1'; 
    }
    paired = false;
}
int * Department::getPrefs()
{
    return prefs;
}
int Department::getID()
{
    return id;
}
Programmer* Department::getProgrammer()
{
    return this->programmer;
}
void Department::setProgrammer(Programmer* prog){
    this->programmer = prog;
}
bool Department::isPaired()
{
    return this->paired;
}
void Department::setPaired(bool a)
{
    this->paired = a;
}
void Department::setPaired()
{
    this->paired = true;
}
bool Department::wouldPrefer(int pID){
    for (auto i = 0; i < 5; i++){
        if (this->prefs[i] == pID)
            return true;
        else if (this->prefs[i] == this->programmer->getID())
            return false;
    }
    return false;
}
Department::~Department()
{
    this->programmer = nullptr;
}
#endif