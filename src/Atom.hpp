#ifndef ATOM__HPP__
#define ATOM__HPP__
#include <string>
#include "OperationElementaire.hpp"

using namespace std;

class Atom : public OperationElementaire
{
public:
	Atom(string, int, AtomType);
	~Atom();

    string getCode();
    void setCode(string);

    int getAction();
    void setAction(int);

    AtomType getAType();
    void setAType(AtomType);

	string toString(int);

	OperationElementaire* getLeft();
	OperationElementaire* getRight();
	OperationElementaire* getStare();
	OperationElementaire* getUne();

private:
    string code;
    int action;
    AtomType aType;
};

#endif // ATOM__HPP__
