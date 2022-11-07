#include "FSM.h"
#include "util.h"

FSM::FSM(set<set<char>> charList) {
    this->charList = charList;
    this->num = 0;
    FSM_Node* firstNode = new FSM_Node(this->num, TokenCode::UNDIFNIE, false);
    this->nodes.push_back(firstNode);
    this->index.insert({firstNode->id, firstNode});
    this->first = firstNode;
    this->num++;
}

void FSM::addNode(FSM_Node* node) {
    this->nodes.push_back(node);
    this->index.insert({node->id, node});
    this->num++;
}

void FSM::addTrans(int from, int to, set<char> chSet){
    FSM_Node* fromNode = this->index[from];
    FSM_Node* toNode = this->index[to];
    if(fromNode->trans.count(chSet)) {
        fromNode->trans[chSet].push_back(toNode);
    } else {
        vector<FSM_Node*> v;
        v.push_back(toNode);
        fromNode->trans.insert({chSet, v});
    }
}

FSM_Node* FSM::getFisrt() {
    return this->first;
}    

FSM_Node* FSM::getNode(int id){
    if(this->index.count(id) > 0) {
        return this->index[id];
    } else {
        return nullptr;
    }
}

set<set<char>> FSM::getCharList() {
    return this->charList;
}

// 该函数暂时仅用于debug
void FSM::printFSM() {
    cout << this->num << endl;
    cout << "================================================================" << endl;
    for(int i = 0; i < this->num; i++) {
        cout << "num:" << i << endl;
        FSM_Node* node = this->index[i];
        if(node->trans.count(getLetterList('a'))) {
            vector<FSM_Node*> v = node->trans[getLetterList('a')];
            for(FSM_Node* node : v) {
                cout << "字母 -> " << node->id << endl;
            }
        }
        if(node->trans.count(getLetterList('0'))) {
            vector<FSM_Node*> v = node->trans[getLetterList('0')];
            for(FSM_Node* node : v) {
                cout << "数字0 -> " << node->id << endl;
            }
        }
        if(node->trans.count(getLetterList('1'))) {
            vector<FSM_Node*> v = node->trans[getLetterList('1')];
            for(FSM_Node* node : v) {
                cout << "数字1-9 -> " << node->id << endl;
            }
        }
        cout << "================================================================" << endl;
    }
}

FSM createNFA() {
    set<set<char>> charList;
    set<char> letterList = {'_'};
    for (char c = 'a'; c <= 'z'; c++) {
        letterList.insert(c);
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        letterList.insert(c);
    }
    charList.insert(letterList);
    set<char> numList;
    for (char c = '1'; c <= '9'; c++) {
        numList.insert(c);
    }
    charList.insert(numList);
    set<char> zeroList = {'0'};
    charList.insert(zeroList);
    FSM NFA = FSM(charList);

    NFA.addNode(new FSM_Node(1, TokenCode::INT, true));         // 只有一个数字
    NFA.addNode(new FSM_Node(2, TokenCode::UNDIFNIE, false));   // 过渡节点
    NFA.addNode(new FSM_Node(3, TokenCode::INT, true));         // 数字
    NFA.addNode(new FSM_Node(4, TokenCode::IDN, true));         // 只有一个字母
    NFA.addNode(new FSM_Node(5, TokenCode::UNDIFNIE, false));   // 过度节点
    NFA.addNode(new FSM_Node(6, TokenCode::IDN, true));         // 标识符

    NFA.addTrans(0, 1, zeroList);
    NFA.addTrans(0, 1, numList);
    NFA.addTrans(0, 2, numList);
    NFA.addTrans(2, 2, zeroList);
    NFA.addTrans(2, 2, numList);
    NFA.addTrans(2, 3, zeroList);
    NFA.addTrans(2, 3, numList);

    NFA.addTrans(0, 4, letterList);
    NFA.addTrans(0, 5, letterList);
    NFA.addTrans(5, 5, letterList);
    NFA.addTrans(5, 5, zeroList);
    NFA.addTrans(5, 5, numList);
    NFA.addTrans(5, 6, zeroList);
    NFA.addTrans(5, 6, numList);
    NFA.addTrans(5, 6, letterList);
    return NFA;
}

FSM NFAtoDFA(FSM NFA) {
    FSM DFA = FSM(NFA.getCharList());


    return DFA;
}