#include <fstream>
#include <iostream>
#include <regex> 
#include <string>
#include <iterator>

using namespace std;

const char* names[] = { "Arzach","Axel", "Billy","Charly","Elliot",
"Elise","Emie","Emma","Enzo","Julia","Justin","Katia","Lou","Lucas",
"Manu","Nelly","Oxford","Rose","Rose Junior", "Sasha","Savage","Shadow",
"Tess","Tom","Zoe","Zoe Junior" };

void findAndReplace(string& line,const char* name, int size, int sizeMatch, string inventory, string updatedInv) {
	string s = "(.*)" + (string)name + "(.*)";
	regex a (s);
	regex i (inventory);
	if (regex_match(line, a) && size == sizeMatch)
		line = regex_replace(line, i, updatedInv);
}
void find(fstream& f) {

	while (!f.eof()) {
		string line;
		const char* name;
		int sizeMatch = 0;
		string inventory = "0";
		string updatedInv = "1";
		int size;
		getline(f, line,'\n');
		for (int i = 0; i < 26; i++) {
			regex a(names[i]);
			if (regex_match(line, a)) {
				name = names[i];
				cout << name;
			}
		}
		
	}
}

void replace() {

}

int main() {
	string line = "I am Adam. Find me. Replace 0 with 1";
	const char* name = { "Adam" };
	int size = 0;
	int sizeMatch = 0;
	string inventory = "0";
	string updatedInv = "1";
	findAndReplace(line, name, size, sizeMatch, inventory, updatedInv);
	fstream f("inventory_export.csv");
	find(f);
	

}