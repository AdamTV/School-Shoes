#include <fstream>
#include <iostream>
#include <regex> 
#include <string>
#include <iterator>
#include <sstream>
#include <iomanip>

using namespace std;

string find(ifstream& fs, string nameAndSize) {
	string inventory = "A";
	string line;
	regex a(nameAndSize, std::regex_constants::icase);
	getline(fs, line, '\n');

	if (regex_match(line, a)) {
		//FIND INVENTORY IN NEW FILE
		line.resize(line.size() - 1);
		auto const pos = line.find_last_of(',');
		inventory = line.substr(pos+1);
		//regex endLine(".*,");
		//line = regex_replace(line, endLine, "");
		//inventory = regex_replace(line, endLine, "");
	}

	return inventory;
}

void replace(fstream& f) {
	string line;
	string name;
	string updatedInv = "A";
	string size;

	getline(f, line, '\n');
	regex header("Handle.*");

	if (regex_match(line, header) || line == "")
		return;

	size_t findCom = line.find(',') + 1;
	string temp = line.substr(findCom);
	size_t pos1 = temp.find(',');
	name = temp.substr(0, pos1);
	regex space(".* .*");

	if (regex_match(line,space)) {
		regex theSpace(" .*");
		name = regex_replace(name, theSpace, "");
		name += "Enfant";
	}

	size_t pos = line.find("Size");
	pos += 5;
	istringstream tmp(line.substr(pos));
	getline(tmp, size, ',');

	if (size.length() == 1)
		size.insert(0, "0");

	string nameAndSize = name;
	nameAndSize += size;
	nameAndSize += ".*";
	ifstream fs("inventaire.csv");

	while (fs) {
		updatedInv = find(fs, nameAndSize);
		if (updatedInv != "A") {
			while (line[(line.length() - 1)] != ',') {
					line.resize(line.length() - 1);
			}
			line += updatedInv;
			ofstream o("newInv.csv", fstream::app);
			cout << name << ": " << size << " updated!\n";
			o << line << endl;
			break;
		}
	}
}

void updateInventory() {
	string line = "Handle,Title,Option1 Name,Option1 Value,Option2 Name,Option2 Value,Option3 Name,Option3 Value,SKU,\"Blainville, Quebec\"";
	ofstream o("newInv.csv");
	o << line << endl;
	fstream f("inventory_export.csv");
	while (f) {
		replace(f);
	}
}

int main() {
	updateInventory();
	cout << "Inventory Updated!";
	return 0;
}