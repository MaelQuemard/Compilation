#include "Scanner.hpp"

Scanner::Scanner(string chaine) {
    this->chaine = chaine;
}

void Scanner::modifierChaine(string chaine) {
    this->chaine = chaine;
}

map<string, string> Scanner::scanG0() {
    string uniteLexicale = "";
    for (int i = 0; i <= chaine.size(); ++i) {
        map<string, string> ret;
        stringstream ss;
        string s;
        ss << chaine[i];
        ss >> s;

        if (estSeparateur(to_string(chaine[i])) || i == chaine.size() || estSymbole(uniteLexicale) || estSymbole(s)) {
            if (premierEstEntier(uniteLexicale))
                throw invalid_argument("Unité lexicale invalide '" + uniteLexicale + "'");

            if (estTerminal(uniteLexicale)) {
                ret["code"] = "ELTER";
                ret["action"] = recupererAction(uniteLexicale);
                ret["type"] = "Terminal";
                ret["chaine"] = recupererChaineSansQuote(recupererChaineSansAction(uniteLexicale));
                this->dicot.push_back(recupererChaineSansQuote(recupererChaineSansAction(uniteLexicale)));
                // v.push_back(ret);
                // return scan(chaine.substr(i), v);
                this->chaine = chaine.substr(i);
                return ret;
            } else if (estSymbole(uniteLexicale)) {
                stringstream ss1;
                string s1;
                ss1 << this->chaine[i+1];
                ss1 >> s1;
                string s2;
                if (s1 == "#") {
                    for (int j = i+1; j < this->chaine.size(); j++) {
                        ss1 << chaine[j+1];
                        ss1 >> s1;
                        if (regex_match(s1, regex("[0-9]"))) {
                            s2 += s1;
                        } else {
                            j = this->chaine.size();
                        }
                    }
                }
                ret["code"] = recupererChaineSansAction(uniteLexicale);
                ret["action"] = s2;
                ret["type"] = "Symbole";
                ret["chaine"] = recupererChaineSansAction(uniteLexicale);
                // v.push_back(ret);
                // return scan(chaine.substr(i+1), v);
                this->chaine = chaine.substr(i+1);
                return ret;
            } else if (estSymbole(s) && uniteLexicale[0] != '\'' && chaine[i+1] != '/') {
                int testIndex = i+1;
                stringstream ss1;
                string s1;
                ss1 << chaine[i+1];
                ss1 >> s1;
                string s2;
                if (s1 == "#") {
                    for (int j = i+1; j < chaine.size(); j++) {
                        stringstream ss2;
                        string s3;
                        ss2 << chaine[j+1];
                        ss2 >> s3;
                        if (regex_match(s3, regex("[0-9]"))) {
                            s2 += s3;
                        } else {
                            testIndex = j+1;
                            j = chaine.size();
                        }
                    }
                }
                ret["code"] = s;
                ret["action"] = s2;
                ret["type"] = "Symbole";
                ret["chaine"] = s;
                // v.push_back(ret);
                // return scan(chaine.substr(testIndex), v);
                this->chaine = chaine.substr(testIndex);
                return ret;
            } else if (!uniteLexicale.empty() && to_string(uniteLexicale[0]) != "39"){
                ret["code"] = "IDNTER";
                ret["action"] = recupererAction(uniteLexicale);
                ret["type"] = "Non terminal";
                ret["chaine"] = recupererChaineSansAction(uniteLexicale);
                // v.push_back(ret);
                // uniteLexicale = "";
                this->dicont.push_back(recupererChaineSansAction(uniteLexicale));
                this->chaine = chaine.substr(i);
                return ret;
            } else if (to_string(uniteLexicale[0]) == "39") {
                uniteLexicale += chaine[i];
            } else {
                if (chaine[i] == '(' && chaine[i+1] == '/') {
                    uniteLexicale += chaine[i];
                    uniteLexicale += chaine[i+1];
                } else if (chaine[i+1] == '/' && chaine[i+2] == ')') {
                    uniteLexicale += chaine[i+1];
                    uniteLexicale += chaine[i+2];
                    i = i+2;
                } else {
                    uniteLexicale = "";
                }
            }
        } else {
            uniteLexicale += chaine[i];
        }
    }
    //return null;
}

