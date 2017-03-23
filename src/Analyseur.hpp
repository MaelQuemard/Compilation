#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Scanner.hpp"
#include "OperationElementaire.hpp"
#include <stack>
#include "Atom.hpp"

using namespace std;

class Analyseur
{
public:

	Analyseur(map<string, OperationElementaire*>, Scanner*);
	~Analyseur();
    bool analyse(OperationElementaire*);
	void G0Action(OperationElementaire*);

private:
	map<string, OperationElementaire*> foret;
	Scanner* sc;
	map<string, string> uniteLexicale;
	stack<OperationElementaire*> s;

};
