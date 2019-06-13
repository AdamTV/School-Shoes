#include <fstream>
#include <iostream>
#include <regex> 
#include <string>
#include <iterator>
#include <sstream>

using namespace std;

//CHANGE GLOBAL VARIABLES TO PARSED STRINGS WITHIN FUNCTION
string names[] = { ".*Arzach.*",".*Axel.*", ".*Billy.*",".*Charly.*",".*Elliot.*",
".*Elise.*",".*Emie.*",".*Emma.*",".*Enzo.*",".*Julia.*",".*Justin.*",".*Katia.*",".*Lou.*",".*Lucas.*",
".*Manu.*",".*Nelly.*",".*Oxford.*",".*Rose.*",".*Rose Junior.*", ".*Sasha.*",".*Savage.*",".*Shadow.*",
".*Tess.*",".*Tom.*",".*Zoe.*",".*Zoe Junior.*" };

string find(ifstream& fs, string nameAndSize) {
	string inventory = "A";
	string line;
	regex a(nameAndSize);
	getline(fs, line, '\n');
		if (regex_match(line, a)) {
			//FIND INVENTORY IN NEW FILE
			regex endLine(".*,");
			line = regex_replace(line, endLine, "");
			inventory = regex_replace(line, endLine, "");
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
	for (int i = 0; i < 25 && notR; i++) {
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
					while (line[(line.length() - 1)] != ',') {
						if (line[(line.length() - 1)] == '1' || line[(line.length() - 1)] == '2' || line[(line.length() - 1)] == '3' 
							|| line[(line.length() - 1)] == '4' || line[(line.length() - 1)] == '5' || line[(line.length() - 1)] == '6' 
							|| line[(line.length() - 1)] == '7' || line[(line.length() - 1)] == '8' || line[(line.length() - 1)] == '9' 
							|| line[(line.length() - 1)] == '0' || line[(line.length() - 1)] == '-')
							line.resize(line.length() - 1);
					}
					line += updatedInv;
					ofstream o("newInv.csv",fstream::app);
					cout << line << endl;
					o << line << endl;
					break;
				}
			}
		}
	}
}

void updateInventory() {
	string line = "Handle,Title,Option1 Name,Option1 Value,Option2 Name,Option2 Value,Option3 Name,Option3 Value,SKU,\"Blainville, Quebec\",";
	ofstream o("newInv.csv");
	o << line << endl;
	fstream f("inventory_export.csv");
	while (f) {
		replace(f);
	}
}

int main() {
	updateInventory();
	return 0;
}