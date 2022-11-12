#include "SymbolTable.h"

void SymbolTable::addSymbol(string name) {
    if(!this->lookupSymbol(name)) {
        this->Hash.insert(make_pair(name, new Record(name, nullptr)));
    } else {
        return;
    }
}

void SymbolTable::removeSymbol(string name) {
    if(this->lookupSymbol(name)) {
        this->Hash.erase(name);
    } else {
        return;
    }
}

void* SymbolTable::getSymbolValue(string name) {
    Record* record = this->Hash.find(name)->second;
    return record->value;
}

bool SymbolTable::lookupSymbol(string name) {
    if(this->Hash.find(name) != this->Hash.end()) {
        return true;
    } else {
        return false;
    }
}

void SymbolTable::printTable() {

    FILE *fp = freopen(symbolTableTxtPath, "w",stdout);
    cout << "name" << "\t" << "value" << endl;
    unordered_map<string, Record*>::iterator it;
    for(it = this->Hash.begin(); it != this->Hash.end(); it++) {
        string name = it->first;
        void* value = it->second;
        cout << name << "\t" << value << endl;
    }
    fflush(fp);
    fclose(fp);
    freopen("CON","w",stdout);
}
