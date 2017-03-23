#ifndef OperationElementaire__HPP__
#define OperationElementaire__HPP__

#include <string>

using namespace std;
enum AtomType { TER, NTER };
class OperationElementaire
{
public:
	OperationElementaire(string);
	~OperationElementaire();

	string nom;

	string getNom();
	void setNom(string);

	virtual string toString(int) = 0;
	virtual OperationElementaire* getLeft() = 0;
	virtual OperationElementaire* getRight() = 0;
	virtual OperationElementaire* getStare() = 0;
	virtual OperationElementaire* getUne() = 0;
	virtual string getCode() = 0;
	virtual int getAction() = 0;
	virtual AtomType getAType() = 0;

private:

};

#endif
