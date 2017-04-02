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
    std::cout << "analyseGPL::" << op->getNom() << '\n';
    bool ana;
    if (op->getNom() == "Conc") {
        bool ana_tmp = analyseGPL(op->getRight());
        if (ana_tmp) {
            ana = analyseGPL(op->getLeft());
        } else {
            ana = false;
        }
    } else if (op->getNom() == "Union") {
        if (analyseGPL(op->getRight())) {
            ana = true;
        } else {
            ana = analyseGPL(op->getLeft());
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
                std::cout << "Atom :: Terminal : opCode : " << op->getCode() << " uniteLexicale : " << this->uniteLexicale["code"] << '\n';
                if (op->getCode() == this->uniteLexicale["code"]) {
                    if (op->getAction() != 0) {
                        int actionType;
                        stringstream s;
                        s << op->getAction();
                        s >> actionType;
                        AtomType aType = this->uniteLexicale["code"] == "IDNTER" ? NTER : TER;
                        std::cout << "--------------Ter----------------GPLAction : " << op->getAction() << '\n';
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
                std::cout << "Atom :: Non Terminal opCode : " << op->getCode() << " uniteLexicale : " << this->uniteLexicale["code"] << '\n';
                if (analyseGPL(this->foret[op->getCode()])) {
                    if (op->getAction() != 0) {
                        int actionType1;
                        stringstream s1;
                        s1 << op->getAction();
                        s1 >> actionType1;
                        AtomType aType = this->uniteLexicale["code"] == "IDNTER" ? NTER : TER;
                        std::cout << "-----------------------NON-Ter-------------------GPLAction : " << op->getAction() << '\n';
                        GPLAction(op, actionType1, aType);
                    }
                    ana = true;
                } else { ana = false; }
                break;
            default:
                ana = false;
                break;
        }
    }
    return ana;
}

void Analyseur::GPLAction(OperationElementaire* op, int actionType, AtomType aType) {
    int ident;
    ident = NULL;
    stringstream s1;
    s1.flush();
    s1 << this->uniteLexicale["chaine"];
    s1 >> ident;
    int i;

    switch (actionType) {
        // Déclaration d'un ident (1)
        case 1:
            cout << "Déclaration d'un ident : " << this->uniteLexicale["chaine"] << endl;
            itab.insert( std::pair<string, int>(this->uniteLexicale["chaine"], pilex.size()+1));
            break;
        // Donner une valeur a la déclaration d'un ident (2)
        case 2:
            cout << "Donner une valeur a la déclaration d'un ident : "<< ident << endl;
            pilex.push_back(ident);
            break;
        // Chargé une addresse (LDA) (3)
        case 3:
            i = itab[this->uniteLexicale["chaine"]];
            std::cout << "Chargé une addresse (LDA) : " << this->uniteLexicale["chaine"] << " adresse : " << i << '\n';
            p_code.push_back(LDA);
            p_code.push_back(i);
            break;
        // Chargé une valeur (LDV) (4)
        case 4:
            i = itab[this->uniteLexicale["chaine"]];
            std::cout << "Chargé une valeur:: chaine : " << this->uniteLexicale["chaine"] << " addresse : " << i << '\n';
            p_code.push_back(LDV);
            p_code.push_back(i);
            break;
        // Chargé une constante (LDC) (5)
        case 5:
            std::cout << "Chargé une constante : "<< ident << '\n';
            p_code.push_back(LDC);
            p_code.push_back(ident);
            break;
        // Identifer un opérateur mathématique (ADD, SUB, DIV...) (10)
        case 6:
            std::cout << "Identifer un opérateur mathématique (ADD, SUB, DIV...) : " << this->uniteLexicale["chaine"] << '\n';
            if (this->uniteLexicale["chaine"] == "+") {
                p_code.push_back(ADD);
            } else if (this->uniteLexicale["chaine"] == "-") {
                p_code.push_back(SUB);
            } else if (this->uniteLexicale["chaine"] == "++") {
                p_code.push_back(INC);
            } else if (this->uniteLexicale["chaine"] == "--") {
                p_code.push_back(DEC);
            } else if (this->uniteLexicale["chaine"] == "*") {
                p_code.push_back(MULT);
            } else if (this->uniteLexicale["chaine"] == "/") {
                p_code.push_back(DIV);
            } else if (this->uniteLexicale["chaine"] == "!") {
                p_code.push_back(NEG);
            }
            break;
        // Cas pour lire une valeur (RDLN) (14)
        case 7:
            std::cout << "Cas pour lire une valeur (RDLN) : " << '\n';
            p_code.push_back(RDLN);
            p_code.push_back(AFF);
            break;
        // Ecrire une valeur (WRTLN) (16)
        case 8:
            std::cout << "Ecrire une valeur (WRTLN)" << '\n';
            p_code.push_back(WRTLN);
            break;
        // Chargé un ou (OR) (30)
        case 9:
            std::cout << "Chargé un ou (OR)" << '\n';
            p_code.push_back(OR);
            break;
        // Chargé un et (AND) (32)
        case 10:
            std::cout << "Chargé un et (AND)" << '\n';
            p_code.push_back(AND);
            break;
        // Chargé un negatif (NOT) (33)
        case 11:
            std::cout << "Chargé un negatif (NOT)" << '\n';
            p_code.push_back(NOT);
            break;
        // Dépiler l'opérateur (OR, AND, NEG) (31)
        case 12:
            std::cout << "Dépiler l'opérateur (OR, AND, NEG)" << '\n';
            p_code.pop_back();
            break;
        // Identifier l'operateur relationnel (SUP, SUPE, INF...) (34)
        case 13:
            std::cout << "Identifier l'operateur relationnel (SUP, SUPE, INF...) : " << this->uniteLexicale["chaine"] << '\n';
            if (this->uniteLexicale["chaine"] == "==") {
                p_code.push_back(EG);
            } else if (this->uniteLexicale["chaine"] == ">") {
                p_code.push_back(SUP);
            } else if (this->uniteLexicale["chaine"] == ">=") {
                p_code.push_back(SUPE);
            } else if (this->uniteLexicale["chaine"] == "<") {
                p_code.push_back(INF);
            } else if (this->uniteLexicale["chaine"] == "<=") {
                p_code.push_back(INFE);
            } else if (this->uniteLexicale["chaine"] == "!=") {
                p_code.push_back(DIFF);
            }
            break;
        // Premiere partie d'un JIF (IF) (chargé le JIF + l'adresse laissée vide pour jump si faux) (20)
        case 14:
            std::cout << "Premiere partie d'un JIF (IF)" << '\n';
            p_code.push_back(JIF);
            pilex.push_back(p_code.size()-1);
            break;
        // Deuxieme partie d'un JIF (ELSE) (mettre l'adresse du saut) (21)
        case 15:
        std::cout << "Deuxieme partie d'un JIF (ELSE)" << '\n';
            p_code[pilex.back()] = p_code.size();
            pilex.pop_back();
            break;
        // Troisieme partie d'un JIF (THEN) (mettre un JMP pour sauté après le else) (22)
        case 16:
            std::cout << "Troisieme partie d'un JIF (THEN)" << '\n';
            p_code.push_back(JIF);
            pilex.push_back(p_code.size()-1);
            break;
        // Quatrième partie d'un JIF (ENDIF) (remplir l'adresse du JMP pour le THEN) (23)
        case 17:
            std::cout << "Quatrième partie d'un JIF (ENDIF)" << '\n';
            p_code[pilex.back()] = p_code.size();
            pilex.pop_back();
            break;
        // Pour le while, JMP pour revenir au début du while (24)
        case 18:
            std::cout << "Pour le while, JMP pour revenir au début du while" << '\n';
            p_code.push_back(JMP);
            p_code.push_back(pilex.back()-1);
            p_code[pilex.back()] = p_code.size();
            break;
        // Chargé une affectation : AFF
        case 19:
            cout << "Chargé une affectation : AFF" << endl;
            p_code.push_back(AFF);
            break;
        // STOP (Pas sur que ce soit néceassaire) (28)
        case 20:
            cout << "STOP" << endl;
            break;
        default:
            cout << "Inconnu" << endl;
            break;
    }
}

void Analyseur::setUnitelexicale() {
    this->uniteLexicale = sc->scanGPL();
}

map<string, OperationElementaire*> Analyseur::getForet() {
    return this->foret;
}
