#ifndef __ANALYSEUR__HPP
#define __ANALYSEUR__HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Scanner.hpp"
#include "OperationElementaire.hpp"
#include <stack>
#include "Atom.hpp"
#include "Union.hpp"
#include "Conc.hpp"
#include "Un.hpp"
#include "Star.hpp"

using namespace std;

enum code { AFF, LDA, LDV, LDC, JMP, JIF, JSR, RSR, SUP, SUPE, INF, INFE, EG, DIFF, AND, OR, NOT, ADD, SUB, DIV, MULT, NEG, INC, DEC, RD, RDLN, WRT, WRTLN, STOP };

class Analyseur
{
public:

	Analyseur(map<string, OperationElementaire*>, Scanner*);
	~Analyseur();
    bool analyseG0(OperationElementaire*);
	void G0Action(OperationElementaire*, int, AtomType);

	bool analyseGPL(OperationElementaire*);
	void GPLAction(OperationElementaire*, int, AtomType);
	void setUnitelexicale();
	map<string, OperationElementaire*> getForet();
	int stringToInt(string);

	vector<int> getPCode();
	vector<int> getPilex();

	void setNameProg(string);

private:
	map<string, OperationElementaire*> foret;
	Scanner* sc;
	map<string, string> uniteLexicale;
	stack<OperationElementaire*> s;

	vector<int> p_code;
	vector<int> pilex;
	map<string, int> itab;

	string valeurEntier = "";
	string valeurOperateur = "";
	string valeurOperateurMath = "";

	string nameProg;

};

#endif // __ANALYSEUR__HPP
