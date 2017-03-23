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

private:
	OperationElementaire* une;
};
