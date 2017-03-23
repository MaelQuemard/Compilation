#include "Conc.hpp"

Conc::Conc(OperationElementaire* left, OperationElementaire* right) : OperationElementaire("Conc") {
	//super("Conc");
	this->left = left;
	this->right = right;
}

OperationElementaire* Conc::getLeft() {
	return this->left;
}

OperationElementaire* Conc::getRight() {
	return this->right;
}

void Conc::setLeft(OperationElementaire* left) {
	this->left = left;
}

void Conc::setRight(OperationElementaire* right) {
	this->right = right;
}

string Conc::toString(int profondeur) {
	string ret;
	for (int i = 0; i <= profondeur; ++i) {
		ret += "---";
	}
	return "--->" + this->nom + "\n" + ret + this->right->toString(profondeur+1) + "\n" + ret + this->left->toString(profondeur+1);
}

OperationElementaire* Conc::getStare(){}
OperationElementaire* Conc::getUne(){}
string Conc::getCode(){return NULL;}
int Conc::getAction(){}
AtomType Conc::getAType(){}
