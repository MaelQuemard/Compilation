#ifndef __SCANNER__HPP
#define __SCANNER__HPP

#include <string>
#include <regex>
#include <map>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Scanner
{
public:

	Scanner(string);
	~Scanner();
	vector<string> symbole = {"+", ",", ";", "[", "]", "->", ".", "(/", "/)", "(", ")"};
	// C'est des codes ascii !!
	vector<string> separateur = {"32", "8", "9"};
	map<string, string> scanG0();
	bool premierEstEntier(string);
	bool estSymbole(string);
	bool estSeparateur(string);
	bool estTerminal(string);
	string recupererAction(string);
	string recupererChaineSansAction(string);
	vector<string> dicot;
	vector<string> dicont;

	map<string, string> scanGPL();

private:
	string chaine;


};

#endif // __SCANNER__HPP
