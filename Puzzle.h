#pragma once
#include<vector>
#include<string>
#include<iostream>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include "constant.h"
#include "util.h"
using namespace std;

class Puzzle
{
public:
	vector<int> arr;
	Puzzle(vector<int> num);
	~Puzzle();
	bool available();

	void puzzleMove(char t); 
	void showMat();
	void shuffleShow(); 
	void restart(); 
	void saveImg(); 
	void save(); 
	void load(); 
	void reduction(); 
	bool check();
private:

};

