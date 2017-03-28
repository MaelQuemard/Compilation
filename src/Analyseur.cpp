#include "Analyseur.hpp"

Analyseur::Analyseur(map<string, OperationElementaire*> foret, Scanner* sc) {
    this->foret = foret;
    this->sc = sc;
    this->uniteLexicale = sc->scanG0();
}

bool Analyseur::analyseG0(OperationElementaire* op) {
    bool ana;
    if (op->getNom() == "Conc") {
        bool ana_tmp = analyseG0(op->getLeft());
        if (ana_tmp) {
            ana = analyseG0(op->getRight());
        } else {
            ana = false;
        }
    } else if (op->getNom() == "Union") {
        if (analyseG0(op->getLeft())) {
            ana = true;
        } else {
            ana = analyseG0(op->getRight());
        }
    } else if (op->getNom() == "Star") {
        ana = true;
        while (analyseG0(op->getStare())) {}
    } else if (op->getNom() == "Un") {
        ana = true;
        if (analyseG0(op->getUne())) {}
    } else if (op->getNom() == "Atom") {
        switch (op->getAType()) {
            // Cas Terminal
            case 0:
                if (op->getCode() == this->uniteLexicale["code"]) {
                    if (op->getAction() != 0) {
                        int actionType;
                        stringstream s;
                        s << this->uniteLexicale["action"];
                        s >> actionType;
                        AtomType aType = this->uniteLexicale["code"] == "IDNTER" ? NTER : TER;
                        G0Action(op, actionType, aType);
                    }
                    this->uniteLexicale = this->sc->scanG0();
                    ana = true;
                } else {
                    ana = false;
                }
                break;
            // Cas non terminal
            case 1:
                if (analyseG0(this->foret[op->getCode()])) {
                    if (op->getAction() != 0) {
                        int actionType1;
                        stringstream s1;
                        s1 << this->uniteLexicale["action"];
                        s1 >> actionType1;
                        AtomType aType = this->uniteLexicale["code"] == "IDNTER" ? NTER : TER;
                        G0Action(op, actionType1, aType);
                    }
                    ana = true;
                }
                break;
            default:
                ana = false;
                break;
        }
    }
    return ana;
}

void Analyseur::G0Action(OperationElementaire* op, int actionType, AtomType aType) {
    OperationElementaire *t1, *t2;
    switch (op->getAction()) {
        // Action 1 : créer arbre
        case 1:
            std::cout << "Action 1" << '\n';
            if (!this->s.empty()) {
                t1 = this->s.top();
                this->s.pop();
                if (!this->s.empty()) {
                    t2 = this->s.top();
                    this->s.pop();
                    this->foret[t2->getCode()] = t1;
                    std::cout << "MON CODE DE MON ARBRE : " << t2->getCode() << endl << "MA SUPER FORET DE " << t2->getCode() << endl << this->foret[t2->getCode()]->toString(0) << '\n';
                }
            }
            break;
        // Action 2 : Créer Terminal
        case 2:
            if (this->uniteLexicale["action"] != "") {
                this->s.push(new Atom(this->uniteLexicale["chaine"], actionType, aType));
            } else {
                this->s.push(new Atom(this->uniteLexicale["chaine"], 0, aType));
            }
            break;
        // Action 3 : Créer union
        case 3:
            if (!this->s.empty()) {
                t1 = this->s.top();
                this->s.pop();
                if (!this->s.empty()) {
                    t2 = this->s.top();
                    this->s.pop();
                    this->s.push(new Union(t1, t2));
                }
            }
            break;
        // Action 4 : Créer Conc
        case 4:
            if (!this->s.empty()) {
                t1 = this->s.top();
                this->s.pop();
                if (!this->s.empty()) {
                    t2 = this->s.top();
                    this->s.pop();
                    this->s.push(new Conc(t1, t2));
                }
            }
            break;
        // Action 5 : Créer terminal / Non terminal
        case 5:
            if (this->uniteLexicale["action"] != "") {
                this->s.push(new Atom(this->uniteLexicale["chaine"], actionType, aType));
            } else {
                this->s.push(new Atom(this->uniteLexicale["chaine"], 0, aType));
            }
            break;
        // Action 6 : Créer star
        case 6:
            if (!this->s.empty()) {
                t1 = this->s.top();
                this->s.pop();
                this->s.push(new Star(t1));
            }
            break;
        // Action 7 : Créer Un
        case 7:
            if (!this->s.empty()) {
                t1 = this->s.top();
                this->s.pop();
                this->s.push(new Un(t1));
            }
            break;
        // Default en cas d'erreur
        default:
            std::cout << "Default case" << '\n';
            break;
    }
}

bool Analyseur::analyseGPL(OperationElementaire* op) {
    bool ana;
    if (op->getNom() == "Conc") {
        bool ana_tmp = analyseGPL(op->getLeft());
        if (ana_tmp) {
            ana = analyseGPL(op->getRight());
        } else {
            ana = false;
        }
    } else if (op->getNom() == "Union") {
        if (analyseGPL(op->getLeft())) {
            ana = true;
        } else {
            ana = analyseGPL(op->getRight());
        }
    } else if (op->getNom() == "Star") {
        ana = true;
        while (analyseGPL(op->getStare())) {}
    } else if (op->getNom() == "Un") {
        ana = true;
        if (analyseGPL(op->getUne())) {}
    } else if (op->getNom() == "Atom") {
        switch (op->getAType()) {
            // Cas Terminal
            case 0:
                if (op->getCode() == this->uniteLexicale["code"]) {
                    if (op->getAction() != 0) {
                        int actionType;
                        stringstream s;
                        s << this->uniteLexicale["action"];
                        s >> actionType;
                        AtomType aType = this->uniteLexicale["code"] == "IDNTER" ? NTER : TER;
                        GPLAction(op, actionType, aType);
                    }
                    this->uniteLexicale = this->sc->scanGPL();
                    ana = true;
                } else {
                    ana = false;
                }
                break;
            // Cas non terminal
            case 1:
                if (analyseGPL(this->foret[op->getCode()])) {
                    if (op->getAction() != 0) {
                        int actionType1;
                        stringstream s1;
                        s1 << this->uniteLexicale["action"];
                        s1 >> actionType1;
                        AtomType aType = this->uniteLexicale["code"] == "IDNTER" ? NTER : TER;
                        GPLAction(op, actionType1, aType);
                    }
                    ana = true;
                }
                break;
            default:
                ana = false;
                break;
        }
    }
    return ana;
}

void Analyseur::GPLAction(OperationElementaire* op, int actionType, AtomType aType) {

}
