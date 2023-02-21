#ifndef PROGRAMMER_H
#define PROGRAMMER_H
#include <string>
using namespace std;
class Department; 
class Programmer
{
private:
    const int id;
    Department* dept;
    bool paired;
    int prefs[5];
public:
    Programmer(int id, string prefs);
    ~Programmer();
    int * getPrefs();
    Department* getDept();
    void setPaired(bool a);
    void setPaired();
    void setDept(Department* dept);
    bool isPaired();
    int   getID();
};

Programmer::Programmer(int id, string prefs) : id(id)
{
    for(int i = 0; i < 5; i++)
    {
        //We subtract '1' because the input is going to be the ASCII value of the number, so '1' is actually '49'
        //We want the id to match with its arr index, so we subtract '1' instead of '0'
        //So in this case '5' - '0' = 5, but '5' - '1' = 4
        this->prefs[i] = prefs[i] - '1'; 

    }
    paired = false;
}
int * Programmer::getPrefs()
{
    return prefs;
}
int Programmer::getID()
{
    return id;
}
Department* Programmer::getDept()
{
    return this->dept;
}
void Programmer::setDept(Department* dept){
    this->dept = dept;
}
bool Programmer::isPaired()
{
    return this->paired;
}
void Programmer::setPaired(bool a){
    this->paired = a;
}
void Programmer::setPaired(){
    this->paired = true;
}
Programmer::~Programmer()
{
}
#endif