#include <string>
#include <regex>
#include <map>
#include <iostream>
#include "OperationElementaire.hpp"
#include "Atom.hpp"
#include "Conc.hpp"
#include "Star.hpp"
#include "Union.hpp"

using namespace std;

class foretGenerateur
{
public:

	foretGenerateur();
	~foretGenerateur();

    OperationElementaire* genA1();
    OperationElementaire* genA2();
    OperationElementaire* genA3();
    OperationElementaire* genA4();
    OperationElementaire* genA5();
	OperationElementaire* genA6();

	map<string, OperationElementaire*> getForet();

private:
	map<string, OperationElementaire*> foret;
};
