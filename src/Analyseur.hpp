#include <string>
#include <iostream>
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

class Analyseur
{
public:

	Analyseur(map<string, OperationElementaire*>, Scanner*);
	~Analyseur();
    bool analyseG0(OperationElementaire*);
	void G0Action(OperationElementaire*, int, AtomType);

	bool analyseGPL(OperationElementaire*);
	void GPLAction(OperationElementaire*, int, AtomType);

private:
	map<string, OperationElementaire*> foret;
	Scanner* sc;
	map<string, string> uniteLexicale;
	stack<OperationElementaire*> s;

};