bool Scanner::premierEstEntier(string s) {
    if (regex_match(s, regex("[0-9][0-9a-zA-Z._-]*"))){
        return true;
    }
    return false;
}

bool Scanner::estSymbole(string s) {
    for (int i = 0; i < symbole.size(); i++) {
        if (s == symbole[i]) {
            return true;
        }
    }
    return false;
}

bool Scanner::estSeparateur(string s) {
    for (int i = 0; i < separateur.size(); i++) {
        if (s == separateur[i]) {
            return true;
        }
    }
    return false;
}

bool Scanner::estTerminal(string s) {
    if (s[0] == '\'') {
        for (int i = 1; i <= s.size(); i++) {
            if (s[i] == '\'') {
                return true;
            }
        }
    }
    return false;
}

string Scanner::recupererAction(string s) {
    string ret;
    //if (regex_match(s, regex("[']*[()_0-9a-zA-Z- ]+[']*[#][0-9]+"))) {
        for (int i = 0; i < s.size(); i++) {
            if (to_string(s[i]) == "35") {
                ret += s.substr(i+1);
            }
        }
    //}
    return ret;
}

string Scanner::recupererChaineSansAction(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (to_string(s[i]) == "35") {
            return s.substr(0, i);
        }
    }
    return s;
}

// map<string, string> Scanner::scanGPL() {
//     string uniteLexicale = "";
//     for (int i = 0; i <= chaine.size(); ++i) {
//         std::cout << "uniteLexicale :: "  << uniteLexicale<< '\n';
//         map<string, string> ret;
//
//         if (estSeparateur(to_string(chaine[i])) || i == chaine.size()) {
//             if (estEntier(uniteLexicale)) {
//                 ret["code"] = "ENTIER";
//                 ret["action"] = recupererAction(uniteLexicale);
//                 ret["type"] = "ENTIER";
//                 ret["chaine"] = recupererChaineSansAction(uniteLexicale);
//                 //this->dicot.push_back(recupererChaineSansAction(uniteLexicale));
//                 // v.push_back(ret);
//                 // return scan(chaine.substr(i), v);
//                 this->chaine = chaine.substr(i+1);
//                 uniteLexicale = "";
//                 return ret;
//             } else if (estIdent(uniteLexicale)) {
//                 ret["code"] = "IDENT";
//                 ret["action"] = recupererAction(uniteLexicale);;
//                 ret["type"] = "IDENT";
//                 ret["chaine"] = recupererChaineSansAction(uniteLexicale);
//                 // v.push_back(ret);
//                 // return scan(chaine.substr(i+1), v);
//                 this->chaine = chaine.substr(i+1);
//                 uniteLexicale = "";
//                 return ret;
//             } else {
//                 ret["code"] = "SYMBOLE";
//                 ret["action"] = recupererAction(uniteLexicale);;
//                 ret["type"] = "SYMBOLE";
//                 ret["chaine"] = recupererChaineSansAction(uniteLexicale);
//                 // v.push_back(ret);
//                 // return scan(chaine.substr(i+1), v);
//                 this->chaine = chaine.substr(i+1);
//                 uniteLexicale = "";
//                 return ret;
//             }
//         } else {
//             uniteLexicale += chaine[i];
//         }
//     }
// }

