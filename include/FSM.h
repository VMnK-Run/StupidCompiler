#ifndef __FSM_H__
#define __FSM_H__

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
using namespace std;
/**
 *  标识符: (a..z|A..Z)(1a_)*
 *  常量：(1...9)(0···9)*
*/
struct FSM_Node {
    int id;                                     // 节点编号
    int state;                                  // 当前节点的状态
    /*为了简化代码量，NFA和DFA都只用下面这个转移矩阵，区别在于DFA的vector只存储一个指针*/
    map<set<char>, vector<FSM_Node*>> trans = {}; // 转移矩阵, 根据输入的字符在哪个集合中决定
    bool isEndState;                            // 是否是终态
    FSM_Node(int id, int state, bool isEndState) {
        this->id = id;
        this->state = state;
        this->isEndState = isEndState;
    }
};

class FSM {
private:
    /* data */
    int num;                            // number of nodes
    set<set<char>> charList;            // 当前NFA的有穷字母表, 集合中的每一个元素为一个集合
    vector<FSM_Node*> nodes;            // 当前NFA所有状态节点
    map<int, FSM_Node*> index = {};     // 根据节点编号索引节点
    FSM_Node* first;                    // 起始节点
public:
    FSM() = default;
    ~FSM() = default;
    FSM(set<set<char>> charList);
    void addNode(FSM_Node* node);                       // 添加节点
    void addTrans(int from, int to, set<char> chSet);   // 添加一条转换规则
    FSM_Node* getFisrt();                               // 获取起始节点
    FSM_Node* getNode(int id);                          // 根据节点编号获得节点指针
    int getNum();
    void printFSM();
    set<set<char>> getCharList();
};


FSM createNFA();  // 根据规则创建NFA

FSM createNFA(string re);   // 根据正则表达式创建NFA

FSM NFAtoDFA(FSM NFA);

FSM minimizeDFA(FSM DFA);

int identity(FSM DFA, string token);    // 是否识别

#endif