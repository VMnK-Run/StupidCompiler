#include "util.h"

void test() {
    std::cout<<"test"<<std::endl;
}

string toLower(string str) {
    string result = str;
    for(unsigned int i = 0; i < str.length(); i++) {
        result[i] = tolower(str[i]);
    }
    return result;
}

bool isAllLetter(string str) {
    for(unsigned int i = 0; i < str.length(); i++) {
        if(!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

void printToken(string token, int code) {
    string result = "";
    result += token;
    result += '\t';
    result += "<";
    switch(code) {
        case TokenCode::KW_INT:
        case TokenCode::KW_VOID:
        case TokenCode::KW_RETURN:
        case TokenCode::KW_CONST:
        case TokenCode::KW_MAIN:
                    result += "KW";
                    break;
        case TokenCode::OP_PLUS:
        case TokenCode::OP_MINUS:
        case TokenCode::OP_MULTIPLY:
        case TokenCode::OP_DIVIDE:
        case TokenCode::OP_PERCENT:
        case TokenCode::OP_EQUAL:
        case TokenCode::OP_GT:
        case TokenCode::OP_LT:
        case TokenCode::OP_ASSIGN:
        case TokenCode::OP_LEQ:
        case TokenCode::OP_GEQ:
        case TokenCode::OP_NEQ:
        case TokenCode::OP_AND:
        case TokenCode::OP_OR:
                    result += "OP";
                    break;

        case TokenCode::SE_LPARENT:
        case TokenCode::SE_RPARENT:
        case TokenCode::SE_LBRACES:
        case TokenCode::SE_RBARCES:
        case TokenCode::SE_SEMICOLON:
        case TokenCode::SE_COMMA:
                    result += "SE";
                    break;
        
        case TokenCode::IDN:
                    result += "IDN";
                    break;
        case TokenCode::INT:
                    result += "INT";
                    break;
        
        case TokenCode::UNDIFNIE:
                    result += "UNDIFNIE";
                    break;
    }
    if(code != TokenCode::IDN && code != TokenCode::INT) {
        result += "," + to_string(code) + ">";
    } else {
        result += "," + token + ">";
    }
    cout << result << endl;
}