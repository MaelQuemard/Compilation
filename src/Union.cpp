#include "Union.hpp"

Union::Union (OperationElementaire* left, OperationElementaire* right) : OperationElementaire("Union") {
	//super("Union");
	this->left = left;
	this->right = right;
}

OperationElementaire* Union::getLeft() {
	return this->left;
}

OperationElementaire* Union::getRight() {
	return this->right;
}

void Union::setLeft(OperationElementaire* left) {
	this->left = left;
}

void Union::setRight(OperationElementaire* right) {
	this->right = right;
}

string Union::toString(int profondeur) {
	string ret;
	for (int i = 0; i <= profondeur; ++i) {
		ret += "---";
	}
	return "--->" + this->nom + "\n" + ret + this->right->toString(profondeur+1) + "\n" + ret + this->left->toString(profondeur+1);
}

OperationElementaire* Union::getStare(){}
OperationElementaire* Union::getUne(){}
string Union::getCode(){}
int Union::getAction(){}
AtomType Union::getAType(){}
