#include "Ham.h"
int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: ./main MST.txt input.txt output.txt\n";
        return 1;
    }
    string mst_file = argv[1];     // ./MST.txt
    string input_file = argv[2];   // ./input.txt
    string output_file = argv[3];  // ./output.txt
    vector<Company> companies = readCompanyList(mst_file);
    HashTable* table = createHashTable(companies);
    ifstream fin(input_file);
    ofstream fout(output_file);
    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Khong the mo file input hoac output\n";
        return 1;
    }
    string name;
    while (getline(fin, name)) {
        Company* result = search(table, name);
        if (result) {
            fout << result->name << "|" << result->profit_tax << "|" << result->address << "\n";
        }
    }
    fin.close();
    fout.close();
    return 0;
}
