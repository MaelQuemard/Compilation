#ifndef __COMPILATEUR__HPP
#define __COMPILATEUR__HPP

#include "foretGenerateur.hpp"
#include "Analyseur.hpp"
#include "Scanner.hpp"
#include "Interpreteur.hpp"
#include <iostream>
#include <fstream>
#include <exception>
#include <map>

using namespace std;

class Compilateur
{
public:
    Compilateur();
    ~Compilateur();

    string readFile(string);
    string waitCommand();
    void executeCommand(string);

private:
    foretGenerateur* fg;
    Scanner* sc;
    Analyseur* analyseur;
    Interpreteur* interpreteur;

};

#endif // __COMPILATEUR__HPP
