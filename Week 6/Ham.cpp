#include "Ham.h"
vector<Company> readCompanyList(string file_name) {
	vector <Company> companies;
	ifstream file(file_name);
	if (!file.is_open()) {
		cerr << "Khong the mo file " << file_name << endl;
		return companies;
	}
	string line;
	while (getline(file, line)) {
		Company comp;
		size_t pos1 = line.find('|');
		size_t pos2 = line.find('|', pos1 + 1);
		if (pos1 != string::npos && pos2 != string::npos) {
			comp.name = line.substr(0, pos1);
			comp.profit_tax = line.substr(pos1 + 1, pos2 - pos1 - 1);
			comp.address = line.substr(pos2 + 1);
			companies.push_back(comp);
		}
	}
	file.close();
	return companies;
}
long long hashString(string company_name) {
	const int p = 31;
	const int m = 2000;
	string s;
	if (company_name.length() <= 20) {
		s = company_name;
	}
	else {
		s = company_name.substr(company_name.length() - 20);
	}
	long long hash_value = 0;
	long long power_of_p = 1;
	for (size_t i = 0; i < s.length(); i++) {
		hash_value = (hash_value + (s[i] * power_of_p) % m) % m;
		power_of_p = (power_of_p * p) % m;
	}
	return hash_value;
}
HashTable* createHashTable(vector<Company> list_company) {
	HashTable* hashtable = new HashTable();
	for (Company c : list_company) {
		long long index = hashString(c.name);
		HashNode* newNode = new HashNode{ c, nullptr };
		newNode->next = hashtable->table[index];
		hashtable->table[index] = newNode;
	}
	return hashtable;
}
void insert(HashTable* hashtable, Company comp) {
	long long index = hashString(comp.name);
	HashNode* newNode = new HashNode{comp, nullptr};
	newNode->next = hashtable->table[index];
	hashtable->table[index] = newNode;
}
Company* search(HashTable* hashtable, string company_name) {
	long long index = hashString(company_name);
	HashNode* current = hashtable->table[index];
	while (current) {
		if (current->data.name == company_name) {
			return &current->data;
		}
		current = current->next;
	}
	return nullptr;
}