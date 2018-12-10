#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<conio.h>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <unordered_map>
#include "constant.h"
#include "util.h"
#include "Img.h"
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
	void saveImg(Img img); 
	void save(); 
	void load(); 
	void reduction(); 
	bool check();
private:
	vector<int> init;//用于保存最初状态，用于重新开始
	unordered_map<string, vector<int>> states;

};