map<string, string> Scanner::scanGPL() {
    string uniteLexicale = "";
    for (int i = 0; i <= chaine.size(); ++i) {
        map<string, string> ret;
        stringstream ss;
        string s;
        ss << chaine[i];
        ss >> s;

        if (estSeparateur(to_string(chaine[i])) || i == chaine.size() || estSymbole(uniteLexicale) || estSymbole(s)) {
            // if (premierEstEntier(uniteLexicale))
            //     throw invalid_argument("Unité lexicale invalide '" + uniteLexicale + "'");

            if (estTerminal(uniteLexicale)) {
                ret["code"] = "ELTER";
                ret["action"] = recupererAction(uniteLexicale);
                ret["type"] = "Terminal";
                ret["chaine"] = recupererChaineSansAction(uniteLexicale);
                //this->dicot.push_back(recupererChaineSansAction(uniteLexicale));
                // v.push_back(ret);
                // return scan(chaine.substr(i), v);
                this->chaine = chaine.substr(i);
                return ret;
            } else if (estSymbole(uniteLexicale)) {
                stringstream ss1;
                string s1;
                ss1 << this->chaine[i+1];
                ss1 >> s1;
                string s2;
                if (s1 == "#") {
                    for (int j = i+1; j < this->chaine.size(); j++) {
                        ss1 << chaine[j+1];
                        ss1 >> s1;
                        if (regex_match(s1, regex("[0-9]"))) {
                            s2 += s1;
                        } else {
                            j = this->chaine.size();
                        }
                    }
                }
                ret["code"] = recupererChaineSansAction(uniteLexicale);
                ret["action"] = s2;
                ret["type"] = "Symbole";
                ret["chaine"] = recupererChaineSansAction(uniteLexicale);
                // v.push_back(ret);
                // return scan(chaine.substr(i+1), v);
                this->chaine = chaine.substr(i+1);
                return ret;
            } else if (estSymbole(s) && uniteLexicale[0] != '\'' && chaine[i+1] != '/') {
                int testIndex = i+1;
                stringstream ss1;
                string s1;
                ss1 << chaine[i+1];
                ss1 >> s1;
                string s2;
                if (s1 == "#") {
                    for (int j = i+1; j < chaine.size(); j++) {
                        stringstream ss2;
                        string s3;
                        ss2 << chaine[j+1];
                        ss2 >> s3;
                        if (regex_match(s3, regex("[0-9]"))) {
                            s2 += s3;
                        } else {
                            testIndex = j+1;
                            j = chaine.size();
                        }
                    }
                }
                ret["code"] = s;
                ret["action"] = s2;
                ret["type"] = "Symbole";
                ret["chaine"] = s;
                // v.push_back(ret);
                // return scan(chaine.substr(testIndex), v);
                this->chaine = chaine.substr(testIndex);
                return ret;
            } else if (estIdent(uniteLexicale)) {
                ret["code"] = recupererChaineSansAction(uniteLexicale);
                ret["action"] = recupererAction(uniteLexicale);
                ret["type"] = "Non terminal";
                ret["chaine"] = recupererChaineSansAction(uniteLexicale);
                this->chaine = chaine.substr(i);
                return ret;
            } else if (!uniteLexicale.empty() && to_string(uniteLexicale[0]) != "39"){
                ret["code"] = "ident";
                ret["action"] = recupererAction(uniteLexicale);
                ret["type"] = "Non terminal";
                ret["chaine"] = recupererChaineSansAction(uniteLexicale);
                // v.push_back(ret);
                // uniteLexicale = "";
                //this->dicont.push_back(recupererChaineSansAction(uniteLexicale));
                this->chaine = chaine.substr(i);
                return ret;
            } else if (to_string(uniteLexicale[0]) == "39") {
                uniteLexicale += chaine[i];
            } else {
                if (chaine[i] == '(' && chaine[i+1] == '/') {
                    uniteLexicale += chaine[i];
                    uniteLexicale += chaine[i+1];
                } else if (chaine[i+1] == '/' && chaine[i+2] == ')') {
                    uniteLexicale += chaine[i+1];
                    uniteLexicale += chaine[i+2];
                    i = i+2;
                } else {
                    uniteLexicale = "";
                }
            }
        } else {
            uniteLexicale += chaine[i];
        }
    }
}

bool Scanner::estEntier(string s) {
    if (regex_match(s, regex("[0-9]+"))){
        return true;
    }
    return false;
}

bool Scanner::estIdent(string s) {
    for (int i = 0; i < dicot.size(); i++) {
        if (s == dicot[i]) {
            return true;
        }
    }
    return false;
}

string Scanner::recupererChaineSansQuote(string s) {
    string chaineSansQuote = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '\'') {
            chaineSansQuote += s[i];
        }
    }
    return chaineSansQuote;
}
