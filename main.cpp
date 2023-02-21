#include <iostream>
#include <string>
#include <fstream>
#include "Programmer.hpp"
#include "Dept.hpp"

//TODO Off by one error for text file vs arr index

Department *g_depts[5];
Programmer *g_programmers[5];

void parseData(string filename){
    //Open the file
    ifstream file(filename);
    //create an array that will hold the data from the file as it stands
    //Its currently in columns, which is a pain to deal with, thats what this function is for
    string depts[5];
    for (int i = 0; i < 5; i++)
    {
        getline(file, depts[i]);
    }

    string programmers[5];
    for (int i = 0; i < 5; i++)
    {
        getline(file, programmers[i]);
    }


    //inverse the data into the global arrays
    for (int i = 0; i < 5; i++)
    {
        //Make a string that is the same length as the preferences, and fill it with spaces so we can access it like an array
        string dPrefs = "     "; //five spaces
        string pPrefs = "     "; 
        //2 at a time, write the first preference to dPrefs and pPrefs respectively, then the second preference, etc
        for (int j = 0; j < 5; j++)
        {
            dPrefs[j] = depts[j][i*2];
            pPrefs[j] = programmers[j][i*2];
        }
        
        //Add the new objects to the global arrays
        g_depts[i] = new Department(i, dPrefs);
        g_programmers[i] = new Programmer(i, pPrefs);

    }
}

bool shouldPair() {
    for (auto i = 0; i < 5; i++){
        if (!g_programmers[i]->isPaired()){
            return true;
        }
    }
    return false;
}

void match(int pID, int gID){
    //if the programmer is already paired, unpair them important for `shouldPair`
    if (g_programmers[pID]->isPaired()){
        g_programmers[pID]->getDept()->setPaired(false);
    }
    g_programmers[pID]->setDept(g_depts[gID]);
    g_programmers[pID]->setPaired();


    //if the programmer is already paired, unpair them important for `shouldPair`
    if (g_depts[gID]->isPaired()){
        g_depts[gID]->getProgrammer()->setPaired(false);
    }
    g_depts[gID]->setProgrammer(g_programmers[pID]);
    g_depts[gID]->setPaired();
}

int main(int argc, char const *argv[])
{   
    if (argc != 2){
        std::cout << "Usage: ./main <filename>" << std::endl;
        return 1;
    }
    string filename = argv[1];
    parseData(filename);

    //Use the Gale-Shapley algorithm to match the programmers and depts
    while (shouldPair() != 0){
        // for each programmer
       for (auto pID = 0; pID < 5; pID++)
       {
        // see if they are paired
        if (g_programmers[pID]->isPaired()){
            continue;
        }
        // if not, lets try to pair them
        int* prefs = g_programmers[pID]->getPrefs();
        for (auto j = 0; j < 5; j++){
            int gID = prefs[j];
            // if the dept hasn't been "proposed" to yet, pair them
            if (!g_depts[gID]->isPaired()){
                match(pID, gID); // hasn't been proposed to yet, must take it
                break;
            // if the dept has been proposed to, but prefers this programmer, pair them
            }else if (g_depts[gID]->wouldPrefer(pID)){
                match(pID, gID); // has been proposed to, but prefers this programmer
                break;
            }
        }
       }
       
    }

    //Print the results
    for (auto i = 0; i < 5; i++){
        std::cout << "Department #" << g_depts[i]->getID() + 1 << " will get Programmer #" << g_depts[i]->getProgrammer()->getID() + 1 << std::endl;
    }

    //Free the memory
    for (auto i = 0; i < 5; i++){
        delete g_depts[i];
        delete g_programmers[i];
    }
    return 0;
}
