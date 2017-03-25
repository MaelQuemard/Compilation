#include "Analyseur.hpp"

Analyseur::Analyseur(map<string, OperationElementaire*> foret, Scanner* sc) {
    this->foret = foret;
    this->sc = sc;
    this->uniteLexicale = sc->scan();
}

bool Analyseur::analyse(OperationElementaire* op) {
    bool ana;
    /*for (int i = 0; i < this->sc->dicot.size(); i++) {
        std::cout << "DICOT[" << i << "]" << this->sc->dicot.at(i) << '\n';
    }
    for (int i = 0; i < this->sc->dicont.size(); i++) {
        std::cout << "DICONT[" << i << "]" << this->sc->dicont.at(i) << '\n';
    }*/
    if (op->getNom() == "Conc") {
        std::cout << "Conc" << '\n';
        std::cout << "OP LEFT :: " << op->getLeft()->getNom() << '\n';
        bool ana_tmp = analyse(op->getLeft());
        std::cout << "ana_tmp : -----------------> : "<< ana_tmp << '\n';
        if (ana_tmp) {
            std::cout << "Vrai Conc : " << this->uniteLexicale["code"] << '\n';
            ana = analyse(op->getRight());
        } else {
            //std::cout << "Op->code : " << op->getCode() << '\n';
            std::cout << "Faux Conc : " << this->uniteLexicale["code"] << '\n';
            ana = false;
        }
    } else if (op->getNom() == "Union") {
        std::cout << "Union" << '\n';
        if (analyse(op->getLeft())) {
            std::cout << "Vrai Union" << '\n';
            ana = true;
        } else {
            std::cout << "Faux Union" << '\n';
            ana = analyse(op->getRight());
        }
    } else if (op->getNom() == "Star") {
        std::cout << "Star" << '\n';
        while (analyse(op->getStare())) {
            std::cout << "Vrai Stare" << '\n';
            ana = true;
        }
    } else if (op->getNom() == "Un") {
        std::cout << "Un" << '\n';
        if (analyse(op->getUne())) {
            std::cout << "Vrai Un" << '\n';
            ana = true;
        }
    } else if (op->getNom() == "Atom") {
        std::cout << "Atom" << '\n';
        if (op->getAType() == 0) {
            std::cout << "Terminal : Code : " << op->getCode() << '\n';
            std::cout << "Terminal : Code uniteLexicale : " << this->uniteLexicale["code"] << '\n';
            if (op->getCode() == this->uniteLexicale["code"]) {
                std::cout << "Terminal : Action : " << op->getAction() << '\n';
                ana = true;
                if (op->getAction() != 0) {
                    G0Action(op);
                    std::cout << "G0Action(op->getAction())" << '\n';
                    this->uniteLexicale = this->sc->scan();
                } else {
                    std::cout << "Faux Atom Terminal" << '\n';
                    this->uniteLexicale = this->sc->scan();
                }
            } else {
                ana = false;
            }
        } else if (op->getAType() == 1) {
            std::cout << "Non terminal : Code : " << op->getCode() << " Action de l'atom : " << op->getAction() << '\n';
            //OperationElementaire* op_tmp = op;
            // bool ana_tmp = analyse(this->foret[op->getCode()]);
            // std::cout << "ana_tmp ================> " << ana_tmp << '\n';
            if (analyse(this->foret[op->getCode()])) {
                ana = true;
                if (op->getAction() != 0) {
                    std::cout << "Non terminal Action != 0" << op->getCode() << '\n';
                    G0Action(op);
                    //std::cout << "G0Action->(op->getAction())" << '\n';
                }
            } else {
                std::cout << "Faux Atom Non terminal" << '\n';
                ana = true;
            }
        }
    }
    return ana;
}

void Analyseur::G0Action(OperationElementaire* op) {
    OperationElementaire *t1, *t2;
    //TODO: Terminer le switch
    switch (op->getAction()) {
        // Action 1 : créer arbre
        case 1:
            //FIXME: Corriger ce case
            std::cout << "Action 1" << '\n';
            if (!this->s.empty()) {
                t1 = this->s.top();
                this->s.pop();
                if (!this->s.empty()) {
                    t2 = this->s.top();
                    this->s.pop();
                    this->foret[t2->getCode()] = t1;
                    std::cout << "MON CODE DE MON ARBRE : " << t2->getCode() << endl << "MA SUPER FORET DE T1 : " << this->foret[t2->getCode()]->toString(0) << '\n';
                    //std::cout << "MON CODE DE MON ARBRE : " << t1->getCode() << endl;
                }
            }
            break;
        // Action 2 : Créer Terminal
        case 2:
            std::cout << "Action 2" << '\n';
            this->s.push(new Atom(this->uniteLexicale["chaine"], 2, NTER));
            std::cout << "G0ACTION CASE 2 : " << this->s.top()->getCode() << '\n';
            break;
        // Action 3 : Créer union
        case 3:
            std::cout << "Action 3" << '\n';
            //std::cout << "G0ACTION CASE 3 : " << this->s.top()->getCode() << '\n';
            if (!this->s.empty()) {
                t1 = this->s.top();
                this->s.pop();
                if (!this->s.empty()) {
                    t2 = this->s.top();
                    this->s.pop();
                    this->s.push(new Union(t1, t2));
                    //std::cout << "MA SUPER FORET DE T1 : " << this->foret["s0"]->toString(0) << '\n';
                }
            }
            break;
        // Action 4 : Créer Conc
        case 4:
            std::cout << "Action 4" << '\n';
            if (!this->s.empty()) {
                std::cout << "G0ACTION CASE 4 : " << this->s.top()->getCode() << '\n';
                t1 = this->s.top();
                this->s.pop();
                if (!this->s.empty()) {
                    t2 = this->s.top();
                    this->s.pop();
                    this->s.push(new Conc(t1, t2));
                    //std::cout << "MA SUPER FORET DE T1 : " << this->foret["s0"]->toString(0) << '\n';
                }
            }
            break;
        // Action 5 : Créer terminal / Non terminal
        case 5:
            std::cout << "Action 5" << '\n';
            this->s.push(new Atom(this->uniteLexicale["chaine"], 5, NTER));
            std::cout << "G0ACTION CASE 5 : " << this->s.top()->getCode() << '\n';
            break;
        // Action 6 : Créer star
        case 6:
            std::cout << "Action 6" << '\n';
            if (!this->s.empty()) {
                //std::cout << "G0ACTION CASE 6 : " << this->s.top()->getCode() << '\n';
                t1 = this->s.top();
                this->s.pop();
                this->s.push(new Star(t1));
                std::cout << "MA SUPER FORET DE T1 : " << this->s.top()->toString(0) << '\n';
            }
            break;
        // Action 7 : Créer Un
        case 7:
            std::cout << "Action 7" << '\n';
            if (!this->s.empty()) {
                std::cout << "G0ACTION CASE 7 : " << this->s.top()->getCode() << '\n';
                t1 = this->s.top();
                this->s.pop();
                this->s.push(new Un(t1));
                //std::cout << "MA SUPER FORET DE T1 : " << this->foret["s0"]->toString(0) << '\n';
            }
            break;
        // Default en cas d'erreur
        default:
            std::cout << "Default case" << '\n';
            break;
    }
}
