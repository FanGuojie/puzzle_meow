#pragma once
#include <vector>
#include<iostream>
#include<string>
using namespace std;
void printNum(vector<int> num); 
void printRule(); 
inline void printseg()
{
	cout << endl;
	cout << "_________________________________" << endl;
}
inline char toCaption(char t) {
	if (t >= 'a' && t <= 'z')
		t = t - 'a' + 'A';
	return t;
}

inline void printDefault(string str) {
	cout << "使用默认参数：" + str << endl;
}