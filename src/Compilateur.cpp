#include "Compilateur.hpp"

using namespace std;

Compilateur::Compilateur() {}

Compilateur::~Compilateur() {}

string Compilateur::readFile(string path) {
    string fileRead = "";
	std::string line;
    std::cout << "PATH :: " << path << '\n';
	ifstream myfile (path);
	if (myfile.is_open()) {
		while (getline (myfile,line)) {
            fileRead += line;
		}
		myfile.close();
	} else std::cout << "FICHIER IMPOSSIBLE A OUVRIR";
    return fileRead;
}

string Compilateur::waitCommand() {
    string command;
    cout << "> ";
    getline(cin,command);
    return command;
}

void Compilateur::executeCommand(string command) {
    cout << "command : '"<< command << "'" <<endl;
    if (command == "generer G0") {
        this->fg = new foretGenerateur();
        cout << "La foret est bien generer" << '\n';
        return;
    } else if (command == "afficher G0") {

        if (this->fg == NULL) {
            cout << "Generer la foret avant, avec la commande : 'generer G0'" << endl;
        } else {
            for(auto& x : this->fg->getForet()){
                cout << "|*****************" << "Arbre [" << x.first << "]*******************|" << endl;
                std::cout << x.second->toString(0) << endl << endl;
    		}
        }
        return;
    } else if (command == "analyser GPL") {

        if (this->fg == NULL) {
            cout << "Generer la foret avant, avec la commande : 'generer G0'" << endl;
        } else {
            string filePath;
            cout << "----> Donnez le chemin du fichier de votre grammaire : "<< endl;
            //getline(cin, filePath);
            string fileReader = readFile("src/grammar.txt");
            std::cout << "TEST READ :: " << fileReader << '\n';

            sc = new Scanner(fileReader);
            analyseur = new Analyseur(fg->getForet(), sc);
            cout << analyseur->analyseG0(fg->getForet()["s"]) << endl;
        }
        return;
    } else if (command == "afficher GPL") {

        if (this->analyseur == NULL) {
            cout << "Analyser la GPL avant, avec la commande : 'analyser GPL'" << endl;
        } else if (this->fg == NULL) {
            cout << "Generer la foret avant, avec la commande : 'generer G0'" << '\n';
        } else {
            for (auto& x : this->analyseur->getForet()) {
                if (x.first != "e" && x.first != "f" && x.first != "n" && x.first != "s" && x.first != "t") {
                    cout << "|*****************" << "Arbre [" << x.first << "]*******************|" << endl;
                    cout << x.second->toString(0) << endl << endl;
                }
            }
        }
        return;
    } else if (command == "analyser prog") {
        sc->modifierChaine("Program cond ; var I , A , B ; BEGIN I = 0 ; A = 5 ; B = 3 ; IF A == 5 THEN A = 3 ; ELSE B = 2 ; ENDIF END .");
        analyseur->setUnitelexicale();
        cout << analyseur->analyseGPL(analyseur->getForet()["Prgm"]) << endl;
        return;
    } else if (command == "aide") {
        cout << "Commande possible : " << endl;
        cout << "     - generer G0 : pour generer la foret G0" << endl;
        cout << "     - afficher G0 : pour afficher la foret G0" << endl;
        cout << "     - analyser GPL : pour analyser la grammaire gpl" << endl;
        cout << "     - afficher GPL : pour afficher la foret de votre GPL" << endl;
        cout << "     - analyser prog : pour analyser votre programme" << endl;
        return;
    } else if (command == "exit") {
        return;
    }

    cout << "Commande non reconnu : Utiliser la commande 'aide'" << endl;
    return;
}

int main(int argc, char const *argv[]) {

    Compilateur* compil = new Compilateur();
    //
    string command;
    do {
        command = compil->waitCommand();
        compil->executeCommand(command);
    } while(command != "exit");
    // foretGenerateur* fg = new foretGenerateur();
    // string testRead = compil->readFile("src/grammar.txt");
    // std::cout << "TEST READ :: " << testRead << '\n';
    //
    // //Scanner* sc = new Scanner("S1 -> [ N1 . '->' . E1 . ','#6 ] . ';' , N1 -> 'IDNTER'#2 , E1 -> T1 . [ '+' . T1#3 ] , T1 -> F1 . [ '.' . F1#4 ] , F1 -> 'IDNTER'#5 + 'ELTER'#5 + '(' . E1 . ')' + '[' . E . ']'#6 + '(/' . E . '/)'#7 , ;");
    // Scanner* sc = new Scanner(testRead);
    // Analyseur* analyseur = new Analyseur(fg->getForet(), sc);
    // std::cout << analyseur->analyseG0(fg->getForet()["s"]) << endl;
    //
    // sc->modifierChaine("Program cond ; var I ; BEGIN IF I == 0 THEN TRUE END .");
    // analyseur->setUnitelexicale();
    // cout << analyseur->analyseGPL(analyseur->getForet()["Prgm"]) << endl;

    return 0;
}
