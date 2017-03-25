#ifndef UN__HPP__
#define UN__HPP__

#include <string>
#include "OperationElementaire.hpp"

using namespace std;

class Un : public OperationElementaire
{
public:
	Un(OperationElementaire*);
	~Un();

    OperationElementaire* getUne();
	void setUne(OperationElementaire*);

	string toString(int);
	OperationElementaire* getLeft();
	OperationElementaire* getRight();
	OperationElementaire* getStare();
	string getCode();
	int getAction();
	AtomType getAType();

private:
	OperationElementaire* une;
};

#endif // UN__HPP__
