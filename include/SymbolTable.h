#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

const char symbolTableTxtPath[] = "symbolTable.txt";

struct Record {
    /* data */
    string name;    // 符号名
    void* value;   // 扩展属性指针
    Record(string name, void* value) : name(name), value(value){}
};


class SymbolTable {
private:
    /* data */
    unordered_map<string, Record*> Hash;
public:
    SymbolTable() = default;
    ~SymbolTable() = default;
    void addSymbol(string name);
    void removeSymbol(string name);
    void* getSymbolValue(string name);
    bool lookupSymbol(string name);
    void printTable();
};

#endif