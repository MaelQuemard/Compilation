#include "foretGenerateur.hpp"

foretGenerateur::foretGenerateur() {
    this->foret["s"] = genA1();
    this->foret["n"] = genA2();
    this->foret["e"] = genA3();
    this->foret["t"] = genA4();
    this->foret["f"] = genA6();
}

OperationElementaire* foretGenerateur::genA1() {
    OperationElementaire* n = new Atom("n", 0, NTER);
    OperationElementaire* fleche = new Atom("->", 1, TER);
    OperationElementaire* e = new Atom("e", 0, NTER);
    OperationElementaire* virgule = new Atom(",", 1, TER);
    OperationElementaire* ptvirgule = new Atom(";", 0, TER);

    OperationElementaire* conc1 = new Conc(n, fleche);
    OperationElementaire* conc2 = new Conc(conc1, e);
    OperationElementaire* conc3 = new Conc(conc2, virgule);
    OperationElementaire* star = new Star(conc3);
    OperationElementaire* conc4 = new Conc(star, ptvirgule);
    return conc4;
}

OperationElementaire* foretGenerateur::genA2() {
    OperationElementaire* idnter = new Atom("IDNTER", 2, TER);
    return idnter;
}

OperationElementaire* foretGenerateur::genA3() {
    OperationElementaire* t = new Atom("t",0,NTER);
    OperationElementaire* plus = new Atom("+",0,TER);
    OperationElementaire* t2 = new Atom("t", 3, NTER);

    OperationElementaire* conc1 = new Conc(plus,t);
    OperationElementaire* star = new Star(conc1);
    OperationElementaire* conc2 = new Conc(t2, star);
    return conc2;
}

OperationElementaire* foretGenerateur::genA4() {
    OperationElementaire* f = new Atom("f",0,NTER);
    OperationElementaire* point = new Atom(".",0,TER);
    OperationElementaire* f2 = new Atom("f", 4, NTER);

    OperationElementaire* conc1 = new Conc(point, f);
    OperationElementaire* star = new Star(conc1);
    OperationElementaire* conc2 = new Conc(f2, star);
    return conc2;
}

OperationElementaire* foretGenerateur::genA5() {
    OperationElementaire* idnter = new Atom("IDNTER", 5, TER);
    OperationElementaire* elter = new Atom("ELTER",5, TER);
    OperationElementaire* parOuvre = new Atom("(", 0, TER);
    OperationElementaire* crochetOuvre = new Atom("[", 0, TER);
    OperationElementaire* crochetFerme = new Atom("]", 6, TER);
    OperationElementaire* parFerme = new Atom(")", 0, TER);
    OperationElementaire* unOuvre = new Atom("(/", 0, TER);
    OperationElementaire* unFerme = new Atom("/)", 7, TER);

    OperationElementaire* conc1 = new Conc(parOuvre,idnter);
    OperationElementaire* conc2 = new Conc(crochetOuvre,idnter);
    OperationElementaire* conc3 = new Conc(unOuvre,idnter);
    OperationElementaire* conc4 = new Conc(conc1,parFerme);
    OperationElementaire* conc5 = new Conc(conc2,crochetFerme);
    OperationElementaire* conc6 = new Conc(conc3,unFerme);
    OperationElementaire* union1 = new Union(conc5,conc6);
    OperationElementaire* union2 = new Union(conc4,union1);
    OperationElementaire* union3 = new Union(elter,union2);
    OperationElementaire* union4 = new Union(idnter,union3);
    //std::cout << union4e->toString(0) << '\n';
    return union4;
}

OperationElementaire* foretGenerateur::genA6() {
    OperationElementaire* idnter = new Atom("IDNTER", 5, TER);
    OperationElementaire* elter = new Atom("ELTER",5, TER);
    OperationElementaire* parOuvre = new Atom("(", 0, TER);
    OperationElementaire* crochetOuvre = new Atom("[", 0, TER);
    OperationElementaire* crochetFerme = new Atom("]", 6, TER);
    OperationElementaire* parFerme = new Atom(")", 0, TER);
    OperationElementaire* unOuvre = new Atom("(/", 0, TER);
    OperationElementaire* unFerme = new Atom("/)", 7, TER);
    OperationElementaire* e = new Atom("e", 0, NTER);

    /*OperationElementaire* union1 = new Union(idnter, elter);
    OperationElementaire* conc1 = new Conc(e, parFerme);
    OperationElementaire*conc2 = new Conc(parOuvre, conc1);
    OperationElementaire* union2 = new Union(union1, conc2);
    OperationElementaire* conc3 = new Conc(e, crochetFerme);
    OperationElementaire* conc4 = new Conc(crochetOuvre, conc3);
    OperationElementaire* union3 = new Union(union2, conc4);
    OperationElementaire* conc5 = new Conc(e, unFerme);
    OperationElementaire* conc6 = new Conc(unOuvre, conc5);
    OperationElementaire* union4 = new Union(union3, conc6);
*/
    OperationElementaire* conc1 = new Conc(unOuvre, e);
    OperationElementaire* conc2 = new Conc(conc1, unFerme);
    OperationElementaire* conc3 = new Conc(crochetOuvre, e);
    OperationElementaire* conc4 = new Conc(conc3, crochetFerme);
    OperationElementaire* union1 = new Union(conc2, conc4);
    OperationElementaire* conc5 = new Conc(parOuvre, e);
    OperationElementaire* conc6 = new Conc(conc5, parFerme);
    OperationElementaire* union2 = new Union(union1, conc6);
    OperationElementaire* union3 = new Union(union2, elter);
    OperationElementaire* union4 = new Union(union3, idnter);
    return union4;
}

map<string, OperationElementaire*> foretGenerateur::getForet() {
    return this->foret;
}
