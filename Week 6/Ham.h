#pragma once
#ifndef HAM_H
#define HAM_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct Company {
	string name;
	string profit_tax;
	string address;
};
struct HashNode {
	Company data;
	HashNode* next;
};
struct HashTable {
	HashNode* table[2000] = { nullptr };
};
vector<Company> readCompanyList(string file_name);
long long hashString(string company_name);
HashTable* createHashTable(vector<Company> list_company);
void insert(HashTable* hash_table, Company company);
Company* search(HashTable* hash_table, string company_name);
#endif // !HAM_H

