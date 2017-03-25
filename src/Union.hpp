#ifndef UNION__HPP__
#define UNION__HPP__

#include <string>
#include "OperationElementaire.hpp"

using namespace std;

class Union : public OperationElementaire
{
public:
	Union(OperationElementaire*, OperationElementaire*);
	~Union();

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

#endif // UNION__HPP__
