#include "OperationElementaire.hpp"

OperationElementaire::OperationElementaire(string nom) {
	this->nom = nom;
}

OperationElementaire::~OperationElementaire() {}

string OperationElementaire::getNom() {
	return this->nom;
}

void OperationElementaire::setNom(string nom) {
	this->nom = nom;
}
