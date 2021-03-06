#ifndef STAR__HPP__
#define STAR__HPP__
#include <string>
#include "OperationElementaire.hpp"

using namespace std;

class Star : public OperationElementaire
{
public:
	Star(OperationElementaire*);
	~Star();

	OperationElementaire* getStare();
	void setStare(OperationElementaire*);

	string toString(int);

	OperationElementaire* getLeft();
	OperationElementaire* getRight();
	OperationElementaire* getUne();
	string getCode();
	int getAction();
	AtomType getAType();

private:
	OperationElementaire* stare;
};

#endif // STAR__HPP__
