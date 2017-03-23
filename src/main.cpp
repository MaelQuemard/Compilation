
#include "foretGenerateur.hpp"
#include "Analyseur.hpp"
#include "Scanner.hpp"
#include <iostream>
#include <exception>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {

    //map<string, OperationElementaire*> foret;
    foretGenerateur* fg = new foretGenerateur();

    //cout << fg->getForet()["n"]->toString(0) << endl;
    Scanner* sc = new Scanner("s0 -> [ 'a'#1 ]#1242 + 'b', ;");
    Analyseur* analyseur = new Analyseur(fg->getForet(), sc);
    std::cout << analyseur->analyse(fg->getForet()["s"]) << endl;

    //cout << foret->at(0)->toString(0);

    // for (int i = 0; i < foret->size(); i++) {
    //     foret[i];
    // }

    //map<string, string> m;

    try {
        /*m = sc->scan();
        std::cout << "Code : " << m["code"] << '\n';
        std::cout << "Type : " << m["type"] << '\n';
        std::cout << "action : " << m["action"] << '\n';
        std::cout << "chaine : " << m["chaine"] << '\n' << endl;
        m = sc->scan();
        std::cout << "Code : " << m["code"] << '\n';
        std::cout << "Type : " << m["type"] << '\n';
        std::cout << "action : " << m["action"] << '\n';
        std::cout << "chaine : " << m["chaine"] << '\n' << endl;
        m = sc->scan();
        std::cout << "Code : " << m["code"] << '\n';
        std::cout << "Type : " << m["type"] << '\n';
        std::cout << "action : " << m["action"] << '\n';
        std::cout << "chaine : " << m["chaine"] << '\n' << endl;
        m = sc->scan();
        std::cout << "Code : " << m["code"] << '\n';
        std::cout << "Type : " << m["type"] << '\n';
        std::cout << "action : " << m["action"] << '\n';
        std::cout << "chaine : " << m["chaine"] << '\n' << endl;
        m = sc->scan();
        std::cout << "Code : " << m["code"] << '\n';
        std::cout << "Type : " << m["type"] << '\n';
        std::cout << "action : " << m["action"] << '\n';
        std::cout << "chaine : " << m["chaine"] << '\n' << endl;
        m = sc->scan();
        std::cout << "Code : " << m["code"] << '\n';
        std::cout << "Type : " << m["type"] << '\n';
        std::cout << "action : " << m["action"] << '\n';
        std::cout << "chaine : " << m["chaine"] << '\n' << endl;
        m = sc->scan();
        std::cout << "Code : " << m["code"] << '\n';
        std::cout << "Type : " << m["type"] << '\n';
        std::cout << "action : " << m["action"] << '\n';
        std::cout << "chaine : " << m["chaine"] << '\n' << endl;
*/
        /*v = sc->scan("s0 -> [ 'az az'#1 ]#1242 + 'b',#13 s1 -> ['c'] + 'd';#12", v);
        for (int i = 0; i < v.size(); i++) {
            std::cout << "Code : " << v[i]["code"] << '\n';
            std::cout << "Type : " << v[i]["type"] << '\n';
            std::cout << "action : " << v[i]["action"] << '\n';
            std::cout << "chaine : " << v[i]["chaine"] << '\n' << endl;
        }*/
        // Analyseur* analyse = new Analyseur();
        // analyse->analyse(v);


    } catch (invalid_argument e) {
        std::cout << "exception : " << e.what() << '\n';
    }

    return 0;
}
