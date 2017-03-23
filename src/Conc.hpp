#include <string>
#include "OperationElementaire.hpp"

using namespace std;

class Conc : public OperationElementaire
{
public:
	Conc(OperationElementaire*, OperationElementaire*);
	~Conc();

	OperationElementaire* getLeft();
	void setLeft(OperationElementaire*);

	OperationElementaire* getRight();
	void setRight(OperationElementaire*);

	string toString(int);

	OperationElementaire* getStare();
	OperationElementaire* getUne();
	string getCode();
	int getAction();
	AtomType getAType();

private:
	OperationElementaire* left;
	OperationElementaire* right;
};
