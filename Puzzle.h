#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<conio.h>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <map>
#include <set>
#include <queue>

#include "constant.h"
#include "util.h"
#include "Img.h"
#define INTVEC vector<int>
using namespace std;


typedef struct Loc
{
	int x, y;
}Loc;
INTVEC up(INTVEC num, Loc loc);
INTVEC down(INTVEC num, Loc loc);
INTVEC left(INTVEC num, Loc loc);
INTVEC right(INTVEC num, Loc loc);
Loc getLoc(INTVEC num);
class Puzzle
{
public:
	INTVEC arr;
	Puzzle(INTVEC num);
	~Puzzle();
	bool available();

	void puzzleMove(char t); 
	void showMat(INTVEC num = {});
	void shuffleShow(); 
	void restart(); 
	void saveImg(Img img); 
	void save(); 
	void load(); 
	void reduction(); 
	bool check();
	void showPossible();
private:
	INTVEC ok;
	INTVEC init;//用于保存最初状态，用于重新开始
	map<string, INTVEC> states;
	void getAll();//获取所有可行方案
	map<INTVEC, string> possible;//第一项是可行方案，第二项是到达路径
	void addPossible(string dir,INTVEC &move,string &basepath, queue<INTVEC> &q);
	/*
	路径定义：改用字符串
	""：完成
	W：上
	S：下
	A：左
	D：右
	*/
};

