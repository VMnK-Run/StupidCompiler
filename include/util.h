#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <string>
#include <set>
#include "TokenCodes.h"
using namespace std;

void test();

string toLower(string str);

bool isAllLetter(string str);

void printToken(string token, int code);

set<char> getLetterList(char ch);

#endif