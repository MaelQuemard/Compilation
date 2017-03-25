#include "Un.hpp"

Un::Un (OperationElementaire* une) : OperationElementaire("Un") {
	//super("Un");
	this->une = une;
}

OperationElementaire* Un::getUne() {
	return this->une;
}

void Un::setUne(OperationElementaire* une) {
	this->une = une;
}

string Un::toString(int profondeur) {
	string ret;
	for (int i = 0; i <= profondeur; ++i) {
		ret += "---";
	}
	return "--->" + this->nom + "\n" + ret + this->une->toString(profondeur+1);
}

OperationElementaire* Un::getLeft(){}
OperationElementaire* Un::getRight(){}
OperationElementaire* Un::getStare(){}
string Un::getCode(){}
int Un::getAction(){}
AtomType Un::getAType(){}
