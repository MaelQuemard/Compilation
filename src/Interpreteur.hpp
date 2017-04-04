#ifndef __INTERPRETEUR__HPP
#define __INTERPRETEUR__HPP

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <fstream>
#include "Analyseur.hpp"

using namespace std;

class Interpreteur
{
public:
    Interpreteur ();
    virtual ~Interpreteur ();

    void execute (vector<int>, vector<int>);
    void interprete (int);
    vector<int> getPilex();

private:
    vector<int> p_code;
    vector<int> pilex;
    int c0;
    int spx;
};

#endif // __INTERPRETEUR__HPP
