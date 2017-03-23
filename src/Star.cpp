#include "Star.hpp"

Star::Star (OperationElementaire* stare) : OperationElementaire("Star") {
	//super("Star");
	this->stare = stare;
}

OperationElementaire* Star::getStare() {
	return this->stare;
}

void Star::setStare(OperationElementaire* stare) {
	this->stare = stare;
}

string Star::toString(int profondeur) {
	string ret;
	for (int i = 0; i <= profondeur; ++i) {
		ret += "---";
	}
	return "--->" + this->nom + "\n" + ret + this->stare->toString(profondeur+1);
}

OperationElementaire* Star::getLeft(){}
OperationElementaire* Star::getRight(){}
OperationElementaire* Star::getUne(){}
string Star::getCode(){}
int Star::getAction(){}
AtomType Star::getAType(){}
