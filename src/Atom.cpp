#include "Atom.hpp"

Atom::Atom(string code, int action, AtomType aType) : OperationElementaire("Atom") {
    this->code = code;
    this->action = action;
    this->aType = aType;
}

string Atom::getCode() {
    return this->code;
}

void Atom::setCode(string code) {
    this->code = code;
}

int Atom::getAction() {
    return this->action;
}

void Atom::setAction(int action) {
    this->action = action;
}

AtomType Atom::getAType() {
    return this->aType;
}

void Atom::setAType(AtomType aType) {
    this->aType = aType;
}

string Atom::toString(int profondeur) {
    return "--->" + this->nom + " " + this->code + " " + std::to_string(this->action) + " " + std::to_string(this->aType);
}

OperationElementaire* Atom::getLeft() {}
OperationElementaire* Atom::getRight() {}
OperationElementaire* Atom::getStare() {}
OperationElementaire* Atom::getUne() {}
