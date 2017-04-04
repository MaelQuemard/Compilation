#include "Interpreteur.hpp"

Interpreteur::Interpreteur() {}

Interpreteur::~Interpreteur () {}

void Interpreteur::execute (vector<int> p_code, vector<int> pilex) {
    this->p_code = p_code;
    this->pilex = pilex;
    this->c0 = 0;
    this->spx = this->pilex.size()-1;
    for (int i = 0; i < 30; i++) {
        this->pilex.push_back(-123);
    }

    while (this->p_code[c0] != 28) {
        interprete(this->p_code[c0]);
        // 
        // std::cout << "/************* Etat de la pile Pilex taille [" << this->pilex.size() << " c0 : " << c0 << "] ****************/" << '\n';
        // for (int j = 0; j < this->pilex.size(); j++) {
        //     std::cout << "Pilex j : " << this->pilex[j] << '\n';
        // }
    }
}

void Interpreteur::interprete (int x) {
    string tmp;
    switch (x) {
        case AFF:
            pilex[pilex[spx-1]] = pilex[spx];
            spx = spx - 2;
            c0++;
            break;
        case LDA:
            spx++;
            pilex[spx] = p_code[c0+1];
            c0 = c0 + 2;
            break;
        case LDV:
            spx++;
            pilex[spx] = pilex[p_code[c0+1]];
            c0 = c0 + 2;
            break;
        case LDC:
            spx++;
            pilex[spx] = p_code[c0+1];
            c0 = c0 + 2;
            break;
        case JMP:
            c0 = p_code[c0+1];
            break;
        case JIF:
            if (pilex[spx] == 1) {
                c0 = c0 + 2;
            } else {
                c0 = p_code[c0+1];
            }
            break;
        case JSR:
            //TODO: code assembleur non gerer
            cout << "code assembleur non gerer" << endl;
            break;
        case RSR:
            //TODO: code assembleur non gerer
            cout << "code assembleur non gerer" << endl;
            break;
        case SUP:
            if (pilex[spx-1] > pilex[spx]) {
                spx++;
                pilex[spx] = 1;
            } else {
                spx++;
                pilex[spx] = 0;
            }
            c0++;
            break;
        case SUPE:
            if (pilex[spx-1] >= pilex[spx]) {
                spx++;
                pilex[spx] = 1;
            } else {
                spx++;
                pilex[spx] = 0;
            }
            c0++;
            break;
        case INF:
            if (pilex[spx-1] < pilex[spx]) {
                spx++;
                pilex[spx] = 1;
            } else {
                spx++;
                pilex[spx] = 0;
            }
            c0++;
            break;
        case INFE:
            if (pilex[spx-1] <= pilex[spx]) {
                spx++;
                pilex[spx] = 1;
            } else {
                spx++;
                pilex[spx] = 0;
            }
            c0++;
            break;
        case EG:
            if (pilex[spx-1] == pilex[spx]) {
                spx++;
                pilex[spx] = 1;
            } else {
                spx++;
                pilex[spx] = 0;
            }
            c0++;
            break;
        case DIFF:
            if (pilex[spx-1] != pilex[spx]) {
                spx++;
                pilex[spx] = 1;
            } else {
                spx++;
                pilex[spx] = 0;
            }
            c0++;
            break;
        case AND:
            if (pilex[spx-3] == 1 && pilex[spx] == 1) {
                spx++;
                pilex[spx] = 1;
            } else {
                spx++;
                pilex[spx] = 0;
            }
            c0++;
            break;
        case OR:
            if (pilex[spx-3] == 1 || pilex[spx] == 1) {
                spx++;
                pilex[spx] = 1;
            } else {
                spx++;
                pilex[spx] = 0;
            }
            c0++;
            break;
        case NOT:
            if (pilex[spx] == 0) {
                spx++;
                pilex[spx] = 1;
            } else {
                spx++;
                pilex[spx] = 0;
            }
            c0++;
            break;
        case ADD:
            pilex[spx-1] = pilex[spx-1] + pilex[spx];
            spx = spx - 1;
            c0++;
            break;
        case SUB:
            pilex[spx-1] = pilex[spx-1] - pilex[spx];
            spx = spx - 1;
            c0++;
            break;
        case DIV:
            pilex[spx-1] = pilex[spx-1] / pilex[spx];
            spx = spx - 1;
            c0++;
            break;
        case MULT:
            pilex[spx-1] = pilex[spx-1] * pilex[spx];
            spx = spx - 1;
            c0++;
            break;
        case NEG:
            pilex[spx] = !pilex[spx];
            c0++;
            break;
        case INC:
            pilex[spx] = pilex[spx]++;
            c0++;
            break;
        case DEC:
            pilex[spx] = pilex[spx]--;
            c0++;
            break;
        case RDLN:
            spx++;
            cout << "Read : ";
            getline(cin, tmp);
            if (regex_match(tmp, regex("[0-9]+"))){
                pilex[spx] = stoi(tmp);
            }
            c0++;
            break;
        case WRTLN:
            cout << "Write : " << pilex[spx] << endl;
            c0++;
            break;
        default:
            cout << "Code inconnu" << endl;
            break;
    }
}

vector<int> Interpreteur::getPilex() {
    return this->pilex;
}
