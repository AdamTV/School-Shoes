#include <fstream>
#include <iostream>
#include <regex> 
#include <string>
#include <iterator>
#include <sstream>

using namespace std;

string names[] = { ".*Arzach.*",".*Axel.*", ".*Billy.*",".*Charly.*",".*Elliot.*",
".*Elise.*",".*Emie.*",".*Emma.*",".*Enzo.*",".*Julia.*",".*Justin.*",".*Katia.*",".*Lou.*",".*Lucas.*",
".*Manu.*",".*Nelly.*",".*Oxford.*",".*Rose.*",".*Rose Junior.*", ".*Sasha.*",".*Savage.*",".*Shadow.*",
".*Tess.*",".*Tom.*",".*Zoe.*",".*Zoe Junior.*" };

//void findAndReplace(string& line,const char* name, int size, int sizeMatch, string inventory, string updatedInv) {
//	string s = "(.*)" + (string)name + "(.*)";
//	regex a (s);
//	regex i (inventory);
//	if (regex_match(line, a) && size == sizeMatch)
//		line = regex_replace(line, i, updatedInv);
//}


string find(ifstream& fs, string nameAndSize) {
	string inventory = "A";
	string line;
	regex a(nameAndSize);
	getline(fs, line, '\n');
		if (regex_match(line, a)) {
			//FIND INVENTORY IN NEW FILE
			size_t pos = line.length();
			pos -= 2;
			inventory = line.substr(pos,1);
		}
	return inventory;
}

void replace(fstream& f) {
	string line;
	string name;
	int sizeMatch = 0;
	string inventory = "0";
	string updatedInv = "A";
	string size;
	bool notR = true;
	getline(f, line, '\n');
	for (int i = 0; i < 26 && notR; i++) {
		regex a(names[i]);
		if (regex_match(line, a)) {
			notR = false;
			name = names[i];
			size_t pos = line.find("Size");
			pos += 5;
			istringstream tmp (line.substr(pos));
			getline(tmp,size,',');
			string nameAndSize = name.substr();
			nameAndSize.resize(nameAndSize.length() - 2);
			nameAndSize += size;
			nameAndSize += ".*";
			//cout << nameAndSize << endl;
			//ifstream fs2("inventory.csv");
			ifstream fs("inventaire.csv");
			//fstream fs("inventory_export.csv");
			while (fs) {
				updatedInv = find(fs, nameAndSize);
				if (updatedInv != "A") {
					regex endLine(".*$");
					line = regex_replace(line, endLine, updatedInv);
					cout << line << endl;
					break;
				}
			}
		}
	}
}


int main() {
	string line = "I am Arzach. Find me. Replace 0 with 1";
	const char* name = { "Arzach" };

	int size = 0;
	int sizeMatch = 0;
	string inventory = "0";
	string updatedInv = "1";
	ofstream f("inventory_export.csv");
	f << "HI\n";
	regex a(".*");
	//getline(f, line, '\n');
	line = regex_replace(line, a, "HI");
	f << "HI";
	cout << line;
	/*while (f) {
		replace(f);
	}*/
	return 0;
}