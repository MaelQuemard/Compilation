
#include "foretGenerateur.hpp"
#include "Analyseur.hpp"
#include "Scanner.hpp"
#include <iostream>
#include <exception>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {

    foretGenerateur* fg = new foretGenerateur();

    Scanner* sc = new Scanner("S1 -> [ N1 . '->' . E1 . ','#6 ] . ';' , N1 -> 'IDNTER'#2 , E1 -> T1 . [ '+' . T1#3 ] , T1 -> F1 . [ '.' . F1#4 ] , F1 -> 'IDNTER'#5 + 'ELTER'#5 + '(' . E1 . ')' + '[' . E . ']'#6 + '(/' . E . '/)'#7 , ;");

    Analyseur* analyseur = new Analyseur(fg->getForet(), sc);
    std::cout << analyseur->analyse(fg->getForet()["s"]) << endl;

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
